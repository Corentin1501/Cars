#include "IA.h"

//##########################################
//                 DONNÉES                //
//##########################################

    extern struct car les_voitures[10];

    int mouvement_actuel_IA_carre = 1;
    float pas_IA_ellipse = 0;

//##########################################
//                FONCTIONS               //
//##########################################

    void jouer_IA_aleatoire(int numero_voiture)
    {
        // Initialiser le générateur de nombres aléatoires avec le temps actuel
        srand(time(NULL));

        // Générer un nombre aléatoire entre 0 et 3
        int mouvement_aleatoire = rand() % 4;

        switch (mouvement_aleatoire)
        {
            case 0: avancer_voiture(numero_voiture);        break;
            case 1: reculer_voiture(numero_voiture);        break;
            case 2: tourner_voiture_droite(numero_voiture); break;
            case 3: tourner_voiture_gauche(numero_voiture); break;
        }

        verif_dehors(numero_voiture);
    }

    void jouer_IA_carre(int numero_voiture)
    {
        switch (mouvement_actuel_IA_carre){
            case 1 :
                if (les_voitures[numero_voiture].position_z >= -90)  avancer_voiture(numero_voiture);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 2 :
                if (les_voitures[numero_voiture].position_x >= -38)  avancer_voiture(numero_voiture);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 3 :
                if (les_voitures[numero_voiture].position_z <= 90)  avancer_voiture(numero_voiture);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 4 :
                if (les_voitures[numero_voiture].position_x <= 38)  avancer_voiture(numero_voiture);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 5 :
                if (les_voitures[numero_voiture].position_z >= -90)  avancer_voiture(numero_voiture);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre = 2;
                }
                break;
        }
    }

    void jouer_IA_ellipse(int numero_voiture)
    {
        // Calcul des coordonnées de l'ellipse
        float x = 41 * cos(-pas_IA_ellipse);
        float y = 85 * sin(-pas_IA_ellipse);

        // Déplacement de la voiture aux coordonnées de l'ellipse
        les_voitures[numero_voiture].position_x = x;
        les_voitures[numero_voiture].position_z = y;

        // Calcul de l'orientation de la voiture
        float dx = -41 * sin(-pas_IA_ellipse);  // Dérivée de x par rapport à t
        float dy = 85 * cos(-pas_IA_ellipse);   // Dérivée de y par rapport à t
        les_voitures[numero_voiture].orientation = atan2(dx, dy) * 180 / 3.14159265359 + 180;

        pas_IA_ellipse += 0.01;
    }


    void jouer_les_IAs(int tempsEcoule)
    {
        jouer_IA_carre(1);    
        jouer_IA_ellipse(2);  
        jouer_IA_aleatoire(3);  
    }