#pragma once


typedef struct sprite
{
  SDL_Texture *texture;
  s_vect pos;
  s_vect size;
  double angle;
} s_sprite;


void sprite_init_texture(s_sprite *s, s_game *game, char *text_path,
                         double scale);
void sprite_init(s_sprite *s, s_vect pos, double angle);
void sprite_destroy(s_sprite *s);
SDL_Rect sprite_rect(s_sprite *s);
void sprite_draw(s_game *game, s_sprite *s);
