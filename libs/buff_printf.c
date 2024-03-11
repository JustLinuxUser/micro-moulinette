#include <printf.h>
#include <stdio.h>
#include <stdlib.h>
#include "buff.h"

char get_hex_ascii(unsigned int i) {
    if (i <= 9) {
        return '0' + i;
    } else {
        return 'A' + i - 10;
    }
}

int print_buff(FILE* stream,
               const struct printf_info* info,
               const void* const* args) {
    const Buff* b;
    char* buffer;
    int len;

    /* Format the output into a string. */
    b = *((const Buff**)(args[0]));
    len = 0;
    for (int i = 0; i < b->len - 1; i++) {
        if (b->ptr[i] >= 32 && b->ptr[i] != 127) {
            if (b->ptr[i] == '\\')
                len++;
            len++;
        } else {
            len += 4;  // \x1A
        }
    }
    len++;  // to allow for the last \0
    buffer = malloc(len);

    for (int i_out = 0, i_src = 0; i_src < b->len - 1; i_src++) {
        char c = b->ptr[i_src];
        if (c >= 32 && c != 127) {
            buffer[i_out++] = c;
        } else if (c == '\n') {
            buffer[i_out++] = '\\';
            buffer[i_out++] = 'n';
        } else if (c == '\t') {
            buffer[i_out++] = '\\';
            buffer[i_out++] = 't';
        } else if (c == '\r') {
            buffer[i_out++] = '\\';
            buffer[i_out++] = 'r';
        } else if (c == '\\') {
            buffer[i_out++] = '\\';
            buffer[i_out++] = '\\';
        } else {
            buffer[i_out++] = '\\';
            buffer[i_out++] = 'x';
            buffer[i_out++] = get_hex_ascii(c / 16);
            buffer[i_out++] = get_hex_ascii(c % 16);
        }
    }
    buffer[len - 1] = 0;

    /* Pad to the minimum field width and print to the stream. */
    len = fprintf(stream, "%s", buffer);

    /* Clean up and return. */
    free(buffer);
    return len;
}

// int print_widget_arginfo(const struct printf_info* info,
//                          size_t n,
//                          int* argtypes) {
int print_buff_arginfo(const struct printf_info* info,
                       size_t n,
                       int argtypes[n],
                       int size[n]) {
    /* We always take exactly one argument and this is a pointer to the
       structure.. */
    if (n > 0)
        argtypes[0] = PA_POINTER;
    return 1;
}
void register_buff_printf() {
    register_printf_specifier('B', print_buff, print_buff_arginfo);
}
