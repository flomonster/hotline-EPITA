#pragma once

#include "vect.h"

#include <SDL.h>


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


SDL_Rect rect_to_SDL(s_rect r, double factor);
