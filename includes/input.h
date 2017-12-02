
#pragma once

#include <SDL.h>
#include <stdbool.h>


typedef struct input
{
  bool keys[1024];
} s_input;


void input_init(s_input *input);
bool input_pressed(s_input *input, SDL_Keycode code);
void input_handle_event(s_input *input, SDL_Event *event);
