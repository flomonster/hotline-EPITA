#include "collision.h"
#include "game.h"


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
