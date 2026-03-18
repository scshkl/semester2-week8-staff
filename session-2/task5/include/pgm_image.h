#ifndef PGMIMAGE_H
#define PGMIMAGE_H

typedef struct {
    int width;
    int height;
    int max_gray;
    unsigned char **pixels;
} PGMImage;


// function prototype
//PGMImage *pgm_create_image(void);
void pgm_free_image(PGMImage *p, int height);
unsigned char ** allocate_image_array(PGMImage p);
void free_image_array(PGMImage *p, int height);
#endif