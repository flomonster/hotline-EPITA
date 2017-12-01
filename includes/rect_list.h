#pragma once

#include <SDL.h>


typedef struct rect_list
{
  SDL_Rect data;
  struct rect_list *next;
} s_rect_list;
