#include <stdlib.h>
#include <stdio.h>
#include "market.h"
#include <time.h>

struct token_in_market notre_market[5][5];

struct token_t liste[MARKET_SIZE]={{{1, 0, 0, 0, 0}},{{0, 1, 0, 0, 0}},{{0, 0, 1, 0, 0}},{{0, 0, 0, 1, 0}},{{0, 0, 0, 0, 1}},{{2, 0, 0, 0, 0}},{{0, 2, 0, 0, 0}},{{0, 0, 2, 0, 0}},{{0, 0, 0, 2, 0}},{{0, 0, 0, 0, 2}},{{1, 0, 0, 0, 0}},{{0, 1, 0, 0, 0}},{{0, 0, 1, 0, 0}},{{0, 0, 0, 1, 0}},{{0, 0, 0, 0, 1}},{{2, 0, 0, 0, 0}},{{0, 2, 0, 0, 0}},{{0, 0, 2, 0, 0}},{{0, 0, 0, 2, 0}},{{0, 0, 0, 0, 2}},{{2, 0, 0, 0, 0}},{{0, 2, 0, 0, 0}},{{0, 0, 2, 0, 0}},{{0, 0, 0, 2, 0}},{{0, 0, 0, 0, 2}}};//la on va mettre une liste de 25 tokens à mettre sur le marchet}
void init_market(struct token_in_market market[5][5])
{
  struct point p[25];
  point_spirale(p);
  for(int l=0; l<MARKET_SIZE;++l)
  {
      int i=p[l].i;
      int j=p[l].j;
      
      market[i][j].token=liste[l];
      market[i][j].pos=p[l];
      market[i][j].etat=1;
      market[i][j].a=define_token_color(liste[l]);
      market[i][j].n=define_token_value(liste[l]);
      
  }
}
void remetre_token_in_market(struct token_t t,struct token_in_market market[5][5])
{
  struct point p[25];
  point_spirale(p);
  for(int k=0; k<25;k++)
  {
    if (market[p[k].i][p[k].j].etat==0)
    {
        market[p[k].i][p[k].j].token = t;
        break;
    }
  }
}
void point_spirale(struct point p[25])//liste de 25 points qui soit remplipar  les points à partir de (3,3)  et dans l'ordre de spirale
{
    int ordre_ligne[4]={0,-1,0,1};
    int ordre_colonne[4]={-1,0,1,0};//1er couple (0,-1) definit un deplacement vers la gauche   2eme couple deplacement haut 3eme droite 4eme bas
    int ligne_actuelle=3;
    int colonne_actuelle=3;
    int dep_act=0; //0 parceque en premier temps on va effectuer un deplacement à gauche qui correspont à l'indice 0
    p[0].i=3;
    p[0].j=3; //nombre de points remplie dans la liste p en paramétre
    int indice_remplissage=1;
      for(int j=1;j<5;++j)
      {
        for(int i=0;i<j;++i)
        {
          p[indice_remplissage].i=ligne_actuelle+ordre_ligne[dep_act];
          p[indice_remplissage].j=colonne_actuelle+ordre_colonne[dep_act];
          indice_remplissage++;
          ligne_actuelle=ligne_actuelle+ordre_ligne[dep_act];
          colonne_actuelle=colonne_actuelle+ordre_colonne[dep_act];
        }
        dep_act=(dep_act+1)%4;

        for(int i=0;i<j;++i)
        {
          p[indice_remplissage].i=ligne_actuelle+ordre_ligne[dep_act];
          p[indice_remplissage].j=colonne_actuelle+ordre_colonne[dep_act];
          indice_remplissage++;
          ligne_actuelle=ligne_actuelle+ordre_ligne[dep_act];
          colonne_actuelle=colonne_actuelle+ordre_colonne[dep_act];

        }
        dep_act=(dep_act+1)%4;
        if(j==4)
        {
            for(int i=0;i<j;++i)
            {
            p[indice_remplissage].i=ligne_actuelle+ordre_ligne[dep_act];
            p[indice_remplissage].j=colonne_actuelle+ordre_colonne[dep_act];
            indice_remplissage++;
            ligne_actuelle=ligne_actuelle+ordre_ligne[dep_act];
            colonne_actuelle=colonne_actuelle+ordre_colonne[dep_act];

            }
        }
      }

    }

void get_available_tokens(struct token_in_market market[5][5])
{
  struct point p[25];
  point_spirale(p);
  for (int l = 0; l < MARKET_SIZE; ++l)
  {
    int i=p[l].i - 1;
    int j=p[l].j - 1;
    if (market[i][j].etat == 1)
    {
      token_display(market[i][j].token, "");
    }
  }
}

void remove_token_from_market(struct token_t token, struct token_in_market market[5][5])
{
  
  struct point p[25];
  point_spirale(p);
  for (int l = 0; l< MARKET_SIZE; l++)
  {
    int i=p[l].i-1;
    int j=p[l].j-1;
    if (token_equals((market[i][j]).token, token))
    {
      (market[i][j]).etat = 0;
      break;//ce break pour ne pas supprimer 2 tokens egaux à "token" en parametre du market 
    }
  }
}

// les 2 prochains fncts fonctionnent  qu'avec des tokens monochromes créer une structure peux corriger le pb ou un tableau pour les couleurs


//retourne les ressources sur le token
unsigned int  define_token_value(struct token_t token)
{
   int n;
   for (unsigned int i = 0; i < NUM_COLORS; ++i)
    if(token.c[i]!=0)
    {
      n=token.c[i];
      break;
    }
  return n;
}
//retourne la couleur du token
int  define_token_color(struct token_t token)
{
  unsigned int a;
  for (unsigned int i = 0; i < NUM_COLORS; ++i)
    if(token.c[i]!=0)
    {
      a=i;
      break;
    }
  return a;
}




//fonction qui genere 3 tokens aleatoires à partir du marché en mettant leurs positions dans la liste L en parametre par effets de bord
void gener_tok(struct point L[3],struct token_in_market  market[5][5])
{
  int k = 0;//ce cas va nous permettre de predre exactement 3tokens
  while (k < 3)
  {
    int i = genererNombreAleatoire(0,4);
    int j = genererNombreAleatoire(0,4);
    if (market[i][j].etat == 1)
    {
      L[k] = market[i][j].pos;
      k++;
    }
  }
}
// Fonction pour g�n�rer un nombre al�atoire dans un intervalle [min, max]
int genererNombreAleatoire(int min, int max)
 {
    // Initialisation de la graine pour la fonction rand() en utilisant l'heure actuell


    // Calcul de la plage des nombres possibles
    int plage = max - min + 1;

    // Generation du nombre aleatoire dans la plage et ajout de l'offset min
    int nombreAleatoire = rand() % plage + min;

    return nombreAleatoire;
} 
