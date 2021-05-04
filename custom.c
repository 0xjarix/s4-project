#include <err.h>
#include "SDL_tools.h"
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "processing.h"
unsigned int* average_color(SDL_Surface* image_surface)
{
    static unsigned int rgb[3];
    int height = image_surface->h;
    int width = image_surface->w;
    unsigned int red = 0;
    unsigned int green = 0;
    unsigned int blu = 0;
    int s = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red += r;//==255?0:r;
            green += g;//==255?0:g;
            blu += b;//==255?0:b;
            s++;
        }
    }
    red /= s;
    green /= s;
    blu /= s;
    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blu;
    return rgb;
}
/*
SDL_surface* rescale(SDL_surface* qr, SDL_surface logo)
{*/
    
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        err(1, "arg error");
    }
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    init_sdl();
    
    image_surface = load_image(argv[1]);
    screen_surface = display_image(image_surface);//image display
    SDL_Surface* image_surface2 = load_image(argv[2]);
    unsigned int* average = average_color(image_surface2);
    printf("r=%d\ng=%d\nb=%d\n",average[0], average[1], average[2]);
    wait_for_keypressed();//wait for a key to be pressed

    int w = image_surface->w;
    int h = image_surface->h;
    //int* greyscale = malloc(w*h*sizeof(int));
    //grayscale(image_surface, greyscale);
    //int* binarisationArray = malloc(w*h*sizeof(int));
    //binarisation(image_surface, binarisationArray, greyscale);
    for(int x = 0; x < h; x++)//for each pixel, steps
    {
	    for(int y = 0; y < w; y++)
	    {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if ((r != 255)&&(g != 255)&&(b != 255))
            //if(binarisationArray[y+x*w] == 1)
            {
	            r = average[0];
	            g = average[1];
	            b = average[2];
	            Uint32 _pixel = SDL_MapRGB(image_surface->format, r, g, b);
	            put_pixel(image_surface, x, y, _pixel);
            }
	    }
    }
    update_surface(screen_surface, image_surface);//redrawing the surfaces

    wait_for_keypressed();//wait for a key to be pressed

    SDL_FreeSurface(image_surface);//freeing the image surface
    SDL_FreeSurface(screen_surface);//freeing the screen surface

    return 0;
}
