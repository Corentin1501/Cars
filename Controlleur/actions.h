#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */

#include "touches.h"

#include "../Vue/switch_blend.h"
#include "../Vue/switch_light.h"
#include "../Modele/opmat.h"

#include <stdlib.h>
#include <GL/glut.h>    
#include "stdbool.h"

float avancer_voiture_x(int numero_voiture);
float avancer_voiture_z(int numero_voiture);
float reculer_voiture_x(int numero_voiture);
float reculer_voiture_z(int numero_voiture);

void updateCameraTPS();
void updateCameraFPS();
void updateCameras();

void avancer_voiture(int numero_voiture);
void reculer_voiture(int numero_voiture);

void tourner_voiture_gauche(int numero_voiture);
void tourner_voiture_droite(int numero_voiture);

void mettre_a_jour_position_voiture(int tempsEcoule);

void touche_relachee(unsigned char key, int x, int y);
void touche_pressee(unsigned char key, int x, int y);
void touche(int touche, int x, int y);

void verif_dehors();

#endif
