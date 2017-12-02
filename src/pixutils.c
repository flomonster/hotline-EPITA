#include "pixutils.h"

#include <assert.h>


static void *get_pixel_data(SDL_Surface *img, int x, int y, int *bpp)
{
    *bpp = img->format->BytesPerPixel;

    assert(*bpp == 4 || *bpp == 3);
    assert(y < img->h && x < img->w);

    Uint8 *pixdata = img->pixels;
    void *right_pixdata = pixdata + y * img->pitch + x * *bpp;
    return right_pixdata;
}

Uint32 get_pixel(SDL_Surface *img, int x, int y)
{
  int bpp;

  void *pixdata = get_pixel_data(img, x, y, &bpp);
  if (bpp == 4)
  {
    Uint32 *pdata = pixdata;
    return *pdata;
  }

  if (bpp == 3)
  {
    Uint8 *p = pixdata;
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  }
  abort();
}


void set_pixel(SDL_Surface *img, int x, int y, Uint32 val)
{
  int bpp;

  void *pixdata = get_pixel_data(img, x, y, &bpp);
  if (bpp == 4)
  {
    Uint32 *pdata = pixdata;
    *pdata = val;
  }
  else if (bpp == 3)
  {
    Uint8 *p = pixdata;
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
      p[0] = val >> 16;
      p[1] = val >> 8;
      p[2] = val;
    }
    else
    {
      p[0] = val >> 16;
      p[1] = val >> 8;
      p[2] = val;
    }
  }
  else
    abort();
}
