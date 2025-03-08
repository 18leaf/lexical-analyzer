#include <stdio.h>
#include "../include/scanner.h"
#include "../include/utils.h"


struct token tokens[TOKEN_ARRAY_SIZE];
// define keywords(only using example for now)
static const char *keywords[] = {
	// python keywords
	"def",
	"print",

	// java
	"public",
	"class",
	"static",
	"void",
	"int"
};
// num of keywords for loops
#define NUM_KEYWORDS sizeof(keywords)/sizeof(const char *)


static void print_tokens(const int token_count) {
	// format tokens in 1 line if they were in a line in original text
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

TrieNode* populate_keyword_table(void) {
	// adds keywords to trie for search
	TrieNode* keywordTrie = create_trie_node('\0');
	for (int i = 0; i < NUM_KEYWORDS; i++) {
		// add to trie
		insert(keywordTrie, keywords[i]);
	};
	return keywordTrie;
};


int main(const int argc, char *argv[]) {
	// initialize trie for keyword lookup table
	TrieNode* keywordTrie = populate_keyword_table();
	char* filename;
	if (argv[1] == NULL && argc > 0) {
		filename = "test.txt";
	}
	else {
		// set filename to given arg
		filename = argv[1];
	}


	// open the source for analyzing (read from txt)
	FILE *file_ptr = fopen(filename, "r");

	if (file_ptr == NULL) {
		// failed to open file
		printf("File not found\n");
		return 0;
	}


	const int token_count = run_scanner(file_ptr, keywordTrie);
	print_tokens(token_count);
	return 1;
}
