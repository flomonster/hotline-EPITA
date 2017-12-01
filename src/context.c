#include <stdlib.h>
#include <SDL.h>

#include "context.h"


s_context *context_init()
{
  s_context *cont = malloc(sizeof (*cont));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
    free(cont);
    return NULL;
  }

  cont->window = SDL_CreateWindow(
             "Hotline EPITA",                    // window title
              SDL_WINDOWPOS_UNDEFINED,           // initial x position
              SDL_WINDOWPOS_UNDEFINED,           // initial y position
              640,                               // width, in pixels
              480,                               // height, in pixels
              SDL_WINDOW_OPENGL                  // flags - see below
              );

  if (!cont->window)
  {
    SDL_Log("Unable to initialize window: %s\n", SDL_GetError());
    free(cont);
    return NULL;
  }

  cont->renderer = SDL_CreateRenderer(cont->window, -1,
                                      SDL_RENDERER_ACCELERATED);
  return cont;
}


void context_free(s_context *context)
{
  SDL_DestroyRenderer(context->renderer);
  SDL_DestroyWindow(context->window);
  free(context);
  SDL_Quit();
}
