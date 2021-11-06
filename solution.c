#include <stdio.h>
#include "m1.h"

int
main(void) {
    int c;
    int curr_len = 0, curr_str = 0, max_len = -1, max_ind = 0;
    max_ind = allocate_new_block(1);
    curr_str = allocate_new_block(1);

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (curr_len > max_len) {
                reallocate(max_ind, curr_len);
                for (int i = 0, tmp; i < curr_len; i++) {
                    tmp = read_byte(curr_str, i);
                    write_byte(max_ind, i, tmp);
                }
                max_len = curr_len;
            }
            delete_block(curr_str);
            curr_str = allocate_new_block(1);
            curr_len = 0;
        }
        else {
           reallocate(curr_str, curr_len + 1);
           write_byte(curr_str, curr_len++, c);
        }
    }
    for (int i = 0; i < max_len; i++) {
        printf("%c", read_byte(max_ind, i));
    }
}
