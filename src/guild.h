// guild.h
#ifndef __GUILD_H__
#define __GUILD_H__
#define MAX_BUILDERS_AVAILABLE_PER_LVL 3

#include "builder.h"


#define GUILD_SIZE 10


struct guild_one_t 
{
    struct builder_t* builder;
    int state;
    int dispo;
};

struct guild_t 
{
  struct guild_one_t indice[MAX_BUILDERS];
};

struct pile_by_level
{
  struct builder_t* level[MAX_BUILDERS];
  int size;
  struct builder_t* disponible[3]; 
};

struct piles_t 
{
  struct pile_by_level pile1;
  struct pile_by_level pile2;
};

void init_guild(struct guild_t* guild );

void init_pile(struct piles_t* pile);

int  get_available_builders(struct guild_t* guild);

struct guild_t* remove_builder_from_guild(const struct builder_t* b,struct guild_t* guild) ;

void shuffle_guild(struct guild_t *guild, unsigned int level,struct piles_t* pile);

int count_builders(struct guild_t *guild, unsigned int level);

void available_shop(struct piles_t *pile, unsigned int level);

#endif // __GUILD_H__

