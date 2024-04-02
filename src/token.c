#include <stdio.h>
#include "token.h"

struct token_t create_simple_token(enum color_t c) {
  struct token_t token={{0,0,0,0,0}};
  token.c[c] = 1;
  return token;
}

struct token_t create_complex_token(unsigned int c[NUM_COLORS])
{
  struct token_t token={{0,0,0,0,0}};
  for (int i=0; i<NUM_COLORS; ++i)
    {
	token.c[i]=c[i];
}
  return token;
}

int token_equals(const struct token_t t1, const struct token_t t2)
{
  for (int i=0; i<NUM_COLORS; ++i)
    {
      if (t1.c[i] != t2.c[i])
	      return 0;
    }
  return 1;
}

void token_display(struct token_t t, const char* prefix)
{
    unsigned int couleur_du_jeton = 0;
    unsigned int nombre_de_ressources = 0;
    for( unsigned int i=0;i<NUM_COLORS;i++)
    {
      if (t.c[i]!=0)
      {
        couleur_du_jeton=i;
        nombre_de_ressources=t.c[i];
      }
    }
    printf("%s Token(%s=%d)\n",prefix,color_to_string(couleur_du_jeton),nombre_de_ressources);
}
