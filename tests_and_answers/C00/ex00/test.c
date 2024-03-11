#include <limits.h>
#include <stdlib.h>
#include "buff.h"
#include "tester.h"
#include "tester/string_teseter.h"

void ft_putchar(char c);

void run_test(char c) {
    char* desc;
    asprintf(&desc, "ft_putchar(%i))", c);
    if (tester_start_test("%s", desc)) {
        return;  // skipping ...
    }

    ft_putchar(c);

    BuffOwned got = tester_get_stdio_alloc();
    BuffOwned exp = buff_owned_new(&c, 1);

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
    for (int i = CHAR_MIN; i < CHAR_MAX; i++) {
        run_test(i);
    }
    tester_end();
}
