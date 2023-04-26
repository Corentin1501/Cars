#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */

#include "touches.h"
#include "../Vue/switch_blend.h"
#include "../Vue/switch_light.h"
#include <stdlib.h>
#include "../Modele/opmat.h"


#include <GL/glut.h>    

void touche_relachee(unsigned char key, int x, int y);

void touche_pressee(unsigned char key, int x, int y);

void touche(int touche, int x, int y);

#endif
