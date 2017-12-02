#pragma once

#include "vect.h"

#include <SDL.h>
#include <SDL_ttf.h>

#define RGBA(R, G, B, A)                      \
  ((SDL_Color)                                \
  {                                           \
    .r = (R),                                 \
    .g = (G),                                 \
    .b = (B),                                 \
    .a = (A),                                 \
  })

#define RGB(R, G, B) RGBA((R), (G), (B), 1.)


typedef struct renderer
{
  SDL_Renderer *renderer;
  double sample_factor;
  TTF_Font *font;
} s_renderer;


void renderer_init(s_renderer *renderer, SDL_Window *window,
                   double sample_factor);
void renderer_destroy(s_renderer *renderer);
void renderer_init_font(s_renderer *r, char *font_name, int font_size);
void renderer_render_text(s_renderer *r, char *text, s_vect pos, SDL_Color clr);
