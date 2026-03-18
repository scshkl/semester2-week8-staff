#ifndef PGM_DISPLAY_H
#define PGM_DISPLAY_H

#include "pgm_process.h"

// function prototype
void print_image_info(const char *filename, PGMImage p);
void print_image_values(PGMImage p);
int get_user_menu_choice(const char *message);
void display_menu(void);

#endif