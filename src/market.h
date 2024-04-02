#ifndef __MARKET_H__
#define __MARKET_H__

#include "token.h"
#define MARKET_SIZE 25
struct point
{
    int i;
    int j;
};

struct token_in_market{
    struct token_t token;
    struct point pos ;
    int etat;                                                        //l'etat=1 si le token est disponible dans le market et =0 si non
    int a;                           // couleur du token 
    unsigned int n;             // valeur correspondante à sa couleur(ressources sur le token)
};

//liste_des_tokens_initiales avec leurs etats 
void init_market(struct token_in_market market[5][5]);
void point_spirale(struct point p[25]);

void  get_available_tokens(struct token_in_market market[5][5]);

void remove_token_from_market(struct token_t token, struct token_in_market market[5][5]);
void remetre_token_in_market(struct token_t t,struct token_in_market market[5][5]);
//Va permettre de déterminer la couleur d'un token 

unsigned int  define_token_value(struct token_t token);

int  define_token_color(struct token_t token);

int is_complex(struct token_t token, struct token_in_market market[5][5]);

void gener_tok(struct point L[3],struct token_in_market  market[5][5]);//une fonction qui permet de prendre trois tokens du marchet d'une maniere aleatoire(on prend les positions)

extern struct token_in_market notre_market[5][5];

int genererNombreAleatoire(int min, int max);


#endif // __MARKET_H__
