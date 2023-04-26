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
#include "Modele/opmat.h"
#include "stdbool.h"
#include "Vue/ppm.h"

#include "Vue/Modele.c"
#include "Vue/HUD.c"

float voiture_x = 9.625;  
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  

bool gameFinished = false;


void faire_la_scene()
{
    struct modele voiture = creerModele("/home/etud/Bureau/Cars-version-visual-studio/modeles/Voiture/voiture.obj");
    struct modele stade = creerModele("/home/etud/Bureau/Cars-version-visual-studio/modeles/Stade_et_pisteV4.obj");


    glColor3f(1,1,0);

    float echelleStade = 3;

    glPushMatrix(); // Stade
    {
        glTranslatef(0,-1,0);
        glScalef(echelleStade,echelleStade,echelleStade);
        afficherModele(stade);
    }
    glPopMatrix();

    glPushMatrix(); // Voiture
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
