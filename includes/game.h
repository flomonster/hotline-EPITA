#pragma once

#include "input.h"
#include "map.h"

#include <stdbool.h>


typedef struct game
{
  SDL_Window *window;
  s_renderer renderer;
  s_input input;
  s_map map;
  bool is_running;
} s_game;


void game_init(s_game *game);
void game_loop(s_game *game);
void game_destroy(s_game *game);
