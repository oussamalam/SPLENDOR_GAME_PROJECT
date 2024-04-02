#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    int l;
    int tours_max=10;
    int seed = 0;
    while ((opt = getopt(argc, argv, "m:s:c:")) != -1)
    {
        switch (opt)
        {
        case 'c':
             l = atoi(optarg);
            break;
        case 'm':
             tours_max = atoi(optarg);
            break;
        case 's':
             seed = atoi(optarg);
            break;
        }
    }
    (void) l;
    unsigned int tp1 = 0;
    struct guild_t guild;
    unsigned int tp2 = 0;
    struct player_t player1;
    struct player_t player2;
    struct piles_t pile;
    init_builders(seed);
    init_guild(&guild);
    init_player(&player1);
    init_player(&player2);
    init_market(notre_market);
    init_pile(&pile);
    shuffle_guild(&guild, 1,&pile);
    shuffle_guild(&guild, 2,&pile);
    available_shop(&pile,1);
    available_shop(&pile,2);

    int nb_tours = 0;
    while (player1.victory_points_of_player < VICTORY_POINTS && player2.victory_points_of_player < VICTORY_POINTS)
    {
        // Au tour du premier joueur de jouer.
        // choix des 3 tokens
        pick_tokens(&player1, notre_market);
        int p = possible(&player1, &pile, &guild);
        // passe son tours
        if (p == 0)
            tp1++;
        // fin de la partie il passe son tour 2 fois d'affilée
        if (tp1 == 2)
        {
            printf("Le player 2 a gagné !\n");
            return 0;
        }
        // joue son tour normalement
        else if (p > 0)
        {
            tp1 = 0;
        }
        // Au tour du deuxième joueur de jouer.
        pick_tokens(&player2, notre_market);
        p = possible(&player2, &pile, &guild);

        // passe son tours
        if (p == 0)
            tp2++;
        // fin de la partie il passe son tour 2 fois d'affilée
        if (tp2 == 2)
        {
            printf("Le player 1 a gagné !\n");
            return 0;
        }
        // joue son tour normalement
        else if (p > 0)
        {
            tp2 = 0;
            }
        if (nb_tours == tours_max)
        {
            printf("Personne n'a gagné, match nul \n");
            return 0;
        }
        nb_tours++;
    }
    return 0;
}
