#include <stdio.h>
#include <stdlib.h>
#include "builder.h"
#include <time.h>
#include "market.h"


struct builder_t
{
  unsigned int level;
  unsigned int points;
  struct buildcost_t requires;
  struct buildcost_t provides;
};

struct builder_t builders[MAX_BUILDERS];

void init_builders(unsigned int seed)
{
  srand(seed);
  //on va mettre le premier builer à la main pour les tests
  for (unsigned int i =0; i<MAX_BUILDERS; ++i)
  {
  builders[i].level = genererNombreAleatoire(1, NUM_LEVELS);
  builders[i].points = genererNombreAleatoire(1, 4);
  builders[i].provides.c = genererNombreAleatoire(0, NUM_COLORS - 1);
  builders[i].provides.n = genererNombreAleatoire(1, 3);
  builders[i].requires.c = genererNombreAleatoire(0, NUM_COLORS - 1);
  builders[i].requires.n = genererNombreAleatoire(1, 3);

  }
}

unsigned int num_builders()
{
  int i=0;
  while (builders[i].provides.n!=0)
  {
    i++;
  }
  if (i>MAX_BUILDERS)
    return MAX_BUILDERS;
  else
    return i;
}

struct builder_t *make_builder(unsigned int index)
{ 
      return &builders[index];    
}
  unsigned int builder_level(const struct builder_t *g)
  {
    return g->level;
  }

  unsigned int builder_points(const struct builder_t *g)
  {
    return g->points;
  }

  struct buildcost_t builder_requires(const struct builder_t *g)
  {
    return g->requires;
  }

  struct buildcost_t builder_provides(const struct builder_t *g)
  {
    return g->provides;
  }
  /* const char* color_to_short_string(enum color_t c); */
  /* int coll[MAX_COLORS]={30,34,32,31,97,33,37,36,35,31}; */

  void builder_display(const struct builder_t *g, const char *prefix)
  {
    printf("%s", prefix);
    printf("Builder (lvl=%d,", builder_level(g));
    printf("cost=%d%s,", builder_requires(g).n, color_to_short_string(builder_requires(g).c));
    printf("prod=%d%s)\n", builder_provides(g).n, color_to_short_string(builder_provides(g).c));
  }
