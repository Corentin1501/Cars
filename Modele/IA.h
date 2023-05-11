#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Regles.h"
#include "../Controlleur/actions.h"
#include "../Vue/init.h"

// struct IA {};

void jouer_IA_aleatoire(int numero_voiture);
void jouer_IA_carre(int tempsEcoule);
void jouer_IA_ellipse(int tempsEcoule);
void jouer_les_IAs();


#endif // IA_H