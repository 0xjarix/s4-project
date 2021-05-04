#ifndef PROCESSING_H
#define PROCESSING_H
#include "SDL_tools.h"

int grayscale(SDL_Surface* image_surface, int* grayscale_image);
double calculateV2(double v, int* greyscale, int size);
double calculateV1(double v, int* greyscale, int size);
void binarisation(SDL_Surface* image_surface, int* binarisation,  int* greyscale);
int accessTable(int* binarisation, int w, int x, int y);
int getSizeOfRepetetiveCharacters(int* binarisation, int w, int h, int i, int k);
int getLeadingSize(int* binarisation, int w, int h, int k);
int isColumnFollowPattern(int x, int y);
int doesFollowPattern(int* binarisation, int w, int h, int k);
void localisation(int* binarisationArray, int w, int h);

#endif
