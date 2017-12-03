#pragma once

#include <SDL.h>
#include <SDL_ttf.h>


typedef enum text_alignment
{
  ALIGN_VLEFT = 0,
  ALIGN_VRIGHT = 1 << 1,
  ALIGN_VCENTER = 1 << 2,
  ALIGN_HTOP = 1 << 3,
  ALIGN_HBOTTOM = 1 << 4,
  ALIGN_HCENTER = 1 << 5,
} e_text_alignment;


typedef struct font
{
  TTF_Font *font;
  SDL_Color color;
  e_text_alignment alignment;
} s_font;


void font_init(s_font *font, char *font_path, int font_size);
void font_destroy(s_font *font);
void font_set_color(s_font *font, SDL_Color color);
void font_set_alignment(s_font *font, e_text_alignment alignment);
