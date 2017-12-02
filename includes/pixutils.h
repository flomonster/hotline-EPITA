#include <SDL.h>

#define PIX_R(Pix) ((Pix) & 0xFF)
#define PIX_G(Pix) (((Pix) >> 8) & 0xFF)
#define PIX_B(Pix) (((Pix) >> 16) & 0xFF)
#define PIX_WHITE 0xFFFFFFFF

Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 val);
