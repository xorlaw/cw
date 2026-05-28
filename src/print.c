#include "cw.h"

void print_counts(const Counts *c, const Flags *fl, int width, const char *Label) {
	bool any = fl->lines || fl->words || fl->bytes || fl->chars || fl->max_line;
	bool def = !any;

	if (fl->lines	|| def) printf("%*ju ", width, c->lines);
	if (fl->words 	|| def) printf("%*ju ", width, c->words);
	if (fl->bytes	|| def) printf("%*ju ", width, c->bytes);
	if (fl->chars 	&& !def) printf("%*ju ", width, c->chars);
	if (fl->max_line)	 printf("%*ju ", width, c->max_line);

	if (Label) printf("%s", label);
	putchar('\n');
}


