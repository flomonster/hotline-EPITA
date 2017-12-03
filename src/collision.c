#include "collision.h"
#include "game.h"
#include "vect.h"


static bool lines_intersect(s_vect l1p1, s_vect l1p2, s_vect l2p1, s_vect l2p2)
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
  return r >= 0 && r <= 1 && s >= 0 && s <= 1;
}


bool sdl_rect_collision(const SDL_Rect *A, const SDL_Rect *B)
{
  return SDL_HasIntersection(&SDL_RECT(A->x - 1, A->y - 1,
                                       A->w + 2, A->h + 2),
                             &SDL_RECT(B->x - 1, B->y - 1,
                                       B->w + 2, B->h + 2));
}


bool rect_has_intersection(const s_rect *A, const s_rect *B)
{
  double Amin;
  double Amax;
  double Bmin;
  double Bmax;

  Amin = A->pos.x;
  Amax = Amin + A->size.x;
  Bmin = B->pos.x;
  Bmax = Bmin + B->size.x;

  if (Bmin > Amin)
      Amin = Bmin;
  if (Bmax < Amax)
      Amax = Bmax;

  if (Amax <= Amin)
      return false;

  Amin = A->pos.y;
  Amax = Amin + A->size.y;
  Bmin = B->pos.y;
  Bmax = Bmin + B->size.y;

  if (Bmin > Amin)
      Amin = Bmin;
  if (Bmax < Amax)
      Amax = Bmax;

  if (Amax <= Amin)
      return false;

  return true;
}


bool rect_raycast(s_vect p1, s_vect p2, s_rect r)
{
  s_vect diff = vect_sub(p2, p1);
  diff = vect_mult(diff, 10000000);
  p2 = VECT(p1.x + diff.x, p1.y + diff.y);
  return lines_intersect(p1, p2, VECT(r.pos.x, r.pos.y),
                         VECT(r.pos.x + r.size.x, r.pos.y)) ||
         lines_intersect(p1, p2, VECT(r.pos.x + r.size.x, r.pos.y),
                         VECT(r.pos.x + r.size.x, r.pos.y + r.size.y)) ||
         lines_intersect(p1, p2, VECT(r.pos.x + r.size.x, r.pos.y + r.size.y),
                         VECT(r.pos.x, r.pos.y + r.size.y)) ||
         lines_intersect(p1, p2, VECT(r.pos.x, r.pos.y + r.size.y),
                         VECT(r.pos.x, r.pos.y));
}
