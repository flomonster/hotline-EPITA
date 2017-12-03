#include "score.h"
#include "sprite.h"
#include "renderer.h"
#include "const.h"

#include <float.h>
#include <stdbool.h>
#include <stdio.h>


void score_init(s_score *score, s_renderer *r, double value)
{
  sprite_init_texture(&score->sprite, r, "res/score-background.png");
  sprite_init_texture(&score->sprite_red, r, "res/score-background-red.png");
  sprite_init(&score->sprite, VECT(-1000., -1000.), 0.);
  sprite_init(&score->sprite_red, VECT(-1000., -1000.), 0.);
  score->value = value;
  score->time_since_last_hit = DBL_MAX;
}


static bool score_invincible(s_score *score)
{
  return score->time_since_last_hit < INVINCIBILITY_FRAME;
}


static void score_decrement(s_score *score, double by)
{
  double next_score = score->value - by;
  score->value = next_score < 0. ? 0. : next_score;
}


void score_hit(s_score *score)
{
  if (score_invincible(score))
    return;
  score->time_since_last_hit = 0.;
  score_decrement(score, HIT_DAMAGE);
}


void score_update(s_score *score, double delta)
{
  score->time_since_last_hit += delta;
  score_decrement(score, delta);
}


void score_draw(s_score *score, s_renderer *r)
{
  s_vect size = renderer_get_screen_size(r);
  s_sprite sprite = score_invincible(score) ? score->sprite_red : score->sprite;
  sprite.pos = VECT(size.x - sprite.size.x / 2 - 20., sprite.size.y / 2 + 20.);
  sprite_draw(&sprite, r, false);
  char text[64];
  int value_i = score->value;
  int minutes = value_i / 60;
  int seconds = value_i % 60;
  sprintf(text, "%d:%02d", minutes, seconds);
  renderer_render_text(r, text, vect_sub(sprite.pos, VECT(21., 10.)),
    RGB(255, 255, 255));
}
