#include "stdlib.h"
#include "player.h"
#include "stdlib.h"
// penser aux provides des builders à ajouter dans les couleurs disponibles au final.  
 struct player_t* ini_player1()
{
     struct player_t play1=
    {
        .victory_points_of_player=0,
        .num_tokens=0,
        .num_builders=0,
        .colors_global_buil={{0,0,0,0,0}},
        .colors_global_tok={{0,0,0,0,0}},
    };
    return &play1;
}

 struct player_t* ini_player2()
{
     struct player_t play2=
    {
        .victory_points_of_player=0,
        .num_tokens=0,
        .num_builders=0,
        .colors_global_buil={{0,0,0,0,0}},
        .colors_global_tok={{0,0,0,0,0}},
    };
    return &play2;
}

// On va compter le nombre de couleurs disponibles pour chaque joueur ce sera plus facile pour les comparaisons pour les achats.
void sum_colors_tok(struct player_t *player)
// La manière dont est codé la chose fait qu'on doit réinitialiser les couleurs à chaque fois
{
    for (unsigned int i = 0; i < NUM_COLORS; ++i)
        player->colors_global_tok[i] = 0;
    for (unsigned int i = 0; i < player->num_tokens; ++i)
    {
        for (unsigned int j = 0; j < NUM_COLORS; ++j)
            player->colors_global_tok[j] += player->tokens[i].c[j];
    }
}
void sum_colors_build(struct player_t *player)
{
    for (unsigned int i = 0; i < NUM_COLORS; ++i)
        player->colors_global_buil[i] = 0;
    for (unsigned int i = 0; i < player->num_builders; ++i)
    {
        player->colors_global_tok[player->bs[i].provides.c] += player->bs[i].provides.n;
    }
}

void hire_builder(struct player_t *player, struct builder_t *builder)
{
    player->bs[player->num_builders] = *builder;
    player->num_builders += 1;
    remove_builder_from_guild(builder);
}
// void hire_builder(struct player_t* player,  struct builder_t* builder)
// {
//     player->bs[player->num_builders]= *builder; 
//     player->num_builders +=1;
//     remove_builder_from_guild(builder);
// }

void pick_token(struct player_t *player, struct token_t token[3])
{
    for (int i = 0; i < 3; ++i)
    {
        player->tokens[player->num_tokens + i] = token[i];
        remove_token_from_market(player->tokens[player->num_tokens + i], notre_market);
    }
    player->num_tokens += 3;
}
// void pick_token(struct player_t* player, struct token_t token[3])
// {
//     for (int i=0; i<3; ++i){
//         player->tokens[player->num_tokens+i]=token[i];
//         remove_token_from_market(player->tokens[player->num_tokens+i],notre_market);
//     }
//     player->num_tokens +=3;
    
// }

// Ici, on n'est pas dans le cas d'un choix aléatoire, le player prendra toujours le premier builder qu'il peut acheter

struct builder_t* builder_shop(struct player_t *player)
{

    for (unsigned int i = 0; i < MAX_BUILDERS; ++i)
    {
        if (available[i].builders != NULL && available[i].builders->requires.n < player->colors_global_buil[available[i].builders->requires.c] + player->colors_global_tok[available[i].builders->requires.c])
            return available[i].builders;
    }
    return NULL;
}
void make_tab(enum color_t c, unsigned int color[NUM_COLORS])
{
    for (unsigned int i = 0; i < NUM_COLORS; ++i)
    {
        if (i == c)
            color[i] = 2;
        else
            color[i] = 0;
    }
}
// Ici, on suppose que le player peut acheter mais on va déterminer si le coût d'achat est optimal ou non . On considère qu'il est optimal
// si on ne perd pas de partie de la couleur. On ne prend pas en compte les provides pour l'instant
int opti_cost(struct builder_t *builder, struct player_t *player)
{

    /* dans un premier temps les tokens sont monochromes on pourra faire une boucle pour vérifier que les autres couleurs
    ont une valeur nulle ou non plus tard  pour éviter de gaspiller des couleurs*/
    if (player->colors_global_tok[builder->requires.c] == builder->requires.n)
        return 1;
    // ici ça sera vrai dès qu'on peut acheter même uniquement avec des tokens donc pas opti
    else if (player->colors_global_tok[builder->requires.c] > builder->requires.n && builder->requires.n % 2 != 0)
    {
        int comp = 0;
        int simp = 0;
        unsigned int f_token[NUM_COLORS];
        make_tab(builder->requires.c, f_token);
        struct token_t token_c = create_complex_token(f_token);
        struct token_t token_s = create_simple_token(builder->requires.c);
        for (unsigned int i = 0; i < player->num_tokens; ++i)
        {
            comp += token_equals(player->tokens[i], token_c);
            simp += token_equals(player->tokens[i], token_s);
            if (comp % 2 == 0 && simp == 0)
                return 0;
            else
                return 1;
        }
    }
    return 0;
}
