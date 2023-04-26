#ifndef __INIT
#define __INIT

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "../Controlleur/touches.h"
#include "lumiere.h"
#include "../Controlleur/actions.h"



GLvoid Redimensionne(GLsizei Width, GLsizei Height);

int notre_init(int argc, char** argv, void (*Modelisation)());

#endif
