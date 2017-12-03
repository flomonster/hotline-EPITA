#pragma once

#include "sprite.h"
#include "renderer.h"


typedef struct game_over
{
  s_sprite sprite_won;
  s_sprite sprite_lost;
  double score;
} s_game_over;


void game_over_init(s_game_over *go, s_renderer *r);
void game_over_set_score(s_game_over *go, double score);
void game_over_draw(s_game_over *go, s_renderer *r);
