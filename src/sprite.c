#include "renderer.h"
#include "sprite.h"
#include "vect.h"
#include "rect.h"
#include "const.h"

#include <SDL.h>
#include <SDL_image.h>


void sprite_init(s_sprite *s, s_renderer *r, char *text_path)
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
  s->pos = VECT(0., 0.);
  s->angle = 0;
  s->angle_orig = VECT(0., 0.);
}


void sprite_set_pos(s_sprite *s, s_vect pos)
{
  s->pos = pos;
}


void sprite_set_angle(s_sprite *s, double angle)
{
  s->angle = angle;
}


void sprite_set_angle_origin(s_sprite *s, s_vect angle_orig)
{
  s->angle_orig = angle_orig;
}


void sprite_destroy(s_sprite *s)
{
  SDL_DestroyTexture(s->texture);
}


void sprite_draw(s_sprite *s, s_renderer *r, bool rel_to_camera)
{
  s_vect half_size = vect_mult(s->size, .5);
  s_vect top_left = vect_sub(s->pos, half_size);
  if (rel_to_camera)
    top_left = renderer_absolute_to_camera(r, top_left);

  s_vect scaled_top_left = renderer_project(r, top_left);
  s_vect scaled_size = renderer_project(r, s->size);
  s_vect scaled_ori = renderer_project(r, vect_add(half_size, s->angle_orig));

  SDL_Rect src = rect_to_SDL(RECT(VECT(0, 0), s->size));
  SDL_Rect dst = rect_to_SDL(RECT(scaled_top_left, scaled_size));
  SDL_Point ori = vect_to_SDL(scaled_ori);
  SDL_RenderCopyEx(r->renderer, s->texture, &src, &dst,
                   s->angle, &ori, SDL_FLIP_NONE);
}


s_rect sprite_rect(s_sprite *s, double factor)
{
  s_vect factor_size = vect_mult(s->size, factor);
  s_vect half_size = vect_mult(factor_size, .5);
  s_vect top_left = vect_sub(s->pos, half_size);

  return RECT(top_left, factor_size);
}
