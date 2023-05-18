#ifndef REGLES_H
#define REGLES_H

#include "../Vue/init.h"    // pour le start_time
#include "stdbool.h"


extern const int NOMBRE_TOURS_POUR_GAGNER;
extern const int NOMBRE_CHECKPOINTS;

extern float chronometre;

void updateChrono();

// TOURS

    bool tourcompleted(int numVoiture, struct car* voitures);
    bool verifVictoire(int numVoiture, struct car* voitures);

// CHECKPOINTS

    bool checkpoint_dans_ordre(int numVoiture, struct car* voitures, int numeroCP);
    void activateCheckPoints(int numVoiture, struct car* voitures, int numeroCP);
    bool CP_passe(int numVoiture, struct car* voitures, int numeroCP);

    void verifier_checkpoints(int numVoiture, struct car* voitures);

#endif // REGLES_H