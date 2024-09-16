#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
} BitReader;

BitReader *bit_read_open(const char *filename) {
    BitReader *bitr = calloc(1, sizeof(BitReader));
    FILE *f = fopen(filename, "rb");
    if (bitr == NULL || f == NULL) {
        return NULL;
    }
    bitr->underlying_stream = f;
    bitr->byte = 0;
    bitr->bit_position = 8;
    return bitr;
}
void bit_read_close(BitReader **pbuf) {
    if ((*pbuf) != NULL) {
        if ((fclose((*pbuf)->underlying_stream)) != 0) {
            fprintf(stderr, "You got a file closing issue.");
            return; //might have to remove this to not get a dumb error
        }
        free(*pbuf);
        (*pbuf) = NULL;
    }
}
uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int byte = fgetc(buf->underlying_stream);
        if (byte == EOF) {
            fprintf(stderr, "You have a bit reading error: EOF");
            return (uint8_t) EOF; //if youre having valgrind issues check here first
        }
        buf->byte = (uint8_t) byte;
        buf->bit_position = 0;
    }
    uint8_t mask = (uint8_t) (1 << (buf->bit_position));
    mask &= buf->byte;
    mask >>= (buf->bit_position);
    buf->bit_position += 1;
    return mask;
}
uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (uint8_t i = 0; i < 32; i++) {
        uint32_t b = (uint32_t) bit_read_bit(buf);
        word |= b << i;
    }
    return word;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (uint8_t i = 0; i < 16; i++) {
        uint8_t b = bit_read_bit(buf);
        word |= (uint16_t) b << i;
    }
    return word;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t b = bit_read_bit(buf);
        byte |= b << i;
    }
    return byte;
}
