#include <stdio.h>
#include "../include/descent-parser.h"
#include "../include/token.h"
#include <stdio.h>
#include <string.h>

/*
PSEUDOCODE/DESIGN HERE

/// GRAMMAR SET REMOVED LEFT RECURSION
<if_stmt>   ->    "if" <named_expr> ":" "\n" <block> <if_next>

<if_next>   ->    <elif_stmt> | <else_block> | empty

<elif_stmt> ->    "elif" <named_expr> ":" "\n" <block> <elif_stmt> | empty

<else_block>->    "else" ":" "\n" <block>

<named_expr> ":" "\n" <block> is going to be shared code
<block> is shared code
note empty will be handled like block -> implies end of if statement
/// END GRAMMAR


// BLOCK consume until [if, elif, else] -> keywords that indicate presence of if stmt grammar => note that elif or else before if is invalid, so check here
//    
// PARSE IF
//    IF is found, start the grammar descent
//    parse named expression
//    expect ":"
//    expect "\n"
//    parse block
//    parse if next
//    
// PARSE NAMED EXPR
//    NAMED EXPR START
//    expect (IDENTIFIER || NUM_LIT || STR_LIT)
//    expect OPERATOR token
//    check for one more operator token (in case == != <= etc) (i only wrote to detect 1 operator like < > etc in scanner)
//    expect (IDENTIFIER || NUM_LIT || STR_LIT)
//
// PARSE BLOCK
//    
//    
//
//
//
//   must be "if" consumethis until -> : \n -> <block>
//          case "if"
//             go above cal
//          case "elif"
//
//          case "else"
 * */




// global vars
// tokens array, current position, token count
static struct token *tokens; // token pointer
static int token_count; // token count
static int current; // current token on


/*
 *	HELPER functions for descent parser
 *
 *
 */

// peek without removing
static struct token	*peek()
{
	return &tokens[current];
}

// move to next
static struct token	*advance()
{
	return &tokens[current++];
}

// match keyword return true if match else false
static bool match_keyword(const char *kw)
{
	const struct token *t = peek();
	if (t->token_type == KEYWORD && !strcmp(t->token_string, kw))
	{
		advance();
		return true;
	}
	return false;
}

/*
 *	Expecting next characters
 *
 *
 */

static bool expect_punct(const char ch)
{
	const struct token *t = peek();
	if (t->token_type == PUNCTUATION && t->token_string[0] == ch) {
		advance();
		return true;
	}

	printf("Expected colon, got ");
	print_token(t);
	fprintf(stderr, "\n");
	return false;
}

static bool expect_newline()
{
	const struct token *t = peek();
	if (t->token_type == NEW_LINE)
	{
		advance();
		return true;
	}
	printf("Expected newline, got ");
	print_token(t);
	fprintf(stderr, "\n");
	return false;
}

/*
 *	parsing functions
 *
 */

static bool parse_named_expression()
{
	const int start = current;
	while (current < token_count)
	{
		struct token *t = peek();

		// success case = : then \n
		if ((t->token_type == PUNCTUATION && t->token_string[0] == ':')
			 || t->token_type == NEW_LINE)
		{
			break;
		}

		// if cannot be if if elif else: or any combination like it inside named expr
		if (t->token_type == KEYWORD &&
			 (!strcmp(t->token_string, "if") ||
			  !strcmp(t->token_string, "elif") ||
			  !strcmp(t->token_string, "else")))
		{
			printf("Found invalid token ");
			print_token(t);
			fprintf(stderr, "\n");
			return false;
		}

		advance();
	}

	// check for existing named expr (no if/elif with named expr)
	if (current == start)
	{
		printf("Expected expression before ':', got ");
		fprintf(stderr, "NULL\n");
		return false;
	}

	return true;
}

static bool parse_block()
{
	if (!expect_newline()) return false;
	// consume until next line (limits blocks to only 1 line PLACE TO IMPROVE TODO)
	while (current < token_count && peek()->token_type != NEW_LINE)
	{
		advance();
	}
	return expect_newline();
}

static bool parse_else_block()
{
	if (!match_keyword("else"))
	{
		const struct token *t = peek();
		printf("Expected token 'else', got ");
		print_token(t);
		fprintf(stderr, "\n");
		return false;
	}
	// there can be no named expr after else
	bool named_expr = false;
	while (peek()->token_string[0] != ':')
	{
		named_expr = true;
		advance();
		//EOF
		if (current >= token_count) break;
	}
	if (named_expr)
	{
		printf("Invalid expr after else");
		fprintf(stderr, "\n");
		return false;
	}

	if (!expect_punct(':')) return false;
	return parse_block();
}

static bool parse_elif_stmt()
{
	if (!match_keyword("elif"))
	{
		const struct token *t = peek();
		printf("Expected 'elif', got ");
		print_token(t);
		fprintf(stderr, "\n");
		return false;
	}
	// parse named expr
	if (!parse_named_expression()) return false;
	// if not expected there is error
	// pattern = : \n <block>
	if (!expect_punct(':')) return false;
	if (!parse_block()) return false;

	const struct token *t = peek();
	// check for elif repeated.. or else
	if (t->token_type == KEYWORD && !strcmp(t->token_string, "elif"))
	{
		return parse_elif_stmt();
	}
	if (t->token_type == KEYWORD && !strcmp(t->token_string, "else"))
	{
		return parse_else_block();
	}
	// end of original else statment
	return true;
}


static bool parse_if_stmt()
{
	if (!match_keyword("if"))
	{
		const struct token *t = peek();
		printf("Expected 'if', got ");
		print_token(t);
		fprintf(stderr, "\n");
		return false;
	}

	// parse named expr until next block
	if (!parse_named_expression()) return false;
	if (!expect_punct(':')) return false;
	if (!parse_block()) return false;

	const struct token *t = peek();
	// legal next blocks after block = elif, else, another block or nothing
	if (t->token_type == KEYWORD && !strcmp(t->token_string, "elif"))
	{
		return parse_elif_stmt();
	}
	if (t->token_type == KEYWORD && !strcmp(t->token_string, "else"))
	{
		return parse_else_block();
	}
	return true;
}


bool descentParser(struct token tokenv[], int tokenc)
{
	// init vars
   tokens = tokenv;
	token_count = tokenc;
	current = 0;

	// iterate until finished
	while (current < token_count)
	{
		struct token *t = peek();
		// continue until if statment found
		if (t->token_type == KEYWORD && !strcmp(t->token_string, "if"))
		{
			if (!parse_if_stmt()) return false;
		}
		else
		{
			advance();
		}
	}

	printf("CODE ACCEPTED\n");
	return true;
}
