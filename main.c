/*
    POUR COMPILER :

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c HUD.c -c
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

    OU 

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c HUD.c -c; gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp
*/


#include "Modele/opmat.h"
#include "Modele/Modele.c"

#include "Vue/init.h"
#include "Vue/axes.h"
#include "Vue/VM_init.h"
#include "Vue/HUD.c"
#include "Vue/ppm.h"

#include "stdbool.h"

float voiture_x = 9.625 * 1.5;  
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  

bool gameFinished = false;


void faire_la_scene()
{
    struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/Vue/modeles-blender/Voiture/voiture_sans_fenetres.obj");
    struct modele stade = creerModele("/home/etud/Documents/S6/STAGE/Cars/Vue/modeles-blender/Stade/Stade_et_piste_version_finale.obj");




    glPushMatrix(); // Stade
    {
        glColor3f(1,1,1); // couleur du stade
        glTranslatef(0,-1,0);
        glScalef(ECHELLE_STADE,ECHELLE_STADE,ECHELLE_STADE);
        afficherModele(stade);
    }
    glPopMatrix();
    // glPushMatrix(); // Sol plat
    // {
    //     glColor3f(1,1,1);
    //     glTranslatef(0,-1,0);
    //     glScalef(60,0.1,60);
    //     glutSolidCube(1);
    // }
    // glPopMatrix();
    

    glPushMatrix(); // Voiture
    {
        // glColor3f(255,144/255.0,144/255.0); // couleur de la voiture
        glColor3f(1,1,1); // couleur de la voiture
        verifier_checkpoints();

        if (verifVictoire() && !gameFinished){
            gameFinished = true;
            printf("Course finie !\n");
        } 

        // verif_dehors();

        glTranslatef(voiture_x, voiture_y, voiture_z);
        // printf("(%f,%f,%f)\n",voiture_x, voiture_y, voiture_z);
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
