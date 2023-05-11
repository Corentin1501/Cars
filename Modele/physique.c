#include <math.h>

#define COEF_RESISTANCE_ROULEMENT 0.013 //POUR CALCULER LA FORCE DE DECELERATION DE LA VOITURE SANS FREINAGE

float gravity=9.81;
float friction_coef=0.9;
float masse=1000;

const float ACCELERATION=2.0;
const float VITESSE_MAX=25.0;
const float TIME_STEP = 0.1;
float vitesse=0.0;

extern struct car les_voitures[10];


/*
####                          #### 
####    mise a jour vitesse   ####
####                          #### 
*/


void update_vitesse(int numero_voiture)
{
    if(les_voitures[numero_voiture].vitesse + ACCELERATION * TIME_STEP < VITESSE_MAX)
    {
        les_voitures[numero_voiture].vitesse += ACCELERATION*TIME_STEP;
    }
    else les_voitures[numero_voiture].vitesse = VITESSE_MAX;
    
    // vitesse += ACCELERATION * TIME_STEP;
}


