#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H

# include "SDL/SDL.h"
# include "SDL/SDL_image.h"

Uint32 get_pixel1(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel1(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface1(SDL_Surface* screen, SDL_Surface* image);
Uint8* pixel_ref1(SDL_Surface *surf, unsigned x, unsigned y);
void init_sdl1();
SDL_Surface* load_image1(char *path);
SDL_Surface* display_image1(SDL_Surface *img);
void wait_for_keypressed1();


#endif
