#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

// lignes d'affichage mises en commentaire : 34, 98, 136


TEXTURE_STRUCT * readPpm(char *ppmFileName)
{
	FILE *file;
	TEXTURE_STRUCT *texture = NULL;
	char buffer[255];
	int pixelFormat;
	int i;


	if ((file = fopen(ppmFileName, "rb")) == NULL)
	{
		printf ("(ERROR) : C function fopen failed in readPpm(%s)\n", ppmFileName);
		getchar();
		return NULL;
	}

	//Test of the magic header (must be P3 or P6)
	fread (buffer, sizeof(char), 2, file);
	buffer[2] = '\0';
	if (strncmp(buffer, "P3", 2) & strncmp(buffer, "P6", 2))
	{
		printf ("(ERROR) : File %s doesn't seem to be a ppm, the header says %s [function readPpm]\n", ppmFileName, buffer);
		getchar();
		return NULL;
	}
	// printf("%s\n", buffer);
	//Allocation of the pointer to the TEXTURE_STRUCT variable
	if ((texture = (TEXTURE_STRUCT *)malloc(sizeof(TEXTURE_STRUCT))) == NULL)
	{
		printf ("(ERROR) : C function malloc failed in readPpm(%s)\n", ppmFileName);
		getchar();
		return NULL;
	}
	
	//Ignoring backspaces, tabulations, end of lines and carriage return
	while (1)
	{
		fread (buffer, sizeof(char), 1, file);
		if (!((buffer[0]==32) || (buffer[0]==9) || (buffer[0]==10) || (buffer[0]==13)))
			break;
	}
	//Reading Width
	i = 1;
	while (1)
	{
		fread (buffer+i, sizeof(char), 1, file);
		if ((buffer[i]==32) || (buffer[i]==9) || (buffer[i]==10) || (buffer[i]==13))
			break;
		i++;
	}
	buffer[i] = '\0';
	texture->width = atoi(buffer);
	//Ignoring backspaces, tabulations, end of lines and carriage return	
	while (1)
	{
		fread (buffer, sizeof(char), 1, file);
		if (!((buffer[0]==32) || (buffer[0]==9) || (buffer[0]==10) || (buffer[0]==13)))
			break;
	}
	//Reading Height
	i = 1;
	while (1)
	{
		fread (buffer+i, sizeof(char), 1, file);
		if ((buffer[i]==32) || (buffer[i]==9) || (buffer[i]==10) || (buffer[i]==13))
			break;
		i++;
	}
	buffer[i] = '\0';
	texture->height = atoi(buffer);
	//Ignoring backspaces, tabulations, end of lines and carriage return	
	while (1)
	{
		fread (buffer, sizeof(char), 1, file);
		if (!((buffer[0]==32) || (buffer[0]==9) || (buffer[0]==10) || (buffer[0]==13)))
			break;
	}
	//Reading bpp
	i = 1;
	while (1)
	{
		fread (buffer+i, sizeof(char), 1, file);
		if ((buffer[i]==32) || (buffer[i]==9) || (buffer[i]==10) || (buffer[i]==13))
			break;
		i++;
	}
	buffer[i] = '\0';
	pixelFormat = atoi(buffer);
	pixelFormat++;
	// printf ("%d %d %d\n", texture->width, texture->height, pixelFormat);
	//Finding the number of bits fitting the pixel format, if available
	if (pixelFormat <= 0)
	{
		printf ("(ERROR) : Pixel Format of the %s ppm file is less or equal to 0\n", ppmFileName);
		getchar();
		free (texture);
		return NULL;
	}
	texture->bpp = 1;
	while ((pixelFormat - (1 << texture->bpp)) >= 1)
		texture->bpp++;
	//printf ("Detected %d BPP\n", texture->bpp);
	//Ignoring backspaces, tabulations, end of lines and carriage return	
	while (1)
	{
		fread (buffer, sizeof(char), 1, file);
		if (!((buffer[0]==32) || (buffer[0]==9) || (buffer[0]==10) || (buffer[0]==13)))
			break;
	}
	//Reading the texture
	//	if ((texture->data = (unsigned char *)malloc(texture->width*texture->height*3*sizeof(unsigned char))) == NULL)
	if ((texture->data = (unsigned char *)malloc(256*256*3*sizeof(unsigned char))) == NULL)
	{
		printf ("(ERROR) : C function malloc failed in readPpm(%s)\n", ppmFileName);
		getchar();
		free(texture);
		return NULL;
	}
	fseek(file, -1, SEEK_CUR);

	int ligne = 0;
	while(ligne < texture->height) {
	  fread(texture->data+(3*256*ligne), sizeof(unsigned char), 3*texture->width, file);
	  ligne++;
	}
	// fread(texture->data, sizeof(unsigned char), 3*texture->width*texture->height, file);
	
	// printf ("(OK) : The file %s was correctly parsed and uploaded in memory [function readPpm]\n", ppmFileName);
	//printf ("%d %d %d\n", texture->width, texture->height, texture->bpp);getchar();getchar();

	texture->width = 256;
	texture->height = 256;
	return texture;

}


unsigned char * rgb2rgba(TEXTURE_STRUCT * texture)
{
  int width = texture->width;
  int height = texture->height;
  unsigned char * data = texture->data;
  unsigned char * temp = (unsigned char *) malloc (sizeof(unsigned char) * width* height *4);
  int i = 0;

  for (i=0; i<width*height; i++)
    {
      temp[i*4+0] = data[i*3+0];
      temp[i*4+1] = data[i*3+1];
      temp[i*4+2] = data[i*3+2];      
      if ((data[i*3+0]==0) && (data[i*3+1]==0) && (data[i*3+2]==0))
	temp[i*4+3] = 255;	// Pixel noir donc transparent
      else
	temp[i*4+3] = (unsigned char)0; // Pixel complÃ¨tement opaque
    }									       
  return temp;
}


void writePpm (char *filename, unsigned char *data)
{
  unsigned int width = 256; 
  unsigned int height = 256; 
  FILE *file;
  char buffer[256];

  buffer[0] = '\0';
  sprintf (buffer, "P6\n%u %u\n255\n", width, height); 
  file = fopen (filename, "wb");
  if (file == NULL)
    {
      printf ("Could not open the file %s\n", filename);
      exit(0);
    }
  if (fwrite (buffer, sizeof(unsigned char), strlen(buffer), file) != strlen(buffer))
    {
      printf ("Error writing header of Ppm File\n");
      exit(0);
    }
  if (fwrite (data, sizeof(unsigned char), 3*width*height, file) != (3*width*height))
    {
      printf("Error in writing data image in Ppm file\n");
      exit(0);
    }
  fclose(file);
}