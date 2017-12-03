#pragma once

#include "renderer.h"
#include "sprite.h"
#include "font.h"


typedef struct score
{
  double value;
  double time_since_last_hit;
  s_sprite sprite;
  s_sprite sprite_red;
  s_font font;
} s_score;


void score_init(s_score *score, s_renderer *r);
void score_set_value(s_score *score, double value);
void score_hit(s_score *score);
void score_update(s_score *score, double delta);
void score_draw(s_score *score, s_renderer *r);
void score_destroy(s_score *score);
