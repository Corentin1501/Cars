/*
    POUR COMPILER :

    gcc opmat.c actions.c VM_init.c ppm.c -c
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

    OU 

    gcc opmat.c actions.c VM_init.c ppm.c -c; gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp
*/


#include "init.h"
#include "axes.h"
#include "VM_init.h"
#include "opmat.h"
#include "stdbool.h"
#include "ppm.h"

#include "Modele.c"

GLvoid Modelisation()
{
    VM_init();

    glColor3f(255,144/255.0,144/255.0);

    struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Voiture/voiture.obj");

    float echelle = 20.0;

    glScalef(echelle,echelle,echelle);
    afficherModele(voiture);
    glScalef(1/echelle,1/echelle,1/echelle);

    aiReleaseImport(voiture.scene);


    axes();
    glutSwapBuffers();
}

int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
