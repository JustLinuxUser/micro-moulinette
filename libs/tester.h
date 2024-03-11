#pragma once
#include <stdbool.h>
#include "buff.h"

static const int COLOR_INFO = 255;
static const int COLOR_SPECIAL = 226;
static const int COLOR_ERR = 196;
static const int COLOR_SUCC = 82;
static const int COLOR_LABEL = 246;

extern bool tester_no_info;
extern bool tester_no_summary;
extern bool tester_stop_on_error;
extern bool ascii_only;

extern FILE* tester_stdio;

int tester_init(int argc, char** argv);

void tester_end();

int get_stdio_count();

int tester_buffcmp(Buff exp, Buff act);

int tester_start_test(char* fmt, ...);

void tester_end_test(int res, char* fmt, ...);

BuffOwned tester_get_stdio_alloc();
