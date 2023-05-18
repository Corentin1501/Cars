#include "IA.h"

//##########################################
//#                 DONNÉES                #
//##########################################

    int mouvement_actuel_IA_carre = 1;
    float pas_IA_ellipse = 0;

    const int NOMBRE_IA = 5;

    struct car lesIAs[5];

//##########################################
//#               IA SCRIPTÉES             #
//##########################################

    void jouer_IA_aleatoire(int numVoiture, struct car* voitures)
    {
        // Initialiser le générateur de nombres aléatoires avec le temps actuel
        srand(time(NULL));

        // Générer un nombre aléatoire entre 0 et 8
        int mouvement_aleatoire = rand() % 8;

        switch (mouvement_aleatoire)
        {
            case 0: avancer_voiture(numVoiture, voitures);                                                break;
            case 1: avancer_voiture(numVoiture, voitures);        tourner_voiture_droite(numVoiture, voitures); break;
            case 2: tourner_voiture_droite(numVoiture, voitures);                                         break;
            case 3: reculer_voiture(numVoiture, voitures);        tourner_voiture_droite(numVoiture, voitures); break;
            case 4: reculer_voiture(numVoiture, voitures);                                                break;
            case 5: reculer_voiture(numVoiture, voitures);        tourner_voiture_gauche(numVoiture, voitures); break;
            case 6: tourner_voiture_gauche(numVoiture, voitures);                                         break;
            case 7: avancer_voiture(numVoiture, voitures);        tourner_voiture_gauche(numVoiture, voitures); break;
        }

        verif_dehors(numVoiture, voitures);
    }

    void jouer_IA_carre(int numVoiture, struct car* voitures)
    {
        switch (mouvement_actuel_IA_carre){
            case 1 :
                if (voitures[numVoiture].position_z >= -90)  avancer_voiture(numVoiture, voitures);
                else {
                    voitures[numVoiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 2 :
                if (voitures[numVoiture].position_x >= -38)  avancer_voiture(numVoiture, voitures);
                else {
                    voitures[numVoiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 3 :
                if (voitures[numVoiture].position_z <= 90)  avancer_voiture(numVoiture, voitures);
                else {
                    voitures[numVoiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 4 :
                if (voitures[numVoiture].position_x <= 38)  avancer_voiture(numVoiture, voitures);
                else {
                    voitures[numVoiture].orientation += 90; 
                    mouvement_actuel_IA_carre++;
                }
                break;
            case 5 :
                if (voitures[numVoiture].position_z >= -90)  avancer_voiture(numVoiture, voitures);
                else {
                    voitures[numVoiture].orientation += 90; 
                    mouvement_actuel_IA_carre = 2;
                }
                break;
        }
    }

    void jouer_IA_ellipse(int numVoiture, struct car* voitures)
    {
        // Calcul des coordonnées de l'ellipse
        float x = 41 * cos(-pas_IA_ellipse);
        float y = 85 * sin(-pas_IA_ellipse);

        // Déplacement de la voiture aux coordonnées de l'ellipse
        voitures[numVoiture].position_x = x;
        voitures[numVoiture].position_z = y;

        // Calcul de l'orientation de la voiture
        float dx = -41 * sin(-pas_IA_ellipse);  // Dérivée de x par rapport à t
        float dy = 85 * cos(-pas_IA_ellipse);   // Dérivée de y par rapport à t
        voitures[numVoiture].orientation = atan2(dx, dy) * 180 / 3.14159265359 + 180;

        pas_IA_ellipse += 0.01;
    }

//##########################################
//#            IA INTELLIGENTES            #
//##########################################

    void bougerIA(int numVoiture, struct car* voitures)
    {
        srand(time(NULL));
        int mouvement_aleatoire = rand() % 5;

        switch (mouvement_aleatoire)
        {
            case 0:  // appuyer sur Z

                accelerer(numVoiture, voitures);  
                avancer_voiture(numVoiture, voitures);
                break;

            case 1:  // appuer sur S

                if (voitures[numVoiture].vitesse > 0)
                {
                    freinage(numVoiture, voitures);        // diminue fortement la vitesse          
                    avancer_voiture(numVoiture, voitures); // avance la voiture avec la nouvelle vitesse    
                }
                else    // si la voiture est à l'arrêt ou recule on augmente la vitesse en marche arrière
                {
                    marcheArriere(numVoiture, voitures);       // augmente la vitesse en arrière (vitesse négativement)
                    reculer_voiture(numVoiture, voitures);     // fait reculer la voiture avec la nouvelle vitesse
                }
                break;

            case 2:  // appuer sur D

                tourner_voiture_droite(numVoiture, voitures); 
                break;

            case 3:  // appuer sur Q

                tourner_voiture_gauche(numVoiture, voitures); 
                break;

            case 4:  // appuer sur rien

                deceleration(numVoiture, voitures);      // diminue la vitesse 
                if (voitures[numVoiture].vitesse > 0)        avancer_voiture(numVoiture, voitures);   // avance la voiture avec la nouvelle vitesse    
                else if(voitures[numVoiture].vitesse < 0)    reculer_voiture(numVoiture, voitures);

                break;
        }
    }

    void entrainerIAs()
    {
        for (int ia = 0; ia < NOMBRE_IA; ia++)     lesIAs[ia] = initialiser_voiture(1);    // tous comme une voiture n°1 
        

        // entrainement

            float tempsEntrainementDeDepart = glutGet(GLUT_ELAPSED_TIME) - start_time;

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)    // on entraine chaque individus
            {
                float tempsDeDepart  = glutGet(GLUT_ELAPSED_TIME) - start_time;

                printf("-------- Entrainement de l'individu n°%d --------\n", indiv);

                int nombreDeMouvements = 0;

                float departChronometre = chronometre;

                while (!lesIAs[indiv].checkpoints[0] && (chronometre - departChronometre) <= 5)   // on entraine jusqu'a ce que l'individu atteigne le premier CP
                {
                    updateChrono();
                    /*
                        Choix possibles de l'IA :
                        - appuyer sur Z     accélerer
                        - appuyer sur S     freiner
                        - appuyer sur D     tourner à droite
                        - appuyer sur Q     tourner à gauche
                        - ne rien appuyer   décelerer
                    */
                   ++ nombreDeMouvements;
                   
                    verifier_checkpoints(indiv, lesIAs);
                    bougerIA(indiv, lesIAs);
                }

                lesIAs[indiv].temps_victoire = glutGet(GLUT_ELAPSED_TIME) - tempsDeDepart;

                printf("\tNombre de mouvements effectués : %d\n", nombreDeMouvements);

            }

            printf("\ntemps d'entrainement : %f \n", (glutGet(GLUT_ELAPSED_TIME) - tempsEntrainementDeDepart));

        // évaluation des résultats




        // Afficher les résultats / données des IAs

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
            {
                printf("individu n°%d :\t[", indiv);
                for (int g = 0; g < NOMBRE_CHECKPOINTS; g++)
                {
                    if (g != 7) printf("%d,",   lesIAs[indiv].checkpoints[g]);
                    if (g == 7) printf("%d]\t(%.1f , %.1f)\t temps : %f\n", lesIAs[indiv].checkpoints[g], lesIAs[indiv].position_x, lesIAs[indiv].position_z, lesIAs[indiv].temps_victoire);
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