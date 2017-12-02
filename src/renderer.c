#include "renderer.h"

#include "vect.h"
#include "rect.h"
#include "const.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


void renderer_init(s_renderer *r, SDL_Window *window,
                   double sample_factor)
{
  if (!IMG_Init(IMG_INIT_PNG))
  {
    SDL_Log("Unable to initialize SDL_Image: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                             SDL_RENDERER_ACCELERATED);
  SDL_RenderSetScale(renderer, 1. / sample_factor, 1. / sample_factor);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
  r->renderer = renderer;
  r->sample_factor = sample_factor;
  r->font = NULL;
}


void renderer_init_font(s_renderer *r, char *font_name, int font_size)
{
  if (TTF_Init() == -1)
  {
    SDL_Log("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    exit(1);
  }

  TTF_Font *font = TTF_OpenFont(font_name, font_size);

  if (font == NULL)
  {
    SDL_Log("Unable to load font: %s\n", TTF_GetError());
    exit(1);
  }

  r->font = font;
}


void renderer_render_text(s_renderer *r, char *text, s_vect pos, SDL_Color clr)
{
  SDL_Surface *surf = TTF_RenderText_Solid(r->font, text, clr);
  if (surf == NULL)
  {
    SDL_Log("Unable to render text: %s\n", TTF_GetError());
    exit(1);
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(r->renderer, surf);

  SDL_Rect dst = rect_to_SDL(
    rect_mult(RECT(pos, VECT(surf->w, surf->h)), SCALE_FACTOR),
    r->sample_factor);
  SDL_RenderCopy(r->renderer, tex, NULL, &dst);

  SDL_FreeSurface(surf);
  SDL_DestroyTexture(tex);
}


void renderer_draw(s_renderer *r)
{
  SDL_RenderPresent(r->renderer);
}


void renderer_destroy(s_renderer *r)
{
  SDL_DestroyRenderer(r->renderer);
  IMG_Quit();
  if (r->font != NULL)
  {
    TTF_CloseFont(r->font);
    TTF_Quit();
  }
}
