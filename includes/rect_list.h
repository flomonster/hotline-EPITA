#pragma once

#include <SDL.h>
#include <stddef.h>


typedef struct rect_list
{
  SDL_Rect rect;
  struct rect_list *next;
  size_t id;
} s_rect_list;


#define RECT_LIST(X, Y, W, H)   \
  (s_rect_list)                 \
  {                             \
    .rect =                     \
    {                           \
      .x = (X),                 \
      .y = (Y),                 \
      .w = (W),                 \
      .h = (H),                 \
    },                          \
    .next = NULL,               \
  }
