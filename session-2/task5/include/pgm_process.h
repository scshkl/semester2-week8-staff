#ifndef PGM_PROCESS_H
#define PGM_PROCESS_H

#include "pgm_io.h"

//function prototype
PGMImage *invert_image_colors(PGMImage p);
PGMImage *rotate_image(PGMImage p, int degrees);

#endif