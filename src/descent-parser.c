#include <stdio.h>
#include "../include/descent-parser.h"
#include "../include/token.h"

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
static struct token *TP; // token pointer
static int POS;
static int TC; // token count



bool descentParser(struct token *TOKEN_ARR, int token_count)
{
   TP = TOKEN_ARR;
   TC = token_count;
   POS = 0;


   // consume all tokens until first if statement
   while(
      (POS < TC)    // not at end
      && !(TP[POS]->token_type == KEYWORD && strcmp(TP[POS]->token_string, "if"))) // NOT (token type == keyword and literal is if)
   {
      // token follows grammar, so advance
      POS++;
   }

   // if statement here // or finished
   while(
      (POS < TC)
         
   )
   {
      // increment position
      POS++;
   }
   
}
