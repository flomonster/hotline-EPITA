#include "collision.h"
#include "walls.h"

bool wall_collides(s_map *map, s_rect *rect)
{
  for (s_rect_list *rlist = map->rect_list; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    if (rect_has_intersection(&wall_rect, rect))
      return true;
  }
  return false;
}
