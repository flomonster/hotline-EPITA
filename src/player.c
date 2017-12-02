#include "collision.h"
#include "const.h"
#include "entity.h"
#include "game.h"
#include "player.h"
#include "rect.h"
#include "walls.h"

#include <math.h>
#include <err.h>


static void player_move(s_player *player, e_dir dir, double delta)
{
  float dx = 0;
  float dy = 0;
  dy += dir & DIR_TOP ? -1 : 0;
  dy += dir & DIR_BOTTOM ? 1 : 0;
  dx += dir & DIR_RIGHT ? 1 : 0;
  dx += dir & DIR_LEFT ? -1 : 0;
  if (dx || dy)
  {
    s_vect direction = vect_mult(vect_normalize(VECT(dx, dy)),
                           player->entity.speed * delta * SAMPLE_FACTOR);
    player->entity.sprite.pos = vect_add(player->entity.sprite.pos, direction);
  }
}

static void player_shoot(s_game *game, s_player *player)
{
  s_vect p1 = player->entity.sprite.pos;
  s_vect p2 = game->input.mouse_pos;

  double dist_wall = INFINITY;
  for (s_rect_list *rlist = game->map.walls; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    float dist = vect_dist(player->entity.sprite.pos, wall_rect.pos);
    if (dist < dist_wall && rect_raycast(p1, p2, wall_rect))
      dist_wall = dist;

  }
  // TODO (Check impact with enemies)
}

static bool player_move_try(s_game *game, s_player *player, e_dir dir,
                            double delta)
{
  s_vect mem = player->entity.sprite.pos;
  player_move(player, dir, delta);
  s_rect rect = sprite_rect(&player->entity.sprite, .5);
  if (wall_collides(&game->map, &rect))
  {
    player->entity.sprite.pos = mem;
    return false;
  }
  return true;
}

void player_init(s_player *player, s_renderer *renderer, s_vect pos)
{
  s_sprite sprite;
  sprite_init_texture(&sprite, renderer, "res/player.png");
  sprite_init(&sprite, pos, 0);
  entity_init(&player->entity, sprite, 2, 15);
}


void player_draw(s_player *player, s_renderer *r, bool debug)
{
  sprite_draw(&player->entity.sprite, r);

  if (!debug)
    return;

  s_rect rect = sprite_rect(&player->entity.sprite, .5);
  s_vect top_left = renderer_project(r,
    renderer_absolute_to_camera(r, rect.pos));
  s_vect size = renderer_project(r, rect.size);
  renderer_draw_rect(r, RECT(top_left, size), RGB(255, 0, 0));
}


void player_update(s_player *player, s_game *game, double delta)
{
  s_vect d = vect_sub(
    renderer_camera_to_absolute(&game->renderer, game->input.mouse_pos),
    player->entity.sprite.pos);
  player->entity.sprite.angle = atan2(d.y, d.x) * 180. / M_PI + 90.;

  // Shoot
  if (game->input.left_click)
    player_shoot(game, player);

  // Move
  e_dir dir = DIR_NONE;
  if (input_key_pressed(&game->input, SDL_SCANCODE_W))
    dir |= DIR_TOP;
  if (input_key_pressed(&game->input, SDL_SCANCODE_D))
    dir |= DIR_RIGHT;
  if (input_key_pressed(&game->input, SDL_SCANCODE_S))
    dir |= DIR_BOTTOM;
  if (input_key_pressed(&game->input, SDL_SCANCODE_A))
    dir |= DIR_LEFT;

  if ((dir & DIR_LEFT) && (dir & DIR_RIGHT))
    dir &= ~(DIR_LEFT | DIR_RIGHT);
  if ((dir & DIR_TOP) && (dir & DIR_BOTTOM))
    dir &= ~(DIR_BOTTOM | DIR_TOP);

  if (player_move_try(game, player, dir, delta))
    return;

  if ((dir & DIR_LEFT) && player_move_try(game, player, DIR_LEFT, delta))
    return;
  if ((dir & DIR_RIGHT) && player_move_try(game, player, DIR_RIGHT, delta))
    return;
  if ((dir & DIR_TOP) && player_move_try(game, player, DIR_TOP, delta))
    return;
  if ((dir & DIR_BOTTOM) && player_move_try(game, player, DIR_BOTTOM, delta))
    return;
}


void player_destroy(s_player *player)
{
  entity_destroy(&player->entity);
}
