#pragma once
#include <stdio.h>
// A view into memory, like str in rust
typedef struct {
    char* ptr;  // const ptr to const char
    size_t len;
} Buff;

// An owned slice of memory
typedef struct {
    char* ptr;  // const ptr to char
    size_t len;
    size_t capacity;
} BuffOwned;

Buff ref(BuffOwned buff);

Buff buff_new(char* const str);

BuffOwned buff_to_owned(Buff b);

BuffOwned buff_owned_new(char* str, size_t len);

void buff_free(BuffOwned* buff);
