#include "game.h"
#include "rect_list.h"
#include "utils.h"
#include "map.h"
#include "rectangulize.h"
#include "sprite.h"

#include <SDL.h>
#include <SDL_image.h>


void map_init(s_map *map, s_renderer *r, char *name)
{
  size_t len = strlen(name);
  const char pre[] = "maps/";
  const char bg_suf[] = "-background.png";
  const char layout_suf[] = "-layout.png";
  char *bg_name = malloc(sizeof (pre) + len + sizeof (bg_suf));
  char *layout_name = malloc(sizeof (pre) + len + sizeof (layout_suf));
  sprintf(bg_name, "%s%s%s", pre, name, bg_suf);
  sprintf(layout_name, "%s%s%s", pre, name, layout_suf);

  SDL_Surface *layout_surf = IMG_Load(layout_name);
  map->rect_list = rectangulize(layout_surf);

  sprite_init_texture(&map->sprite, r, bg_name);
  s_vect center_pos = vect_add(VECT(0, 0), vect_mult(map->sprite.size, 0.5));
  sprite_init(&map->sprite, center_pos, 0.);

  free(bg_name);
  free(layout_name);
}


void map_draw(s_map *map, s_renderer *renderer)
{
  sprite_draw(&map->sprite, renderer);
}


void map_destroy(s_map *map)
{
  sprite_destroy(&map->sprite);
}
