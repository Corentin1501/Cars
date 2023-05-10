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

#include "Modele/Car.h"

#include "stdbool.h"

GLuint liste_affichage_voiture;
GLuint liste_affichage_stade;
GLuint liste_affichage_piste;

// struct car les_voitures[10];

GLvoid Modelisation()
{
    VM_init();

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade

        glPushMatrix();
        {
            verifier_checkpoints();
            verifVictoire();
            
            glTranslatef(les_voitures[0].position_x, les_voitures[0].position_y, les_voitures[0].position_z);
            glRotatef(les_voitures[0].orientation ,0,1,0);
            glCallList(liste_affichage_voiture); // Afficher la voiture
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(les_voitures[1].position_x, les_voitures[1].position_y, les_voitures[1].position_z);
            glRotatef(les_voitures[1].orientation ,0,1,0);
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
