#include "Car.h"


struct car initialiser_voiture(int numero_voiture)
{
    struct car une_voiture;

    if (numero_voiture == 0)    // la voiture du joueur est le la voiture n°0
    {
        une_voiture.position_x = 35;
        une_voiture.IsVoitureDuJoueur = true;
        une_voiture.vitesse = 0;
    }
    else 
    {
        une_voiture.position_x = 35 + (numero_voiture * 3);
        une_voiture.IsVoitureDuJoueur = false;
        une_voiture.vitesse = 5;
    } 

    une_voiture.position_y = 0.0;
    une_voiture.position_z = 0.0;

    une_voiture.orientation = 180;

    for (int g = 0; g < 8; g++) une_voiture.checkpoints[g] = false;

    une_voiture.aGagne = false;
    une_voiture.temps_victoire = 0.0;
    une_voiture.currentCP = 0;
    une_voiture.currentLap = 1;
    

    return une_voiture;
}