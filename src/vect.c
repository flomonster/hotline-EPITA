#include <math.h>

#include "vect.h"


s_vect vect_add(s_vect a, s_vect b)
{
  return VECT(a.x + b.x,
              a.y + b.y);
}


s_vect vect_sub(s_vect a, s_vect b)
{
  return VECT(a.x - b.x,
              a.y - b.y);
}


double vect_dist(s_vect a, s_vect b)
{
  s_vect v = vect_sub(b, a);
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}


s_vect vect_mult(s_vect a, double s)
{
  return VECT(a.x * s, a.y * s);
}
