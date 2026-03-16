/**
 * @file activity3-pgm_tools_refactored.c
 * @brief Tools for manipulating PGM (Portable Gray Map) image files
 * 
 * COMP1850 Structures Activity 3
 * 
 * Your task is to refactor this file to use a PGMImage structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_tools.h"

int get_user_menu_choice(const char *message);
void display_menu(void);

int main(int argc, char **argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    /* Read the image */
    PGMImage *image = read_pgm_image(argv[1]);
    
    /* Check if image reading was successful */
    if (image == NULL) {
        return 1;
    }
    
    /* Display image information */
    print_image_info(argv[1], *image);

    int choice = -1;
    char output_filename[100];
    int rotation_degrees;
    //unsigned char **processed_image = NULL;
    PGMImage *processed_image = NULL;

    /* Main program loop */
    do {
        choice = -1;
        display_menu();
        while (choice < 1)
            choice = get_user_menu_choice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            print_image_values(*image);
            break;
            
        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
           processed_image = invert_image_colors(*image);
            
            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */
            
           if (save_pgm_image(output_filename, *processed_image)) {
               printf("Inverted image saved to %s\n", output_filename);
           } else {
               printf("Failed to save inverted image\n");
           }
            
            /* Free the processed image memory */
           free_image_array(processed_image, processed_image->height);
            break;
            
        case 3: /* Rotate image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Enter rotation in degrees (90, 180, or 270): ");
            scanf("%d", &rotation_degrees);
            getchar(); /* Consume newline */
            
            /* Validate rotation degrees */
            if (rotation_degrees != 90 && rotation_degrees != 180 && rotation_degrees != 270) {
                printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
                break;
            }
            
            printf("Rotating image by %d degrees...\n", rotation_degrees);
            processed_image = rotate_image(*image, rotation_degrees);
            
            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */
            
            /* For 90 and 270 degree rotations, height and width are swapped */
            if (rotation_degrees == 90 || rotation_degrees == 270) {
                if (save_pgm_image(output_filename, *processed_image)) {
                    printf("Rotated image saved to %s\n", output_filename);
                } else {
                    printf("Failed to save rotated image\n");
                }
                free_image_array(processed_image, processed_image->width);
            } else { // 180 degrees 
                if (save_pgm_image(output_filename, *processed_image)) {
                    printf("Rotated image saved to %s\n", output_filename);
                } else {
                    printf("Failed to save rotated image\n");
                }
                free_image_array(processed_image, processed_image->height);
            }
            break;
            
        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            free_image_array(image, image->height);
            return 0;
            
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}

/**
 * @brief Gets user menu choice from standard input
 * 
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int get_user_menu_choice(const char *message) {
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

/**
 * @brief Displays the main program menu
 */
void display_menu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}

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


/**
 * @brief Reads a PGM image from a file
 * 
 * @param filename Path to the PGM file
 * @param height Pointer to store the image height
 * @param width Pointer to store the image width
 * @param max_gray Pointer to store the max gray value
 * @return unsigned char** 2D array of image pixels, or NULL if reading fails
 */
PGMImage *read_pgm_image(const char *filename) {
    /* TODO: Refactor this to use your PGMImage structure */
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

/**
 * @brief Prints information about the PGM image
 * 
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void print_image_info(const char *filename, PGMImage p) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", p.width, p.height);
    printf("Max Gray Value: %d\n", p.max_gray);
}

/**
 * @brief Prints the pixel values of the image
 * 
 * @param pixels The 2D array of image pixels
 * @param height Image height
 * @param width Image width
 */
void print_image_values(PGMImage p) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("\nImage Pixel Values (%dx%d):\n", p.width, p.height);
    for (int i = 0; i < p.height; i++) {
        for (int j = 0; j < p.width; j++) {
            printf("%3d ", p.pixels[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Inverts the colours of the image (255-value)
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return unsigned char** New image with inverted colours
 */
 
PGMImage * invert_image_colors(PGMImage p) {
    // TODO: Refactor this to use your PGMImage structure 
    // Allocate memory for the inverted image 
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


/**
 * @brief Rotates the image by the specified angle
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param degrees Rotation angle (90, 180, or 270 degrees)
 * @return unsigned char** New rotated image
 */
PGMImage *rotate_image(PGMImage p, int degrees) {
    /* TODO: Refactor this to use your PGMImage structure */
   // unsigned char **rotated_image;

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

/**
 * @brief Saves a PGM image to a file
 * 
 * @param filename Output filename
 * @param pixels Image pixel array
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return int 1 if successful, 0 if failed
 */
int save_pgm_image(const char *filename, PGMImage p) {
    /* TODO: Refactor this to use your PGMImage structure */
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
