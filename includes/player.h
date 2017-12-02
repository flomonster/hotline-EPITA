#pragma once

#include "entity.h"

struct game;

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
  s_entity entity;
} s_player;


void player_init(s_player *player, s_renderer *renderer, s_vect pos);
void player_draw(s_player *player, s_renderer *renderer, bool debug);
void player_update(s_player *player, struct game *game, double delta);
void player_destroy(s_player *player);
