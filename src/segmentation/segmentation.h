/*
** QrCode Segmentation
** In order to use this segmentation, include this file into your file.
*/

# ifndef _SEGQR_H_
# define _SEGQR_H_

# include "geotrans.h"
# include "proc_code.h"
# include "extcode.h"
# include "FPValid.h"
# include "fpfind.h"
# include "../preprocessing/preprocessing.h"
# include "surfdraw.h"
# include <stdio.h>

/*  Segments the Img in order to find a QrCode and extracts its info
**  Returns structure PCode with :
**                                  ->Version   (int) 
**                                  ->Mask      (int)
**                                  ->ECL       (char)
**                                  ->BStream   (char*) This is the Bit Stream
*/
struct PCode *Segmentation(SDL_Surface *img);

/*  Same as above, but shows also the different steps of the segmentation */
struct PCode *SegmentationDemo(SDL_Surface *img, SDL_Surface *demo);

/* Combines previous functions into one function that takes the path to the img
 * to treat and if a Demo is asked*/
struct PCode *SegmentationFromFile(char *File, int Demo);

/* Frees the structure PCode */
void Free_PCode(struct PCode *c);

# endif
