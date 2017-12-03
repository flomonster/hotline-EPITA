#include "renderer.h"
#include "vect.h"
#include "rect.h"
#include "const.h"
#include "game.h"

#include <SDL.h>
#include <SDL_image.h>


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
  r->camera = VECT(0, 0);
}


void renderer_render_text(s_renderer *r, s_font *font, char *text, s_vect pos,
                          bool rel_to_camera)
{
  SDL_Surface *surf = TTF_RenderText_Blended(font->font, text, font->color);
  if (surf == NULL)
  {
    SDL_Log("Unable to render text: %s\n", TTF_GetError());
    exit(1);
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(r->renderer, surf);

  s_vect top_left = pos;
  s_vect size = VECT(surf->w, surf->h);

  if (font->alignment & ALIGN_VRIGHT)
    top_left = vect_sub(top_left, VECT(size.x, 0.));
  else if (font->alignment & ALIGN_VCENTER)
    top_left = vect_sub(top_left, VECT(size.x / 2., 0.));

  if (font->alignment & ALIGN_HBOTTOM)
    top_left = vect_sub(top_left, VECT(0., size.y));
  else if (font->alignment & ALIGN_HCENTER)
    top_left = vect_sub(top_left, VECT(0., size.y / 2.));

  if (rel_to_camera)
    top_left = renderer_absolute_to_camera(r, top_left);

  s_vect scaled_top_left = renderer_project(r, top_left);
  s_vect scaled_size = renderer_project(r, size);
  SDL_Rect dst = rect_to_SDL(RECT(scaled_top_left, scaled_size));
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


void renderer_draw_line(s_renderer *r, s_vect from, s_vect to, SDL_Color c)
{
  SDL_SetRenderDrawColor(r->renderer, c.r, c.g, c.b, c.a);
  SDL_RenderDrawLine(r->renderer, from.x, from.y, to.x, to.y);
}
