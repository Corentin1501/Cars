#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#include "Car.h"

#define M_PI 3.14159265358979323846

void accelerer(int numVoiture, struct car* voitures);
void marcheArriere(int numVoiture, struct car* voitures);
void deceleration(int numVoiture, struct car* voitures);
void freinage(int numVoiture, struct car* voitures);

void avancer_voiture(int numVoiture, struct car* voitures);
void reculer_voiture(int numVoiture, struct car* voitures);
void tourner_voiture_gauche(int numVoiture, struct car* voitures);
void tourner_voiture_droite(int numVoiture, struct car* voitures);

void verif_dehors(int numVoiture, struct car* voitures);


#endif // PHYSIQUE_H