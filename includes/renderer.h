#pragma once

#include <SDL.h>


typedef struct renderer
{
  SDL_Renderer *renderer;
  double sample_factor;
} s_renderer;


void renderer_init(s_renderer *renderer, SDL_Window *window,
                   double sample_factor);
void renderer_destroy(s_renderer *renderer);
