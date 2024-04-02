#include "guild.h"
#include <stdio.h>
#include "assert.h"
#include "stdbool.h"
#define N 5
struct guild_t guild;

//The test consists to verify if the the element in the guild is a the builder we init in builder.c
void test_builder_in_guild(struct guild_t* guild)
{
  init_guild(guild);
  const struct builder_t* b= make_builder(1);
  assert((guild->indice[1].builder == b) == true );
  
}

void test_builder_unavailable(const struct builder_t* b, struct guild_t *guild)
{
  init_guild(guild);
  remove_builder_from_guild(b,guild);
  for(int i=0; i < N; ++i)
    if (guild->indice[i].builder == b)
    {
      assert((guild->indice[i].state == 0) == true);
    }
}


