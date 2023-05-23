#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>      // pour le printf

extern const int NOMBRE_DE_GENES;

struct car
{
    float position_x;
    float position_y;
    float position_z;

    float orientation;
    float vitesse;
    
    char * fichier_modele;    //chemin fichier voiture
    char * fichier_texture;    //chemin fichier tex

    bool IsVoitureDuJoueur;

    bool checkpoints[8];

    bool aGagne;
    float temps_victoire;
    int currentCP;
    int currentLap;

    int mouvementEffectue;
    int note;
    bool aToucheLeMur;

    /*
        0 : accelere
        1 : ne fais rien
        2 : freine / recule
        3 : tourne à gauche 
        4 : tourne à droite
    */
    bool genes[32][5];
};


struct car initialiser_voiture(int numero_voiture);
void resetVoiture(int numero_voiture, struct car* voitures);

void afficherVoiture(int numero_voiture, struct car* voitures, int maxGenes);

// #endif