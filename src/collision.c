#include <SDL.h>

#include "entity.h"


SDL_Rect entity_rect(s_entity *entity)
{
  SDL_Rect out;
  out.x = entity->pos.x - entity->size.x;
  out.y = entity->pos.y - entity->size.y;
  out.w = entity->size.x;
  out.h = entity->size.y;
  return out;
}
