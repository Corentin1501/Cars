// gcc -Wall ppm.c -c -o ppm.o

#ifndef LIB_PPM_H
#define LIB_PPM_H

typedef struct
{
  int width, height, bpp;
  unsigned char *data;
} TEXTURE_STRUCT;

TEXTURE_STRUCT * readPpm (char *ppmFileName);
void writePpm (char *filename, unsigned char *data);
unsigned char * rgb2rgba(TEXTURE_STRUCT * texture);
#endif