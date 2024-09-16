//written by Isabella Shapland

#include "bitreader.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    Node *stack[64] = { 0 };
    int stack_top = 0;
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);
    assert(type1 == 'H');
    assert(type2 == 'C');
    Node *node;
    uint16_t num_nodes = (uint16_t) (2 * num_leaves - 1);
    for (int i = 0; i < num_nodes; i++) {
        uint8_t bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[stack_top];
            stack_top--;
            node->left = stack[stack_top];
            stack_top--;
        }
        stack_top++;
        stack[stack_top] = node;
    }
    Node *code_tree = stack[stack_top];
    stack_top--;
    for (uint32_t i = 0; i < filesize; i++) {
        Node *currnode = code_tree;
        while (1) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit == 0) {
                currnode = currnode->left;
            } else {
                currnode = currnode->right;
            }
            if (currnode->right == NULL && currnode->left == NULL) {
                break;
            }
        }
        fputc(currnode->symbol, fout);
    }
    node_free(&code_tree);
}

int main(int argc, char **argv) {
    bool h = false;
    //bool error = false;
    int option = 0;
    char *output = NULL;
    char *input = NULL;

    while ((option = getopt(argc, argv, "hi:o:")) != -1) {
        switch (option) {
        case 'i': {
            if (optarg != NULL) {
                input = optarg;
                break;
            } else {
                fprintf(stderr, "dehuff:  unknown or poorly formatted option -i\n");
                return 1;
            }
        }
        case 'h': {
            h = true;
            break;
        }

        case 'o': {
            if (optarg != NULL) {
                output = optarg;
                break;

            } else {
                fprintf(stderr, "dehuff:  unknown or poorly formatted option -o\n");
                return 1;
            }
            break;
        }

        case '?': {
            fprintf(stderr, "dehuff:  unknown or poorly formatted option -%c'\n", optopt);
            return 1;
        }
        }
    }
    if (input == NULL) {
        fprintf(stderr, "dehuff:  -i option is required\n");
        h = true;

    } else if (output == NULL) {
        fprintf(stderr, "dehuff:  -o option is required\n");
        h = true;
    }
    if (h) {
        printf("Usage: dehuff -i infile -o outfile\n");
        printf("       dehuff -h");
        return 0;
    }
    BitReader *br = bit_read_open(input);
    if (br == NULL) {
        return 1;
    }
    FILE *outfile = fopen(output, "wb");
    dehuff_decompress_file(outfile, br);
    bit_read_close(&br);
    fclose(outfile);
    return 0;
}
