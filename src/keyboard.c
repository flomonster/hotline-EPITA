#include "keyboard.h"

#include <SDL.h>
#include <stdbool.h>


void keyboard_init(s_keyboard *k)
{
  memset(k->keys, 0, sizeof (k->keys));
}


bool keyboard_pressed(s_keyboard *k, SDL_Keycode code)
{
  return k->keys[code];
}


void keyboard_handle_event(s_keyboard *k, SDL_Event *event)
{
  switch (event->type) {
  case SDL_KEYDOWN:
    k->keys[event->key.keysym.scancode] = true;
    break;
  case SDL_KEYUP:
    k->keys[event->key.keysym.scancode] = false;
    break;
  default:
    break;
  }
}
