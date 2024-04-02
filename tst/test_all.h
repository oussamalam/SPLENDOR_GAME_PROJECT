#ifndef __TEST_ALL_H__
#define __TEST_ALL_H__
#include "player.h"

void test_level();
void test_point();
void test_requires();
void test_provides();
void test_color();
void test_token();  
void test_builder_in_guild(struct guild_t* guild);
void test_builder_unavailable(const struct builder_t* b, struct guild_t *guild);
void test_token_equals();
void test_token_m();
void test_rm_token(struct token_t t,struct token_in_market market[5][5]);
void test_available_m(struct token_t t, struct token_in_market market[5][5]);
void test_player(struct player_t * player);
void test_pick_token(struct player_t* player, struct token_in_market market[5][5]);
void test_hire_build(struct player_t* player, struct guild_t* guild);
#endif //__TEST_ALL_H__