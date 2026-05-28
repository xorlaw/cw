#include "cw.h"

void count_stream(FILE *f, Counts *c) {
	memset(c, 0, sizeof(*c));

	bool in_word = false;
	uintmax_t line_len = 0;
	int ch;
	char mb_buf[MB_LEN_MAX];
	int mb_len = 0;

	while ((ch = getc_unlocked(f)) != EOF) {
			c->bytes++

			mb_buf[mb_len++] = (char)ch;
			wchart wc;
			int r = mbtowc(&wc, mb_buf, mb_len);
			if (r == -1) {
				if (mb_len < MB_LEN_MAX) continue;

				mbtowc(NULL, NULL, 0);
				mb_len = 0;
			} else {
				mb_len = 0;
				c->chars++;
			}

			if (ch == '\n') {
				c->lines++;
				if (line_len > c->max_line) c->max_line = line_len;
				line_len = 0;
				in_word = false;
			} else {
				line_len++;
			}

			bool is_space = (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\f' || ch == '\v');
			if (is_space) {
				in_word = false;
			} else if (!in_word) {
				in_word = true;
				c->words++;
			}
	}

	if (line_len > c->max_line) c->max_line = line_len;
}
