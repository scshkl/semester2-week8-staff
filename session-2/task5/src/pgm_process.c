#include "pgm_process.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//================================================================================
/**
 * @brief Inverts the colours of the image (255-value)
 * 
 * @param original_image Original PGMImage
 * @return Pointer to new PGMImage with inverted colours
 */
PGMImage *invert_image_colors(PGMImage p){
    PGMImage *p1 = (PGMImage *)malloc(sizeof(PGMImage));

    p1->pixels = allocate_image_array(p);

    if (p1->pixels == NULL) {
        return NULL;
    }
    
    p1->width = p.width;
    p1->height = p.height;
    p1->max_gray = p.max_gray;

    // Invert each pixel (max_gray - value) 
    for (int i = 0; i < p.height; i++) {
        for (int j = 0; j < p.width; j++) {
            p1->pixels[i][j] = p.max_gray - p.pixels[i][j];
        }
    }
    
    return p1;
}

//================================================================================
/**
 * @brief Rotates the image by the specified angle
 * 
 * @param original_image Original PGMImage
 * @param degrees Rotation angle (90, 180, or 270 degrees)
 * @return pointer to PGMImage
 */
PGMImage *rotate_image(PGMImage p, int degrees){
    PGMImage *p1 = (PGMImage *)malloc(sizeof(PGMImage));
    p1->pixels = allocate_image_array(p);
    if (p1->pixels == NULL) {
        return NULL;
    }
    
    p1->width = p.width;
    p1->height = p.height;
    p1->max_gray = p.max_gray;

    switch (degrees) {
        case 90:
            // For 90 degrees, width and height are swapped          
            // 90 degree rotation algorithm 
            for (int i = 0; i < p.height; i++) {
                for (int j = 0; j < p.width; j++) {
                    p1->pixels[j][p.height-1-i] = p.pixels[i][j];
                }
            }
            break;
            
        case 180:
            // 180 degree rotation algorithm 
            for (int i = 0; i < p.height; i++) {
                for (int j = 0; j < p.width; j++) {
                    p1->pixels[p.height-1-i][p.width-1-j] = p.pixels[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            // 270 degree rotation algorithm 
            for (int i = 0; i < p.height; i++) {
               for (int j = 0; j < p.width; j++) {
                   p1->pixels[p.width-1-j][i] = p.pixels[i][j];
               }
           }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }
    
    return p1;
}