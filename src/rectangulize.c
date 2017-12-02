#include "pixutils.h"
#include "rect_list.h"
#include "utils.h"
#include "rectangulize.h"

#include <SDL.h>
#include <stdbool.h>


static bool is_interesting(SDL_Surface *img, int x, int y,
                           const s_fill_conf *conf)
{
  return conf->interest(get_pixel(img, x, y));
}


static s_rect_list *fill_rect(SDL_Surface *img, int x, int y,
                              const s_fill_conf *conf)
{
  int lh = 1;
  int lw = 0;

  for (int i = x; i < img->w; i++)
  {
    if (!is_interesting(img, i, y, conf))
      break;
    lw++;
    set_pixel(img, i, y, conf->fill_val);
  }

  do {
    bool cont = true;
    for (int i = x; i < x + lw; i++)
      if (!is_interesting(img, i, y + lh, conf))
      {
        cont = false;
        break;
      }

    if (!cont)
      break;

    for (int i = x; i < x + lw; i++)
      set_pixel(img, i, y + lh, conf->fill_val);

    lh++;
  } while (y + lh < img->h);

  s_rect_list *ret = xmalloc(sizeof(*ret));
  *ret = RECT_LIST(x, y, lw, lh);
  return ret;
}


s_rect_list *rectangulize(SDL_Surface *img, const s_fill_conf *conf)
{
  s_rect_list *res = NULL;

  for (int y = 0; y < img->h; y++)
    for (int x = 0; x < img->w; x++)
      if (is_interesting(img, x, y, conf))
      {
        s_rect_list *new = fill_rect(img, x, y, conf);
        new->next = res;
        res = new;
      }

  return res;
}
