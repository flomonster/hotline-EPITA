#pragma once

#include "vect.h"
#include "rect.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define RGBA(R, G, B, A)                      \
  ((SDL_Color)                                \
  {                                           \
    .r = (R),                                 \
    .g = (G),                                 \
    .b = (B),                                 \
    .a = (A),                                 \
  })

#define RGB(R, G, B) RGBA((R), (G), (B), 1.)


typedef enum text_alignment
{
  ALIGN_VLEFT = 0,
  ALIGN_VRIGHT = 1 << 1,
  ALIGN_VCENTER = 1 << 2,
  ALIGN_HTOP = 1 << 3,
  ALIGN_HBOTTOM = 1 << 4,
  ALIGN_HCENTER = 1 << 5,
} e_text_alignment;


typedef struct renderer
{
  SDL_Renderer *renderer;
  double sample_factor;
  TTF_Font *font;
  s_vect camera;
} s_renderer;


struct game;


void renderer_init(s_renderer *renderer, SDL_Window *window,
                   double sample_factor);
void renderer_destroy(s_renderer *renderer);
void renderer_init_font(s_renderer *r, char *font_name, int font_size);
void renderer_render_text(s_renderer *r, char *text, s_vect pos, SDL_Color clr,
                          e_text_alignment ta, bool rel_to_camera);
void renderer_draw(s_renderer *r);
void renderer_update(s_renderer *r, struct game *game);
s_vect renderer_absolute_to_camera(s_renderer *r, s_vect v);
s_vect renderer_camera_to_absolute(s_renderer *r, s_vect v);
s_vect renderer_project(s_renderer *r, s_vect v);
s_vect renderer_get_screen_size(s_renderer *r);
void renderer_draw_rect(s_renderer *r, s_rect rect, SDL_Color c);
void renderer_draw_line(s_renderer *r, s_vect from, s_vect to, SDL_Color c);
