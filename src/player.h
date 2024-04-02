#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "guild.h"
#include "market.h"



#define VICTORY_POINTS 20
#define  PLAYER_MAX_TOKENS 10
#define MAX_COLORS 5

//Pas normal on ne devrait pas avoir à réimporter la définition de la structure 

struct builder_t
{
  unsigned int level;
  unsigned int index;
  unsigned int points;
  struct buildcost_t requires;
  struct buildcost_t provides;
};

struct player_t {
    struct token_t tokens[PLAYER_MAX_TOKENS];
    struct builder_t* builders[MAX_BUILDERS];
    unsigned int victory_points_of_player;
    unsigned int num_tokens;
    unsigned int num_builders;
    unsigned int colors_global_tok[NUM_COLORS];
    unsigned int colors_global_buil[NUM_COLORS];
};

void init_player( struct player_t *play );

void display_player( struct player_t* player);

int voisins(struct point p,struct point L[4]);
void pick_tokens(struct player_t *player,struct token_in_market market[5][5]);

//Embauche le builder pour le player en question. 
void hire_builder( struct player_t* player,  struct builder_t* builder, struct guild_t* guild);

int possible(struct player_t *player, struct piles_t* pile, struct guild_t* guild);
//Permet de définir tous les builders possibles à l'achat pour le joueur.


//Choisit le builder qui sera acheté par le joueur, de manière aléatoire.
struct builder_t* builder_shop(struct builder_t* builders[MAX_BUILDERS], unsigned int n);

//int opti_cost(struct builder_t* builder,struct player_t* player);


#endif //__PLAYER_H__
