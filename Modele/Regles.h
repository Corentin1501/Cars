#ifndef REGLES_H
#define REGLES_H

#include "../Vue/init.h"    // pour le start_time
#include "stdbool.h"


extern const int NOMBRE_TOURS_POUR_GAGNER;
extern const int NOMBRE_CHECKPOINTS;

extern int Current_Lap;
extern int Current_CP;

extern float victory_time;
extern float chronometre;

extern bool victoire;

void updateChrono();

bool verifVictoire();

void verifier_checkpoints();

#endif // REGLES_H