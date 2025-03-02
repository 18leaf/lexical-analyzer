#include <stdio.h>
#include "../include/scanner.h"

static void print_tokens(const int token_count) {
	for (int i = 0; i < token_count - 1; i++) {
		if (tokens[i].line_number != tokens[i + 1].line_number) {
			print_token(&tokens[i]);
			printf("\n\n");
		} else {
			print_token(&tokens[i]);
			printf(" | ");
		}
	};
};


int main(void) {

	// open the source for analyzing (read from txt)
	FILE *file_ptr = fopen("test.txt", "r");


	const int token_count = run_scanner(file_ptr);
	print_tokens(token_count);
	// scan
	return 1;
}
