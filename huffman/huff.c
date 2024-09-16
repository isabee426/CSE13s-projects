//written by Isabella Shapland

#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    //create char and filesize variables
    int ch = 0;
    uint32_t filesize = 0;
    //repopulate it w null values so the tree is never empty
    ++histogram[0x00];
    ++histogram[0xff];
    //get and count every char
    while ((ch = fgetc(fin)) != EOF) { //might need to be char type?
        ++histogram[ch];
        ++filesize;
    }
    //fprintf(stderr, "filesize = %u",filesize);
    //return total number of chars
    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();
    for (int i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            //fprintf(stderr, "histogram %d = %u\n", i, histogram[i]);
            Node *new = node_create((uint8_t) i, histogram[i]); //free this
            (*num_leaves)++;
            enqueue(pq, new);
        }
    }
    //fprintf(stderr, "numleaves = %u", *num_leaves);
    while (!(pq_is_empty(pq)) && !(pq_size_is_1(pq))) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *new = node_create(0, (left->weight + right->weight));
        new->left = left;
        new->right = right;
        enqueue(pq, new);
    }
    Node *node = dequeue(pq);
    pq_free(&pq);
    return node;
}

void fill_code_table(Code *code_table, Node *n, uint64_t c, uint8_t cl) {
    if (n->left != NULL && n->right != NULL) {
        fill_code_table(code_table, n->left, c, cl + 1);
        c |= (uint64_t) 1 << cl;
        fill_code_table(code_table, n->right, c, cl + 1);
    } else {
        code_table[n->symbol].code = c;
        code_table[n->symbol].code_length = cl;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        bit_write_bit(outbuf, (uint8_t) 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, (uint8_t) 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);
    while (1) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}

int main(int argc, char **argv) {
    uint32_t histogram[256] = { 0 };
    bool h = false;
    //bool error = false;
    int option = 0;
    FILE *input = stdin;
    char *output = NULL;

    while ((option = getopt(argc, argv, "hi:o:")) != -1) {
        switch (option) {
        case 'i': {
            if (optarg != NULL) {
                input = fopen(optarg, "rb");
                if (input == NULL) {
                    fprintf(stderr, "huff:  error reading input file %s\n", optarg);
                    return 1;
                }
            } else {
                fprintf(stderr, "huff:  unknown or poorly formatted option -%c'\n", optopt);
                return 1;
            }
            break;
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
                fprintf(stderr, "huff:  unknown or poorly formatted option -%c'\n", optopt);
                return 1;
            }
        case '?': {
            fprintf(stderr, "huff:  unknown or poorly formatted option -%c'\n", optopt);
            return 1;
        }
        }
        }
    }

    if (input == stdin) {
        fprintf(stderr, "huff:  -i option is required\n");
        h = true;

    } else if (output == NULL) {
        fprintf(stderr, "huff:  -o option is required\n");
        h = true;
    }
    if (h) {
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -h");
        return 0;
    }
    Code *code_table = (Code *) malloc(256 * sizeof(Code));
    BitWriter *bw = bit_write_open(output);
    if (bw == NULL) {
        fclose(input);
        free(code_table);
        return 1;
    }
    uint32_t filesize = fill_histogram(input, histogram);
    uint16_t num_leaves = 0;
    Node *tree = create_tree(histogram, &num_leaves);
    //FILE *outfile = fopen(output, "wb");
    if (tree == NULL) {
        fclose(input);
        free(code_table);
        bit_write_close(&bw);
        return 1;
    }
    //node_print_tree(tree);

    fill_code_table(code_table, tree, 0, 0);
    if (fseek(input, 0, SEEK_SET) != 0) {
        fclose(input);
        bit_write_close(&bw);
        node_free(&tree);
        free(code_table);
        return 1;
    }
    huff_compress_file(bw, input, filesize, num_leaves, tree, code_table);
    fclose(input);
    bit_write_close(&bw);
    node_free(&tree);
    free(code_table);
    return 0;
}
