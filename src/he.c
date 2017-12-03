#include "game.h"

#include <err.h>


int main(int argc, char **argv)
{
  if (argc != 2)
    errx(1, "Usage: %s [map]", argv[0]);

  s_game game;
  game_init(&game, argv[1]);

  game_loop(&game);

  game_destroy(&game);

  return 0;
}
