
#include "pgm_image.h"
#include "pgm_io.h"
#include "pgm_process.h"
#include "pgm_display.h"
#include <stdio.h>

int main(int argc, char **argv){
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