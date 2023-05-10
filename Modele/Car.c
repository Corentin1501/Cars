#include "Car.h"


struct car initialiser_voiture(int numero_voiture)
{
    struct car une_voiture;

    //===== POSITION =====

    if (numero_voiture == 0)    // la voiture du joueur est le la voiture n°0
        une_voiture.position_x = 35;
    else 
        une_voiture.position_x = 35 + (numero_voiture * 3);

    une_voiture.position_y = 0.0;
    une_voiture.position_z = 0.0;

    une_voiture.orientation = 180;
    une_voiture.vitesse     = 0.0;

    return une_voiture;
}

void accelerate_car(struct car une_voiture)
{
    une_voiture.vitesse += ACCELERATION * TIME_STEP;
}