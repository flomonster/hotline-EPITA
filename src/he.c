#include "context.h"


int main(int argc, char **argv)
{
  argc = argc;
  argv = argv;

  s_context *cont = context_init();

  SDL_Delay(3000);

  context_free(cont);

  return 0;
}
