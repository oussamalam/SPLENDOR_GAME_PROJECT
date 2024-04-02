#include "project2.h"
#include <stdio.h>
#include <stdlib.h>
#define VICTORY_POINTS 20
#define MAX_TURNS 100

int main()
{
    struct guild_t guild;
    struct piles_t pile;
    struct player_t *player1;
    struct player_t *player2;
    init_player(player1);
    init_player(player2);
    init_market(notre_market);
    init_pile(&pile);
    shuffle_guild(&guild, 1,&pile);
    shuffle_guild(&guild, 2,&pile);
    available_shop(&pile,1);
    available_shop(&pile,2);
    int etat_de_jeu_player1;
    int etat_de_jeu_player2;
    int tours=0;
    while( player1->victory_points_of_player<VICTORY_POINTS && player1->victory_points_of_player<VICTORY_POINTS && tours< MAX_TURNS )
    {
        etat_de_jeu_player1=jouer(player1,&pile,&guild);
        if(player1->victory_points_of_player > VICTORY_POINTS)
        {
            printf("le premier joueur a gagné");
            return 0;
        }
        etat_de_jeu_player2=jouer(player1,&pile,&guild);
        if(player2->victory_points_of_player>VICTORY_POINTS)
        {
            printf("le deuxieme joueur a gagné");
            return 0;
        }
        tours++;
        if(etat_de_jeu_player1==0 && etat_de_jeu_player2==0) 
        {
            printf("MATCH NULL");
            break;//le jeu est terminé si aucum joueur a joué dans un tour
        }            
    }
    if(player1->victory_points_of_player > player2->victory_points_of_player)
    {
        printf("le premier joueur a gagné");
        return 0;
    }
    else if(player2->victory_points_of_player > player1->victory_points_of_player)
    {
        printf("le deuxieme joueur a gagné");
        return 0;
    }
    else
    {
        printf("egalité entre les deux joueurs");
        return 0;
    }
}

int  jouer(struct player_t *player,struct piles_t *pile,struct guild_t* guild)//etat de jeux qui sera retourne =1 si le joueur a joue et 0 si il a passé son tour
{
    int etat_de_jeu=1;
    int nbr_poss_embauche = possible(player,pile, guild);//retourne le nombre de builders possibles pour l'embauche et aussi rempli la liste bd_possible par les positions de builders possibles pour l'embaucge dans la guild
    if(nbr_poss_embauche!=0)
    {
        int j=genererNombreAleatoire(1,2);
        if(j==1 && count_builders_disp_by_level(pile,1)>0)
        {
            int l=genererNombreAleatoire(0,count_builders_disp_by_level(pile,1)-1);
            hire_builder(player,pile->pile1.disponible[l],guild);
            player->victory_points_of_player+=builder_points(pile->pile1.disponible[l]);
            etat_de_jeu=1;
        }

    }
    else if(player->num_tokens<PLAYER_MAX_TOKENS)
    {
        pick_tokens(player, notre_market);
            
    }
    else
    {
        etat_de_jeu=0;//le joueur passe son tour
    }
    return etat_de_jeu;
}