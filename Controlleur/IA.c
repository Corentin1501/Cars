#include "IA.h"

//##########################################
//#                 DONNÉES                #
//##########################################

    int mouvement_actuel_IA_carre = 1;
    float pas_IA_ellipse = 0;

    struct car lesIAs[20];

//##########################################
//#               IA SCRIPTÉES             #
//##########################################

    void jouer_IA_aleatoire(int numero_voiture, struct car* voitures)
    {
        // Initialiser le générateur de nombres aléatoires avec le temps actuel
        srand(time(NULL));

        // Générer un nombre aléatoire entre 0 et 8
        int mouvement_aleatoire = rand() % 8;

        switch (mouvement_aleatoire)
        {
            case 0: avancer_voiture(numero_voiture, voitures);                                                break;
            case 1: avancer_voiture(numero_voiture, voitures);        tourner_voiture_droite(numero_voiture, voitures); break;
            case 2: tourner_voiture_droite(numero_voiture, voitures);                                         break;
            case 3: reculer_voiture(numero_voiture, voitures);        tourner_voiture_droite(numero_voiture, voitures); break;
            case 4: reculer_voiture(numero_voiture, voitures);                                                break;
            case 5: reculer_voiture(numero_voiture, voitures);        tourner_voiture_gauche(numero_voiture, voitures); break;
            case 6: tourner_voiture_gauche(numero_voiture, voitures);                                         break;
            case 7: avancer_voiture(numero_voiture, voitures);        tourner_voiture_gauche(numero_voiture, voitures); break;
        }

        verif_dehors(numero_voiture, voitures);
    }

    void jouer_IA_carre(int numero_voiture, struct car* voitures)
    {
        switch (mouvement_actuel_IA_carre){
            case 1 :
                if (les_voitures[numero_voiture].position_z >= -90)  avancer_voiture(numero_voiture, voitures);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 2 :
                if (les_voitures[numero_voiture].position_x >= -38)  avancer_voiture(numero_voiture, voitures);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 3 :
                if (les_voitures[numero_voiture].position_z <= 90)  avancer_voiture(numero_voiture, voitures);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 4 :
                if (les_voitures[numero_voiture].position_x <= 38)  avancer_voiture(numero_voiture, voitures);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 5 :
                if (les_voitures[numero_voiture].position_z >= -90)  avancer_voiture(numero_voiture, voitures);
                else {
                    les_voitures[numero_voiture].orientation += 90; 
                    mouvement_actuel_IA_carre = 2;
                }
                break;
        }
    }

    void jouer_IA_ellipse(int numero_voiture, struct car* voitures)
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

//##########################################
//#            IA INTELLIGENTES            #
//##########################################

    /*
        Choix possibles de l'IA :
        - appuyer sur Z     accélerer
        - appuyer sur S     freiner
        - appuyer sur Q     tourner à gauche
        - appuyer sur D     tourner à droite
        - ne rien appuyer   décelerer
    */

    void entrainerIAs()
    {
        for (int ia = 0; ia < 20; ia++)     lesIAs[ia] = initialiser_voiture(1);    // tous comme une voiture n°1 
        

        // entrainement
        

            for (int indiv = 0; indiv < 20; indiv++)
            {
                while (!lesIAs[indiv].checkpoints[0])
                {
                    verifier_checkpoints(indiv, lesIAs);
                    avancer_voiture(indiv, lesIAs);
                }
            }

        // Afficher les résultats / données des IAs

            for (int indiv = 0; indiv < 20; indiv++)
            {
                printf("individu n°%d :\t[", indiv);
                for (int g = 0; g < 8; g++)
                {
                    if (g != 7) printf("%d,",   lesIAs[indiv].checkpoints[g]);
                    if (g == 7) printf("%d]\t(%.1f , %.1f)\n", lesIAs[indiv].checkpoints[g], lesIAs[indiv].position_x, lesIAs[indiv].position_z);
                }
            }
    }

//##########################################
//#          JOUER TOUTES LES IAS          #
//##########################################

    void jouer_les_IAs(int tempsEcoule)
    {
        jouer_IA_carre(1, les_voitures);    
        jouer_IA_ellipse(2, les_voitures);  
        jouer_IA_aleatoire(3, les_voitures);  
    }