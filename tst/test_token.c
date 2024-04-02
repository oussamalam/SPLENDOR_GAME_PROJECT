#include "token.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

//Is-it really useful ? 
void test_token_equals()
{
  struct token_t token1 = {{1,0,0,0,0}};
  struct token_t token2 = {{1,0,0,0,0}};
  struct token_t token3 = {{0,2,0,0,0}};
  assert(token_equals(token1,token2) == 1);
  assert(token_equals(token2,token3) == 0);
  
}

// Verifiying if the token is really a token 

void test_token()
{
  struct token_t token = create_simple_token(RED);
  struct token_t t = {{0,0,0,1,0}};
  assert(token_equals(token,t) == 1);
}

