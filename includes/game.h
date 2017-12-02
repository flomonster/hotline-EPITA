#pragma once

#include "context.h"
#include "keyboard.h"

#include <stdbool.h>


typedef struct game
{
  s_context *context;
  s_keyboard keyboard;
  bool isRunning;
} s_game;


void game_init(s_game *game);
void game_loop(s_game *game);
void game_destroy(s_game *game);
