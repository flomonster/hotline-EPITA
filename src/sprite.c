#include "renderer.h"
#include "sprite.h"
#include "vect.h"
#include "rect.h"
#include "const.h"

#include <SDL.h>
#include <SDL_image.h>


void sprite_init_texture(s_sprite *s, s_renderer *r, char *text_path)
{
  SDL_Surface *image = IMG_Load(text_path);
  if (!image)
  {
    SDL_Log("IMG_load failed: %s\n", IMG_GetError());
    return;
  }
  s->texture = SDL_CreateTextureFromSurface(r->renderer, image);
  s->size = VECT(image->w, image->h);
  SDL_FreeSurface(image);
}


void sprite_init(s_sprite *s, s_vect pos, double angle)
{
  s->pos = pos;
  s->angle = angle;
}


void sprite_destroy(s_sprite *s)
{
  SDL_DestroyTexture(s->texture);
}


void sprite_draw(s_sprite *s, s_renderer *r)
{
  s_vect top_left = vect_sub(s->pos, vect_mult(s->size, .5));

  // Scale the destination to the display.
  s_rect scaled_dst = rect_mult(RECT(top_left, s->size), SCALE_FACTOR);

  // Scale to the sample factor.
  SDL_Rect src = rect_to_SDL(RECT(VECT(0, 0), s->size), r->sample_factor);
  SDL_Rect dst = rect_to_SDL(scaled_dst, r->sample_factor);
  SDL_Point ori = vect_to_SDL(s->pos, r->sample_factor);
  SDL_RenderCopyEx(r->renderer, s->texture, &src, &dst,
                   s->angle, &ori, SDL_FLIP_NONE);
}
