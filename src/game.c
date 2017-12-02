#include "context.h"
#include "game.h"

#include <stdbool.h>

#define FRAME_RATE 60


void game_init(s_game *game)
{
  game->context = context_create();
  keyboard_init(&game->keyboard);
  game->isRunning = false;
}


static void game_handle_event(s_game *game, SDL_Event *event)
{
  keyboard_handle_event(&game->keyboard, event);

  switch (event->type)
  {
  case SDL_QUIT:
    game->isRunning = false;
    break;
  default:
    break;
  }
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

    // TODO: call entities update functions

    if (delta_time < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE - delta_time);
  }
}


void game_destroy(s_game *game)
{
  context_free(game->context);
}
