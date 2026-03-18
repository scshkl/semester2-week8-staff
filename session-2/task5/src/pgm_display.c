#include "pgm_display.h"
#include <stdio.h>

// =======================================================================================
/**
 * @brief Prints information about the PGM image
 * 
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void print_image_info(const char *filename, PGMImage p){
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", p.width, p.height);
    printf("Max Gray Value: %d\n", p.max_gray);
}

// =======================================================================================
/**
 * @brief Prints the pixel values of the image
 * 
 * @param pixels The 2D array of image pixels
 * @param height Image height
 * @param width Image width
 */
void print_image_values(PGMImage p){
    printf("\nImage Pixel Values (%dx%d):\n", p.width, p.height);
    for (int i = 0; i < p.height; i++) {
        for (int j = 0; j < p.width; j++) {
            printf("%3d ", p.pixels[i][j]);
        }
        printf("\n");
    }
}

// =======================================================================================
/**
 * @brief Gets user menu choice from standard input
 * 
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int get_user_menu_choice(const char *message){
    char buffer[100];
    int choice;
    printf("%s: ", message);
    fgets(buffer, 100, stdin);
    int check = sscanf(buffer, "%d", &choice);
    if (!check) {
        return -1;
    }
    return choice;
}

// =======================================================================================
/**
 * @brief Displays the main program menu
 */
void display_menu(void){
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}