#include "collision.h"
#include "const.h"
#include "enemy.h"
#include "entity.h"
#include "game.h"
#include "pixutils.h"
#include "utils.h"


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


static bool ennemy_has_shoot(s_enemy *enemy, s_game *game)
{
  s_vect p1 = enemy->entity.sprite.pos;
  s_vect p2 = game->player.entity.sprite.pos;

  double dist_wall = INFINITY;
  for (s_rect_list *rlist = game->map.walls; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    float dist = vect_dist(p1, wall_rect.pos);
    if (dist < dist_wall && rect_raycast(p1, p2, wall_rect))
      dist_wall = dist;
  }

  float dist = vect_dist(p1, p2);
  return dist < dist_wall;
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


void enemy_init(s_enemy *enemy, s_renderer *renderer)
{
  enemy->lastshoot = 0;
  enemy->nextpoint = enemy->waypoints;
  s_sprite sprite;
  sprite_init(&sprite, renderer, "res/enemy.png");
  entity_init(&enemy->entity, sprite, 2, 7);
}


void enemy_draw(s_enemy *enemy, s_renderer *r, bool debug)
{
  if (!enemy->entity.life)
    return;

  sprite_draw(&enemy->entity.sprite, r, true);
  if (!debug)
    return;

  s_rect rect = sprite_rect(&enemy->entity.sprite, .5);
  s_vect top_left = renderer_project(r,
    renderer_absolute_to_camera(r, rect.pos));
  s_vect size = renderer_project(r, rect.size);
  renderer_draw_rect(r, RECT(top_left, size), RGB(255, 0, 0));
}


void enemy_update(s_enemy *enemy, s_game *game, double delta)
{
  if (!enemy->entity.life)
    return;
  s_vect next = VECT(enemy->nextpoint->vect.x, enemy->nextpoint->vect.y);
  if (vect_dist(enemy->entity.sprite.pos, next) < 1)
  {
    if (enemy->nextpoint->next)
      enemy->nextpoint = enemy->nextpoint->next;
    else
      enemy->nextpoint = enemy->waypoints;
    next = VECT(enemy->nextpoint->vect.x, enemy->nextpoint->vect.y);
  }

  // Shoot
  enemy->lastshoot += delta;
  if (ennemy_has_shoot(enemy, game))
  {
    s_vect d = vect_sub(game->player.entity.sprite.pos,
                        enemy->entity.sprite.pos);
    enemy->entity.sprite.angle = atan2(d.y, d.x) * 180. / M_PI + 90.;
    if (enemy->lastshoot > ENEMIES_LOAD_TIME)
    {
      enemy->lastshoot = 0;
      score_hit(&game->score);
    }
    return;
  }

  // Rotation
  s_vect d = vect_sub(next, enemy->entity.sprite.pos);
  enemy->entity.sprite.angle = atan2(d.y, d.x) * 180. / M_PI + 90.;

  // Move
  s_vect dir = VECT(next.x - enemy->entity.sprite.pos.x,
                    next.y - enemy->entity.sprite.pos.y);
  dir = vect_mult(vect_normalize(dir),
                  enemy->entity.speed * delta * SAMPLE_FACTOR);
  enemy->entity.sprite.pos = vect_add(enemy->entity.sprite.pos, dir);
}


void enemy_destroy(s_enemy *enemy)
{
  entity_destroy(&enemy->entity);
  while (enemy->waypoints)
  {
    s_ivect_list *tmp = enemy->waypoints;
    enemy->waypoints = enemy->waypoints->next;
    free(tmp);
  }
}
