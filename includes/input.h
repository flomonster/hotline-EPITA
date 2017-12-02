
#pragma once

#include "vect.h"

#include <SDL.h>
#include <stdbool.h>


typedef struct input
{
  bool keys[1024];
  s_vect mouse_pos;
} s_input;


void input_init(s_input *input);
bool input_key_pressed(s_input *input, SDL_Keycode code);
void input_handle_event(s_input *input, SDL_Event *event);
s_vect input_mouse_pos(s_input *input);
