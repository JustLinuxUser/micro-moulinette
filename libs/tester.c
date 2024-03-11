#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "ansi.h"
#include "buff.h"
#include "buff_printf.h"
#include "tester.h"
#include "tester/logger.h"

FILE* tester_stdio;
int tester_oldstdio[2];

int test_idx = -1;
unsigned int tests_passed = 0;
unsigned int tests_failed = 0;
unsigned int tests_skipped = 0;
char* test_desc = 0;

// cmd flags
int tester_only_run = -1;
bool tester_no_info = false;
bool tester_no_summary = false;
bool tester_stop_on_error = false;
bool ascii_only = false;

int get_stdio_count() {
    fflush(stdout);  // If some dummy used printf :)

    int count;
    ioctl(tester_oldstdio[0], FIONREAD, &count);
    return count;
}

// returns 1 if buffers are equal, else returns 0;
int tester_buffcmp(Buff exp, Buff act) {
    if (exp.len != act.len) {
        return 1;
    }
    for (int i = 0; i < act.len - 1; i++) {  // nullptr doesn't count
        if (exp.ptr[i] != act.ptr[i]) {
            return 1;
        }
    }
    return 0;
}

// Starts a test, but leaves the cursor on the same line
int tester_start_test(char* fmt, ...) {
    test_idx++;
    if (test_idx != tester_only_run && tester_only_run != -1) {
        tests_skipped++;
        return 1;
    }
    tester_log_tag(MSG_TEST_PROGRESS, "test %i: ", test_idx);

    va_list args;
    va_start(args, fmt);
    // ansi_set_color(tester_stdio, COLOR_INFO);
    // vfprintf(tester_stdio, fmt, args);
    tester_vlog_color(MSG_TEST_PROGRESS, COLOR_INFO, fmt, args);
    va_end(args);
    return 0;
}

void tester_end() {
    if (tester_no_summary)
        return;
    fprintf(tester_stdio, "\n\n-------------\n");
    fprintf(tester_stdio, "total: %i\n", test_idx + 1);
    fprintf(tester_stdio, "tests_skipped: %i\n", tests_skipped);
    fprintf(tester_stdio, "tests_failed: %i\n", tests_failed);
    fprintf(tester_stdio, "tests_passed: %i\n", tests_passed);
    fclose(tester_stdio);
}

// Ends a test, goes to the new line, ment to be used with start_test
void tester_end_test(int res, char* fmt, ...) {
    ansi_delete_line(tester_stdio);
    if (res == 0) {
        tester_log_tag(MSG_TEST_SUCC, "test %i: ", test_idx);
        tests_passed++;
    } else {
        tester_log_tag(MSG_TEST_FAIL, "test %i: ", test_idx);
        if (tester_stop_on_error)
            tester_only_run = test_idx;
        tests_failed++;
    }
    va_list args;
    va_start(args, fmt);
    ansi_set_color(tester_stdio, COLOR_INFO);
    vfprintf(tester_stdio, fmt, args);
    va_end(args);
    tester_log_color(MSG_TEST_PROGRESS, 0, "\n");
}

// Allocates and returns a BuffOwned, if stdio is empty, returns
// (BuffOwned){.len=0, .ptr=0}
BuffOwned tester_get_stdio_alloc() {
    size_t len = get_stdio_count();
    char* ptr = malloc(len + 1);
    read(tester_oldstdio[0], ptr, len);
    ptr[len] = 0;
    return (BuffOwned){.len = len + 1, .ptr = ptr};
}

int parce_args(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        char* eq = strchr(argv[i], '=');
        if (eq == 0) {
            tester_log_tag(MSG_ERROR, "failded to parce the input opts!!!\n");
            exit(2);
        }
        int key_len = eq - argv[i] + 1;
        char* key = malloc(key_len);
        strlcpy(key, argv[i], key_len);

        int val_len = strlen(argv[i]) - key_len + 1;
        char* val = malloc(val_len);
        strlcpy(val, argv[i] + key_len, val_len);

        if (strcmp("only_run", key) == 0) {
            tester_only_run = atoi(val);
        } else if (strcmp("no_info", key) == 0) {
            tester_no_info = atoi(val);
        } else if (strcmp("no_summary", key) == 0) {
            tester_no_summary = atoi(val);
        } else if (strcmp("stop_on_error", key) == 0) {
            tester_stop_on_error = atoi(val);
        } else if (strcmp("ascii_only", key) == 0) {
            ascii_only = atoi(val);
        } else {
            tester_log_tag(MSG_ERROR, "Unknown key <%s>\n", key);
            exit(3);
        }

        free(key);
        free(val);
    }
    return 0;
}

int tester_init(int argc, char** argv) {
    pipe(tester_oldstdio);
    tester_stdio = fdopen(
        dup(1), "w");  // creating a duplicate of actuall stdio to use later
    dup2(tester_oldstdio[1],
         1);  // replacing regular stdio with our pipe, to read what the
              // process/function is printing
    register_buff_printf();
    parce_args(argc, argv);
    return 0;
}
