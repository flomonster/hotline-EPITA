#include "game.h"


int main(int argc, char **argv)
{
  argc = argc;
  argv = argv;

  s_game game;
  game_init(&game);

  game_loop(&game);

  game_destroy(&game);

  return 0;
}
