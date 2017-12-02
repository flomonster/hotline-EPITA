#pragma once

#include <SDL.h>

#include "sprite.h"


typedef struct entity
{
  int life;
  float speed;
  s_sprite sprite;
} s_entity;


void entity_init(s_entity *ent, s_sprite s, int life, float speed);
void entity_destroy(s_entity *ent);
