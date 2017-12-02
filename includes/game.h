#pragma once

#include "context.h"
#include "input.h"
#include "map.h"

#include <stdbool.h>


typedef struct game
{
  s_context *context;
  s_input input;
  s_map map;
  bool isRunning;
} s_game;


void game_init(s_game *game);
void game_loop(s_game *game);
void game_destroy(s_game *game);
