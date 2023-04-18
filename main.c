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

float voiture_x = 3;              
float voiture_y = 0;               
float voiture_z = 0;  
float voiture_orientation = 180;  

const int NOMBRE_CHECKPOINTS = 4;
bool checkpoints[4] = {false, false, false, false};

int Tour_en_cours = 1;

//########## Données ##########
    // voiture
        float voiture_longueur = 2.9;
        float voiture_largeur = 1.250;
        float voiture_hauteur = 0.725;


bool tourcompleted(){
    for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) if(!checkpoints[i]) return false;
    return true;
}

bool checkpoint_dans_ordre(int num){
    if(num == 0) return true;
    else return !checkpoints[num] && checkpoints[num-1];
}

void activateCheckPoints(int numeroCP){
    checkpoints[numeroCP] = true;

    // verif si ça fait un tour
    if(tourcompleted()){
        ++Tour_en_cours;
        printf("tour complété ! tour n°%d\n", Tour_en_cours);

        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) checkpoints[i] = false;
    }
}

bool CP1_passe(){ return (voiture_x <=0) && (voiture_z >= -4) && (voiture_z <= -2); }
bool CP2_passe(){ return (voiture_z >=0) && (voiture_x >= -4) && (voiture_x <= -2); }
bool CP3_passe(){ return (voiture_x >=0) && (voiture_z <=  4) && (voiture_z >=  2); }
bool CP4_passe(){ return (voiture_z <=0) && (voiture_x <=  4) && (voiture_x >=  2); }

void verifier_checkpoints(){
    if(CP1_passe() && checkpoint_dans_ordre(0) && !checkpoints[0]) 
    {
        printf("checkpoint 1 passé !\n"); activateCheckPoints(0);
    }
    else if(CP2_passe() && checkpoint_dans_ordre(1) && !checkpoints[1]) 
    {
        printf("checkpoint 2 passé !\n"); activateCheckPoints(1);
    }
    else if(CP3_passe() && checkpoint_dans_ordre(2) && !checkpoints[2]) 
    {
        printf("checkpoint 3 passé !\n"); activateCheckPoints(2);
    }
    else if(CP4_passe() && checkpoint_dans_ordre(3) && !checkpoints[3]) 
    {
        printf("checkpoint 4 passé !\n"); activateCheckPoints(3);
    }
}


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
