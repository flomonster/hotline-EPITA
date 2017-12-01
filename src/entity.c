#include <SDL.h>
#include <SDL_image.h>

#include "entity.h"


void entity_init_texture(s_entity *ent, s_context *cont, char *text_path,
                         float scale)
{
  SDL_Surface *image = IMG_Load(text_path);
  if (!image)
  {
    SDL_Log("IMG_load failed: %s\n", IMG_GetError());
    return;
  }
  ent->texture = SDL_CreateTextureFromSurface(cont->renderer, image);
  ent->size = VECT(image->w * scale, image->h * scale);
  SDL_FreeSurface(image);
}


void entity_init(s_entity *ent, s_vect pos, e_dir dir, double angle)
{
  ent->pos = pos;
  ent->dir = dir;
  ent->angle = angle;
}


void entity_destroy(s_entity *ent)
{
  SDL_DestroyTexture(ent->texture);
}
