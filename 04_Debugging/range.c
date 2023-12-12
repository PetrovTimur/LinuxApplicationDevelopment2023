#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if ((argc < 2) || argc > 4) {
		printf("%s\n", "help for range:\n"
					   "\trange - print a sequence of numbers\n"
					   "SYNOPSIS\n"
					   "\t./range LAST\n"
					   "\t./range FIRST LAST\n"
					   "\t./range FIRST LAST STEP");
		return 0;
	}

	int N = (argc == 2) ? atoi(argv[1]) : atoi(argv[2]);
	int M = (argc == 2) ? 0 : atoi(argv[1]);
	int S = (argc == 4) ? atoi(argv[3]) : 1;

	for (int i = M; i < N; i += S) {
		printf("%d\n", i);
	}


	return 0;
}