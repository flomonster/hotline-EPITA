#pragma once


typedef struct vect2
{
  double x;
  double y;
} s_vect2;


#define VECT(X, Y)                            \
  ((s_vect)                                   \
  {                                           \
    .x = (X),                                 \
    .y = (Y)                                  \
  })

typedef s_vect2 s_vect;

s_vect vect_add(s_vect a, s_vect b);
s_vect vect_sub(s_vect a, s_vect b);
double vect_dist(s_vect a, s_vect b);
s_vect vect_mult(s_vect a, double s);
