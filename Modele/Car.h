#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <stdbool.h>

#define VITESSE_MAX 50
#define ACCELERATION 2
#define TIME_STEP 0.03


struct car
{
    float position_x;
    float position_y;
    float position_z;

    float orientation;
    float vitesse;
    
    char * fichier_modele;    //chemin fichier voiture
    char * fichier_texture;    //chemin fichier tex
};


struct car initialiser_voiture(int numero_voiture);
void accelerate_car(struct car voiture);

// #endif