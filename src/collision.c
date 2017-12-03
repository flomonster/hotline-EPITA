#include "collision.h"
#include "game.h"
#include "vect.h"


static bool lines_intersect(s_vect *out, s_vect l1p1, s_vect l1p2, s_vect l2p1,
                            s_vect l2p2)
{
  float q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) -
            (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
  float d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) -
            (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);
  if (!d)
    return false;
  float r = q / d;
  q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) -
      (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
  float s = q / d;
  if (r < 0. || r > 1. || s < 0. || s > 1.)
    return false;
  s_vect res = vect_add(l1p1, vect_mult(vect_sub(l1p2, l1p1), r));
  out->x = res.x;
  out->y = res.y;
  return true;
}


bool sdl_rect_collision(const SDL_Rect *a, const SDL_Rect *b)
{
  return SDL_HasIntersection(&SDL_RECT(a->x - 1, a->y - 1,
                                       a->w + 2, a->h + 2),
                             &SDL_RECT(b->x - 1, b->y - 1,
                                       b->w + 2, b->h + 2));
}


bool rect_has_intersection(const s_rect *a, const s_rect *b)
{
  double a_min;
  double a_max;
  double b_min;
  double b_max;

  a_min = a->pos.x;
  a_max = a_min + a->size.x;
  b_min = b->pos.x;
  b_max = b_min + b->size.x;

  if (b_min > a_min)
    a_min = b_min;
  if (b_max < a_max)
    a_max = b_max;

  if (a_max <= a_min)
      return false;

  a_min = a->pos.y;
  a_max = a_min + a->size.y;
  b_min = b->pos.y;
  b_max = b_min + b->size.y;

  if (b_min > a_min)
    a_min = b_min;
  if (b_max < a_max)
    a_max = b_max;

  if (a_max <= a_min)
      return false;

  return true;
}


bool rect_raycast(s_vect *out, s_vect p1, s_vect p2, s_rect r)
{
  s_vect diff = vect_sub(p2, p1);
  diff = vect_mult(diff, 10000000);
  p2 = VECT(p1.x + diff.x, p1.y + diff.y);
  return lines_intersect(out, p1, p2, VECT(r.pos.x, r.pos.y),
                         VECT(r.pos.x + r.size.x, r.pos.y)) ||
         lines_intersect(out, p1, p2, VECT(r.pos.x + r.size.x, r.pos.y),
                         VECT(r.pos.x + r.size.x, r.pos.y + r.size.y)) ||
         lines_intersect(out, p1, p2, VECT(r.pos.x + r.size.x, r.pos.y + r.size.y),
                         VECT(r.pos.x, r.pos.y + r.size.y)) ||
         lines_intersect(out, p1, p2, VECT(r.pos.x, r.pos.y + r.size.y),
                         VECT(r.pos.x, r.pos.y));
}
