#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFSIZE 1000


int main(int argc, char const *argv[])
{
	if (argc < 3) {
		fprintf(stdout, "%s\n", "help");
	}

	FILE *f_in = fopen(argv[1], "rb");
	if (f_in == NULL) {
		perror("Error. Could not open infile");
		exit(1);
	}

	FILE *f_out = fopen(argv[2], "w");
	if (f_out == NULL) {
		perror("Error. Could not open outfile");
		exit(2);
	}

	struct stat file_status;
	if (stat(argv[1], &file_status) < 0) {
        perror("Error. Could not get input file size");
        exit(1);
    }
    long infile_size = file_status.st_size;

	char buffer[BUFSIZE];
	size_t nmemb = sizeof(buffer) / sizeof(char);
	size_t bytes_read, total_bytes = 0;


	while (!feof(f_in)) {
		bytes_read = fread(buffer, sizeof(char), nmemb, f_in);
		if (ferror(f_out)) {
			perror("Error. Could not write to outfile");
			exit(1);
		}

		if (fwrite(buffer, sizeof(char), bytes_read, f_out) != bytes_read) {
			fprintf(stderr, "%s\n", "Error. Could not write enough bytes");
			exit(1);
		}

		total_bytes += bytes_read;
	}

	if (ferror(f_in)) {
		perror("Error. Could not read from infile");
		exit(1);
	}

    if (infile_size != total_bytes * sizeof(char)) {
    	fprintf(stderr, "%s\n", "Error. File sizes do not match. Abort moving");
    	exit(1);
    }

	fclose(f_in);
	fclose(f_out);

	remove(argv[1]);

	return 0;
}