#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "const.h"
#include "score.h"
#include "pixutils.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <err.h>

#define FRAME_RATE 60


static SDL_Window *window_create(void)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Window *window = SDL_CreateWindow(
             "Hotline EPITA",                    // window title
              SDL_WINDOWPOS_UNDEFINED,           // initial x position
              SDL_WINDOWPOS_UNDEFINED,           // initial y position
              1000,                               // width, in pixels
              1000,                               // height, in pixels
              SDL_WINDOW_OPENGL                  // flags - see below
              );

  if (!window)
  {
    SDL_Log("Unable to initialize window: %s\n", SDL_GetError());
    return NULL;
  }

  return window;
}


void game_init(s_game *game, const char *map_name)
{
  game->window = window_create();
  game->debug = false;
  renderer_init(&game->renderer, game->window, SAMPLE_FACTOR);
  input_init(&game->input);
  map_init(&game->map, &game->renderer, map_name);
  game->is_running = false;
  player_init(&game->player, &game->renderer);
  score_init(&game->score, &game->renderer);

  s_enemy_list *enemy = game->map.enemies;
  while (enemy)
  {
    enemy_init(&enemy->enemy, &game->renderer);
    enemy = enemy->next;
  }

  game_over_init(&game->game_over, &game->renderer);
}


void game_destroy(s_game *game)
{
  map_destroy(&game->map);
  renderer_destroy(&game->renderer);
  SDL_DestroyWindow(game->window);
  player_destroy(&game->player);
  game_over_destroy(&game->game_over);
  score_destroy(&game->score);
}


static double game_find_duration(s_map *map)
{
  SDL_Surface *img = map->layout_surf;
  for (int y = 0; y < img->h; y++)
    for (int x = 0; x < img->w; x++)
    {
      Uint32 pix = get_pixel(img, x, y);
      if (PIX_R(pix) == 84)
        return PIX_G(pix);
    }
  errx(1, "couldn't find any duration on the map");
}


void game_start(s_game *game)
{
  game->is_game_over = false;
  score_reset(&game->score, game_find_duration(&game->map));
  player_reset(&game->player, player_find_pos(&game->map));

  s_enemy_list *enemy = game->map.enemies;
  while (enemy)
  {
    enemy_reset(&enemy->enemy);
    enemy = enemy->next;
  }
}


static void game_draw(s_game *game)
{
  SDL_SetRenderDrawColor(game->renderer.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer.renderer);

  if (game->is_game_over)
  {
    game_over_draw(&game->game_over, &game->renderer);
    return;
  }

  map_draw(&game->map, &game->renderer, game->debug);
  player_draw(&game->player, &game->renderer, game->debug);
  score_draw(&game->score, &game->renderer);

  s_enemy_list *enemy = game->map.enemies;
  while (enemy)
  {
    enemy_draw(&enemy->enemy, &game->renderer, game->debug);
    enemy = enemy->next;
  }
}


static bool game_is_finished(s_game *game)
{
  s_enemy_list *el = game->map.enemies;
  while (el)
  {
    if (el->enemy.life)
      return false;
    el = el->next;
  }
  return true;
}


static void game_update(s_game *game, double delta)
{
  input_update(&game->input);

  if (input_should_quit(&game->input)
      || input_key_down(&game->input, SDL_SCANCODE_ESCAPE))
    game->is_running = false;

  if (input_key_down(&game->input, SDL_SCANCODE_TAB))
    game->debug = !game->debug;

  if (game->is_game_over)
  {
    if (input_key_down(&game->input, SDL_SCANCODE_SPACE))
      game_start(game);
    return;
  }

  player_update(&game->player, game, delta);

  s_enemy_list *enemy = game->map.enemies;
  while (enemy)
  {
    enemy_update(&enemy->enemy, game, delta);
    enemy = enemy->next;
  }

  score_update(&game->score, delta);

  if (game->score.value == 0. || game_is_finished(game))
  {
    game->is_game_over = true;
    game_over_set_score(&game->game_over, game->score.value,
                        game_find_duration(&game->map));
  }

  renderer_update(&game->renderer, game);
}


void game_loop(s_game *game)
{
  game->is_running = true;
  game_start(game);

  uint64_t time_last = 0;
  uint64_t time_now = SDL_GetPerformanceCounter();
  double frequency = SDL_GetPerformanceFrequency();

  while (game->is_running)
  {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();
    double delta = (time_now - time_last) / frequency;

    game_update(game, delta);
    game_draw(game);
    renderer_draw(&game->renderer);

    // In order for the game to sleep most of the time, so it doesn't take
    // 100% CPU.
    SDL_Delay(1);
  }
}
