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

GLuint liste_affichage_voiture; // Créer la liste d'affichage pour la voiture
GLuint liste_affichage_stade; // Créer la liste d'affichage pour le stade



void créer_la_scene()
{

    //##################################################
    //             LISTE AFFICHAGE VOITURE            //
    //##################################################

        liste_affichage_voiture = glGenLists(1); // Créer la liste d'affichage pour la voiture
        glNewList(liste_affichage_voiture, GL_COMPILE); // Début de l'enregistrement de la liste
            struct modele voiture = creerModele("/home/etud/Documents/S6/STAGE/Cars/Vue/modeles-blender/Voiture/voiture_sans_fenetres.obj");
            glPushMatrix(); // Voiture
            {
                glColor3f(1,1,1); // couleur de la voiture
                verifier_checkpoints();

                if (verifVictoire() && !gameFinished){
                    gameFinished = true;
                    printf("Course finie !\n");
                } 
                // verif_dehors();

                glTranslatef(voiture_x, voiture_y, voiture_z);
                glRotatef(voiture_orientation,0,1,0);

                afficherModele(voiture);
            }
            glPopMatrix();
        glEndList(); // Fin de l'enregistrement de la liste

    //##################################################
    //              LISTE AFFICHAGE STADE             //
    //##################################################

        liste_affichage_stade = glGenLists(1); // Créer une nouvelle liste d'affichage
        glNewList(liste_affichage_stade, GL_COMPILE); // Début de l'enregistrement de la liste
            struct modele stade = creerModele("/home/etud/Documents/S6/STAGE/Cars/Vue/modeles-blender/Stade/Stade_et_piste_version_finale.obj");
            glPushMatrix(); // Stade
        {
            glColor3f(1,1,1); // couleur du stade
            glTranslatef(0,-1,0);
            glScalef(ECHELLE_STADE,ECHELLE_STADE,ECHELLE_STADE);
            afficherModele(stade);
        }
        glPopMatrix();
        glEndList(); // Fin de l'enregistrement de la liste



    aiReleaseImport(voiture.scene);
    aiReleaseImport(stade.scene);
}


GLvoid Modelisation()
{
    VM_init();

    créer_la_scene();

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade
        glCallList(liste_affichage_voiture); // Afficher la voiture
        
    //-----------------------------------

    axes();

    drawHUD(); // Dessiner le HUD après la scène 3D

    
    glutSwapBuffers();
}



int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
