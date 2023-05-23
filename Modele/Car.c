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

    for (int g = 0; g < NOMBRE_DE_GENES; g++) for (int param = 0; param < 8; param++)  une_voiture.genes[g][param] = false;

    une_voiture.aGagne = false;
    une_voiture.temps_victoire = 0.0;
    une_voiture.currentCP = 0;
    une_voiture.currentLap = 1;
    
    une_voiture.mouvementEffectue = 0;
    une_voiture.note = 0;
    une_voiture.aToucheLeMur = false;

    return une_voiture;
}

void resetVoiture(int numero_voiture, struct car* voitures)
{
    if (35 + (numero_voiture * 3) < 70) voitures[numero_voiture].position_x = 35 + (numero_voiture * 3);
    else                                voitures[numero_voiture].position_x = 35 + ((numero_voiture - 10) * 3);

    voitures[numero_voiture].position_y = 0.0;
    voitures[numero_voiture].position_z = 0.0;

    voitures[numero_voiture].orientation = 180;
    voitures[numero_voiture].vitesse = 0;

    for (int c = 0; c < 8; c++) voitures[numero_voiture].checkpoints[c] = false;

    voitures[numero_voiture].aGagne = false;
    voitures[numero_voiture].temps_victoire = 0.0;
    voitures[numero_voiture].currentCP = 0;
    voitures[numero_voiture].currentLap = 1;
    
    voitures[numero_voiture].mouvementEffectue = 0;
    voitures[numero_voiture].note = 0;
}

void afficherVoiture(int numero_voiture, struct car* voitures, int maxGenes)
{
    printf("\nindividu n°%d :\n", numero_voiture);
        printf("\t position :\t(%.1f,%.1f,%.1f)\n", voitures[numero_voiture].position_x, voitures[numero_voiture].position_y, voitures[numero_voiture].position_z);
        printf("\t orientation :\t%.1f\n", voitures[numero_voiture].orientation);
        printf("\t vitesse :\t%.1f\n", voitures[numero_voiture].vitesse);
        printf("\t mouvements : \t%d\n", voitures[numero_voiture].mouvementEffectue);
        printf("\t note : \t%d\n", voitures[numero_voiture].note);
        printf("\t temps : \t%.2f\n", voitures[numero_voiture].temps_victoire);
        printf("\n");
        for (int g = 0; g < maxGenes; g++)
        {
            printf("\t\t gene n°%d [", g);
            for (int move = 0; move < 5; move++)
            {
                // if (voitures[numero_voiture].genes[g][move]) printf("%s ; ", move);
                printf("%d ", voitures[numero_voiture].genes[g][move]);
            }
            printf("]\n");
        }
        printf("\n");
}