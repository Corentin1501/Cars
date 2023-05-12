#ifndef HUD_H
#define HUD_H

#include "stdbool.h"

#include "../Modele/Regles.h"
/*
    #include "Regles.h" pour utiliser ces variables :
        - NOMBRE_CHECKPOINTS
        - Current_Lap
        - Current_CP
        - victory_time
        - chronometre
        - victoire

        - les_voitures[]
*/

void glutBitmapString(void *font, const unsigned char *string);

void drawHUD();

#endif // HUD_H