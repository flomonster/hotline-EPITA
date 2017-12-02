#include "enemy.h"
#include "utils.h"
#include "pixutils.h"


#define IS_ENEMY(PVal) (PIX_R(PVal) == 127)
#define ENEMY_ID(PVal) PIX_G(PVal)
#define ENEMY_PATH_ID(PVal) PIX_B(PVal)


static s_enemy *find_enemy(s_enemy_list *list, unsigned char id)
{
  for (s_enemy_list *cur = list; cur; cur = cur->next)
    if (id == cur->enemy.id)
      return &cur->enemy;
  return NULL;
}


static void enemy_insert_waypoint(s_enemy *e, s_ivect_list *w)
{
  s_ivect_list **ip = &e->waypoints;
  while (*ip && (*ip)->id < w->id)
    ip = &(*ip)->next;
  w->next = *ip;
  *ip = w;
}


s_enemy_list *enemies_load(SDL_Surface *img)
{
  s_enemy_list *elist = NULL;

  for (int y = 0; y < img->h; y++)
    for (int x = 0; x < img->w; x++)
    {
      Uint32 pval = get_pixel(img, x, y);
      if (IS_ENEMY(pval))
      {
        unsigned char e_id = ENEMY_ID(pval);
        s_enemy *e = find_enemy(elist, e_id);
        if (!e)
        {
          s_enemy_list *nel = xmalloc(sizeof(s_enemy_list));
          nel->next = elist;
          elist = nel;
          e = &nel->enemy;
          e->id = e_id;
          e->waypoints_count = 0;
          e->waypoints = NULL;
        }

        s_ivect_list *npoint = xmalloc(sizeof(*npoint));
        npoint->vect = IVECT(x, y);
        npoint->id = ENEMY_PATH_ID(pval);
        enemy_insert_waypoint(e, npoint);
        e->waypoints_count++;
      }
    }

  return elist;
}
