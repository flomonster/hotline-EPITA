#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "rect_list.h"
#include "vect.h"
#include "renderer.h"
#include "sprite.h"


typedef struct map
{
  s_sprite sprite;
  s_rect_list *rect_list;
} s_map;


void map_init(s_map *map, s_renderer *renderer, char *name);
void map_draw(s_map *map, s_renderer *renderer);
void map_destroy(s_map *map);
