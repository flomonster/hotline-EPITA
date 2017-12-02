#include "game.h"
#include "sprite.h"
#include "vect.h"
#include "rect.h"

#include <SDL.h>
#include <SDL_image.h>


void sprite_init_texture(s_sprite *s, s_game *game, char *text_path,
                         double scale)
{
  SDL_Surface *image = IMG_Load(text_path);
  if (!image)
  {
    SDL_Log("IMG_load failed: %s\n", IMG_GetError());
    return;
  }
  s->texture = SDL_CreateTextureFromSurface(game->renderer, image);
  s->size = VECT(image->w * scale, image->h * scale);
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


void sprite_draw(s_game *game, s_sprite *s)
{
  s_vect top_left = vect_sub(s->pos, vect_mult(s->size, .5));
  SDL_Rect src = rect_to_SDL(RECT(VECT(0., 0.), s->size), game->sample_factor);
  SDL_Rect dst = rect_to_SDL(RECT(top_left, s->size), game->sample_factor);
  SDL_Point ori = vect_to_SDL(s->pos, game->sample_factor);
  SDL_RenderCopyEx(game->renderer, s->texture, &src, &dst,
                   s->angle, &ori, SDL_FLIP_NONE);
}
