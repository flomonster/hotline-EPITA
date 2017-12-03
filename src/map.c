#include "game.h"
#include "rect_list.h"
#include "utils.h"
#include "map.h"
#include "rectangulize.h"
#include "sprite.h"
#include "rect.h"
#include "const.h"
#include "walls.h"
#include "enemy.h"

#include <err.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>




void map_init(s_map *map, s_renderer *r, const char *name)
{
  size_t len = strlen(name);
  const char pre[] = "maps/";
  const char bg_suf[] = "-background.png";
  const char layout_suf[] = "-layout.png";
  char *bg_name = malloc(sizeof (pre) + len + sizeof (bg_suf));
  char *layout_name = malloc(sizeof (pre) + len + sizeof (layout_suf));
  sprintf(bg_name, "%s%s%s", pre, name, bg_suf);
  sprintf(layout_name, "%s%s%s", pre, name, layout_suf);

  map->layout_surf = IMG_Load(layout_name);
  map->walls = wall_find(map->layout_surf);
  map->enemies = enemies_load(map->layout_surf);
  sprite_init_texture(&map->sprite, r, bg_name);
  s_vect center_pos = vect_add(VECT(0, 0), vect_mult(map->sprite.size, 0.5));
  sprite_init(&map->sprite, center_pos, 0.);

  free(bg_name);
  free(layout_name);
}


void map_draw(s_map *map, s_renderer *r, bool debug)
{
  sprite_draw(&map->sprite, r, true);

  if (!debug)
    return;

  for (s_rect_list *rect = map->walls; rect; rect = rect->next)
  {
    const SDL_Rect *map_rect = &rect->rect;
    s_vect top_left = renderer_project(r,
      renderer_absolute_to_camera(r, VECT(map_rect->x, map_rect->y)));
    s_vect size = renderer_project(r, VECT(map_rect->w, map_rect->h));
    renderer_draw_rect(r, RECT(top_left, size), RGB(255, 0, 0));
  }
}


void map_destroy(s_map *map)
{
  sprite_destroy(&map->sprite);
}
