//
// Created by Lindsey on 2/28/2025.
//

#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_STRING_SIZE 32


enum ETokenType {
	KEYWORD,
	IDENTIFIER,
	OPERATOR,
	NUM_LITERAL,
	STR_LITERAL,
	PUNCTUATION,
	END
};

// Contains token type and string
// and token string
struct token {
	enum ETokenType token_type;
	// limit to size of 16 for now (example is not longer)
	char token_string[TOKEN_STRING_SIZE];
	// store location line number, beginning char pos
	// position[0] = line, [1] = beginning_char
	int line_number;
	int lexeme_start;
};

struct token init_token(int line_number, int lexeme_start);

void print_token(const struct token *token);
void print_token_type(enum ETokenType token_type);
void set_token_type(struct token *token, enum ETokenType token_type);
void set_token_string(struct token *token, const char token_string[TOKEN_STRING_SIZE]);
void set_line_number(struct token *token, int line_number, int lexeme_start);


#endif //TOKEN_H

