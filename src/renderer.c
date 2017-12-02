#include "renderer.h"

#include <SDL.h>
#include <SDL_image.h>


void renderer_init(s_renderer *r, SDL_Window *window,
                   double sample_factor)
{
  if (!IMG_Init(IMG_INIT_PNG))
  {
    SDL_Log("Unable to initialize SDL_Image: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                             SDL_RENDERER_ACCELERATED);

  r->renderer = renderer;
  r->sample_factor = sample_factor;
}


void renderer_destroy(s_renderer *r)
{
  SDL_DestroyRenderer(r->renderer);
}
