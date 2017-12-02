
#pragma once

#include <SDL.h>
#include <stdbool.h>


typedef struct keyboard
{
  bool keys[1024];
} s_keyboard;


void keyboard_init(s_keyboard *k);
bool keyboard_pressed(s_keyboard *k, SDL_Keycode code);
void keyboard_handle_event(s_keyboard *k, SDL_Event *event);
