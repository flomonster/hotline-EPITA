#pragma once

#include "input.h"
#include "map.h"

#include <stdbool.h>

#define RENDER_SCALE_FACTOR 8
#define SAMPLE_FACTOR 2


typedef struct game
{
  SDL_Window *window;
  s_renderer renderer;
  s_input input;
  s_map map;
  bool isRunning;
} s_game;


void game_init(s_game *game);
void game_loop(s_game *game);
void game_destroy(s_game *game);
