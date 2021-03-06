#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "rect_list.h"
#include "vect.h"
#include "renderer.h"
#include "sprite.h"
#include "enemy.h"


typedef struct map
{
  s_sprite sprite;
  s_rect_list *walls;
  s_enemy_list *enemies;
  SDL_Surface *layout_surf;
} s_map;


void map_init(s_map *map, s_renderer *renderer, const char *name);
void map_draw(s_map *map, s_renderer *renderer, bool debug);
void map_destroy(s_map *map);
