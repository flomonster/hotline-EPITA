#pragma once


typedef struct vect2
{
  int x;
  int y;
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
float vect_dist(s_vect a, s_vect b);
