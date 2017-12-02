#pragma once

#include "ivect.h"


typedef struct ivect_list
{
  struct ivect_list *next;
  unsigned char id;
  s_ivect vect;
} s_ivect_list;


#define IVECT_LIST(X, Y) \
  (s_ivect_list)         \
  {                      \
    .vect =              \
    {                    \
      .x = (X),          \
      .y = (Y),          \
    },                   \
  }
