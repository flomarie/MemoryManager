#include <stdio.h>
#include <stdlib.h>
#include "m1.h"

enum {BLOCK_NUM = 2000, MEM_SIZE = 1000000};

static char memory[MEM_SIZE];//memory
static int blocks[BLOCK_NUM];//index of the beggining of th block
static int sizes[BLOCK_NUM];//sizes of blocks
static int cnt_blocks = 0;
static int begin = 0;
static int is_deleted[BLOCK_NUM];

int allocate_new_block(int size) {
    cnt_blocks++;
    sizes[cnt_blocks] = size;
    blocks[cnt_blocks] = begin;
    begin += size;
    return cnt_blocks;
}

void delete_block(int desc) {
    if (desc > cnt_blocks || is_deleted[desc]) {
        printf("Non-existent block descriptor");
        exit(1);
    }
    for (int i = desc; i <= cnt_blocks; i++) {
        if (is_deleted == 0) {
            for (int j = 0; j <  sizes[i]; j++) {
                memory[blocks[i] + j - sizes[desc]] = memory[blocks[i] + j];
            }
            blocks[i] -= sizes[desc];
        }
    }
    begin -= sizes[desc];
    cnt_blocks--;
}

unsigned char read_byte(int desc, int  offset) {
    if (desc > cnt_blocks || is_deleted[desc] || offset > sizes[desc]) {
        printf("Unable to read byte");
        exit(1);
    }
    return memory[blocks[desc] + offset];
}

void write_byte(int desc, int offset, unsigned char value) {
    if (desc > cnt_blocks || is_deleted[desc] || offset > sizes[desc]) {
        printf("Unable to write byte");
        exit(1);
    }
    memory[blocks[desc] + offset] = value;
}

int reallocate(int desc, int new_size) {
    if (is_deleted[desc] || desc > cnt_blocks) {
        printf("Unable to reallocate");
        return 1;
    }
    if (new_size <= sizes[desc]) {
        int delta = sizes[desc] - new_size;
        for (int i = desc; i <= cnt_blocks; i++) {
            if (is_deleted == 0) {
                for (int j = 0; j < sizes[i]; j++) {
                    memory[blocks[i] + j - delta] = memory[blocks[i] + j];
                }
                 blocks[i] -= delta;
            }
        }
        sizes[desc] = new_size;
        begin -= delta;
        return 0;
    }
    if (new_size > sizes[desc]) {
       int delta = new_size - sizes[desc];
       for (int i = cnt_blocks; i > desc; i--) {
           if (is_deleted == 0) {
               for (int j = sizes[i] - 1; j >= 0; j--) {
                   memory[blocks[i] + j + delta] = memory[blocks[i] + j];
               }
               blocks[i] += delta;
           }
       }
       sizes[desc] = new_size;
       begin += delta;
       return 0;
    }
    
}
