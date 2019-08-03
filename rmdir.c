/*
 * UNG's Not GNU
 *
 * Copyright (c) 2011-2019, Jakob Kaivo <jkk@ung.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _XOPEN_SOURCE 500
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int prune = 0;

	int c;
	while ((c = getopt(argc, argv, "p")) != -1) {
		switch (c) {
		case 'p':
			prune = 1;
			break;

		default:
			return 1;
		}
	}

	if (optind >= argc) {
		return 1;
	}

	int retval = 0;
	do {
		if (prune) {
			char *working = argv[optind];
			while (strcmp(working, ".") && strcmp(working, "/")) {
				if (rmdir(working) != 0) {
					fprintf(stderr, "rmdir: %s: %s\n",
						working, strerror(errno));
					retval = 1;
					break;
				}
				working = dirname(working);
			}

		} else if (rmdir(argv[optind]) != 0) {
			fprintf(stderr, "rmdir: %s: %s\n", argv[optind],
				strerror(errno));
			retval = 1;
		}
	} while (++optind < argc);

	return retval;
}
