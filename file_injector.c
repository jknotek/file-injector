
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_READ_SIZE 10000

void print_usage() {
	printf("Usage: file-injector 'string to find' file-to-replace.txt < template-file.txt > injected.txt\n");
}

int print_file(const char file_name[]) {
	FILE *fp;
	if ((fp = fopen(file_name, "rb")) == NULL) {
		return 0;
	}

	char buf[MAX_READ_SIZE];

	int bytes_read;

	while ((bytes_read = fread(buf, 1, MAX_READ_SIZE, fp)) != 0) {
		fwrite(buf, 1, bytes_read, stdout);
	}

	fclose(fp);

	return 1;
}

int main(int argc, char const *argv[]) {

	if (argc == 1) {
		print_usage();
		exit(1);
	}

	if ((argc - 1) % 2 != 0) {
		fprintf(
			stderr,
			"Must have an even number of arguments.\n"
			"(e.g. `'search 1' replace-file-1 'search 2' replace-file-2 [...]`)\n"
		);
		exit(1);
	}

	int c;
	// TODO: determine this from actually checking args
	int longest_search = 30;
	int exit_code = 0;

	char *curr_buffer = malloc(longest_search+1);
	char *compare_buffer = malloc(longest_search+1);

	if (curr_buffer == NULL || compare_buffer == NULL) {
		fprintf(stderr, "Could not allocate memory.\n");
		exit_code = 1;
		goto quit;
	}

	for (int l=0; l<longest_search; l++) {
		if ((c = getchar()) == EOF) {
			fprintf(stderr, "One or more search terms is larger than the template file!\n");
			exit_code = 1;
			goto quit;
		}
		curr_buffer[l] = c;
	}
	curr_buffer[longest_search] = '\0';

	int skip;
	int found;
	int search_length;

	while (1) {
		found = 0;

		for (int i=1; i<argc; i+=2) {
			search_length = strlen(argv[i]);
			strcpy(compare_buffer, curr_buffer);
			compare_buffer[search_length] = '\0';

			if (strcmp(compare_buffer, argv[i]) == 0) {
				if (print_file(argv[i+1]) == 0) {
					fprintf(stderr, "Couldn't open file: %s\n", argv[i+1]);
					goto quit;
				}
				skip = search_length;
				found = 1;
			}
		}

		if (!found) {
			skip = 1;
			printf("%c", curr_buffer[0]);
		}

		for (int s=0; s<skip; s++) {
			// shift all characters one index behind
			for (int j=0; j<longest_search; j++) {
				curr_buffer[j] = curr_buffer[j+1];
			}

			if ((c = getchar()) != EOF) {
				curr_buffer[longest_search-1] = c;
			}

			if (curr_buffer[0] == '\0') {
				goto quit;
			}
		}
	}

	quit:
	free(curr_buffer);
	free(compare_buffer);

	return exit_code;
}
