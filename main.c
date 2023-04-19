/*
    POUR COMPILER :

    gcc opmat.c actions.c VM_init.c ppm.c -c
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

    OU 

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c -c; 
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

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

bool gameFinished = false;

float chronometre = 0.0f;
void glutBitmapString(void *font, const unsigned char *string);

            // dessin du HUD
            // glColor3f(1,1,1);
            // glRasterPos2f(10,10);
            // char buffer[256];
            // sprintf(buffer,"Tours : %d", Current_Lap);
            // glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
            // sprintf(buffer,"Chronomètre : %.2f s", chronometre);
            // glRasterPos2f(10,30);
            // glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);

void drawHUD()
{
    float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float windowWidth = glutGet(GLUT_WINDOW_WIDTH);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glLoadIdentity();

            // dessin du HUD
            glColor3f(1,1,1);
            glRasterPos2f(10,10);
            char buffer[256];
            sprintf(buffer,"Tours : %d", Current_Lap);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
            sprintf(buffer,"Chronometre : %.2f s", chronometre);
            glRasterPos2f(10,30);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void faire_la_scene()
{
    struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Voiture/voiture.obj");
    struct modele stade = creerModele("/home/etud/Documents/S6/STAGE/Cars/modeles/Stade_et_piste.obj");


    GLUquadric *quadric = gluNewQuadric();
    GLfloat outerradius = 4;
    GLfloat innerradius = 2;

    GLfloat cubeSize = 0.5;

    // glPushMatrix();
    // {
    //     glColor3f(0,0.5,0.5);
    //     glTranslatef(0, -0.1, 0);
    //     glRotatef(-90,1,0,0);
    //     gluDisk(quadric,innerradius,outerradius,30,30);
    //     // glScalef(4,0.1,12);
    //     // glutSolidCube(1);
    // }
    // glPopMatrix();

    glColor3f(1,1,0);

    afficherModele(stade);

    glPushMatrix();
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
