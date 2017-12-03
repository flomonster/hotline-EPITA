#include "score.h"
#include "sprite.h"
#include "renderer.h"
#include "const.h"
#include "game_over.h"

#include <stdio.h>
#include <stdbool.h>


void game_over_init(s_game_over *go, s_renderer *r)
{
  sprite_init(&go->sprite_won, r, "res/game-over-won.png");
  sprite_init(&go->sprite_lost, r, "res/game-over-lost.png");
  go->score = 0.;
}


void game_over_set_score(s_game_over *go, double score)
{
  go->score = score;
}


void game_over_draw(s_game_over *go, s_renderer *r)
{
  bool won = go->score > 0.;
  s_sprite sprite = won ? go->sprite_won : go->sprite_lost;
  s_vect size = renderer_get_screen_size(r);
  s_vect center = vect_mult(size, .5);
  sprite_set_pos(&sprite, center);
  sprite_draw(&sprite, r, false);

  if (!won)
    return;

  char text[64];
  int value_i = go->score;
  int minutes = value_i / 60;
  int seconds = value_i % 60;
  sprintf(text, "%d:%02d", minutes, seconds);
  renderer_render_text(r, text, vect_add(center, VECT(0, 60.)),
    RGB(255, 255, 255), ALIGN_VCENTER | ALIGN_HCENTER, false);
}
