#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "rhash.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#endif

int main(int argc, char const *argv[])
{
	unsigned char *digest = (unsigned char *) malloc(64 * sizeof(unsigned char));
	char output[130];

	rhash_library_init();

	const char *delim = " ";

#ifndef USE_READLINE
	size_t linesize = 100;
	char *line = (char *) malloc(linesize * sizeof(char));

	while (getline(&line, &linesize, stdin) != -1) {
#else
	char *line;
	while ((line = readline("Enter line: ")) != NULL) {
#endif
		line[strcspn(line, "\n")] = 0;
		char *arg1 = strtok(line, delim);
		char *arg2 = strtok(NULL, delim);

		int FLAGS = 0;
		if (isupper(arg1[0])) {
			FLAGS |= RHPR_HEX;
		} else {
			FLAGS |= RHPR_BASE64;
		}

		int code = 0;
		if (strcasecmp(arg1, "md5") == 0)
			code = RHASH_MD5;
		else if (strcasecmp(arg1, "sha1") == 0)
			code = RHASH_SHA1;
		else if (strcasecmp(arg1, "tth") == 0)
			code = RHASH_TTH;
		else {
			fprintf(stderr, "%s\n", "Error. Please enter valid hash type: MD5, SHA1, TTH.");
			return 1;
		}

		if (arg2[0] == '\"') {
			const char *delim2 = "\"";
			char *msg = strtok(arg2, delim2);
			if (rhash_msg(code, msg, strlen(msg), digest) < 0) {
				perror("Error. Could not generate hash");
				return 2;
			}
			arg2 = (char *) malloc(strlen(msg) + 3);
			snprintf(arg2, strlen(msg) + 3, "\"%s\"", msg);
		} else {
			if (rhash_file(code, arg2, digest) < 0) {
				perror("Error. Could not generate hash");
				return 2;
			}
		}

		if (!rhash_print_bytes(output, digest, rhash_get_digest_size(code), FLAGS)) {
			fprintf(stderr, "%s\n", "Error. Could not print hash to buffer.");
			return 3;
		}

		printf("%s (%s) = %s\n", rhash_get_name(code), arg2, output);
	}

	return 0;
}