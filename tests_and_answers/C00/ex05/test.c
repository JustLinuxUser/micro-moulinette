#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buff.h"
#include "tester.h"
#include "tester/string_teseter.h"

void ft_print_comb();

void correct() {
    for (int a = 0; a <= 7; a++) {
        for (int b = a + 1; b <= 8; b++) {
            for (int c = b + 1; c <= 9; c++) {
                printf("%i%i%i", a, b, c);
                if (a != 7 || b != 8 || c != 9) {
                    printf(", ");
                }
            }
        }
    }
}

void run_test() {
    char* desc;
    asprintf(&desc, "ft_print_comb()");

    if (tester_start_test("%s", desc)) {
        return;  // skipping ...
    }

    ft_print_comb();
    BuffOwned got = tester_get_stdio_alloc();
    correct();
    BuffOwned exp = tester_get_stdio_alloc();

    int status = tester_buffcmp(ref(exp), ref(got));
    tester_end_test(status, "%s", desc);

    if (status != 0) {
        tester_buffcmp_long_line(ref(exp), ref(got));
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
