#include <stdlib.h>
#include "pgm_image.h"
#include <stdio.h>


//====================================================================================
/**
 * @brief Allocates a 2D array for storing the image pixels
 * 
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @return unsigned char** 2D array of image pixels, or NULL if allocation fails
 */
unsigned char ** allocate_image_array(PGMImage p) {
    /* TODO: Refactor this to use your PGMImage structure */
    //unsigned char **array = calloc(height, sizeof(unsigned char *));
    unsigned char ** pixels = calloc (p.height, sizeof(unsigned char *));

    if (pixels == NULL) {
        printf("Error: Memory allocation failed for image array\n");
        return NULL;
    }
    
    for (int i = 0; i < p.height; i++) {
        pixels[i] = calloc(p.width, sizeof(unsigned char));
        if (pixels[i] == NULL) {
            /* Free previously allocated memory if this allocation fails */
            for (int j = 0; j < i; j++) {
                free(pixels[j]);
            }
            free(pixels);
            printf("Error: Memory allocation failed for image row %d\n", i);
            return NULL;
        }
    }

    return pixels;
}

//===============================================================================
/**
 * @brief Frees memory allocated for a 2D image array
 * 
 * @param image The 2D image array to free
 * @param height Number of rows in the image
 */
void pgm_free_image(PGMImage *p, int height){
    if (p->pixels == NULL) return;
    
    for (int i = 0; i < height; i++) {
        free(p->pixels[i]);
    }
    free(p->pixels);
}

//============================================================================
/**
 * @brief Frees memory allocated for a 2D image array
 * 
 * @param image The 2D image array to free
 * @param height Number of rows in the image
 */
 
void free_image_array(PGMImage *p, int height) {
    // TODO: Refactor this to use your PGMImage structure
    if (p->pixels == NULL) return;
    
    for (int i = 0; i < height; i++) {
        free(p->pixels[i]);
    }
    free(p->pixels);
}