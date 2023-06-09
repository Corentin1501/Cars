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

GLvoid Modelisation()
{
    VM_init();

    //------ Affichage de la scène ------

        glCallList(liste_affichage_stade); // Afficher le stade

        int nombreDeVoitureAAfficher = 10;

        for (int num = 0; num < nombreDeVoitureAAfficher; num++)
        {
            glPushMatrix();
            {
                if (num == 0)
                {
                    verifier_checkpoints(num, les_voitures);
                    verifVictoire(num, les_voitures);
                }
                glTranslatef(les_voitures[num].position_x, les_voitures[num].position_y, les_voitures[num].position_z);
                glRotatef(les_voitures[num].orientation ,0,1,0);
                glCallList(liste_affichage_voiture); // Afficher la voiture
            }
            glPopMatrix();
        }

        // Si l'on veut afficher les dernières positions des IAs après leurs entrainement

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

        // Si l'on veut savoir dans quel gène la voiture du joueur se situe

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
