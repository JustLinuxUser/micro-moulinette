#pragma once
#include <stdarg.h>
#include <stdlib.h>

enum MSG_TYPE {
    MSG_ERROR,
    MSG_INFO,
    MSG_TEST_SUCC,
    MSG_TEST_FAIL,
    MSG_TEST_PROGRESS,
};

extern int MSG_TYPE_COLOR[];

size_t tester_vlog(int type, char* fmt, va_list args);

size_t tester_log(int type, char* fmt, ...);

size_t tester_vlog_tag(int type, char* fmt, va_list args);

size_t tester_log_tag(int type, char* fmt, ...);

size_t tester_vlog_color(int type, int color, char* fmt, va_list args);

size_t tester_log_color(int type, int color, char* fmt, ...);
