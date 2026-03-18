#include "pgm_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =======================================================================================
/**
 * @brief Reads a PGM image from a file
 * 
 * @param filename Path to the PGM file
 * @return pointer to PGMImage created dynamically
 */
PGMImage *read_pgm_image(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    PGMImage *p1 = (PGMImage *)malloc(sizeof(PGMImage));

    /* Read PGM header */
    char magic_number[3];
    if (fscanf(file, "%2s", magic_number) != 1) {
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }
    
    if (strcmp(magic_number, "P2") != 0) {
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }
    
    if (fscanf(file, "%d %d", &(p1->width), &(p1->height)) != 2) {
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }
    
    if (fscanf(file, "%d", &(p1->max_gray)) != 1) {
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }
    
    /* Allocate memory for the pixel array */
    p1->pixels = allocate_image_array(*p1);

    if (p1->pixels == NULL) {
        fclose(file);
        return NULL;
    }
    
    /* Read pixel values */
    int pixel_value;
    for (int i = 0; i < p1->height; i++) {
        for (int j = 0; j < p1->width; j++) {
            if (fscanf(file, "%d", &pixel_value) != 1) {
                printf("Error: Could not read pixel value at position (%d,%d)\n", j, i);
               // free_image_array(pixels, *height);
                fclose(file);
                return NULL;
            }
            p1->pixels[i][j] = (unsigned char)pixel_value;
        }
    }
    
    fclose(file);
    return p1;
}

// =======================================================================================
/**
 * @brief Saves a PGM image to a file
 * 
 * @param filename Output filename
 * @param PGMImage
 * @return int 1 if successful, 0 if failed
 */
int save_pgm_image(const char *filename, PGMImage p){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", filename);
        return 0;
    }
    
    /* Write PGM header */
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", p.width, p.height);
    fprintf(file, "%d\n", p.max_gray);
    
    /* Write pixel values */
    for (int i = 0; i < p.height; i++) {
        for (int j = 0; j < p.width; j++) {
            fprintf(file, "%d ", p.pixels[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    return 1;
}