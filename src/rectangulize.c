#include "pixutils.h"
#include "rect_list.h"
#include "utils.h"
#include "rectangulize.h"

#include <SDL.h>
#include <stdbool.h>

#define PIX_EPSILON 20


static bool is_wall(SDL_Surface *img, int x, int y)
{
  Uint32 pval = get_pixel(img, x, y);
  return (PIX_R(pval) < PIX_EPSILON
          && PIX_G(pval) < PIX_EPSILON
          && PIX_B(pval) < PIX_EPSILON);
}


static s_rect_list *fill_rect(SDL_Surface *img, int x, int y)
{
  int lh = 1;
  int lw = 0;

  for (int i = x; i < img->w; i++)
    if (is_wall(img, i, y))
    {
      lw++;
      set_pixel(img, i, y, PIX_WHITE);
    }

  do {
    bool cont = true;
    for (int i = x; i < x + lw; i++)
      if (!is_wall(img, i, y + lh))
      {
        cont = false;
        break;
      }

    if (!cont)
      break;

    for (int i = x; i < x + lw; i++)
      set_pixel(img, i, y + lh, PIX_WHITE);

    lh++;
  } while (y + lh < img->h);

  s_rect_list *ret = xmalloc(sizeof(*ret));
  *ret = RECT_LIST(x, y, lw, lh);
  return ret;
}


s_rect_list *rectangulize(SDL_Surface *img)
{
  s_rect_list *res = NULL;

  for (int y = 0; y < img->h; y++)
    for (int x = 0; x < img->w; x++)
      if (is_wall(img, x, y))
      {
        s_rect_list *new = fill_rect(img, x, y);
        new->next = res;
        res = new;
      }

  return res;
}
