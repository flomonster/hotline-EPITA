#include "renderer.h"
#include "vect.h"
#include "rect.h"
#include "const.h"
#include "game.h"

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
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "anisotropic");
  r->renderer = renderer;
  r->sample_factor = sample_factor;
  r->font = NULL;
  r->camera = VECT(0, 0);
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
  SDL_Surface *surf = TTF_RenderText_Blended(r->font, text, clr);
  if (surf == NULL)
  {
    SDL_Log("Unable to render text: %s\n", TTF_GetError());
    exit(1);
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(r->renderer, surf);

  s_vect top_left = renderer_project(r, pos);
  s_vect size = renderer_project(r, VECT(surf->w, surf->h));
  SDL_Rect dst = rect_to_SDL(RECT(top_left, size));
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


void renderer_update(s_renderer *r, s_game *game)
{
  r->camera = game->player.entity.sprite.pos;
}


s_vect renderer_get_screen_size(s_renderer *r)
{
  int w;
  int h;
  SDL_GetRendererOutputSize(r->renderer, &w, &h);
  return VECT(w, h);
}


s_vect renderer_absolute_to_camera(s_renderer *r, s_vect v)
{
  return vect_add(vect_sub(v, r->camera),
                  vect_mult(renderer_get_screen_size(r), .5));
}


s_vect renderer_camera_to_absolute(s_renderer *r, s_vect v)
{
  int w;
  int h;
  SDL_GetRendererOutputSize(r->renderer, &w, &h);

 return vect_sub(vect_add(v, r->camera), VECT(w / 2., h / 2.));
}


s_vect renderer_project(s_renderer *r, s_vect v)
{
  return vect_mult(v, SCALE_FACTOR * r->sample_factor);
}


void renderer_draw_rect(s_renderer *r, s_rect rect, SDL_Color c)
{
  SDL_Rect sdl_rect = rect_to_SDL(rect);
  SDL_SetRenderDrawColor(r->renderer, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(r->renderer, &sdl_rect);
}
