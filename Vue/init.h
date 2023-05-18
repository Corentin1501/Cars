#ifndef __INIT
#define __INIT

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "stdbool.h"

#include "lumiere.h"
#include "ppm.h"
#include "../Controlleur/touches.h"
#include "../Controlleur/actions.h"
#include "../Controlleur/IA_entrainement.h"
#include "../Modele/Modele.h"

extern GLuint liste_affichage_voiture; // Créer la liste d'affichage pour la voiture
extern GLuint liste_affichage_stade; // Créer la liste d'affichage pour le stade
extern GLuint liste_affichage_piste; // Créer la liste d'affichage pour la piste avec les textures
extern GLuint liste_affichage_ciel; // Créer la liste d'affichage pour la piste avec les textures

extern float start_time;
extern GLuint textures[10];
extern bool gameFinished;

GLvoid Redimensionne(GLsizei Width, GLsizei Height);

int notre_init(int argc, char** argv, void (*Modelisation)());

#endif