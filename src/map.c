#include "rect_list.h"
#include "utils.h"
#include "map.h"
#include "rectangulize.h"

#include <SDL.h>
#include <SDL_image.h>


void map_init(s_map *map, SDL_Renderer *renderer, char *name)
{
  size_t len = strlen(name);
  const char pre[] = "maps/";
  const char bg_suf[] = "-background.png";
  const char layout_suf[] = "-layout.png";
  char *bg_name = malloc(sizeof (pre) + len + sizeof (bg_suf));
  char *layout_name = malloc(sizeof (pre) + len + sizeof (layout_suf));
  sprintf(bg_name, "%s%s%s", pre, name, bg_suf);
  sprintf(layout_name, "%s%s%s", pre, name, layout_suf);
  SDL_Surface *bg_surf = IMG_Load(bg_name);
  SDL_Surface *layout_surf = IMG_Load(layout_name);
  free(bg_name);
  free(layout_name);
  // map->rect_list = rectangulize(layout_surf);
  map->texture = SDL_CreateTextureFromSurface(renderer, bg_surf);
  map->size.x = bg_surf->w;
  map->size.y = bg_surf->h;
  SDL_FreeSurface(layout_surf);
  SDL_FreeSurface(bg_surf);
}
