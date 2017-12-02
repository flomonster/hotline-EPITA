#include <SDL.h>

#define PIX_R(Pix) ((Pix) & 0xFF)
#define PIX_G(Pix) ((Pix) & 0xFF << 8)
#define PIX_B(Pix) ((Pix) & 0xFF << 16)
#define PIX_WHITE 0xFFFFFFFF

Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 val);
