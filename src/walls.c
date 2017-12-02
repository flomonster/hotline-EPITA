#include "collision.h"
#include "walls.h"
#include "rectangulize.h"

#include <SDL.h>
#include <SDL_image.h>

#include "pixutils.h"

#define PIX_EPSILON 20


static bool is_wall(Uint32 pval)
{
  return (PIX_R(pval) < PIX_EPSILON
          && PIX_G(pval) < PIX_EPSILON
          && PIX_B(pval) < PIX_EPSILON);
}


s_rect_list *wall_find(SDL_Surface *img)
{
  const s_fill_conf wall_find_conf =
  {
    .interest = is_wall,
    .fill_val = 0x00001100,
  };
  return rectangulize(img, &wall_find_conf);
}


bool wall_collides(s_map *map, s_rect *rect)
{
  for (s_rect_list *rlist = map->walls; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    if (rect_has_intersection(&wall_rect, rect))
      return true;
  }
  return false;
}
