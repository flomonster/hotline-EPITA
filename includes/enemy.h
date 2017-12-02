#pragma once

#include "ivect_list.h"

#include <SDL.h>
#include <stddef.h>


typedef struct enemy
{
  unsigned char id;
  size_t waypoints_count;
  s_ivect_list *waypoints;
} s_enemy;


typedef struct enemy_list
{
  struct enemy enemy;
  struct enemy_list *next;
} s_enemy_list;


s_enemy_list *enemies_load(SDL_Surface *img);
