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
  s_vect angle_orig;
  double angle;
} s_sprite;


void sprite_init(s_sprite *s, s_renderer *r, char *text_path);
void sprite_set_pos(s_sprite *s, s_vect pos);
void sprite_set_angle(s_sprite *s, double angle);
void sprite_set_angle_origin(s_sprite *s, s_vect orig);
void sprite_destroy(s_sprite *s);
s_rect sprite_rect(s_sprite *s, double factor);
void sprite_draw(s_sprite *s, s_renderer *r, bool rel_to_camera);
