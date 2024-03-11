#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buff.h"
#include "tester.h"
#include "tester/string_teseter.h"

void ft_putnbr(int n);

void correct(int n) {
    printf("%i", n);
}

void run_test(int n, char* act) {
    char* desc;
    asprintf(&desc, "ft_putnbr(%i) // %s", n, act);

    if (tester_start_test("%s", desc)) {
        return;  // skipping ...
    }

    ft_putnbr(n);
    BuffOwned got = tester_get_stdio_alloc();
    correct(n);
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
    run_test(0, "check zero");
    run_test(8, "regular number");
    run_test(1, "regular number");
    run_test(42, "regular number");
    run_test(-1, "regular negative number");
    run_test(-123, "regular negative number");
    run_test(-42, "regular negative number");
    run_test(INT_MIN, "smallest number possible");
    run_test(INT_MAX, "largest number possible");
    tester_end();
}
