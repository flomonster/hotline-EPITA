#pragma once

#include "rect.h"
#include "renderer.h"
#include "vect.h"

#include <stdbool.h>


typedef struct sprite
{
  SDL_Texture *texture;
  s_vect pos;
  s_vect size;
  double angle;
} s_sprite;


void sprite_init_texture(s_sprite *s, s_renderer *r, char *text_path);
void sprite_init(s_sprite *s, s_vect pos, double angle);
void sprite_destroy(s_sprite *s);
s_rect sprite_rect(s_sprite *s, double factor);
void sprite_draw(s_sprite *s, s_renderer *r, bool rel_to_camera);
