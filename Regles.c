#include "init.h"
#include "VM_init.h"
#include "stdbool.h"

float voiture_x;              
float voiture_y;               
float voiture_z;  

const int NOMBRE_TOURS_POUR_GAGNER = 5 ;
const int NOMBRE_CHECKPOINTS       = 8 ;

int Current_Lap = 1;
bool liste_checkpoints[8] = {false, false, false, false, false, false, false, false};

//#####################################################
//#                    CHRONOMETRE                    #
//#####################################################

    #include <time.h>
    #include <string.h>

    float start_time = 0;
    float chronometre;

    void updateChrono() 
    {
        chronometre = glutGet(GLUT_ELAPSED_TIME) - start_time;  // temps en millisecondes
        chronometre = chronometre / 1000.0;                     // temps en secondes
    }

//#####################################################
//#                       TOURS                       #
//#####################################################

    bool tourcompleted()
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) 
        {
            if(!liste_checkpoints[i]) return false;
        }
        return true;
    }

    bool verifVictoire()
    {
        return Current_Lap > NOMBRE_TOURS_POUR_GAGNER;
    }

//#####################################################
//#                    CHECKPOINTS                    #
//#####################################################



    bool checkpoint_dans_ordre(int num)
    {
        if(num == 0) 
            return true;
        else 
            return !liste_checkpoints[num] && liste_checkpoints[num-1];
    }

    void activateCheckPoints(int numeroCP)
    {
        liste_checkpoints[numeroCP] = true;

        // verification si ça fait un tour
        if(tourcompleted())
        {
            ++Current_Lap;
            printf("tour complété ! tour n°%d\n", Current_Lap);

            for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) liste_checkpoints[i] = false;
        }
    }

    bool CP1_passe(){ return (voiture_x <=0) && (voiture_z >= -4) && (voiture_z <= -2); }
    bool CP2_passe(){ return (voiture_z >=0) && (voiture_x >= -4) && (voiture_x <= -2); }
    bool CP3_passe(){ return (voiture_x >=0) && (voiture_z <=  4) && (voiture_z >=  2); }
    bool CP4_passe(){ return (voiture_z <=0) && (voiture_x <=  4) && (voiture_x >=  2); }

    void verifier_checkpoints(){
        if(CP1_passe() && checkpoint_dans_ordre(0) && !liste_checkpoints[0]) 
        {
            printf("checkpoint 1 passé !\n"); activateCheckPoints(0);
        }
        else if(CP2_passe() && checkpoint_dans_ordre(1) && !liste_checkpoints[1]) 
        {
            printf("checkpoint 2 passé !\n"); activateCheckPoints(1);
        }
        else if(CP3_passe() && checkpoint_dans_ordre(2) && !liste_checkpoints[2]) 
        {
            printf("checkpoint 3 passé !\n"); activateCheckPoints(2);
        }
        else if(CP4_passe() && checkpoint_dans_ordre(3) && !liste_checkpoints[3]) 
        {
            printf("checkpoint 4 passé !\n"); activateCheckPoints(3);
        }
    }
