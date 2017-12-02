#include "entity.h"
#include "game.h"
#include "player.h"
#include "const.h"

#include <math.h>


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
}


void player_destroy(s_player *player)
{
  entity_destroy(&player->entity);
}
