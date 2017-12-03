#pragma once

#include "input.h"
#include "map.h"
#include "player.h"
#include "score.h"
#include "game_over.h"

#include <stdbool.h>


typedef struct game
{
  SDL_Window *window;
  s_renderer renderer;
  s_input input;
  s_map map;
  bool is_running;
  bool debug;
  s_player player;
  s_score score;
  bool is_game_over;
  s_game_over game_over;
} s_game;


void game_init(s_game *game, const char *map_name);
void game_loop(s_game *game);
void game_destroy(s_game *game);
