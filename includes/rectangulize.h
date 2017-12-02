#pragma once

#include <SDL.h>
#include <stdbool.h>

typedef bool (*f_interest)(Uint32 val);


typedef struct fill_conf
{
  f_interest interest;
  Uint32 fill_val;
} s_fill_conf;

s_rect_list *rectangulize(SDL_Surface *img, const s_fill_conf *conf);
