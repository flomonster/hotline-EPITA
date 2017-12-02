#include "entity.h"
#include "sprite.h"


void entity_init(s_entity *ent, s_sprite s, int life, float speed)
{
  ent->sprite = s;
  ent->life = life;
  ent->speed = speed;
}


void entity_destroy(s_entity *ent)
{
  sprite_destroy(&ent->sprite);
}
