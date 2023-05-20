#include "Car.h"


const int NOMBRE_DE_GENES = 32;

struct car initialiser_voiture(int numero_voiture)
{
    struct car une_voiture;

    if (numero_voiture == 0)    // la voiture du joueur est le la voiture n°0
    {
        une_voiture.position_x = 35;
        une_voiture.IsVoitureDuJoueur = true;
    }
    else 
    {
        if (35 + (numero_voiture * 3) < 70) une_voiture.position_x = 35 + (numero_voiture * 3);
        else                                une_voiture.position_x = 35 + ((numero_voiture - 10) * 3);
        une_voiture.IsVoitureDuJoueur = false;
    } 

    une_voiture.position_y = 0.0;
    une_voiture.position_z = 0.0;

    une_voiture.orientation = 180;
    une_voiture.vitesse = 0;

    for (int c = 0; c < 8; c++) une_voiture.checkpoints[c] = false;

    for (int g = 0; g < 8; g++) for (int param = 0; param < 8; param++)  une_voiture.genes[g][param] = false;

    une_voiture.aGagne = false;
    une_voiture.temps_victoire = 0.0;
    une_voiture.currentCP = 0;
    une_voiture.currentLap = 1;
    
    une_voiture.mouvementEffectue = 0;
    une_voiture.note = 0;

    return une_voiture;
}

void afficherVoiture(struct car voiture)
{
    printf("\tposition :\t(%.1f,%.1f,%.1f)\n", voiture.position_x, voiture.position_y, voiture.position_z);
    printf("\torientation :\t%.1f\n", voiture.orientation);
    printf("\tvitesse :\t%.1f\n", voiture.vitesse);
    printf("\tjoueur ?\t%d\n", voiture.IsVoitureDuJoueur);
}