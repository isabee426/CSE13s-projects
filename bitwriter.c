#include "bitwriter.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
} BitWriter;

BitWriter *bit_write_open(const char *filename) {
    BitWriter *bitw = calloc(1, sizeof(BitWriter));
    FILE *f = fopen(filename, "wb");
    if (bitw == NULL || f == NULL) {
        return NULL;
    }
    bitw->underlying_stream = f;
    bitw->bit_position = 0;
    bitw->byte = 0;
    return bitw;
}
void bit_write_close(BitWriter **pbuf) {
    if ((*pbuf) != NULL) {
        if ((*pbuf)->bit_position > 0) {
            if ((fputc((*pbuf)->byte, (*pbuf)->underlying_stream)) == EOF) {
                fprintf(stderr, "bit write error: closing");
                return; //close?
            }
        }
        if (fclose((*pbuf)->underlying_stream) == EOF) {
            fprintf(stderr, "bit write error: file cant close");
            return;
        } //check 4 error
        free(*pbuf);
        (*pbuf) = NULL;
    }
}
void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        int result = fputc((buf)->byte, (buf)->underlying_stream);
        if (result == EOF) {
            fprintf(stderr, "bit write error");
            return;
        }
        buf->byte = 0;
        buf->bit_position = 0;
    }
    bit = (uint8_t) (bit << buf->bit_position);
    buf->byte |= bit;
    buf->bit_position += 1;
}
void bit_write_uint8(BitWriter *buf, uint8_t x) {
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t mask = (uint8_t) (1 << i);
        mask &= x;
        mask >>= i;
        bit_write_bit(buf, mask);
    }
}
void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (uint16_t i = 0; i < 16; i++) {
        uint16_t mask = (uint16_t) (1 << i);
        mask &= x;
        mask >>= i;
        bit_write_bit(buf, (uint8_t) mask);
    }
}
void bit_write_uint32(BitWriter *buf, uint32_t byte) {
    for (uint32_t i = 0; i < 32; i++) {
        uint32_t mask = (uint32_t) (1 << i);
        mask &= byte;
        mask >>= i;
        bit_write_bit(buf, (uint8_t) mask);
    }
}
