/*
    POUR COMPILER :

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c HUD.c -c
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

    OU 

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c HUD.c -c; gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp
*/


#include "init.h"
#include "axes.h"
#include "VM_init.h"
#include "opmat.h"
#include "stdbool.h"
#include "ppm.h"

#include "Modele.c"
#include "HUD.c"

float voiture_x = 9.625;  
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  

bool gameFinished = false;


void faire_la_scene()
{
    struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Voiture/voiture_sans_fenetres.obj");
    struct modele stade = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Stade_et_pisteV3.obj");


    GLUquadric *quadric = gluNewQuadric();
    GLfloat outerradius = 4;
    GLfloat innerradius = 2;

    GLfloat cubeSize = 0.5;


    glColor3f(1,1,0);

    afficherModele(stade);

    glPushMatrix(); // voiture
    {
        glColor3f(255,144/255.0,144/255.0);
        verifier_checkpoints();

        if (verifVictoire() && !gameFinished){
            gameFinished = true;
            printf("Course finie !\n");
        } 

        glTranslatef(voiture_x, voiture_y, voiture_z);
        glRotatef(voiture_orientation,0,1,0);

        afficherModele(voiture);
    }
    glPopMatrix();

    aiReleaseImport(voiture.scene);
    aiReleaseImport(stade.scene);
}


GLvoid Modelisation()
{
    VM_init();

    faire_la_scene();

    axes();

    drawHUD(); // Dessiner le HUD après la scène 3D

    
    glutSwapBuffers();
}



int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
