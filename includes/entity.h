#pragma once


typedef struct entity
{
  SDL_Texture *texture;
  s_vect pos;
  s_vect size;
  s_vect velocity;
  double angle;
} s_entity;


void entity_init_texture(s_entity *ent, s_context *cont, char *text_path,
                         float scale);
void entity_init(s_entity *ent, s_vect pos, s_vect velocity, double angle);
void entity_destroy(s_entity *ent);
