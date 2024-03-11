#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buff.h"
#include "tester.h"
#include "tester/string_teseter.h"

void ft_print_reverse_alphabet(void);

void ft_print_reverse_alphabet_correct(void) {
    char c;

    c = 'z';
    while (c >= 'a') {
        write(1, &c, 1);
        c--;
    }
}

void run_test() {
    char* desc;
    asprintf(&desc, "ft_print_reverse_alphabet()");

    if (tester_start_test("%s", desc)) {
        return;  // skipping ...
    }

    ft_print_reverse_alphabet();
    BuffOwned got = tester_get_stdio_alloc();
    ft_print_reverse_alphabet_correct();
    BuffOwned exp = tester_get_stdio_alloc();

    int status = tester_buffcmp(ref(exp), ref(got));
    tester_end_test(status, "%s", desc);

    if (status != 0) {
        tester_buffcmp_loud(ref(exp), ref(got));
    }
    buff_free(&got);
    buff_free(&exp);
    free(desc);
}

int main(int argc, char** argv) {
    tester_init(argc, argv);
    run_test();
    tester_end();
}
