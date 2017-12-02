#pragma once

#include <SDL.h>

#include "rect.h"
#include <stdbool.h>


bool rect_has_intersection(const s_rect *A, const s_rect *B);
