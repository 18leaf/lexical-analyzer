#include "../include/token.h"
#include "../include/descent-parser.h"
/*
  if:
    stmt
  else:
    stmt
  elif:
    stmt
 * */

/*
 *
 * TODO print token that causes Error
 * */

bool descentParser(struct token *TOKEN_ARR, int token_count)
{
  // START if -> wait for :\n\t
  // if \n before : ERror
  // if elif if, else, error
   // must be if : stmt
  

   // if <expr> : \n<block>
   // <block>
   struct token curr;
   int state = 0; // state represents section ie -> enter if state = 1, wait for :, keep iterating over tokens
   for (int i = 0; i < token_count; i++)
   {
      curr = TOKEN_ARR[i];
      switch (state)
      {
         // simply consume token
         case 0:
            // look for entry into new state -> if
            if (curr.token_type == KEYWORD) // match for
            {
               printf("KEYWORD\n");
               state = 1;
            }
            break;
         case 1:
            // keyword here search for next token
            if (curr.token_type == PUNCTUATION)
            {
               printf("PUNCTUATION");
               state = 0;
            }
            else if (curr.token_type == NEW_LINE)
            {
               printf("\nNEWLINE TOO EARLY INCORRRECT SYNTAx\n");
               return false;
            }
            break;
      }

   }
   return true;


}
