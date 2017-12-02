#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "rect_list.h"
#include "vect.h"


typedef struct map
{
  SDL_Texture *texture;
  s_rect_list *rect_list;
  s_vect size;
} s_map;


void map_init(s_map *map, SDL_Renderer *renderer, char *name);
void map_destroy(s_map *map);
