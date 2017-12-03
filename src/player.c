#include "collision.h"
#include "const.h"
#include "game.h"
#include "player.h"
#include "rect.h"
#include "walls.h"
#include "pixutils.h"

#include <math.h>
#include <err.h>
#include <float.h>


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
                           player->speed * delta * SAMPLE_FACTOR);
    player->sprite.pos = vect_add(player->sprite.pos, direction);
  }
}

static void player_shoot(s_game *game, s_player *player)
{
  s_vect p1 = player->sprite.pos;
  s_vect p2 = renderer_camera_to_absolute(&game->renderer,
                                          game->input.mouse_pos);

  double dist_wall = INFINITY;
  for (s_rect_list *rlist = game->map.walls; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    s_vect res;
    if (rect_raycast(&res, p1, p2, wall_rect))
    {
      float dist = vect_dist(p1, res);
      if (dist < dist_wall)
        dist_wall = dist;
    }
  }

  s_enemy *enemy = NULL;
  s_enemy_list *el = game->map.enemies;
  while (el)
  {
    s_rect enemy_rect = sprite_rect(&el->enemy.sprite, .5);
    s_vect res;
    if (el->enemy.life && rect_raycast(&res, p1, p2, enemy_rect))
    {
      float dist = vect_dist(p1, res);
      if (dist < dist_wall)
      {
        enemy = &el->enemy;
        dist_wall = dist;
      }
    }
    el = el->next;
  }
  if (enemy)
  {
    enemy->life--;
    enemy->last_shot_at = 0.;
  }
}

static bool player_move_try(s_game *game, s_player *player, e_dir dir,
                            double delta)
{
  s_vect mem = player->sprite.pos;
  player_move(player, dir, delta);
  s_rect rect = sprite_rect(&player->sprite, .5);
  if (wall_collides(&game->map, &rect))
  {
    player->sprite.pos = mem;
    return false;
  }
  return true;
}


s_vect player_find_pos(s_map *map)
{
  SDL_Surface *img = map->layout_surf;
  for (int y = 0; y < img->h; y++)
    for (int x = 0; x < img->w; x++)
    {
      if (get_pixel(img, x, y) == 0xff0000ff)
        return VECT(x, y);
    }
  errx(1, "couldn't find any played on the map");
}


void player_init(s_player *player, s_renderer *renderer)
{
  sprite_init(&player->sprite_normal, renderer, "res/player.png");
  sprite_init(&player->sprite_hurt, renderer, "res/player-hurt.png");
  sprite_init(&player->sprite_shot, renderer, "res/shot.png");
  player_reset(player, VECT(0., 0.));
}


void player_reset(s_player *player, s_vect pos)
{
  player->lastshoot = DBL_MAX;
  player->last_shot_at = DBL_MAX;
  player->speed = 25;
  player->sprite = player->sprite_normal;

  sprite_set_angle(&player->sprite, 0.);
  sprite_set_pos(&player->sprite, pos);
}


void player_draw(s_player *player, s_renderer *r, bool debug)
{
  sprite_draw(&player->sprite, r, true);

  if (player->lastshoot < .1)
  {
    s_sprite sprite = player->sprite_shot;
    sprite_set_pos(&sprite,
      vect_add(player->sprite.pos, VECT(11., -32.)));
    sprite_set_angle(&sprite, player->sprite.angle);
    sprite_set_angle_origin(&sprite, VECT(-11., 32.));
    sprite_draw(&sprite, r, true);
  }

  if (!debug)
    return;

  s_rect rect = sprite_rect(&player->sprite, .5);
  s_vect top_left = renderer_project(r,
    renderer_absolute_to_camera(r, rect.pos));
  s_vect size = renderer_project(r, rect.size);
  renderer_draw_rect(r, RECT(top_left, size), RGB(255, 0, 0));
}


void player_update(s_player *player, s_game *game, double delta)
{
  s_vect d = vect_sub(
    renderer_camera_to_absolute(&game->renderer, game->input.mouse_pos),
    player->sprite.pos);
  player->sprite.angle = atan2(d.y, d.x) * 180. / M_PI + 90.;

  // Shoot
  player->lastshoot += delta;
  player->last_shot_at += delta;
  if (player->lastshoot > PLAYER_LOAD_TIME && game->input.left_click)
  {
    player_shoot(game, player);
    player->lastshoot = 0;
  }

  double angle = player->sprite.angle;
  s_vect pos = player->sprite.pos;
  player->sprite = player->last_shot_at < .1
    ? player->sprite_hurt
    : player->sprite_normal;
  sprite_set_angle(&player->sprite, angle);
  sprite_set_pos(&player->sprite, pos);

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
  sprite_destroy(&player->sprite_normal);
  sprite_destroy(&player->sprite_hurt);
  sprite_destroy(&player->sprite_shot);
}
