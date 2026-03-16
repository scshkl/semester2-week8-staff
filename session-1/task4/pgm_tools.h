#ifndef PGMTOOLS_H
#define PGMTOOLS_H

typedef struct pgm_image{
    int width;
    int height;
    int max_gray;
    unsigned char **pixels;
} PGMImage;


int allocate_image_array(PGMImage *p);
void free_image_array(PGMImage *p);
PGMImage *read_pgm_image(const char *filename);
void print_image_info(const char *filename, PGMImage p);
void print_image_values(PGMImage p);
unsigned char **invert_image_colors(PGMImage p);
unsigned char **rotate_image(PGMImage p);
int save_pgm_image(const char *filename, PGMImage);

#endif