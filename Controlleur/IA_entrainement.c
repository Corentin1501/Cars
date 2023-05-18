#include "IA_entrainement.h"

#define M_PI 3.14159265358979323846

struct voitureIA individus[20];

const int NOMBRE_CHECKPOINTS_IA = 8;

float chronometre_IA = 0.0;

void initialiserIA()
{
    for (int i = 0; i < 20; i++)
    {
        for (int g = 0; g < 8; g++) 
            individus[i].genes[g] = false;

        individus[i].angleRotation = 180.0;
        individus[i].vitesse = 1.0;
        individus[i].position.x = 35.0;
        individus[i].position.y = 0.0;
        individus[i].position.z = 0.0;
    }
}

//###################################################################################
//#                       DÉFINIR LES GÈNES / ZONE / POSITION                       #
//###################################################################################

    bool tourcompletedIA(int numeroIndividu)
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS_IA; i++) 
        {
            if(!individus[numeroIndividu].genes[i]) return false;
        }
        return true;
    }

    bool checkpoint_dans_ordreIA(int numeroIndividu, int numeroCP)
    {
        if(numeroCP == 0) 
            return true;
        else 
            return !individus[numeroIndividu].genes[numeroCP] && individus[numeroIndividu].genes[numeroCP - 1];
    }


    void activateCheckPointsIA(int numeroIndividu, int numeroCP)
    {
        individus[numeroIndividu].genes[numeroCP] = true;
        ++individus[numeroIndividu].CurrentCheckpoint;

        // verification si ça fait un tour
        if(tourcompletedIA(numeroIndividu))
        {
            ++individus[numeroIndividu].CurrentLap;
            for (int i = 0; i < NOMBRE_CHECKPOINTS_IA; i++) individus[numeroIndividu].genes[i] = false;
        }
    }


    bool CP_passeIA(int numeroIndividu, int numeroCP)
    {
        switch (numeroCP)
        {
            case 0: return ((10 <= individus[numeroIndividu].position.x)   && (individus[numeroIndividu].position.x <= 60)    && (individus[numeroIndividu].position.z <= -70)); break;
            case 1: return ((individus[numeroIndividu].position.x <= 0)    && (-125 <= individus[numeroIndividu].position.z)  && (individus[numeroIndividu].position.z <= -75)); break;
            case 2: return ((-60 <= individus[numeroIndividu].position.x)  && (individus[numeroIndividu].position.x <= -10)   && (-70 <= individus[numeroIndividu].position.z)); break;
            case 3: return ((-75 <= individus[numeroIndividu].position.x)  && (individus[numeroIndividu].position.x <= -25)   && (0 <= individus[numeroIndividu].position.z));   break;
            case 4: return ((-60 <= individus[numeroIndividu].position.x)  && (individus[numeroIndividu].position.x <= -10)   && (70 <= individus[numeroIndividu].position.z));  break;
            case 5: return ((0 <= individus[numeroIndividu].position.x)    && (75 <= individus[numeroIndividu].position.z)    && (individus[numeroIndividu].position.z <= 125)); break;
            case 6: return ((10 <= individus[numeroIndividu].position.x)   && (individus[numeroIndividu].position.x <= 60)    && (individus[numeroIndividu].position.z <= 70));  break;
            case 7: return ((25 <= individus[numeroIndividu].position.x)   && (individus[numeroIndividu].position.x <= 75)    && (individus[numeroIndividu].position.z <= 0));   break;
            
            default:    return false;   break;
        }
    }

    void verifier_checkpointsIA(int numeroIndividu)
    {
        for (int cp = 0; cp < NOMBRE_CHECKPOINTS_IA; cp++){
            if(CP_passeIA(numeroIndividu, cp) && checkpoint_dans_ordreIA(numeroIndividu, cp) && !individus[numeroIndividu].genes[cp]){
                activateCheckPointsIA(numeroIndividu, cp);
            }
        }
    }

//###################################################################################
//#                             DÉFINITIONS DES ACTIONS                             #
//###################################################################################

    float avancer_voiture_x_IA(int numeroIndividu){ return individus[numeroIndividu].vitesse * sin((individus[numeroIndividu].angleRotation * M_PI) / 180); }
    float avancer_voiture_z_IA(int numeroIndividu){ return individus[numeroIndividu].vitesse * cos((individus[numeroIndividu].angleRotation * M_PI) / 180); }
    float reculer_voiture_x_IA(int numeroIndividu){ return avancer_voiture_x_IA(numeroIndividu) / 2.0; }
    float reculer_voiture_z_IA(int numeroIndividu){ return avancer_voiture_z_IA(numeroIndividu) / 2.0; }
    void tourner_voiture_gauche_IA(int numeroIndividu){ individus[numeroIndividu].angleRotation += 5; }
    void tourner_voiture_droite_IA(int numeroIndividu){ individus[numeroIndividu].angleRotation -= 5; }

    void avancer_voiture_IA(int numeroIndividu)
    {
        individus[numeroIndividu].position.x += avancer_voiture_x_IA(numeroIndividu);
        individus[numeroIndividu].position.z += avancer_voiture_z_IA(numeroIndividu);
    }

    void reculer_voiture_IA(int numeroIndividu)
    {
        individus[numeroIndividu].position.x -= reculer_voiture_x_IA(numeroIndividu);
        individus[numeroIndividu].position.z -= reculer_voiture_z_IA(numeroIndividu);
    }


/*
    Choix possibles de l'IA :
    - appuyer sur Z     accélerer
    - appuyer sur S     freiner
    - appuyer sur Q     tourner à gauche
    - appuyer sur D     tourner à droite
    - ne rien appuyer   décelerer
*/

void entrainerIAs()
{
    initialiserIA();

    chronometre_IA = glutGet(GLUT_ELAPSED_TIME) - start_time;

    // entrainement
    

        chronometre_IA = glutGet(GLUT_ELAPSED_TIME) - start_time;

        for (int indiv = 0; indiv < 20; indiv++)
        {
            while (!individus[indiv].genes[0])
            {
                verifier_checkpointsIA(indiv);
                avancer_voiture_IA(indiv);
            }
        }

        
        

    // Afficher les résultats / données des IAs

        for (int indiv = 0; indiv < 20; indiv++)
        {
            printf("individu n°%d :\t[", indiv);
            for (int g = 0; g < 8; g++)
            {
                if (g != 7) printf("%d,",   individus[indiv].genes[g]);
                if (g == 7) printf("%d]\t(%.1f , %.1f)\n", individus[indiv].genes[g], individus[indiv].position.x, individus[indiv].position.z);
            }
        }
}