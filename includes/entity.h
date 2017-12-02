#pragma once

#include <SDL.h>

#include "sprite.h"


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


typedef struct entity
{
  e_dir dir;
  s_sprite sprite;
} s_entity;


void entity_init(s_entity *ent, s_sprite s, e_dir dir);
void entity_destroy(s_entity *ent);
