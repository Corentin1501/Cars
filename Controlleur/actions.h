#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */

#include "touches.h"

#include "../Vue/switch_blend.h"
#include "../Vue/switch_light.h"
#include "../Modele/opmat.h"
#include "../Modele/physique.h"      // pour créer le tableau de voiture (avec la struct car) et utiliser la physique

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

void updateCameras();

void mettre_a_jour_position_voiture();

void touche_relachee(unsigned char key, int x, int y);
void touche_pressee(unsigned char key, int x, int y);
void touche(int touche, int x, int y);

// void verif_dehors(int numero_voiture);


#endif
