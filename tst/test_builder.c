#include "builder.h"
#include <assert.h>
#include <stdbool.h>


void test_level()
{
  const struct builder_t* b= make_builder(0);
  assert((builder_level(b)==1)== true);
}

void test_point()
{
  const struct builder_t* b= make_builder(0);
  assert ((builder_points(b)==4) == true);
}
void test_requires()
{
  const struct builder_t* b = make_builder(0);
  assert ((builder_requires(b).c == BLUE) == true);
  assert ((builder_requires(b).n == 1) == true);
}

void test_provides()
{ 
  const struct builder_t* b = make_builder(0);
  assert ((builder_provides(b).c == BLACK) == true);
  assert ((builder_provides(b).n == 2) == true);
}
void test_display()
{
  const struct builder_t *g = make_builder(2);
  builder_display(g,"---");
}


