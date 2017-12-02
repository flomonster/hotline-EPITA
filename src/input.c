#include "input.h"

#include <SDL.h>
#include <stdbool.h>


void input_init(s_input *input)
{
  memset(input->keys, 0, sizeof (input->keys));
}


bool input_pressed(s_input *input, SDL_Keycode code)
{
  return input->keys[code];
}


void input_handle_event(s_input *input, SDL_Event *event)
{
  switch (event->type) {
  case SDL_KEYDOWN:
    input->keys[event->key.keysym.scancode] = true;
    break;
  case SDL_KEYUP:
    input->keys[event->key.keysym.scancode] = false;
    break;
  default:
    break;
  }
}
