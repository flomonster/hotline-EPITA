#pragma once

#include "map.h"

#include <SDL.h>


typedef struct context
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} s_context;


s_context *context_create(void);
void context_free(s_context *context);
