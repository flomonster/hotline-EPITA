#include "collision.h"
#include "const.h"
#include "enemy.h"
#include "game.h"
#include "pixutils.h"
#include "utils.h"

#include <float.h>


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
  s_vect p1 = enemy->sprite.pos;
  s_vect p2 = game->player.sprite.pos;

  double dist_wall = INFINITY;
  for (s_rect_list *rlist = game->map.walls; rlist; rlist = rlist->next)
  {
    SDL_Rect *r = &rlist->rect;
    s_rect wall_rect = RECT(VECT(r->x, r->y), VECT(r->w, r->h));
    s_vect res;
    if (rect_raycast(&res, p1, p2, wall_rect))
    {
      float dist = vect_dist(p1, res);
      if (dist < dist_wall)
        dist_wall = dist;
    }
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
  enemy_reset(enemy);
  sprite_init(&enemy->sprite_shot, renderer, "res/shot.png");
  sprite_init(&enemy->sprite_normal, renderer, "res/enemy.png");
  sprite_init(&enemy->sprite_hurt, renderer, "res/enemy-hurt.png");
}


void enemy_reset(s_enemy *enemy)
{
  enemy->lastshoot = DBL_MAX;
  enemy->nextpoint = enemy->waypoints;
  enemy->last_shot_at = DBL_MAX;
  enemy->life = 2;
  enemy->speed = 7;

  enemy->sprite = enemy->sprite_normal;

  sprite_set_pos(&enemy->sprite, VECT(enemy->waypoints->vect.x,
                 enemy->waypoints->vect.y));
  sprite_set_angle(&enemy->sprite, 0.);
  enemy->nextpoint = enemy->waypoints;
}


void enemy_draw(s_enemy *enemy, s_renderer *r, bool debug)
{
  if (!enemy->life)
    return;

  sprite_draw(&enemy->sprite, r, true);

  if (enemy->lastshoot < .1)
  {
    s_sprite sprite = enemy->sprite_shot;
    sprite_set_pos(&sprite,
      vect_add(enemy->sprite.pos, VECT(3., -35.)));
    sprite_set_angle(&sprite, enemy->sprite.angle);
    sprite_set_angle_origin(&sprite, VECT(-3., 35.));
    sprite_draw(&sprite, r, true);
  }

  if (!debug)
    return;

  s_rect rect = sprite_rect(&enemy->sprite, .5);
  s_vect top_left = renderer_project(r,
    renderer_absolute_to_camera(r, rect.pos));
  s_vect size = renderer_project(r, rect.size);
  renderer_draw_rect(r, RECT(top_left, size), RGB(255, 0, 0));
}


void enemy_update(s_enemy *enemy, s_game *game, double delta)
{
  if (!enemy->life)
    return;
  s_vect next = VECT(enemy->nextpoint->vect.x, enemy->nextpoint->vect.y);
  if (vect_dist(enemy->sprite.pos, next) < 1)
  {
    if (enemy->nextpoint->next)
      enemy->nextpoint = enemy->nextpoint->next;
    else
      enemy->nextpoint = enemy->waypoints;
    next = VECT(enemy->nextpoint->vect.x, enemy->nextpoint->vect.y);
  }

  // Shoot
  enemy->lastshoot += delta;
  enemy->last_shot_at += delta;

  float angle;
  s_vect pos;

  if (ennemy_has_shoot(enemy, game))
  {
    s_vect d = vect_sub(game->player.sprite.pos,
                        enemy->sprite.pos);
    angle = atan2(d.y, d.x) * 180. / M_PI + 90.;
    pos = enemy->sprite.pos;
    if (enemy->lastshoot > ENEMIES_LOAD_TIME)
    {
      enemy->lastshoot = 0;
      game->player.last_shot_at = 0.;
      score_hit(&game->score);
    }
  }
  else
  {
    // Rotation
    s_vect d = vect_sub(next, enemy->sprite.pos);
    angle = atan2(d.y, d.x) * 180. / M_PI + 90.;

    // Move
    s_vect dir = VECT(next.x - enemy->sprite.pos.x,
                      next.y - enemy->sprite.pos.y);
    dir = vect_mult(vect_normalize(dir),
                    enemy->speed * delta * SAMPLE_FACTOR);
    pos = vect_add(enemy->sprite.pos, dir);
  }

  enemy->sprite = enemy->last_shot_at < .1f
    ? enemy->sprite_hurt
    : enemy->sprite_normal;
  sprite_set_pos(&enemy->sprite, pos);
  sprite_set_angle(&enemy->sprite, angle);

}


void enemy_destroy(s_enemy *enemy)
{
  sprite_destroy(&enemy->sprite_normal);
  sprite_destroy(&enemy->sprite_hurt);
  sprite_destroy(&enemy->sprite_shot);
  while (enemy->waypoints)
  {
    s_ivect_list *tmp = enemy->waypoints;
    enemy->waypoints = enemy->waypoints->next;
    free(tmp);
  }
}
