#include "Regles.h"

const int NOMBRE_TOURS_POUR_GAGNER = 2;
const int NOMBRE_CHECKPOINTS       = 8;

float chronometre;

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
        Vérifie si une voiture donnée dans un tableau donné a fait un tour (si tous les Checkpoints sont validés)
        @return vrai ou faux
    */
    bool tourcompleted(int numVoiture, struct car* voitures)
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) 
        {
            if(!voitures[numVoiture].checkpoints[i]) return false;
        }
        return true;
    }

    /*
        Vérifie si une voiture donnée dans un tableau donné a fait le nombre de tours nécessaire pour gagner
        @return vrai ou faux
    */
    bool verifVictoire(int numVoiture, struct car* voitures)
    {
        bool victoireDeLaVoiture = voitures[numVoiture].currentLap > NOMBRE_TOURS_POUR_GAGNER;

        if(victoireDeLaVoiture && !voitures[numVoiture].aGagne){
            voitures[numVoiture].temps_victoire = chronometre;
            voitures[numVoiture].aGagne = true;         // booléen necessaire sinon le temps de victoire afficher simplement le chrono qui tourne
        } 

        return victoireDeLaVoiture;
    }

//#####################################################
//#                    CHECKPOINTS                    #
//#####################################################

    /*
        Vérifie quand un Checkpoint est passé, par une voiture donnée dans un tableau donné, si le Checkpoint précédent a aussi été passé
        @param numVoiture Numéro de la voiture
        @param voitures Tableau contenant les voitures
        @param numeroCP Numéro du Checkpoint passé
        @return vrai ou faux
    */
    bool checkpoint_dans_ordre(int numVoiture, struct car* voitures, int numeroCP)
    {
        if(numeroCP == 0) 
            return true;
        else 
            return !voitures[numVoiture].checkpoints[numeroCP] && voitures[numVoiture].checkpoints[numeroCP - 1];
    }

    /*
        Active un certain Checkpoint et augmente le nombre de tours complété si tous les checkpoints ont été passés pour une voiture donnée dans un tableau donné
        @param numVoiture Numéro de la voiture
        @param voitures Tableau contenant les voitures
        @param numeroCP Numéro du Checkpoint qu'on active
    */
    void activateCheckPoints(int numVoiture, struct car* voitures, int numeroCP)
    {
        voitures[numVoiture].checkpoints[numeroCP] = true;
        voitures[numVoiture].currentCP ++;

        // verification si ça fait un tour
        if(tourcompleted(numVoiture, voitures))
        {
            voitures[numVoiture].currentLap ++;
            for (int i = 0; i < NOMBRE_CHECKPOINTS; i++) voitures[numVoiture].checkpoints[i] = false;
        }
    }

    /*
        Verifie si les coordonnées d'une une voiture donnée dans un tableau donné ont passées un checkpoint
        @param numVoiture Numéro de la voiture
        @param voitures Tableau contenant les voitures
        @param numeroCP Numéro du Checkpoint qu'on vérifie
        @return vrai ou faux
    */
    bool CP_passe(int numVoiture, struct car* voitures, int numeroCP)
    {
        switch (numeroCP)
        {
            case 0: return ((10 <= voitures[numVoiture].position_x)   && (voitures[numVoiture].position_x <= 60)    && (voitures[numVoiture].position_z <= -70)); break;
            case 1: return ((voitures[numVoiture].position_x <= 0)    && (-125 <= voitures[numVoiture].position_z)  && (voitures[numVoiture].position_z <= -75)); break;
            case 2: return ((-60 <= voitures[numVoiture].position_x)  && (voitures[numVoiture].position_x <= -10)   && (-70 <= voitures[numVoiture].position_z)); break;
            case 3: return ((-75 <= voitures[numVoiture].position_x)  && (voitures[numVoiture].position_x <= -25)   && (0 <= voitures[numVoiture].position_z));   break;
            case 4: return ((-60 <= voitures[numVoiture].position_x)  && (voitures[numVoiture].position_x <= -10)   && (70 <= voitures[numVoiture].position_z));  break;
            case 5: return ((0 <= voitures[numVoiture].position_x)    && (75 <= voitures[numVoiture].position_z)    && (voitures[numVoiture].position_z <= 125)); break;
            case 6: return ((10 <= voitures[numVoiture].position_x)   && (voitures[numVoiture].position_x <= 60)    && (voitures[numVoiture].position_z <= 70));  break;
            case 7: return ((25 <= voitures[numVoiture].position_x)   && (voitures[numVoiture].position_x <= 75)    && (voitures[numVoiture].position_z <= 0));   break;
            
            default:    return false;   break;
        }
    }

    /*
        Effectue une vérification complète des Checkpoints pour une voiture donnée dans un tableau donné
        - Si un Checkpoint est passé
        - S'il est passé dans l'ordre
        - S'il n'était pas déjà activé
        @param numVoiture Numéro de la voiture
        @param voitures Tableau contenant les voitures
    */
    void verifier_checkpoints(int numVoiture, struct car* voitures)
    {
        for (int i = 0; i < NOMBRE_CHECKPOINTS; i++){
            if(CP_passe(numVoiture, voitures, i) && checkpoint_dans_ordre(numVoiture, voitures, i) && !voitures[numVoiture].checkpoints[i]){
                activateCheckPoints(numVoiture, voitures, i);
            }
        }
    }
