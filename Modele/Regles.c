#include "../Vue/init.h"
#include "../Vue/VM_init.h"

#include "stdbool.h"

// Coordonnées de la voiture
float voiture_x;              
float voiture_y;               
float voiture_z; 

const int NOMBRE_TOURS_POUR_GAGNER = 5 ;
const int NOMBRE_CHECKPOINTS       = 8 ;
const float ECHELLE_STADE_CP = 3;

int Current_Lap = 1;
int Current_CP = 0;
bool liste_checkpoints[8] = {false, false, false, false, false, false, false, false};

float start_time = 0;
float victory_time = 0;
bool victory_time_calculated = false;
float chronometre;

bool victoire = false;


//#####################################################
//#                    CHRONOMETRE                    #
//#####################################################

    /*
        Met à jour le chronomètre et le met en secondes
    */
    void updateChrono() 
    {
        chronometre = glutGet(GLUT_ELAPSED_TIME) - start_time;  // temps en millisecondes
        chronometre = chronometre / 1000.0;                     // temps en secondes
    }

//#####################################################
//#                       TOURS                       #
//#####################################################

    /*
        Vérifie si un tour a été fait (si tous les Checkpoints sont validés)
        @return vrai ou faux
    */
    bool tourcompleted()
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) 
        {
            if(!liste_checkpoints[i]) return false;
        }
        return true;
    }

    /*
        Vérifie si le nombre de tours nécessaire pour gagner a été atteint
        @return vrai ou faux
    */
    bool verifVictoire()
    {
        victoire = Current_Lap > NOMBRE_TOURS_POUR_GAGNER;

        if(victoire && !victory_time_calculated){
            victory_time = chronometre;
            victory_time_calculated = true;         // booléen necessaire sinon le temps de victoire afficher simplement le chrono qui tourne
        } 

        return victoire;
    }

//#####################################################
//#                    CHECKPOINTS                    #
//#####################################################

    /*
        Vérifie quand un Checkpoint est passé si le Checkpoint précédent a aussi été passé
        @param numeroCP Numéro du Checkpoint passé
        @return vrai ou faux
    */
    bool checkpoint_dans_ordre(int numeroCP)
    {
        if(numeroCP == 0) 
            return true;
        else 
            return !liste_checkpoints[numeroCP] && liste_checkpoints[numeroCP-1];
    }

    /*
        Active un certain Checkpoint et augmente le nombre de tours complété si tous les checkpoints ont été passés
        @param numeroCP Numéro du Checkpoint qu'on active
    */
    void activateCheckPoints(int numeroCP)
    {
        liste_checkpoints[numeroCP] = true;
        ++Current_CP;

        // verification si ça fait un tour
        if(tourcompleted())
        {
            ++Current_Lap;
            for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) liste_checkpoints[i] = false;
        }
    }

    /*
        Verifie si les coordonnées de la voiture ont passées un checkpoint
        @param numeroCP Numéro du Checkpoint qu'on vérifie
        @return vrai ou faux
    */
    bool CP_passe(int numeroCP)
    {
        switch (numeroCP)
        {
            case 0: return ((0 <= voiture_x)        && (voiture_x <= 5.5*ECHELLE_STADE_CP)       && (voiture_z <= -7.5*ECHELLE_STADE_CP));    break;
            case 1: return ((voiture_x <= 0)        && (-12.5*ECHELLE_STADE_CP <= voiture_z)     && (voiture_z <= -7.5*ECHELLE_STADE_CP));    break;
            case 2: return ((-5.5*ECHELLE_STADE_CP <= voiture_x)     && (voiture_x <= 0)         && (-7.5*ECHELLE_STADE_CP <= voiture_z));    break;
            case 3: return ((-7.25*ECHELLE_STADE_CP <= voiture_x)    && (voiture_x <= -3.25*ECHELLE_STADE_CP)     && (0 <= voiture_z));       break;
            case 4: return ((-5.5*ECHELLE_STADE_CP <= voiture_x)     && (voiture_x <= 0)         && (7.5*ECHELLE_STADE_CP <= voiture_z));     break;
            case 5: return ((0 <= voiture_x)        && (7.5*ECHELLE_STADE_CP <= voiture_z)       && (voiture_z <= 12.5*ECHELLE_STADE_CP));    break;
            case 6: return ((0 <= voiture_x)        && (voiture_x <= 5.5*ECHELLE_STADE_CP)       && (voiture_z <= 7.5*ECHELLE_STADE_CP));     break;
            case 7: return ((3*ECHELLE_STADE_CP <= voiture_x)        && (voiture_x <= 7.25*ECHELLE_STADE_CP)      && (voiture_z <= 0));       break;
            
            default:    return false;   break;
        }
    }

    /*
        Effectue une vérification complète des Checkpoints
        - Si un Checkpoint est passé
        - S'il est passé dans l'ordre
        - S'il n'était pas déjà activé
    */
    void verifier_checkpoints()
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++){
            if(CP_passe(i) && checkpoint_dans_ordre(i) && !liste_checkpoints[i]){
                activateCheckPoints(i);
            }
        }
    }
