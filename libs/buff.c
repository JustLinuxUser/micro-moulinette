#include "buff.h"
#include <printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates a Buff, given BuffOwned
Buff ref(BuffOwned buff) {
    return (Buff){.ptr = buff.ptr, .len = buff.len};
}

// Convert a C literal to Buff
Buff buff_new(char* const str) {
    return (Buff){.ptr = str, .len = strlen(str)};
}

BuffOwned buff_to_owned(Buff b) {
    BuffOwned ret = {0};
    ret.ptr = malloc(b.len);
    ret.len = b.len;
    ret.capacity = b.len;
    for (int i = 0; i < b.len; i++) {
        ret.ptr[i] = b.ptr[i];  // Copy the last \0 too
    }
    return ret;
}

// Create a new owned buff from cstr, copies memory
BuffOwned buff_owned_new(char* str, size_t len) {
    BuffOwned ret = {0};
    ret.ptr = malloc(len + 1);
    ret.len = len + 1;
    ret.capacity = len + 1;
    for (int i = 0; i < len; i++) {
        ret.ptr[i] = str[i];
    }
    ret.ptr[len] = 0;
    return ret;
}

// Free memory in BuffOwned, replace the ptr with NULL, len with 0
void buff_free(BuffOwned* buff) {
    free(buff->ptr);
    memset(buff, 0, sizeof(BuffOwned));
}
