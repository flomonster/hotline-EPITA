#include "input.h"
#include "const.h"

#include <SDL.h>
#include <stdbool.h>


static void input_reset_keys(s_input *input)
{
  memset(input->keys_down, 0, sizeof (input->keys_down));
  memset(input->keys_up, 0, sizeof (input->keys_up));
}


void input_init(s_input *input)
{
  memset(input->keys, 0, sizeof (input->keys));
  input_reset_keys(input);
  input->mouse_pos.x = 0.;
  input->mouse_pos.y = 0.;
  input->left_click = false;
  input->right_click = false;
  input->should_quit = false;
}


bool input_key_pressed(s_input *input, SDL_Keycode code)
{
  return input->keys[code];
}


bool input_key_up(s_input *input, SDL_Keycode code)
{
  return input->keys_up[code];
}


bool input_key_down(s_input *input, SDL_Keycode code)
{
  return input->keys_down[code];
}


bool input_should_quit(s_input *input)
{
  return input->should_quit;
}


static void input_handle_event(s_input *input, SDL_Event *event)
{
  switch (event->type) {
  case SDL_QUIT:
    input->should_quit = true;
    break;
  case SDL_KEYDOWN:
    input->keys[event->key.keysym.scancode] = true;
    input->keys_down[event->key.keysym.scancode] = true;
    break;
  case SDL_KEYUP:
    input->keys[event->key.keysym.scancode] = false;
    input->keys_up[event->key.keysym.scancode] = true;
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


void input_update(s_input *input)
{
  input_reset_keys(input);

  SDL_Event event;
  while (SDL_WaitEventTimeout(&event, 0))
    input_handle_event(input, &event);
}


s_vect input_mouse_pos(s_input *input)
{
  return input->mouse_pos;
}
