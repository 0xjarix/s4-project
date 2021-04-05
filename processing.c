#include <err.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_tools.h"

//SDL TOOLS
/*int init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        return 0;
    }//errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    return 1;
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;
    img = IMG_Load(path);
    if(!img){
        exit(1);
    }
    return img;
}

//static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}


Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);
    
    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;
            
        case 2:
            return *(Uint16 *)p;
            
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            
        case 4:
            return *(Uint32 *)p;
    }
    
    return 0;
}*/
//1st step: binarization
int grayscale(SDL_Surface* image_surface, int* grayscale_image)
{
    int height = image_surface->h;
    int width = image_surface->w;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            grayscale_image[i+width*j] = average;
        }
    }
    return 0;
}

double calculateV2(double v, int* greyscale, int size)
{
    double d = 0;
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        if (greyscale[i]>v)
        {
                d += greyscale[i];
                counter++;
        }
    }
    return d/counter;
}

double calculateV1(double v, int* greyscale, int size)
{
    double d = 0;
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        if (greyscale[i]<=v)
        {
                d += greyscale[i];
                counter++;
        }
    }
    return d/counter;
}

void binarisation(SDL_Surface* image_surface, int* binarisation,  int* greyscale)
{
    int w = image_surface->w;
    int h = image_surface->h;
    int size = h*w;

    double o = 128;
    double v2 = calculateV2(o,greyscale, size);
    double v1 = calculateV1(o+v2, greyscale, size);

        
    double Told=128;
    double Tnew = 128;
    do{
         v2 = calculateV2(Told, greyscale, size);
         v1 = calculateV1(Told + v2, greyscale, size);
         Told = Tnew;
         Tnew =v1/2;
      } while(Tnew!=Told);
        
      for(int i=0;i<size;++i)
      {
         binarisation[i] = greyscale[i]> Tnew ? 1 : 0;
      }
}

//2nd step: Localization of QR code
int accessTable(int* binarisation, int w, int x, int y)
{
    return binarisation[x + y*w];
}

int getSizeOfRepetetiveCharacters(int* binarisation, int w, int h, int i, int k)
{
    int colorOfFirstPixel = binarisation[i + k*h];
    int currentColor = colorOfFirstPixel;
    int index = 0;
    while(currentColor == colorOfFirstPixel && index+i < w)
    {
        index++;
        currentColor = accessTable(binarisation, w, index+i, k);
    }
    return index;
}

int getLeadingSize(int* binarisation, int w, int h, int k)
{
    return getSizeOfRepetetiveCharacters(binarisation, w, h, 0, k);
}
/*
int isColumnFollowPattern(int x, int y)
{
    //TODO
}*/

int doesFollowPattern(int* binarisation, int w, int h, int k, int* ratioPtr)
{
 //   printf("\n");

    int firstColor = accessTable(binarisation, w, 0, k);
    if(firstColor == 1)
    {
        return 0;
    }

    //Size of first black block
    int ratio = getSizeOfRepetetiveCharacters(binarisation, w, h, 0, k);
    
    {
        int currentCursor= ratio;
 //   printf("%d:",ratio/ratio);

    int sizeOfFirstWhiteBlock = getSizeOfRepetetiveCharacters(binarisation, w, h, currentCursor, k);
//    printf("%d:",sizeOfFirstWhiteBlock/ratio);

    if(sizeOfFirstWhiteBlock*1.0/ratio > 1.2 || sizeOfFirstWhiteBlock*1.0/ratio < 0.9  )
    {
        return 0;
    }
    currentCursor+= sizeOfFirstWhiteBlock;

    int sizeOfSecondBlackBlock = getSizeOfRepetetiveCharacters(binarisation, w, h, currentCursor, k);

    if(sizeOfSecondBlackBlock*1.0/ratio < 2.8  ||sizeOfSecondBlackBlock*1.0/ratio > 3.6)
    {
        return 0;
    }
    currentCursor+= sizeOfSecondBlackBlock;

   // printf("%d:",sizeOfSecondBlackBlock/ratio);

    int sizeOfSecondWhiteBlock = getSizeOfRepetetiveCharacters(binarisation, w, h, currentCursor, k);
    if(sizeOfSecondWhiteBlock*1.0/ratio >1.2 || sizeOfSecondWhiteBlock*1.0/ratio <0.8)
    {
        return 0;
    }
   // printf("%d:",sizeOfSecondWhiteBlock/ratio);
    currentCursor+= sizeOfSecondWhiteBlock;

        int sizeOfThirdBlackBlock = getSizeOfRepetetiveCharacters(binarisation, w, h,currentCursor, k);
        if(sizeOfThirdBlackBlock*1.0/ratio<0.8 || sizeOfThirdBlackBlock*1.0/ratio>1.2)
        {
            return 0;
        }
    }

  //  printf("%d:",sizeOfThirdBlackBlock/ratio);;
    *ratioPtr = ratio;
    return 1;
}

void localisation(int* binarisationArray, int w, int h)
{
    int lengthOfFirstBlock=0;
    int ratio1 = 0;
    while(lengthOfFirstBlock<h && !doesFollowPattern(binarisationArray, w, h, lengthOfFirstBlock, &ratio1))
    {
        lengthOfFirstBlock++;
    }

    int lengthOfBlockFollowingPattern=0;
    int line =lengthOfFirstBlock;

    while(line<h && doesFollowPattern(binarisationArray, w, h, line, &ratio1) )
    {
        lengthOfBlockFollowingPattern++;
        line++;
    }

    int firstCenter = lengthOfFirstBlock + lengthOfBlockFollowingPattern/2;
    printf("firstCenter=%d \n",firstCenter);

    int lengthOfSecondBlock=0;
    int startIndex = h-7*ratio1;
    int ratio2 = 0;

    while(lengthOfFirstBlock<h && !doesFollowPattern(binarisationArray, w, h, startIndex, &ratio2))
    {
        lengthOfSecondBlock++;
        startIndex++;
    }
   // printf("lengthOfSecondBlock=%d \n",lengthOfSecondBlock);
    int lengthOfSeconBlockBlockFollowingPattern=0;

    while(lengthOfFirstBlock<h && doesFollowPattern(binarisationArray, w, h, startIndex, &ratio2))
    {
        lengthOfSeconBlockBlockFollowingPattern++;
        startIndex++;
    }
    
    if(ratio1!=ratio2){
        return;
    }
    
    printf("secondCenter=%d \n",h-7*ratio2+lengthOfSecondBlock+lengthOfSeconBlockBlockFollowingPattern/2);

//    printf("lengthOfSeconBlockBlockFollowingPattern=%d \n",lengthOfSeconBlockBlockFollowingPattern);
 
 }

int main(int argc,  char * arg[])
{
    if (argc != 2)
    {
        err(1, "arg error");
    }
    /*if(!init_sdl())
    {
        return -1;
    }*/
    init_sdl();

    SDL_Surface* image_surface = load_image(arg[1]);

    int w = image_surface->w;
    int h = image_surface->h;
    int* greyscale = malloc(w*h*sizeof(int));
    grayscale(image_surface, greyscale);
    int* binarisationArray = malloc(w*h*sizeof(int));
    binarisation(image_surface, binarisationArray, greyscale);
    
    for(int j=0;j<h;++j){
        //printf("(%d)",j);
        for(int i=0;i<w;++i){
            printf("%d",binarisationArray[i+j*w]);
        }
        printf("\n");
    }
    
    localisation(binarisationArray, w, h);

    
    return 0;
}
