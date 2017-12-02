
#pragma once

#include "vect.h"

#include <SDL.h>
#include <stdbool.h>


typedef struct input
{
  bool keys[1024];
  bool keys_up[1024];
  bool keys_down[1024];
  bool should_quit;
  s_vect mouse_pos;
  bool left_click;
  bool right_click;
} s_input;


void input_init(s_input *input);
bool input_key_pressed(s_input *input, SDL_Keycode code);
bool input_key_down(s_input *input, SDL_Keycode code);
bool input_key_up(s_input *input, SDL_Keycode code);
bool input_should_quit(s_input *input);
void input_update(s_input *input);
s_vect input_mouse_pos(s_input *input);
