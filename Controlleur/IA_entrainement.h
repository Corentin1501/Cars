#ifndef IA_ENTRAINEMENT_H
#define IA_ENTRAINEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../Modele/opmat.h"
#include "../Modele/Regles.h"


struct pos
{
    float x,y,z;
};

struct voitureIA 
{
    bool genes[8];
    float angleRotation;
    float vitesse;
    struct pos position;
    int CurrentCheckpoint;
    int CurrentLap;
};

void entrainerIAs();

#endif // IA_ENTRAINEMENT_H