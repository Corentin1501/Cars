#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Controlleur/actions.h" // pour avoir le tableau de voitures

void jouer_IA_aleatoire(int numero_voiture);
void jouer_IA_carre(int tempsEcoule);
void jouer_IA_ellipse(int tempsEcoule);
void jouer_les_IAs();


#endif // IA_H