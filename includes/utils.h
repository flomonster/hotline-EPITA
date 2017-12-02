#pragma once

#include <stddef.h>
#include <SDL.h>


#define RECT(X, Y, W, H)                      \
  ((SDL_Rect)                                 \
  {                                           \
    .x = (X),                                 \
    .y = (Y),                                 \
    .w = (W),                                 \
    .h = (H),                                 \
  })


void *xmalloc(size_t size);
