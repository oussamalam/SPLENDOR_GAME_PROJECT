#include <stdlib.h>
#include <stdio.h>
#include "guild.h"

#define N 5

void init_guild(struct guild_t *guild)
{

  for (unsigned int i = 0; i < num_builders(); ++i)
  {
    guild->indice[i].builder = make_builder(i);
    guild->indice[i].state = 1;
    guild->indice[i].dispo = 1;
  }
}

int genererNombreAleatoire1(int min, int max)
{
  // Initialisation de la graine pour la fonction rand() en utilisant l'heure actuell

  // Calcul de la plage des nombres possibles
  int plage = max - min + 1;

  // Generation du nombre aleatoire dans la plage et ajout de l'offset min
  int nombreAleatoire = rand() % plage + min;

  return nombreAleatoire;
}

void init_pile(struct piles_t* pile)
{
  for (int i = 0; i< MAX_BUILDERS_AVAILABLE_PER_LVL; ++i)
  {
    pile->pile1.disponible[i]=NULL;
    pile->pile2.disponible[i]=NULL;
  }
  pile->pile1.size=0;
  pile->pile2.size=0;
  for (int i = 0; i< MAX_BUILDERS; ++i)
  {
    pile->pile1.level[i]=NULL;
    pile->pile2.level[i]=NULL;
  }
}


// Fonction pas réeellement utile
int get_available_builders(struct guild_t *guild)
{
  int s = 0;
  for (unsigned int i = 0; i < num_builders(); ++i)
  {
    if (guild->indice[i].state == 1)
      s++;
  }
  return s;
}

// permet de compter le nombre de builder dispo dans la guilde pour achat par level.
int count_builders(struct guild_t *guild, unsigned int level)
{
  int s = 0;
  for (unsigned int i = 0; i < num_builders(); ++i)
  {
    if (builder_level(guild->indice[i].builder) == level && guild->indice[i].dispo == 1)
      s++;
  }
  return s;
}
int count_builders_disp_by_level( struct piles_t *pile, unsigned int level)
{
  int num=0;
  if(level==1)
  {
    for(int i=0;i<MAX_BUILDERS_AVAILABLE_PER_LVL;i++)
    {
      if(pile->pile1.disponible[i]!=NULL)
      {
        num+=1;
      }
    }
  }
  if(level==2)
  {
    for(int i=0;i<MAX_BUILDERS_AVAILABLE_PER_LVL;i++)
    {
      if(pile->pile1.disponible[i]!=NULL)
      {
        num+=1;
      }
    }
  }
  return num;
}

//Permet la création de 2 piles une pour chaque niveau dont on connait la talle 
void shuffle_guild(struct guild_t *guild, unsigned int level, struct piles_t *pile)
{
  int i = 0;
  int k = count_builders(guild, level);
  while (i < k)
  {
    int l = genererNombreAleatoire1(0, num_builders() - 1);
    if (builder_level(guild->indice[l].builder) == level && guild->indice[l].dispo == 1)
    {
      guild->indice[l].dispo = 0;
      if (level == 1)
      {
        pile->pile1.level[i] = guild->indice[l].builder;
        pile->pile1.size ++;
      }
      else if (level == 2)
      {
        pile->pile2.level[i] = guild->indice[l].builder;
        pile->pile2.size ++;
      }
      ++i;
    }
  }
}

// On créée un tableau qui correspond aux builders disponibles, on ne l'utilisera qu'à l'initialisation.
void available_shop(struct piles_t *pile, unsigned int level)
{
  if (level == 1)
  {
    for (int i = 0; i < MAX_BUILDERS_AVAILABLE_PER_LVL; ++i)
    {
      if (pile->pile1.disponible[i] == NULL)
      {
        // on fait en sorte à ce qu'il n'y ait pas de souci lorsqu'il n'y a plus de builders
        if (pile->pile1.size == 0)
          return;
        else if (pile->pile1.size>0)
        {
        pile->pile1.disponible[i] = pile->pile1.level[pile->pile1.size - 1];
        pile->pile1.size--;
        }
      }
    }
}
else if(level==2)
    {   
    for (int i = 0; i < MAX_BUILDERS_AVAILABLE_PER_LVL; ++i)
{
      if (pile->pile2.disponible[i] == NULL)
        {
          if (pile->pile2.size == 0)
            return;
          else if (pile->pile1.size>0)
          {
            pile->pile2.disponible[i] = pile->pile2.level[pile->pile2.size - 1];
            pile->pile2.size--;
          }
        }
    }  
  }
}

struct guild_t *remove_builder_from_guild(const struct builder_t *b, struct guild_t *guild)
{
  for (int i = 1; i < N; ++i)
  {
    if (guild->indice[i].builder == b)
      guild->indice[i].state = 0;
  }
  return guild;
}
