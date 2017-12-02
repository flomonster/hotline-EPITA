#include "entity.h"
#include "game.h"
#include "player.h"
#include "const.h"

#include <math.h>


static void player_move(s_player *player)
{
  float dx = 0;
  float dy = 0;
  dy += player->entity.dir & DIR_TOP ? -1 : 0;
  dy += player->entity.dir & DIR_BOTTOM ? 1 : 0;
  dx += player->entity.dir & DIR_RIGHT ? 1 : 0;
  dx += player->entity.dir & DIR_LEFT ? -1 : 0;
  if (dx || dy)
  {
    s_vect dir = vect_mult(vect_normalize(VECT(dx, dy)), player->speed);
    player->entity.sprite.pos = vect_add(player->entity.sprite.pos, dir);
  }
}


void player_init(s_player *player, s_renderer *renderer, s_vect pos)
{
  player->life = 2;
  player->speed = 1;
  s_sprite sprite;
  sprite_init_texture(&sprite, renderer, "res/player.png");
  sprite_init(&sprite, pos, 0);
  entity_init(&player->entity, sprite, DIR_NONE);
}


void player_draw(s_player *player, s_renderer *renderer)
{
  sprite_draw(&player->entity.sprite, renderer);
}


void player_update(s_player *player, s_game *game)
{
  double dy = game->input.mouse_pos.y - player->entity.sprite.pos.y;
  double dx = game->input.mouse_pos.x - player->entity.sprite.pos.x;
  player->entity.sprite.angle = atan2(dy, dx) * 180. / M_PI + 90.;

  player->entity.dir = DIR_NONE;
  if (input_key_pressed(&game->input, SDL_SCANCODE_W))
    player->entity.dir |= DIR_TOP;
  if (input_key_pressed(&game->input, SDL_SCANCODE_D))
    player->entity.dir |= DIR_RIGHT;
  if (input_key_pressed(&game->input, SDL_SCANCODE_S))
    player->entity.dir |= DIR_BOTTOM;
  if (input_key_pressed(&game->input, SDL_SCANCODE_A))
    player->entity.dir |= DIR_LEFT;

  if ((player->entity.dir & DIR_LEFT) && (player->entity.dir & DIR_RIGHT))
    player->entity.dir &= ~(DIR_LEFT | DIR_RIGHT);
  if ((player->entity.dir & DIR_TOP) && (player->entity.dir & DIR_BOTTOM))
    player->entity.dir &= ~(DIR_BOTTOM | DIR_TOP);

  player_move(player);
}


void player_destroy(s_player *player)
{
  entity_destroy(&player->entity);
}
