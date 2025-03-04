//
// Created by Lindsey on 2/28/2025.
//

#include "../include/scanner.h"

#include <string.h>

#include "../include/token.h"

// temp array to store tokens
// already created extern in scanner.h

int run_scanner(FILE *file, TrieNode *keywordTrie) {
	// count/save position of token
	int token_pos = 0;

	// get buffer for line, save line number
	char line[1024];
	int line_number = 1;
	// reads entire line (line length limit = 1024)
	while (fgets(line, 1024, file)) {
		// iterate over each char in line
		// check if first in series of chars (important for token identification)
		bool is_first = true;
		// hold value for beginning of lexeme/token
		char token_string_buffer[TOKEN_STRING_SIZE];
		for (int i = 0; i < TOKEN_STRING_SIZE; i++) {
			token_string_buffer[i] = '\0';
		}
		int lexeme_start = 0;
		enum ETokenType current_token_type = END;
		for (int char_pos = 0; char_pos < strlen(line); char_pos++) {
			// if first, create a token to hold data
			if (is_first) {
				lexeme_start = char_pos;
				// pick which state it is
				// switch case and assign current token type
				// NOTE handle identifiers and keywords the same for now
				// only relevant until lookup (keyword = identifier here)

				// skip empty or spaces
				if (line[char_pos] == ' ' || line[char_pos] == '\n') {
					continue;
				}
				// first token_string_buffer = char of line position of first

				//  || line[char_pos] == '_'
				if ((line[char_pos] >= 'A' && line[char_pos] <= 'Z')
					|| (line[char_pos] >= 'a' && line[char_pos] <= 'z')
					|| line[char_pos] == '_') {
					if (line[char_pos] == '(' || line[char_pos] == '.') {
						printf("\nTF %c\n", line[char_pos]);
					}
					current_token_type = IDENTIFIER;
					// init new token ** significant that I do not define token_Type here... still needs validation
					tokens[token_pos] = init_token(line_number, lexeme_start);
				}
				// is it a digit? -> numerical literal
				else if (line[char_pos] >= '0'  && line[char_pos] <= '9' ) {
					current_token_type = NUM_LITERAL;
					tokens[token_pos] = init_token(line_number, lexeme_start);
				}
				// is it an operator
				else if (line[char_pos] == '+' || line[char_pos] == '=') {
					current_token_type = OPERATOR;
					tokens[token_pos] = init_token(line_number, lexeme_start);
				}
				// is it some other punctuation
				else if (line[char_pos] == ':' || line[char_pos] == ','
					|| line[char_pos] == '.' || line[char_pos] == ';'
					|| line[char_pos] == '(' || line[char_pos] == ')'
					|| line[char_pos] == '{' || line[char_pos] == '}'
					|| line[char_pos] == '[' || line[char_pos] == ']') {
					current_token_type = PUNCTUATION;
					tokens[token_pos] = init_token(line_number, lexeme_start);
				}
				// is it a string literal (for now treating java like pythons)
				else if (line[char_pos] == '\'' || line[char_pos] == '"') {
					current_token_type = STR_LITERAL;
					tokens[token_pos] = init_token(line_number, lexeme_start);
				}

				token_string_buffer[char_pos - lexeme_start] = line[char_pos];
				is_first = false;
			}
			// continue adding to token buffer until reach terminate char
			else {
				bool ended = false;
				switch (current_token_type) {
					case IDENTIFIER:
						// current def = identifier ends IF it does not have alphanumeric or _ inside
						if ((line[char_pos] >= 'A' && line[char_pos] <= 'Z')
							|| (line[char_pos] >= 'a' && line[char_pos] <= 'z')
							|| line[char_pos] == '_'
							|| (line[char_pos] >= '0' && line[char_pos] <= '9' )) {
							//ended = true;
							token_string_buffer[char_pos - lexeme_start] = line[char_pos];
							// TODO KEYWORDS
						}
						// else == not valid or terminated
						else {
							ended = true;
						}
						break;
					case OPERATOR:
						//check for termination (believe only 1 so by default yes)
						// ignore below just to remove CLion IDE suggestions
						current_token_type = OPERATOR;
						ended = true;
						break;
					case PUNCTUATION:
						// default to true (only 1 at a time)
						ended = true;
						break;
					case NUM_LITERAL:
						if ((line[char_pos] >= '0' && line[char_pos] <= '9')
							|| line[char_pos] == '.') {
							token_string_buffer[char_pos - lexeme_start] = line[char_pos];
							// TODO further define int, float, etc
						} else {
							ended = true;
						}
						break;
					case STR_LITERAL:
						if (line[char_pos] == '"' || line[char_pos] == '\'') {
							token_string_buffer[char_pos - lexeme_start] = line[char_pos];
							char_pos++;
							ended = true;
						} else {
							token_string_buffer[char_pos - lexeme_start] = line[char_pos];
						}
						break;
					default:
						break;
				}
				if (ended) {

					if (current_token_type == IDENTIFIER) {
						if (is_keyword(keywordTrie, token_string_buffer)) {
							current_token_type = KEYWORD;
						}
					}

					set_token_string(&tokens[token_pos], token_string_buffer);
					set_token_type(&tokens[token_pos], current_token_type);
					is_first = true;
					token_pos++;
					char_pos--;
					// reset token_type
					current_token_type = END;

					// reset token_string_buffer to null char
					for (int i = 0; i < TOKEN_STRING_SIZE; i++) {
						token_string_buffer[i] = '\0';
					}
				}
			}
		}
		line_number++;
	};
	return token_pos;
};

// return true if is keyword
bool is_keyword(TrieNode* keywordTrie, const char word[TOKEN_STRING_SIZE]) {
	// see utils.c for below implementation
	return search(keywordTrie, word);
}