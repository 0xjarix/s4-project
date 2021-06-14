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
    int s = height*width;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Uint32 pixel = get_pixel1(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red += r;//==255?0:r);
            green += g;// ==255?0:g);
            blu += b;// == 255?0:b);
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

void overlay (SDL_Surface* image_surface, SDL_Surface* logo)
{
    int hi = image_surface->h;
    int wi = image_surface->w;
    int hl = logo->h;
    int wl = logo->h;
    int sl = wl*hl;
    int red [sl];
    int green [sl];
    int blu [sl];
    int c = 0;
    for (int i = wl; i > 0; i--)
    {
        for (int j = hl; j > 0; j--)
        {
            Uint32 pixel = get_pixel1(logo, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, logo->format, &r, &g, &b);
            red[c]=r;
            green[c]=g;
            blu[c]=b;
            c++;
        }
    }
    if (hl==wl)
    {
        for (int i = 0; i < wi; i++)
        {
            for (int j = 0; j < hi; j++)
            {
                Uint32 pixel = get_pixel1(image_surface, i, j);
                Uint8 r, g, b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                if (c!=0 && (i >= wi/2.7 && i <= wi-wi/2.7) &&(j>=hi/2.7 &&
                            j <= hi-hi/2.7))
                {
                    r = red[c];
                    g = green[c];
                    b = blu[c];
                    Uint32 _pixel = SDL_MapRGB(image_surface->format, r, g, b);
                    put_pixel1(image_surface, i, j, _pixel);
                    c--;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < wi; i++)
        {
            for (int j = 0; j < hi; j++)
            {
                Uint32 pixel = get_pixel1(image_surface, i, j);
                Uint8 r, g, b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                if (c!=0 && (j>=hi/2.2 && j <= hi-hi/2.2))
                {
                    r = red[c];
                    g = green[c];
                    b = blu[c];
                    Uint32 _pixel = SDL_MapRGB(image_surface->format, r, g, b);
                    put_pixel1(image_surface, i, j, _pixel);
                    c--;
                }
           }
        }
    }
}

void color_average(SDL_Surface* image_surface, SDL_Surface* logo)
{
    unsigned int* average = average_color(logo);
    int w = image_surface->w;
    int h = image_surface->h;
    for(int x = 0; x < h; x++)//for each pixel, steps
        {
            for(int y = 0; y < w; y++)
            {
                Uint32 pixel = get_pixel1(image_surface, x, y);
                Uint8 r, g, b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                if ((r != 255)&&(g != 255)&&(b != 255))
                //if(binarisationArray[y+x*w] == 1)
                {
                    r = average[0];
                    g = average[1];
                    b = average[2];
                    Uint32 _pixel = SDL_MapRGB(image_surface->format, r, g, b);
                    put_pixel1(image_surface, x, y, _pixel);
                }
            }
        }
}

void res(SDL_Surface* logo, int x, int y)
{
    int w = logo->w;
    int h = logo->h;
    SDL_Surface * image_surface = NULL;
    for(int i = 0; i<w; i++)
    {
        for(int j = 0; j<h; j++)
        {
            Uint32 pixel = get_pixel1(logo, i*(w/x), j*(h/y));
            Uint8 r, g, b;
            Uint8 red, green, blu;
            SDL_GetRGB(pixel, logo->format, &r, &g, &b);
            red = r;
            green = g;
            blu = b;
            Uint32 _pixel = SDL_MapRGB(image_surface->format, red, green, blu);
            put_pixel1(image_surface, i, j, _pixel);
       }
    }
}

void custom(int argc, char* argv[])
{
    if (argc != 3) {
        return;
    }
     SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    init_sdl1();
    image_surface = load_image1(argv[1]);
    //screen_surface = display_image(image_surface);//image display
    SDL_Surface* logo = load_image1(argv[2]);
//    int w = image_surface->w;
//    int h = image_surface->h;
//    wait_for_keypressed();//wait for a key to be pressed
//    res(logo, w/4, h/4);
//    screen_surface = display_image(logo);
    //wait_for_keypressed();//wait for a key to be pressed
    screen_surface = display_image1(image_surface);//image display
    //wait_for_keypressed();//wait for a key to be pressed
    color_average(image_surface, logo);//moyenne des couleurs
    update_surface1(screen_surface, image_surface);
    //wait_for_keypressed();//wait for a key to be pressed
    overlay(image_surface, logo);//logo au centre du qr code
    update_surface1(screen_surface, image_surface);
    wait_for_keypressed1();//wait for a key to be pressed
    SDL_FreeSurface(image_surface);//freeing the image surface
    SDL_FreeSurface(screen_surface);//freeing the screen surface
}


/*int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        err(1, "arg error");
    }
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    init_sdl();
    image_surface = load_image(argv[1]);
    //screen_surface = display_image(image_surface);//image display
    SDL_Surface* logo = load_image(argv[2]);
//    int w = image_surface->w;
//    int h = image_surface->h;
//    wait_for_keypressed();//wait for a key to be pressed
//    res(logo, w/4, h/4);
//    screen_surface = display_image(logo);
    wait_for_keypressed();//wait for a key to be pressed
    screen_surface = display_image(image_surface);//image display
    wait_for_keypressed();//wait for a key to be pressed
    color_average(image_surface, logo);//moyenne des couleurs
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();//wait for a key to be pressed
    overlay (image_surface, logo);//logo au centre du qr code
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();//wait for a key to be pressed
    SDL_FreeSurface(image_surface);//freeing the image surface
    SDL_FreeSurface(screen_surface);//freeing the screen surface
    return 0;
}*/

