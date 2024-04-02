#include "player.h"
#include <stdio.h>
#include "assert.h"
#include "stdbool.h"


int tokens[3];
struct builder_t *dispo[MAX_BUILDERS];

void test_player(struct player_t* player)
{

    init_player(player);
    assert((player->num_tokens == 0) == true);
    assert((player->num_builders == 0) == true);
    assert((player->victory_points_of_player == 0) == true);
    assert((player->colors_global_tok[1] == 0) == true);
    assert((player->colors_global_buil[1] == 0) == true);
}

void test_pick_token(struct player_t *player, struct token_in_market market[5][5])
{
    pick_tokens(player, market);
    assert((player->num_tokens == 3) == true);
}

void test_hire_build(struct player_t *player, struct piles_t* pile,struct guild_t *guild)
{
    int n = possible(player, pile, guild);
    (void) n;
    assert((player->num_builders == 1) == true);
    
}

// int main()
// {
//     struct guild_t guild;
//     struct player_t play;
//     init_guild(&guild);
//     test_player(&play);
//     test_pick_token(&play, notre_market);
//     test_hire_build(&play, &guild);
//     return 0;
// }
void test_possible(struct player_t *player, struct piles_t *pile,struct guild_t *guild)
{
    shuffle_guild(guild,1,pile);
    int p=possible(player,pile,guild);
    printf("le nombre de builders de niveau 1 qui peuvent etre embauché par le player est %d\n",p);
}

void test_affichage_voisins(struct point p)
{
    printf("les voisins de (%d,%d) sont : \n",p.i,p.j);
    struct point L[4];
    voisins(p,L);
    char* liste[4]={"gauche","droite","bas","haut"};
    struct point point0;
    point0.i=0;
    point0.j=0;
    for(int l=0;l<4;++l)
    {
        if(  L[l].i !=point0.i ||  L[l].j !=point0.j)
        {
            printf("      voisin %s --> (%d,%d) \n",liste[l], L[l].i, L[l].j);
        }
    }

}