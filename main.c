/*
    POUR COMPILER :

    make clean
    puis 
    make

    OU

    make clean; make

*/


#include "Vue/init.h"
#include "Vue/axes.h"
#include "Vue/VM_init.h"
#include "Vue/HUD.c"
#include "Vue/ppm.h"

#include "stdbool.h"

float voiture_x = 50;  
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  

GLuint liste_affichage_voiture;
GLuint liste_affichage_stade;
GLuint liste_affichage_piste;

GLvoid Modelisation()
{
    VM_init();

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade

        glPushMatrix();
        {
            verifier_checkpoints();
            verifVictoire();
            
            glTranslatef(voiture_x, voiture_y, voiture_z);
            glRotatef(voiture_orientation,0,1,0);
            glCallList(liste_affichage_voiture); // Afficher la voiture
        }
        glPopMatrix();

        

        glCallList(liste_affichage_piste); // Afficher la piste

    //-----------------------------------

    axes();

    drawHUD(); // Dessiner le HUD après la scène 3D

    
    glutSwapBuffers();
}



int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
