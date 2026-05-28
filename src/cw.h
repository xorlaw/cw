#define _POSIX_C_SOURCE 200809L
#ifndef WC_H
#define WC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <errno.h>
#include <limits.h>

typedef struct {
	uintmax_t lines;
	uintmax_t words;
	uintmax_t bytes;
	uintmax_t chars;
	uintmax_t max_line;
} Counts;

typedef struct {
	bool lines;
	bool words;
	bool bytes;
	bool chars;
	bool max_line;
} Flags;

void count_stream(FILE *f, Counts *c);
void print_counts(const Counts *c, const Flags *fl, int width, const char *label);

#endif
