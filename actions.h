#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */

#include "touches.h"
#include "switch_blend.h"
#include "switch_light.h"
#include <stdlib.h>
#include "opmat.h"


#include <GL/glut.h>    

void touche_relachee(unsigned char key, int x, int y);

void touche_pressee(unsigned char key, int x, int y);

void touche(int touche, int x, int y);

void verif_dehors();

#endif
