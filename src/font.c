
#include "font.h"
#include "renderer.h"

#include <SDL_ttf.h>


static int font_count = 0;


void font_init(s_font *font, char *font_path, int font_size)
{
  if (font_count == 0 && TTF_Init() == -1)
  {
    SDL_Log("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    exit(1);
  }

  TTF_Font *sdl_font = TTF_OpenFont(font_path, font_size);

  if (sdl_font == NULL)
  {
    SDL_Log("Unable to load font: %s\n", TTF_GetError());
    exit(1);
  }

  font_count++;

  font->font = sdl_font;
  font->color = RGB(0., 0., 0.);
  font->alignment = 0;
}


void font_destroy(s_font *font)
{
  TTF_CloseFont(font->font);
  font_count--;
  if (font_count == 0)
    TTF_Quit();
}


void font_set_color(s_font *font, SDL_Color color)
{
  font->color = color;
}


void font_set_alignment(s_font *font, e_text_alignment alignment)
{
  font->alignment = alignment;
}
