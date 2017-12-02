#pragma once

#include "map.h"
#include "rect.h"

#include <stdbool.h>
#include "rect_list.h"


bool wall_collides(s_map *map, s_rect *rect);
s_rect_list *wall_find(SDL_Surface *img);
