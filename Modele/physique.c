#include "physique.h"

const float ACCELERATION = 2.0;
const float VITESSE_MAX_AVANT  = 25.0;
const float VITESSE_MAX_ARRIERE  = -10.0;
const float TIME_STEP    = 0.1;

//#####################################################
//#                     PHYSIQUE                      #
//#####################################################

    // Augmente la vitesse de la voiture
    void accelerer(int numVoiture, struct car* voitures)
    {
        if(voitures[numVoiture].vitesse + ACCELERATION * TIME_STEP < VITESSE_MAX_AVANT)
            voitures[numVoiture].vitesse += ACCELERATION*TIME_STEP;
        else 
            voitures[numVoiture].vitesse = VITESSE_MAX_AVANT;
    }

    // Augmente la vitesse de la voiture négativement pour reculer
    void marcheArriere(int numVoiture, struct car* voitures)
    {
        if(voitures[numVoiture].vitesse - ACCELERATION * TIME_STEP > VITESSE_MAX_ARRIERE)
            voitures[numVoiture].vitesse -= ACCELERATION * TIME_STEP;
        else 
            voitures[numVoiture].vitesse = VITESSE_MAX_ARRIERE;

    }

    // Diminue la vitesse de la voiture
    void deceleration(int numVoiture, struct car* voitures)
    {
        float forceDeceleration = 0.08;

        if      (voitures[numVoiture].vitesse - forceDeceleration > 0)  voitures[numVoiture].vitesse -= forceDeceleration;
        else if (voitures[numVoiture].vitesse + forceDeceleration < 0)  voitures[numVoiture].vitesse += forceDeceleration;
        else                                                                    voitures[numVoiture].vitesse = 0;
    }
        
    // Diminue fortement la vitesse de la voiture
    void freinage(int numVoiture, struct car* voitures)
    {
        float forceDeFreinage = 0.6;

        if (voitures[numVoiture].vitesse - forceDeFreinage > 0) 
            voitures[numVoiture].vitesse -= forceDeFreinage;
        else 
            voitures[numVoiture].vitesse = 0;
    }

//#####################################################
//#         BOUGER LA VOITURE SELON LES AXES          #
//#####################################################

    float avancer_voiture_x(int numVoiture, struct car* voitures){ return voitures[numVoiture].vitesse * TIME_STEP * sin((voitures[numVoiture].orientation * M_PI) / 180); }
    float avancer_voiture_z(int numVoiture, struct car* voitures){ return voitures[numVoiture].vitesse * TIME_STEP * cos((voitures[numVoiture].orientation * M_PI) / 180); }
    float reculer_voiture_x(int numVoiture, struct car* voitures){ return avancer_voiture_x(numVoiture, voitures)/2.0; }
    float reculer_voiture_z(int numVoiture, struct car* voitures){ return avancer_voiture_z(numVoiture, voitures)/2.0; }

//#####################################################
//#                BOUGER LES VOITURES                #
//#####################################################

    void avancer_voiture(int numVoiture, struct car* voitures)
    {
        // Avancer la voiture dans la direction de l'orientation
        voitures[numVoiture].position_x += avancer_voiture_x(numVoiture, voitures);
        voitures[numVoiture].position_z += avancer_voiture_z(numVoiture, voitures);
    }

    void reculer_voiture(int numVoiture, struct car* voitures)
    {
        // Reculer la voiture dans la direction de l'orientation
        voitures[numVoiture].position_x += reculer_voiture_x(numVoiture, voitures);
        voitures[numVoiture].position_z += reculer_voiture_z(numVoiture, voitures);
    }

    void tourner_voiture_gauche(int numVoiture, struct car* voitures)
    {
        // Tourner la voiture vers la gauche
        voitures[numVoiture].orientation += 5;
    }

    void tourner_voiture_droite(int numVoiture, struct car* voitures)
    {
        // Tourner la voiture vers la droite
        voitures[numVoiture].orientation -= 5;
    }

//#####################################################
//#                 SORTIES DE PISTE                  #
//#####################################################

    /*
        Equation de l'ellipse du tour de stade :
            (x / 70)² + (y / 120)² = 1
        Equation de l'ellipse de la barrière au centre du stade :
            (x / 30)² + (y / 80)² = 1
    */

    void verif_dehors(int numVoiture, struct car* voitures)
    {
        float Ellipse_exterieure = pow(voitures[numVoiture].position_x / 70, 2) + pow(voitures[numVoiture].position_z / 120, 2);
        float Ellipse_interieure = pow(voitures[numVoiture].position_x / 30, 2) + pow(voitures[numVoiture].position_z / 80, 2);

        if (Ellipse_exterieure > 1 || Ellipse_interieure < 1) {

            voitures[numVoiture].aToucheLeMur = true;
            
            float projection_x, projection_z;
            float min_distance_exterieure = 1000000000;
            float min_distance_interieure = 1000000000;

            if (Ellipse_exterieure > 1) {
                for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
                    float x = cos(angle) * 70;
                    float z = sin(angle) * 120;
                    float distance = sqrt(pow(voitures[numVoiture].position_x - x, 2) + pow(voitures[numVoiture].position_z - z, 2));
                    if (distance < min_distance_exterieure) {
                        min_distance_exterieure = distance;
                        projection_x = x;
                        projection_z = z;
                    }
                }
            }

            if (Ellipse_interieure < 1) {
                for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
                    float x = cos(angle) * 30;
                    float z = sin(angle) * 80;
                    float distance = sqrt(pow(voitures[numVoiture].position_x - x, 2) + pow(voitures[numVoiture].position_z - z, 2));
                    if (distance < min_distance_interieure) {
                        min_distance_interieure = distance;
                        projection_x = x;
                        projection_z = z;
                    }
                }
            }

            voitures[numVoiture].position_x = projection_x;
            voitures[numVoiture].position_z = projection_z;
            if(voitures[numVoiture].vitesse-0.8>0)
                 voitures[numVoiture].vitesse-=0.8;
            else voitures[numVoiture].vitesse=0;
        }
    }
