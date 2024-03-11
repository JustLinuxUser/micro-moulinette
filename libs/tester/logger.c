#include "tester/logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <tester.h>
#include "ansi.h"

int MSG_TYPE_COLOR[] = {
    COLOR_ERR, COLOR_INFO, COLOR_SUCC, COLOR_ERR, COLOR_INFO,
};

size_t tester_vlog(int type, char* fmt, va_list args) {
    return vfprintf(tester_stdio, fmt, args);
}

size_t tester_log(int type, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t printed = tester_vlog(type, fmt, args);
    va_end(args);
    return printed;
}

size_t tester_vlog_tag(int type, char* fmt, va_list args) {
    ansi_set_color(tester_stdio, MSG_TYPE_COLOR[type]);
    size_t printed = 0;
    if (type == MSG_INFO) {
        printed += tester_log(type, "INFO: ");
    } else if (type == MSG_ERROR) {
        printed += tester_log(type, "ERR: ");
    } else if (type == MSG_TEST_FAIL) {
        printed += tester_log(type, "FAIL: ");
    } else if (type == MSG_TEST_SUCC) {
        printed += tester_log(type, "SUCC: ");
    } else if (type == MSG_TEST_PROGRESS) {
        printed += tester_log(type, "RUNNING: ");
    }

    printed += tester_vlog(type, fmt, args);
    ansi_reset_terminal(tester_stdio);
}

size_t tester_log_tag(int type, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t printed = tester_vlog_tag(type, fmt, args);
    va_end(args);
    return printed;
}

size_t tester_vlog_color(int type, int color, char* fmt, va_list args) {
    ansi_set_color(tester_stdio, color);

    size_t printed = tester_vlog(type, fmt, args);

    ansi_reset_terminal(tester_stdio);
    return printed;
}

size_t tester_log_color(int type, int color, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t printed = tester_vlog_color(type, color, fmt, args);
    va_end(args);
    return printed;
}
