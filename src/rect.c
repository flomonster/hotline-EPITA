#include "vect.h"
#include "rect.h"

#include <SDL.h>


s_rect rect_mult(s_rect r, double factor)
{
  s_rect out =
  {
    .pos = vect_mult(r.pos, factor),
    .size = vect_mult(r.size, factor),
  };
  return out;
}


SDL_Rect rect_to_SDL(s_rect r)
{
  SDL_Rect out;
  out.x = round(r.pos.x);
  out.y = round(r.pos.y);
  out.w = round(r.size.x);
  out.h = round(r.size.y);
  return out;
}
