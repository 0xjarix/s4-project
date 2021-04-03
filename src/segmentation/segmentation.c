#include "segmentation.h"
#include <unistd.h>

static inline void print_mat(char **mat, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("[ ");
        for(int j = 0; j < size; j++)
        {
            printf("%c ", mat[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

static inline void free_FPat(struct FPat *f)
{
    if(f == NULL)
        return;
    free_Dmat(f->centers);
    free_Dvector(f->ems_vector);
    free(f);
}

static inline void free_FPresults(struct FPresults *f)
{
    if(f == NULL)
        return;
    free(f);
}

static inline void free_QrCode(struct QrCode *q)
{
    if(q == NULL)
        return;

    for(int i = 0; i < (q->version * 4 + 17); i++)
    {
        free(q->mat[i]);
    }
    free(q->mat);
    free(q);
}

static inline void free_GeoImg(struct GeoImg *g)
{
    free(g->coordA);
    free(g->coordB);
    free(g->coordC);
    SDL_FreeSurface(g->img);
    free(g);
}

static inline
void free_segmentation(struct FPat *f, struct FPresults *fp, struct GeoImg *g,\
        struct QrCode *q)
{
    free_FPat(f);
    free_FPresults(fp);
    free_GeoImg(g);
    free_QrCode(q);
}

void free_PCode(struct PCode *c)
{
    if(c == NULL)
        return;
    free(c->BStream);
    free(c);
}

/*---Main Functions---*/

    static inline
void ImageProcessing(SDL_Surface *img)
{
    grayscale(img);
    int threshold = otsu(img);
    if(threshold == 0)
        threshold = 1;
    binarize(img, threshold);
}

    static inline
void ImageProcessingDemo(SDL_Surface *img)
{
    grayscale(img);
    //display_image(img);
    int threshold = otsu(img);
    if(threshold == 0)
        threshold = 1;
    binarize(img, threshold);
    display_image(img);
}

    static inline
void writeWhiteEpi(char *s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '1' || s[i] == '0')
            s[i] = 'w';
        i++;
    }
}

struct PCode *Segmentation(SDL_Surface *img)
{
    ImageProcessing(img);
    struct FPat *f = findFP(img);
    struct FPresults *fp = QrCode_found(f);
    if(fp == NULL)
        err(EXIT_FAILURE, "Segmentation error : No Valid QrCode found");
    struct GeoImg *g = GeoTransform(img, fp);
    ImageProcessing(g->img);
    struct QrCode *qr = extract_QrCode(g);
    struct PCode *c = get_code(qr);
    free_segmentation(f, fp, g, qr);
    SDL_FreeSurface(img);
    return c;
}



struct PCode *SegmentationDemo(SDL_Surface *img, SDL_Surface *demo)
{
    printf("> Testing segmentation...\n");
    printf(">>>   Starting now:\n");
    for (int i= 0; i < 10000; i++)
        continue;
    ImageProcessing(img);
    display_image(img);
    printf("      - Preprocessing finished.\n");
    struct FPat *f = findFP(img);
    struct FPresults *fp = QrCode_found(f);
    if(fp == NULL)
    {
        printf("No QrCode were found, exit...\n");
        err(EXIT_FAILURE, "Segmentation error : No Valid QrCode found");
    }
    drawFP(demo, f->centers, f->ems_vector, fp->indexA);
    display_image(demo);

    puts("      - Finder Pattern successful, QR code found.\n");
    struct GeoImg *g = GeoTransform(img, fp);
    ImageProcessing(g->img);
    struct QrCode *qr = extract_QrCode(g);

    display_image(g->img);
    printf("Bit Matrix :\n");
    print_mat(qr->mat, qr->version * 4 + 17);
    struct PCode *c = get_code(qr);
    puts("> Bit stream extracted from the QR code matrix:");
    printf("%s\n", c->BStream);
    SDL_FreeSurface(img);
    SDL_FreeSurface(demo);
    return c;
}

struct PCode *SegmentationFromFile(char *File, int Demo)
{
    init_sdl();
    SDL_Surface *img = load_image(File);
    struct PCode *c;
    if(Demo == 1)
    {
        SDL_Surface *demo = load_image(File);
        display_image(img);
        c = SegmentationDemo(img, demo);
    }
    else
    {
        c = Segmentation(img);
    }

    SDL_Quit();
    return c;
}

// Uncomment to run the segmentation separately from the program.
/*int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        if(strcmp(argv[2], "-d") == 0)
        {
            SegmentationFromFile(argv[1], 1);
        }
    }
    else if(argc > 1)
        SegmentationFromFile(argv[1], 0);
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}*/
