#pragma once

#include <SDL.h>

#include "context.h"
#include "vect.h"


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
  SDL_Texture *texture;
  s_vect pos;
  s_vect size;
  e_dir dir;
  double angle;
} s_entity;


void entity_init_texture(s_entity *ent, s_context *cont, char *text_path,
                         float scale);
void entity_init(s_entity *ent, s_vect pos, e_dir dir, double angle);
void entity_destroy(s_entity *ent);
SDL_Rect entity_rect(s_entity *entity);
