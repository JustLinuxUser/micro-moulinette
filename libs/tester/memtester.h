#include <stdbool.h>
#include <stdint.h>
typedef struct {
    int len;
    void* varptr;
    void*** layer_ptrs;
} ptr_chain;

typedef struct mem_error {
    bool has_error;  // has error = true if true, false if false :)
    uint8_t layer;   // layer = idx of a layer with the first error pos
    uint8_t pos;     // pos = idx of the first error pos inside the layer
    bool multiple;   // multiple = check if there were multiple errors
} mem_error;

// Create a pointer chain with bounds, use tester_ptr_chain_check,
// tester_ptr_chain_free
ptr_chain tester_ptr_chain(unsigned int depth);

mem_error tester_ptr_chain_check(ptr_chain chain);

// Print the errors of tester_ptr_chain_check, prints nothing if no error is
// found
void tester_print_mem_error(mem_error e);

void tester_ptr_chain_free(ptr_chain chain);
