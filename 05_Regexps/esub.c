#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10

int main(int argc, char *argv[]) {
    int errcode;
    char msgbuf[100];
    regex_t regex;
    regmatch_t bags[MAXGR];

    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    if (argc != 4) {
    	fprintf(stderr, "Wrong number of arguments, need exactly 3\n");
    	exit(1);
    }

    if (errcode = regcomp(&regex, regexp, REG_EXTENDED) != 0) {
    	regerror(errcode, &regex, msgbuf, sizeof(msgbuf));
    	fprintf(stderr, "Could not compile regex: %s\n", msgbuf);
    	exit(2);
    }


    if (!(errcode = regexec(&regex, string, MAXGR, bags, 0))) {
        for (int i=0; i < bags[0].rm_so; i++)
    		printf("%c", string[i]);
        for (int i=0; i < strlen(substitution); i++) {
    		printf("%c", substitution[i]);
    	}
    	for (int i=bags[0].rm_eo; i < strlen(string); i++) {
    		printf("%c", string[i]);
    	}

        printf("\n");

    } else if (errcode == REG_NOMATCH) {
    	puts("No match");
	} else {
	    regerror(errcode, &regex, msgbuf, sizeof(msgbuf));
	    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	    exit(3);
	}

    regfree(&regex);

    return 0;
}