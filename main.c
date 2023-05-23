/*
    POUR COMPILER :

    make clean
    puis 
    make

    OU

    make clean; make

*/


#include "Vue/init.h"
#include "Vue/VM_init.h"
#include "Vue/HUD.h"

bool IAtrained = false;

GLvoid Modelisation()
{
    VM_init();

    if (!IAtrained)
    {
        start_time_des_IAs = (float)glutGet(GLUT_ELAPSED_TIME);
        jouer_IA_smart();

        IAtrained = true;
    }

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade

        int nombreDeVoitureAAfficher = 5;

        // for (int num = 0; num < nombreDeVoitureAAfficher; num++)
        // {
            // glPushMatrix();
            // {
            //     if (num == 0)
            //     {
            //         verifier_checkpoints(num, les_voitures);
            //         verifVictoire(num, les_voitures);
            //     }
            //     glTranslatef(les_voitures[num].position_x, les_voitures[num].position_y, les_voitures[num].position_z);
            //     glRotatef(les_voitures[num].orientation ,0,1,0);
            //     glCallList(liste_affichage_voiture); // Afficher la voiture
            // }
            // glPopMatrix();
        // }

        glPushMatrix();
        {
            verifier_checkpoints(VOITURE_DU_JOUEUR, les_voitures);
            verifVictoire(VOITURE_DU_JOUEUR, les_voitures);

            glTranslatef(les_voitures[VOITURE_DU_JOUEUR].position_x, les_voitures[VOITURE_DU_JOUEUR].position_y, les_voitures[VOITURE_DU_JOUEUR].position_z);
            glRotatef(les_voitures[VOITURE_DU_JOUEUR].orientation ,0,1,0);
            glCallList(liste_affichage_voiture); // Afficher la voiture
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(les_voitures[4].position_x, les_voitures[4].position_y, les_voitures[4].position_z);
            glRotatef(les_voitures[4].orientation ,0,1,0);
            glCallList(liste_affichage_voiture); // Afficher la voiture
        }
        glPopMatrix();
        
        // for (int num = 0; num < NOMBRE_IA; num++)
        // {
        //     glPushMatrix();
        //     {
        //         glColor3f(0,1,0);

        //         glTranslatef(lesIAs[num].position_x, lesIAs[num].position_y, lesIAs[num].position_z);
        //         glRotatef(lesIAs[num].orientation ,0,1,0);
        //         glCallList(liste_affichage_voiture); // Afficher la voiture
        //     }
        //     glPopMatrix();
        // }

        // printf("%d\n", getCurrentGene(VOITURE_DU_JOUEUR, les_voitures));

        

        glCallList(liste_affichage_piste); // Afficher la piste
        glCallList(liste_affichage_ciel); // Afficher le ciel

    //-----------------------------------

    drawHUD(); // Dessiner le HUD après la scène 3D

    glutSwapBuffers();
}



int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
