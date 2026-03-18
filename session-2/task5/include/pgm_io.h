#ifndef PGM_IO_H
#define PGM_IO_H

#include "pgm_image.h"

PGMImage *read_pgm_image(const char *filename);
int save_pgm_image(const char *filename, PGMImage p);

#endif

