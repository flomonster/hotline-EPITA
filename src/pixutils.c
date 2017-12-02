#include "pixutils.h"

#include <assert.h>


static Uint32 *get_pixel_addr(SDL_Surface *img, int x, int y)
{
    int bpp = img->format->BytesPerPixel;
    // we will always use 4bytes deep PNGs
    assert(bpp == 4);
    assert(y < img->h && x < img->w);

    Uint8 *pixdata = img->pixels;
    void *right_pixdata = pixdata + y * img->pitch + x * bpp;
    return right_pixdata;
}

Uint32 get_pixel(SDL_Surface *img, int x, int y)
{
  return *get_pixel_addr(img, x, y);
}


void set_pixel(SDL_Surface *img, int x, int y, Uint32 val)
{
  *get_pixel_addr(img, x, y) = val;
}
