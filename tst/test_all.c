#include "test_all.h"

int main()
{
  struct guild_t guild;
  struct player_t play;
  struct piles_t pile;
  init_builders(0);
  for (unsigned int i =0 ; i<NUM_COLORS; ++i)
  {
    play.colors_global_tok[i]=5;
  }
  init_guild(&guild);
  init_player(&play);
  init_pile(&pile);
  test_level();
  test_point();
  test_requires();
  test_provides();
  test_color();
  test_token();
  test_builder_in_guild(&guild);
  test_builder_unavailable(make_builder(3),&guild);
  test_token_equals();
  // test_token_m();
  // test_rm_token(t,notre_market);
  // test_available_m(t, notre_market);
  test_player(&play);
  // test_pick_token(&play, notre_market);
  //test_hire_build(&play, &guild);
  return 0;
}

