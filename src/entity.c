#include "entity.h"
#include "sprite.h"


void entity_init(s_entity *ent, s_sprite *s, e_dir dir)
{
  ent->sprite = s;
  ent->dir = dir;
}


void entity_destroy(s_entity *ent)
{
  sprite_destroy(ent->sprite);
}
