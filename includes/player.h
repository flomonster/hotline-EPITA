#pragma once

#include "entity.h"


typedef struct player
{
  s_entity entity;
  int life;
  float speed;
} s_player;


void player_init(s_game *game, s_player *player, s_vect pos);
void player_draw(s_game *game, s_player *player);
void player_update(s_game *game, s_player *player);
void player_destroy(s_player *player);
