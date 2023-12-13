#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "rhash.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#endif




int main(int argc, char const *argv[])
{
	const char* msg = "message digest";
	char digest[64];
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
		else
			printf("%s\n", "err");

		if (arg2[0] == '\"') {
			const char *delim2 = "\"";
			char *msg = strtok(arg2, delim2);
			int res = rhash_msg(code, msg, strlen(msg), digest);
			arg2 = (char *) malloc(strlen(msg) + 3);
			int k = snprintf(arg2, strlen(msg) + 3, "\"%s\"", msg);
		} else {
			int res = rhash_file(code, arg2, digest);
		}

		rhash_print_bytes(output, digest, rhash_get_digest_size(code), FLAGS);

		printf("%s (%s) = %s\n", rhash_get_name(code), arg2, output);
	}

	return 0;
}