#include "context.h"
#include "game.h"

#include <stdbool.h>

#define FRAME_RATE 60


void game_init(s_game *game)
{
  game->context = context_create();
  game->isRunning = false;
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

    // TODO

    if (delta_time < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE - delta_time);
  }
}


void game_destroy(s_game *game)
{
  context_free(game->context);
}
