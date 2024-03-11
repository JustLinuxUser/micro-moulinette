#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tester.h>

void ansi_set_color(FILE* fp, unsigned char c) {
    if (!ascii_only)
        fprintf(fp, "\x1B[38;5;%im", c);
}

void ansi_set_bold(FILE* fp) {
    if (!ascii_only)
        fprintf(fp, "\x1B[1m");
}

void ansi_reset_bold(FILE* fp) {
    if (!ascii_only)
        fprintf(fp, "\x1B[22m");
}

void ansi_delete_line(FILE* fp) {
    if (!ascii_only)
        fprintf(fp, "\r\x1B[0J");
    else
        fprintf(fp, "\n");
}

void ansi_reset_terminal(FILE* fp) {
    if (!ascii_only) {
        fprintf(fp, "\x1B[0m");   // reset color
        fprintf(fp, "\x1B[22m");  // reset bold mode.
        fprintf(fp, "\x1B[22m");  // reset dim/faint mode.
        fprintf(fp, "\x1B[23m");  // reset italic mode.
        fprintf(fp, "\x1B[24m");  // reset underline mode.
        fprintf(fp, "\x1B[25m");  // reset blinking mode
        fprintf(fp, "\x1B[27m");  // reset inverse/reverse mode
        fprintf(fp, "\x1B[28m");  // reset hidden/invisible mode
        fprintf(fp, "\x1B[29m");  // reset strikethrough mode.
    }
    fflush(fp);
}
