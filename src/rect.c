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


SDL_Rect rect_to_SDL(s_rect r, double factor)
{
  s_rect scaled = rect_mult(r, factor);
  SDL_Rect out;
  out.x = round(scaled.pos.x);
  out.y = round(scaled.pos.y);
  out.w = round(scaled.size.x);
  out.h = round(scaled.size.y);
  return out;
}
