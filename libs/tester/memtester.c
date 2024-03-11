#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <tester/memtester.h>
#include "tester.h"
#include "tester/logger.h"

// Create a pointer chain with bounds, use tester_ptr_chain_check,
// tester_ptr_chain_free
ptr_chain tester_ptr_chain(unsigned int depth) {
    void*** layers = calloc(depth, sizeof(void*));
    for (int i = 0; i < depth; i++) {
        layers[i] = calloc(3, sizeof(void*));
        if (i != 0)
            layers[i - 1][1] = layers[i][1];
    }
    ptr_chain ret = {
        .len = depth, .varptr = layers[depth - 1] + 1, .layer_ptrs = layers};
    return ret;
}

mem_error tester_ptr_chain_check(ptr_chain chain) {
    int error_count = 0;
    mem_error ret = {0};
    for (int i = 0; i < chain.len; i++) {
        void** curr_layer = chain.layer_ptrs[i];
        tester_log(MSG_ERROR, "sizeof(curr_layer) %zu \n", sizeof(curr_layer));
        tester_log(MSG_ERROR, "sizeof(curr_layer[0]) %zu \n",
                   sizeof(curr_layer[0]));
        tester_log(MSG_ERROR, "%p: curr_layer[0]\n", curr_layer);
        tester_log(MSG_ERROR, "%p: curr_layer[1]\n", curr_layer + 1);
        tester_log(MSG_ERROR, "%p: curr_layer[2]\n", curr_layer + 2);
        for (int j = 0; j < 3; j += 2) {
            if (curr_layer[j] != 0) {
                if (error_count == 0) {
                    ret.has_error = true;
                    ret.layer = i;
                    ret.pos = j;
                } else {
                    ret.multiple = true;
                }
                error_count++;
            }
        }
    }

    // chain.len -1 because the last ptr can point anywhere
    for (int i = 0; i < chain.len - 1; i++) {
        void** curr_layer = chain.layer_ptrs[i];
        if ((curr_layer + 1)[1] != curr_layer[1]) {
            if (error_count == 0) {
                ret.has_error = true;
                ret.layer = i;
                ret.pos = 1;
            } else {
                ret.multiple = true;
            }
            error_count++;
        }
    }
    return ret;
}

void tester_print_mem_error(mem_error e) {
    if (!e.has_error)
        return;
    tester_log_tag(MSG_INFO, "Memory corruption detected!!\n");
    tester_log_tag(MSG_INFO, "Layer: %i, Pos: %i\n", e.layer, e.pos);
    if (e.multiple)
        tester_log_tag(
            MSG_INFO,
            "Warning: Multiple errors detected, only the first one is "
            "shown...\n");
}

void tester_ptr_chain_free(ptr_chain chain) {
    for (int i = 0; i < chain.len; i++) {
        free(chain.layer_ptrs[i]);
    }
    free(chain.layer_ptrs);
}
