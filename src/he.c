#include "context.h"


int main(int argc, char **argv)
{
  argc = argc;
  argv = argv;

  s_context *cont = context_create();



  SDL_Delay(10000);

  context_free(cont);

  return 0;
}
