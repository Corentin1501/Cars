#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "actions.h" // pour avoir les fonctions de déplacement de voiture et la struct car

void jouer_IA_aleatoire(int numero_voiture);
void jouer_IA_carre(int numero_voiture);
void jouer_IA_ellipse(int numero_voiture);
void jouer_les_IAs();


#endif // IA_H