#pragma once

#include "entity.h"

struct game;

typedef struct player
{
  s_entity entity;
  int life;
  float speed;
} s_player;


void player_init(s_player *player, s_renderer *renderer, s_vect pos);
void player_draw(s_player *player, s_renderer *renderer);
void player_update(s_player *player, struct game *game);
void player_destroy(s_player *player);
