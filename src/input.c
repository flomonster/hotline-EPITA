#include "input.h"
#include "const.h"

#include <SDL.h>
#include <stdbool.h>


void input_init(s_input *input)
{
  memset(input->keys, 0, sizeof (input->keys));
  input->mouse_pos.x = 0.;
  input->mouse_pos.y = 0.;
  input->left_click = false;
  input->right_click = false;
}


bool input_key_pressed(s_input *input, SDL_Keycode code)
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
  case SDL_MOUSEMOTION:
    input->mouse_pos.x = event->motion.x * 1. / SCALE_FACTOR;
    input->mouse_pos.y = event->motion.y * 1. / SCALE_FACTOR;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event->button.button == SDL_BUTTON_LEFT)
      input->left_click = true;
    if (event->button.button == SDL_BUTTON_RIGHT)
      input->right_click = true;
    break;
  case SDL_MOUSEBUTTONUP:
    if (event->button.button == SDL_BUTTON_LEFT)
      input->left_click = false;
    if (event->button.button == SDL_BUTTON_RIGHT)
      input->right_click = false;
  default:
    break;
  }
}


s_vect input_mouse_pos(s_input *input)
{
  return input->mouse_pos;
}
