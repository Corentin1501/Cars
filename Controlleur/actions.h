#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */

#include "touches.h"

#include "../Vue/switch_blend.h"
#include "../Vue/switch_light.h"
#include "../Modele/opmat.h"
#include "../Modele/Car.h"      // pour créer le tableau de voiture (avec la struct car)

#include <stdlib.h>
#include <GL/glut.h>    
#include <time.h>
#include "stdbool.h"

// les coordonées de la caméra 
    // vue FPS
        extern float camera_FPS_x;              
        extern float camera_FPS_y;       
        extern float camera_FPS_z;       
    // vue TPS
        extern float camera_TPS_x;              
        extern float camera_TPS_y;      
        extern float camera_TPS_z;      
    // son orientation
        extern float camera_orientation_x;   
        extern float camera_orientation_z;   
    // la vue
        extern bool vue_FPS;
        extern bool vue_TPS;
        extern bool vue_ARR;
// tableau des voitures        
extern struct car les_voitures[10];

void initialiser_voitures_et_touches();

void acceleration(int numero_voiture);
void deceleration(int numero_voiture);
void freinage(int numero_voiture);
void reculer(int numero_voiture);

void updateCameras();

float avancer_voiture_x(int numero_voiture);
float avancer_voiture_z(int numero_voiture);
float reculer_voiture_x(int numero_voiture);
float reculer_voiture_z(int numero_voiture);

void avancer_voiture(int numero_voiture);
void reculer_voiture(int numero_voiture);

void tourner_voiture_gauche(int numero_voiture);
void tourner_voiture_droite(int numero_voiture);

void mettre_a_jour_position_voiture();

void touche_relachee(unsigned char key, int x, int y);
void touche_pressee(unsigned char key, int x, int y);
void touche(int touche, int x, int y);

void verif_dehors(int numero_voiture);


#endif
