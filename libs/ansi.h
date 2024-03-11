#pragma once
#include <stdio.h>

void ansi_reset_terminal(FILE* fp);

void ansi_delete_line(FILE* fp);

void ansi_reset_bold(FILE* fp);

void ansi_set_bold(FILE* fp);

void ansi_set_color(FILE* fp, unsigned char c);
