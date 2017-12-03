#pragma once

#include "entity.h"
#include "ivect_list.h"
#include "player.h"

#include <SDL.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct enemy
{
  unsigned char id;
  size_t waypoints_count;
  s_ivect_list *waypoints;
  s_ivect_list *nextpoint;
  s_entity entity;
} s_enemy;


typedef struct enemy_list
{
  struct enemy enemy;
  struct enemy_list *next;
} s_enemy_list;


s_enemy_list *enemies_load(SDL_Surface *img);
void enemy_init(s_enemy *enemy, s_renderer *renderer, s_vect pos);
void enemy_draw(s_enemy *enemy, s_renderer *renderer, bool debug);
void enemy_update(s_enemy *enemy, s_player *player, double delta);
