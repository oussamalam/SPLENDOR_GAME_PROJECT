#include "market.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


unsigned int L[3]={0,0,0};

void test_token_m()
{ 
   struct token_t mon_token={{1,0,0,0,0}};
   assert((token_equals(notre_market[0][0].token,mon_token))== true);
}
//Probleme on ne modifie pas le bon tableau. 
void test_rm_token(struct token_t t,struct token_in_market market[5][5] )
{
   remove_token_from_market(t,market);
   assert((market[0][0].etat==0)== true);
}

void test_available_m(struct token_t t, struct token_in_market market[5][5])
{
   remove_token_from_market(t,market);
   assert((market[0][0].etat == 0) ==true); 
}
void test_availables(struct token_in_market market[5][5])
{
   get_available_tokens(market);
}
void test_aleatoire()
{
   int alea=genererNombreAleatoire(0,1);
   printf("%d",alea);
}


//le plateau
void remplire_matrice(int L[5][5])
   {
      struct point p[25];
      point_spirale(p);
      for(int l=0;l<25;++l)
      {
         L[p[l].i-1][p[l].j-1]=l+1;
      }
   }
void test_affichage_plateau()
{
   int L[5][5];
   remplire_matrice(L);
   for(int i=0;i<5;++i)
   {
      for(int j=0; j<5;++j)
      {

            if(L[i][j]<10)
            {
                printf("| %d",L[i][j]);
            }
            else
            {
                printf("|%d",L[i][j]);
            }


      }
      printf("|\n ---------------\n");
   }
}

void test_market(struct token_t t,struct token_in_market market[5][5],int L[5][5])
{
   test_token_m();
   test_rm_token(t,market );
   test_available_m(t,market);
   test_availables(market);
   test_aleatoire();
   remplire_matrice(L);
   test_affichage_plateau();
}