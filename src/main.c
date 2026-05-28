#include "cw.h"
#include <unistd.h>

static int count_width(uintmax_t n) {
	int w = 1;
	while (n >= 10) { n /= 10; w++ }
	return w;
}

static uintmax_t max5(const Counts *c) {
	uintmax_t m = c->lines;
	if (c->words	> m) m = c->words;
	if (c->bytes	> m) m = c->bytes;
	if (c->chars	> m) m = c->chars;
	if (c->max_line > m) m = c->max_line;
	return m;
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");

	Flags fl = {0};
	int opt;
	while ((opt = getopt(argc, argv, "lwcmL")) != -1) {
		switch (opt) {
			case 'l' : fl.lines	= true; break;
			case 'w' : fl.words	= true; break;
			case 'c' : fl.bytes	= true; fl.chars = false; break;
		        case 'm' : fl.chars	= true; fl.bytes = false; break;
			case 'L' : fl.max_line 	= true; break;
			default:
				   fprintf(stderr, "usage: wc [-lwcmL] [file]\n");
				   return 1;
		}
	}

	int	file_count = argc - optind;
	Counts 	total	   = {0};
	Counts 	c;
	int	status	   = 0;
	int	width	   = 7;

	if (file_count == 0) {
		count_stream(stdin, &c);
		int w = count_width(max5(&c));
		if (w > width) width = w;
		print_counts(&c, &fl, width, NULL);
		return 0;
	}

	Counts *results = calloc(file_count, sizeof(Counts));
	if (!results) { perror("calloc"); return 1; }

	for (int i = 0; i < file_count; i++) {
		FILE *f = fopen(argv[optind + i], "r");
		if (!f) {
			fprintf(stderr, "wc: %s: %s\n", argv[optind + i], strerror(errno));
			status = 1;
			continue;
		}
		count_stream(f, &results[i]);
		fclose(f);

		total.lines	+= results[i].lines;
		total.words	+= results[i].words;
		total.bytes	+= results[i].bytes;
		total.chars	+= results[i].chars;
		if (results[i].max_line > total.max_line)
			total.max_line = results[i].max_line;

		int w = count_width(max5(&results[i]));
		if (w > width) width = w;
	}

	if (file_count > 1) {
		int w = count_width(max5(&total));
		if (w > width) width = w;
	}

	for (int i = 0; i < file_count; i++)
		print_counts(&results[i], &fl, width, argv[optind + i]);

	if (file_count > 1)
		print_counts(&total, &fl, width, "total");

	free(results);
	return status;
}
