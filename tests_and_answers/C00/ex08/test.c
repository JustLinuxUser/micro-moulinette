#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buff.h"
#include "tester.h"
#include "tester/logger.h"
#include "tester/string_teseter.h"

void ft_print_combn(int n);

void correct_rec(int* arr, int n, int pos) {
    int iters = 11 - n + pos - arr[pos];
    // 1 [0-9]
    // 2 [0-8, 1-9]
    // 3 [0-7, 1-8, 2-9]
    for (int i = 0; i < iters; i++) {
        if (pos < n - 1) {
            arr[pos + 1] = arr[pos] + 1;
            correct_rec(arr, n, pos + 1);
        } else {
            bool final = true;
            for (int j = 0; j < n; j++) {
                printf("%i", arr[j]);
                // final 1: 9
                // final 2: 8, 9
                // final 2: 7, 8, 9
                if (arr[j] != 10 - n + j) {
                    final = false;
                }
            }
            if (!final) {
                printf(", ");
            }
        }
        arr[pos]++;
    }
}

void correct(int n) {
    int arr[9];
    arr[0] = 0;
    if (n < 1 || n > 9) {
        return;
    }
    correct_rec(arr, n, 0);
}

void run_test(int n) {
    char* desc;
    asprintf(&desc, "ft_print_combn(%i)", n);

    if (tester_start_test("%s", desc)) {
        return;  // skipping ...
    }

    ft_print_combn(n);
    BuffOwned got = tester_get_stdio_alloc();
    correct(n);
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
    run_test(0);
    run_test(1);
    run_test(2);
    run_test(3);
    run_test(4);
    run_test(5);
    run_test(6);
    run_test(7);
    run_test(8);
    run_test(9);
    run_test(10);
    run_test(-1);
    run_test(INT_MAX);
    run_test(INT_MIN);
    tester_end();
}
