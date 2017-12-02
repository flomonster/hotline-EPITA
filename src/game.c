#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "const.h"

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
  renderer_init(&game->renderer, game->window, SAMPLE_FACTOR);
  renderer_init_font(&game->renderer, "res/hellovetica.ttf", 8);
  input_init(&game->input);
  map_init(&game->map, &game->renderer, "test");
  game->is_running = false;
  player_init(&game->player, &game->renderer, VECT(50, 50));
}


static void game_handle_event(s_game *game, SDL_Event *event)
{
  input_handle_event(&game->input, event);

  if (input_key_pressed(&game->input, SDL_SCANCODE_ESCAPE))
    game->is_running = false;

  switch (event->type)
  {
  case SDL_QUIT:
    game->is_running = false;
    break;
  default:
    break;
  }
}


static void game_draw(s_game *game)
{
  map_draw(&game->map, &game->renderer);
  player_draw(&game->player, &game->renderer);
}


static void game_update(s_game *game)
{
  player_update(&game->player, game);
}


void game_loop(s_game *game)
{
  game->is_running = true;

  uint64_t time_last = 0;
  uint64_t time_now = 0;
  double frequency = SDL_GetPerformanceFrequency();

  while (game->is_running)
  {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();
    double delta_time = (time_now - time_last) * 1000 / frequency;

    SDL_Event event;
    while (SDL_WaitEventTimeout(&event, 0))
      game_handle_event(game, &event);

    game_update(game);
    game_draw(game);
    SDL_RenderPresent(game->renderer.renderer);

    if (delta_time < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE - delta_time);
  }
}


void game_destroy(s_game *game)
{
  map_destroy(&game->map);
  renderer_destroy(&game->renderer);
  SDL_DestroyWindow(game->window);
  player_destroy(&game->player);
}
