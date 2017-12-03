#pragma once

#include "sprite.h"
#include "renderer.h"
#include "font.h"


typedef struct game_over
{
  s_sprite sprite_won;
  s_sprite sprite_lost;
  double score;
  double max_score;
  s_font font;
} s_game_over;


void game_over_init(s_game_over *go, s_renderer *r);
void game_over_set_score(s_game_over *go, double score, double max_score);
void game_over_draw(s_game_over *go, s_renderer *r);
void game_over_destroy(s_game_over *go);
