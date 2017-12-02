#include "context.h"
#include "game.h"

#include <stdbool.h>

#define FRAME_RATE 60


void game_init(s_game *game)
{
  game->context = context_create();
  input_init(&game->input);
  map_init(&game->map, game->context->renderer, "test");
  game->isRunning = false;
}


static void game_handle_event(s_game *game, SDL_Event *event)
{
  input_handle_event(&game->input, event);

  if (input_key_pressed(&game->input, SDL_SCANCODE_ESCAPE))
    game->isRunning = false;

  switch (event->type)
  {
  case SDL_QUIT:
    game->isRunning = false;
    break;
  default:
    break;
  }
}


static void game_draw(s_game *game)
{
  SDL_Rect src =
  {
    .x = 0, .y = 0,
    .w = game->map.size.x, .h = game->map.size.y,
  };

  SDL_RenderCopy(game->context->renderer,
                 game->map.texture,
                 &src,
                 NULL);

  SDL_RenderPresent(game->context->renderer);
}


void game_loop(s_game *game)
{
  game->isRunning = true;

  uint64_t time_last = 0;
  uint64_t time_now = 0;
  double frequency = SDL_GetPerformanceFrequency();

  while (game->isRunning)
  {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();
    double delta_time = (time_now - time_last) * 1000 / frequency;

    SDL_Event event;
    while (SDL_WaitEventTimeout(&event, 0))
      game_handle_event(game, &event);

    game_draw(game);
    // TODO: call entities update functions

    if (delta_time < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE - delta_time);
  }
}


void game_destroy(s_game *game)
{
  context_free(game->context);
  map_destroy(&game->map);
}
