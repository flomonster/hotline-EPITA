#pragma once

#include "ivect_list.h"
#include "player.h"

#include <SDL.h>
#include <stddef.h>
#include <stdbool.h>

struct game;


typedef struct enemy
{
  unsigned char id;
  size_t waypoints_count;
  s_ivect_list *waypoints;
  s_ivect_list *nextpoint;
  float lastshoot;
  s_sprite sprite;
  s_sprite sprite_normal;
  s_sprite sprite_hurt;
  s_sprite sprite_shot;
  double last_shot_at;
  double life;
  double speed;
} s_enemy;


typedef struct enemy_list
{
  struct enemy enemy;
  struct enemy_list *next;
} s_enemy_list;


s_enemy_list *enemies_load(SDL_Surface *img);
void enemy_init(s_enemy *enemy, s_renderer *renderer);
void enemy_draw(s_enemy *enemy, s_renderer *renderer, bool debug);
void enemy_update(s_enemy *enemy, struct game *game, double delta);
void enemy_reset(s_enemy *enemy);
