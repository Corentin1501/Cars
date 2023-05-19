#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "actions.h"
#include "../Modele/Regles.h"

void jouer_IA_aleatoire(int numero_voiture, struct car* voitures);
void jouer_IA_carre(int numero_voiture, struct car* voitures);
void jouer_IA_ellipse(int numero_voiture, struct car* voitures);
void jouer_les_IAs(int tempsEcoule);

int getCurrentGene(int numVoiture, struct car* tab);

void entrainerIAs();

extern const int NOMBRE_IA;
extern struct car lesIAs[7];


#endif // IA_H