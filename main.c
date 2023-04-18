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
#include "Regles.c"

float voiture_x = 3;              
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  


GLvoid Modelisation()
{
    VM_init();

    struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Voiture/voiture.obj");


    GLUquadric *quadric = gluNewQuadric();
    GLfloat outerradius = 4;
    GLfloat innerradius = 2;

    GLfloat cubeSize = 0.5;

    glPushMatrix(); // sol
    {
        glColor3f(0,1,0);
        glTranslatef(0, -0.1, 0);
        glRotatef(-90,1,0,0);
        gluDisk(quadric,innerradius,outerradius,30,30);
        // glScalef(4,0.1,12);
        // glutSolidCube(1);
    }
    glPopMatrix();

    glPushMatrix(); // voiture
    {

        glColor3f(255,144/255.0,144/255.0);
        verifier_checkpoints();

        if (verifVictoire()) printf("Course finie !");
        

        glTranslatef(voiture_x, voiture_y, voiture_z);
        glRotatef(voiture_orientation,0,1,0);

        afficherModele(voiture);
    }
    glPopMatrix();
    

    aiReleaseImport(voiture.scene);
    axes();
    glutSwapBuffers();
}

int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
