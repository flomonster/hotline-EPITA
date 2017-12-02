#include "player.h"
#include "entity.h"

#include <math.h>


void player_init(s_game *game, s_player *player, s_vect pos)
{
  player->life = 2;
  player->speed = 1;
  s_sprite sprite;
  sprite_init_texture(&sprite, &game->renderer, "res/player.png", 1);
  sprite_init(&sprite, pos, 0);
  entity_init(&player->entity, sprite, DIR_NONE);
}


void player_draw(s_game *game, s_player *player)
{
  game = game;
  player = player;
  // TODO
}


void player_update(s_game *game, s_player *player)
{
  double dy = game->input.mouse_pos.y - player->entity.sprite.pos.y;
  double dx = game->input.mouse_pos.x - player->entity.sprite.pos.x;
  player->entity.sprite.angle = atan2(dy, dx);
}


void player_destroy(s_player *player)
{
  entity_destroy(&player->entity);
}
