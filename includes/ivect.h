#pragma once


typedef struct ivect
{
  int x;
  int y;
} s_ivect;


#define IVECT(X, Y) \
  ((s_ivect)        \
  {                 \
    .x = (X),       \
    .y = (Y)        \
  })
