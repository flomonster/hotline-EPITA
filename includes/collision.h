#pragma once

#include <SDL.h>

#include "rect.h"
#include <stdbool.h>


bool rect_has_intersection(const s_rect *A, const s_rect *B);
bool sdl_rect_collision(const SDL_Rect *A, const SDL_Rect *B);
bool rect_raycast(s_vect *out, s_vect p1, s_vect p2, s_rect r);
