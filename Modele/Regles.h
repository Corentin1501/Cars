#ifndef REGLES_H
#define REGLES_H

#include <stdbool.h>

extern const int NOMBRE_TOURS_POUR_GAGNER;
extern const int NOMBRE_CHECKPOINTS;

extern int Current_Lap;
extern int Current_CP;

extern float victory_time;
extern float chronometre;

extern bool victoire;

void updateChrono();
bool tourcompleted();
bool verifVictoire();
bool checkpoint_dans_ordre(int numeroCP);
void activateCheckPoints(int numeroCP);
bool CP_passe(int numeroCP);

#endif // REGLES_H