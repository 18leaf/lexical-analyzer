//
// Created by Lindsey on 2/28/2025.
//

#include "../include/token.h"
#include <stdio.h>
#include <string.h>


// return newly created token
struct token init_token(const int line_number, const int lexeme_start) {
	return (struct token) {
		.token_type = END,
		.token_string = "",
		.line_number = line_number,
		.lexeme_start = lexeme_start,
		};
};


void set_token_string(struct token *token, const char token_string[TOKEN_STRING_SIZE]) {
	// copy string to token_string
	for (int i = 0; i < TOKEN_STRING_SIZE; i++) {
		if (token_string[i] == '\0') {

		} else {
			token->token_string[i] = token_string[i];
		}
	};
};

void set_token_type(struct token *token, const enum ETokenType token_type) {
	token->token_type = token_type;
};



// print enumerated token type
void print_token_type(const enum ETokenType token_type) {
    switch (token_type) {
    	case KEYWORD:
    		printf("KEYWORD");
    		break;
		case IDENTIFIER:
			printf("IDENTIFIER");
			break;
		case OPERATOR:
			printf("OPERATOR");
    		break;
		case NUM_LITERAL:
			printf("NUM_LITERAL");
			break;
    	case STR_LITERAL:
    		printf("STR_LITERAL");
    		break;
    	case PUNCTUATION:
    		printf("PUNCTUATION");
    		break;
		default:
			printf("UNKNOWN");
    };
}

// print token in format TOKEN[Lexeme]
void print_token(const struct token *token) {
	// print token type
	print_token_type(token->token_type);
	printf("[");

	//print token contents
	// i less than size of token string and token string not terminated
  	for (int i = 0; i < TOKEN_STRING_SIZE && token->token_string[i] != '\0'; i++) {
  		printf("%c", token->token_string[i]);
  	}
	printf("]%d:%d", token->line_number, token->lexeme_start);
};