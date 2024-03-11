#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#include "tester.h"
#include "tester/logger.h"

void tester_print_char(char c) {
    if (c >= 32 && c != 127) {
        tester_log_color(MSG_INFO, COLOR_INFO, "%c", c);
    } else {
        tester_log_color(MSG_INFO, COLOR_SPECIAL, "\\x%c%c", c / 16, c % 16);
    }
}

void tester_print_labeled_buff(char* label, Buff s) {
    tester_log_color(MSG_INFO, COLOR_LABEL, "%s: ", label);

    tester_log_color(MSG_INFO, COLOR_SPECIAL, "\"");

    for (int i = 0; i < s.len; i++) {
        tester_print_char(s.ptr[i]);
    }

    tester_log_color(MSG_INFO, COLOR_SPECIAL, "\"");
    fprintf(tester_stdio, "\n");
}

int tester_print_labeled_buff_segment(char* label,
                                      Buff s,
                                      unsigned int start,
                                      unsigned int streak) {
    int printed = 0;
    printed += tester_log_color(MSG_INFO, COLOR_LABEL, "%s: ", label);
    printed += tester_log_color(MSG_INFO, COLOR_LABEL, "CHAR: %i ", start);

    printed += tester_log_color(MSG_INFO, COLOR_SPECIAL, "\"");
    printed += tester_log_color(MSG_INFO, COLOR_SPECIAL, "...");

    for (int i = start; i < s.len && i - start < streak; i++) {
        if (s.ptr[i] >= 32 && s.ptr[i] != 127) {
            tester_log_color(MSG_INFO, COLOR_INFO, "%c", s.ptr[i]);
        } else {
            tester_log_color(MSG_INFO, COLOR_SPECIAL, "\\x%X", s.ptr[i]);
        }
    }

    tester_log_color(MSG_INFO, COLOR_SPECIAL, "...");
    tester_log_color(MSG_INFO, COLOR_SPECIAL, "\"");
    fprintf(tester_stdio, "\n");
    return printed;
}

// returns 1 if buffers are equal, else returns 0;
// prints the buffers

int tester_error_idx(Buff exp, Buff act) {
    int min_len = MIN(act.len, exp.len);
    for (int i = 0; i < min_len - 1; i++) {  // nullptr doesn't count
        if (exp.ptr[i] != act.ptr[i]) {
            return i;
        }
    }
    if (exp.len != act.len) {
        if (exp.len < act.len)
            return exp.len - 1;
        else
            return act.len - 1;
    }
    return -1;
}

int tester_buffcmp_loud(Buff exp, Buff act) {
    int status = tester_buffcmp(exp, act);
    if (status == 0) {
        tester_print_labeled_buff("     TESTING", exp);
    } else {
        tester_print_labeled_buff("     EXPECTED", exp);
        tester_print_labeled_buff("     GOT     ", act);
    }
    return status;
}

int tester_buffcmp_long_line(Buff exp, Buff act) {
    int status = tester_error_idx(exp, act);
    if (status == -1) {
        tester_print_labeled_buff("     TESTING", exp);
    } else {
        int start = MAX(status - 10, 0);
        tester_print_labeled_buff_segment("     EXPECTED", exp, start, 70);
        int offset =
            tester_print_labeled_buff_segment("     GOT     ", act, start, 70);
        for (int i = start; i < status + offset; i++) {
            tester_print_char(' ');
        }
        tester_print_char('^');
        tester_log_color(MSG_INFO, COLOR_ERR, "Error here\n");
    }
    return status;
}
