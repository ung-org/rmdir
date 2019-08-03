/*
 * UNG's Not GNU
 * 
 * Copyright (c) 2011, Jakob Kaivo <jakob@kaivo.net>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>

const char *rmdir_desc = "remove directories";
const char *rmdir_inv = "rmdir [-p] dir...";

int main(int argc, char **argv)
{
	int c;
	int prune = 0;
	int retval = 0;

	while ((c = getopt(argc, argv, ":p")) != -1) {
		switch (c) {
		case 'p':
			prune = 1;
			break;
		default:
			return 1;
		}
	}

	if (optind >= argc)
		return 1;

	while (optind < argc) {
		if (prune) {
			char *working = argv[optind];
			while (strcmp(working, ".") && strcmp(working, "/")) {
				retval = rmdir(working);
				working = dirname(working);
			}
		} else {
			retval = rmdir(argv[optind]);
		}
		optind++;
	}

	return retval;
}
