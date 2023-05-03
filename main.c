/*
    POUR COMPILER :

    gcc opmat.c actions.c VM_init.c init.c ppm.c Modele.c Regles.c HUD.c -c
    gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

    OU 

gcc Modele/opmat.c Controlleur/actions.c Vue/VM_init.c Vue/init.c Vue/ppm.c Modele/Regles.c Vue/HUD.c Modele/physique.c -c; gcc main.c Controlleur/actions.o Vue/axes.o Vue/init.o Vue/switch_blend.o Vue/switch_light.o Vue/VM_init.o Vue/ppm.o Modele/opmat.o -lm -lGL -lGLU -lglut -o test -lassimp

move_object_files:
	mv *.o Objet/

    	$(CC) Modele/opmat.c Controlleur/actions.c Vue/VM_init.c Vue/init.c Vue/ppm.c Modele/Regles.c Vue/HUD.c Modele/physique.c -c;$(CC) main.c Objet/actions.o Objet/axes.o Objet/init.o Objet/switch_blend.o Objet/switch_light.o Objet/VM_init.o Objet/ppm.o Objet/opmat.o $(GL) -o $@ $(ASS)


*/


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
GLuint liste_affichage_piste; // Créer la liste d'affichage pour la piste avec les textures

GLuint textures[10];

void créer_la_scene()
{
    //##################################################
    //             LISTE AFFICHAGE VOITURE            //
    //##################################################

        liste_affichage_voiture = glGenLists(1); // Créer la liste d'affichage pour la voiture

        glNewList(liste_affichage_voiture, GL_COMPILE); // Début de l'enregistrement de la liste

            struct modele voiture = creerModele("./Vue/modeles-blender/Voiture/voiture_sans_fenetres.obj");

            glPushMatrix(); // Voiture
            {
                glColor3f(1,0,1); // couleur de la voiture
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

            struct modele stade = creerModele("./Vue/modeles-blender/Stade/Stade_plat.obj");
            // chargerTextures(&stade);
            glPushMatrix(); // Stade
            {
                glColor3f(1,1,1); // couleur du stade
                glTranslatef(0,-1,0);
                glScalef(ECHELLE_STADE,ECHELLE_STADE,ECHELLE_STADE);
                afficherModeleAvecTextures(stade);
            }
            glPopMatrix();


        glEndList(); // Fin de l'enregistrement de la liste

    //##################################################
    //              LISTE AFFICHAGE PISTE             //
    //##################################################

        liste_affichage_piste = glGenLists(1); // Créer une nouvelle liste d'affichage

        glNewList(liste_affichage_piste, GL_COMPILE); // Début de l'enregistrement de la liste

            struct modele piste = creerModele("./Vue/modeles-blender/Stade/Piste/Piste_seul.obj");
            glPushMatrix(); // Piste
            {
                glColor3f(1,1,1); // couleur de la piste
                glTranslatef(0,-2,0);
                glScalef(ECHELLE_STADE,ECHELLE_STADE,ECHELLE_STADE);
                afficherModeleAvecTextures(piste);
            }
            glPopMatrix();

        glEndList(); // Fin de l'enregistrement de la liste


    aiReleaseImport(voiture.scene);
    aiReleaseImport(stade.scene);
    aiReleaseImport(piste.scene);
}


GLvoid Modelisation()
{
    VM_init();

    créer_la_scene();

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade
        glCallList(liste_affichage_voiture); // Afficher la voiture
        // glCallList(liste_affichage_piste); // Afficher la piste

    //-----------------------------------

    axes();

    drawHUD(); // Dessiner le HUD après la scène 3D

    
    glutSwapBuffers();
}



int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
