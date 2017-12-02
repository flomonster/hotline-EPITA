#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "const.h"
#include "score.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

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
              640,                               // width, in pixels
              480,                               // height, in pixels
              SDL_WINDOW_OPENGL                  // flags - see below
              );

  if (!window)
  {
    SDL_Log("Unable to initialize window: %s\n", SDL_GetError());
    return NULL;
  }

  return window;
}


void game_init(s_game *game)
{
  game->window = window_create();
  game->debug = false;
  renderer_init(&game->renderer, game->window, SAMPLE_FACTOR);
  renderer_init_font(&game->renderer, "res/font.ttf", 20);
  input_init(&game->input);
  map_init(&game->map, &game->renderer, "fourth-floor");
  game->is_running = false;
  player_init(&game->player, &game->renderer, player_find_pos(&game->map));
  score_init(&game->score, &game->renderer, 60.);
}


static void game_draw(s_game *game)
{
  SDL_SetRenderDrawColor(game->renderer.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer.renderer);
  map_draw(&game->map, &game->renderer, game->debug);
  player_draw(&game->player, &game->renderer, game->debug);
  score_draw(&game->score, &game->renderer);
}


static void game_update(s_game *game, double delta)
{
  input_update(&game->input);

  if (input_should_quit(&game->input)
      || input_key_down(&game->input, SDL_SCANCODE_ESCAPE))
    game->is_running = false;

  if (input_key_down(&game->input, SDL_SCANCODE_TAB))
    game->debug = !game->debug;

  player_update(&game->player, game, delta);

  score_update(&game->score, delta);

  renderer_update(&game->renderer, game);
}


void game_loop(s_game *game)
{
  game->is_running = true;

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
  }
}


void game_destroy(s_game *game)
{
  map_destroy(&game->map);
  renderer_destroy(&game->renderer);
  SDL_DestroyWindow(game->window);
  player_destroy(&game->player);
}
