#include "init.h"
#include "VM_init.h"
#include "stdbool.h"

float voiture_x;              
float voiture_y;               
float voiture_z;  

const int NOMBRE_TOURS_POUR_GAGNER = 2;
const int NOMBRE_CHECKPOINTS = 4;

int  Current_Lap = 1;
bool checkpoints[4] = {false, false, false, false};

//#####################################################
//#                    CHRONOMETRE                    #
//#####################################################

    #include <time.h>
    #include <string.h>

    // bool isRunning = false;
    // clock_t startTime, currentTime;
    // int elapsedTime = 0;

    // // Fonction pour afficher le temps écoulé sur la fenêtre GLUT
    // void displayElapsedTime()
    // {
    //     glClearColor(1.0, 1.0, 1.0, 1.0);  // Couleur de fond blanche
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glColor3f(0.0, 0.0, 0.0);  // Couleur du texte en noir

    //     char elapsedTimeString[10];
    //     sprintf(elapsedTimeString, "%d", elapsedTime);  // Conversion de l'entier en chaîne de caractères

    //     // Affichage du temps écoulé en haut de la fenêtre
    //     glRasterPos2f(-0.9, 0.9);
    //     int len = strlen(elapsedTimeString);
    //     for (int i = 0; i < len; i++)
    //     {
    //         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, elapsedTimeString[i]);
    //     }

    //     glFlush();
    // }

    // // Fonction pour mettre à jour le temps écoulé
    // void updateElapsedTime()
    // {
    //     if (isRunning)
    //     {
    //         currentTime = clock();
    //         elapsedTime = (int)((currentTime - startTime) / CLOCKS_PER_SEC);
    //     }
    // }

    // void refresh(int value)
    // {
    //     updateElapsedTime();
    //     glutPostRedisplay();  // Redessine la fenêtre
    //     glutTimerFunc(1000, refresh, 0);  // Appelle la fonction refresh() toutes les 1000 ms (1 seconde)
    // }



//#####################################################
//#                       TOURS                       #
//#####################################################


    bool tourcompleted()
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) 
        {
            if(!checkpoints[i]) return false;
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
            return !checkpoints[num] && checkpoints[num-1];
    }

    void activateCheckPoints(int numeroCP)
    {
        checkpoints[numeroCP] = true;

        // verification si ça fait un tour
        if(tourcompleted())
        {
            ++Current_Lap;
            printf("tour complété ! tour n°%d\n", Current_Lap);

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
