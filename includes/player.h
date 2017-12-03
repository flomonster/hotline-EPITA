#pragma once

#include "sprite.h"

struct game;
struct map;

typedef enum dir
{
  DIR_NONE = 0,
  DIR_RIGHT = 1 << 0,
  DIR_TOP = 1 << 1,
  DIR_LEFT = 1 << 2,
  DIR_BOTTOM = 1 << 3,
  DIR_TOP_RIGHT = DIR_TOP | DIR_RIGHT,
  DIR_TOP_LEFT = DIR_TOP | DIR_LEFT,
  DIR_BOTTOM_RIGHT = DIR_BOTTOM | DIR_RIGHT,
  DIR_BOTTOM_LEFT = DIR_BOTTOM | DIR_LEFT,
} e_dir;


typedef struct player
{
  double speed;
  float lastshoot;
  s_sprite sprite;
  s_sprite sprite_normal;
  s_sprite sprite_hurt;
  s_sprite sprite_shot;
  double last_shot_at;
} s_player;


s_vect player_find_pos(struct map *map);
void player_init(s_player *player, s_renderer *renderer);
void player_reset(s_player *player, s_vect pos);
void player_draw(s_player *player, s_renderer *renderer, bool debug);
void player_update(s_player *player, struct game *game, double delta);
void player_destroy(s_player *player);
