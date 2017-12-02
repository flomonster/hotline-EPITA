#pragma once

#include "vect.h"

#include <SDL.h>


#define SDL_RECT(X, Y, W, H)                  \
  ((SDL_Rect)                                 \
  {                                           \
    .x = (X),                                 \
    .y = (Y),                                 \
    .w = (W),                                 \
    .h = (H),                                 \
  })


#define RECT(Pos, Size)                       \
  ((s_rect)                                   \
  {                                           \
    .pos = (Pos),                             \
    .size = (Size),                           \
  })


typedef struct rect
{
  s_vect pos;
  s_vect size;
} s_rect;


s_rect rect_mult(s_rect r, double factor);
SDL_Rect rect_to_SDL(s_rect r);
