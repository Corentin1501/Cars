#include "IA.h"

//##########################################
//#                 DONNÉES                #
//##########################################

    int mouvement_actuel_IA_carre = 1;
    float pas_IA_ellipse = 0;

    const int NOMBRE_IA = 7;

    struct car lesIAs[7];

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
        voitures[numVoiture].vitesse = 5.0;

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

    //=================================================
    //=                     GÈNES                     =
    //=================================================

        /*
            Définis les limites des zones des différents gènes.
            @param numVoiture Numéro de la voiture
            @param voitures Tableau contenant les voitures
            @return le numéro du gène dans lequel se trouve la voiture donnée
        */
        int getCurrentGene(int numVoiture, struct car* tab)
        {
            if      ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (-17.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <   0.0)) return 0;
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (-35.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -17.5)) return 1;    
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (-52.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -35.0)) return 2;    
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (-70.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -52.5)) return 3;
            else if (((-tab[numVoiture].position_x) / 2.5 - 70 < tab[numVoiture].position_z)    && (-70.0 >= tab[numVoiture].position_z)) return 4;     
            else if (((-tab[numVoiture].position_x) / 2.5 - 70 > tab[numVoiture].position_z)    && (-tab[numVoiture].position_x)       - 70 < tab[numVoiture].position_z) return 5;     
            else if (((-tab[numVoiture].position_x)       - 70 > tab[numVoiture].position_z)    && (-tab[numVoiture].position_x) * 2.5 - 70 < tab[numVoiture].position_z) return 6;     
            else if (((-tab[numVoiture].position_x) * 2.5 - 70 > tab[numVoiture].position_z)    && (  0.0 <= tab[numVoiture].position_x)) return 7;    
            else if ((( tab[numVoiture].position_x) * 2.5 - 70 > tab[numVoiture].position_z)    && (  0.0 >= tab[numVoiture].position_x)) return 8;    
            else if ((( tab[numVoiture].position_x)       - 70 > tab[numVoiture].position_z)    && ( tab[numVoiture].position_x) * 2.5 - 70 < tab[numVoiture].position_z) return 9;     
            else if ((( tab[numVoiture].position_x) / 2.5 - 70 > tab[numVoiture].position_z)    && ( tab[numVoiture].position_x)       - 70 < tab[numVoiture].position_z) return 10;     
            else if ((( tab[numVoiture].position_x) / 2.5 - 70 < tab[numVoiture].position_z)    && (-70.0 >= tab[numVoiture].position_z)) return 11;     
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && (-70.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -52.5)) return 12;
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && (-52.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -35.0)) return 13;    
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && (-35.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < -17.5)) return 14;    
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && (-17.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <   0.0)) return 15;
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && (  0.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <  17.5)) return 16;
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && ( 17.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <  35.0)) return 17;    
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && ( 35.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <  52.5)) return 18;    
            else if ((-75 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 0)   && ( 52.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <  70.0)) return 19;
            else if (((-tab[numVoiture].position_x) / 2.5 + 70 > tab[numVoiture].position_z)    && ( 70.0 <= tab[numVoiture].position_z)) return 20;    
            else if (((-tab[numVoiture].position_x) / 2.5 + 70 < tab[numVoiture].position_z)    && (-tab[numVoiture].position_x)       + 70 > tab[numVoiture].position_z) return 21;
            else if (((-tab[numVoiture].position_x)       + 70 < tab[numVoiture].position_z)    && (-tab[numVoiture].position_x) * 2.5 + 70 > tab[numVoiture].position_z) return 22;     
            else if (((-tab[numVoiture].position_x) * 2.5 + 70 < tab[numVoiture].position_z)    && (  0.0 >= tab[numVoiture].position_x)) return 23;  
            else if ((( tab[numVoiture].position_x) * 2.5 + 70 < tab[numVoiture].position_z)    && (  0.0 <= tab[numVoiture].position_x)) return 24;  
            else if ((( tab[numVoiture].position_x)       + 70 < tab[numVoiture].position_z)    && ( tab[numVoiture].position_x) * 2.5 + 70 > tab[numVoiture].position_z) return 25;     
            else if ((( tab[numVoiture].position_x) / 2.5 + 70 < tab[numVoiture].position_z)    && ( tab[numVoiture].position_x)       + 70 > tab[numVoiture].position_z) return 26;
            else if ((( tab[numVoiture].position_x) / 2.5 + 70 > tab[numVoiture].position_z)    && ( 70.0 <= tab[numVoiture].position_z)) return 27;    
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && ( 52.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < 70.0)) return 28;
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && ( 35.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < 52.5)) return 29;    
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && ( 17.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < 35.0)) return 30;    
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (  0.0 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z < 17.5)) return 31;

            else return 666;
        }

        // void verifier_genes(int numVoiture, struct car* voitures)
        // {
        //     for (int unGene = 0; unGene < NOMBRE_DE_GENES; unGene++){
        //         if(genePasse(numVoiture, voitures, unGene)){
        //             activateCheckPoints(numVoiture, voitures, unGene);
        //         }
        //     }
        // }   

    void bougerIA(int numVoiture, struct car* voitures)
    {
        int mouvement = 0;

        if (voitures[numVoiture].currentCP == 0) mouvement = 0;

        switch (mouvement)
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
        verif_dehors(numVoiture, voitures);
    }

    void initialiserIA()
    {
        // initialiser les paramètres des IAs

            for (int ia = 0; ia < NOMBRE_IA; ia++) lesIAs[ia] = initialiser_voiture(ia + 3);    // les 3 premieres places des voitures sont deja prises     
        
        // changer les valeurs de départ des IAs




            for (int ia = 0; ia < NOMBRE_IA; ia++)
            {
                lesIAs[ia].genes[0][0] = true;  // le premier gène va faire accélerer toutes les IAs
            } 

        // printf("\n");

    }


    void entrainerIAs()
    {
        initialiserIA();

        // entrainement

            float tempsEntrainementDeDepart = glutGet(GLUT_ELAPSED_TIME) - start_time;

            int nombreVoitureFinis = 0;

            bool entrainerLesVoitures = true;

            if (entrainerLesVoitures)
            {
                for (int indiv = 0; indiv < NOMBRE_IA; indiv++)    // on entraine chaque individus
                {
                    float tempsDeDepart  = glutGet(GLUT_ELAPSED_TIME) - start_time;

                    // printf("-------- Entrainement de l'individu n°%d --------\n", indiv);

                    float departChronometre = chronometre;

                    // printf("\ttemps de depart : %.2f\n", departChronometre);

                    // on entraine jusqu'a ce que l'individu atteigne le premier CP avant 5 secondes découlées
                    while (!lesIAs[indiv].checkpoints[0] && (chronometre - departChronometre) <= 1)   
                    {
                        updateChrono();

                        ++ lesIAs[indiv].mouvementEffectue;
                    
                        verifier_checkpoints(indiv, lesIAs);
                        bougerIA(indiv, lesIAs);
                    }

                    if(lesIAs[indiv].checkpoints[0]) ++ nombreVoitureFinis;

                    lesIAs[indiv].temps_victoire = glutGet(GLUT_ELAPSED_TIME) - tempsDeDepart;

                    // printf("\tNombre de mouvements effectués : %d\n\n", lesIAs[indiv].mouvementEffectue);

                }
            }

        // évaluation des résultats

            printf("\nNombre de voiture qui ont finis : %d\n", nombreVoitureFinis);



        // Afficher les résultats / données des IAs

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
            {
                printf("individu n°%d :\t[", indiv);
                for (int g = 0; g < NOMBRE_CHECKPOINTS; g++)
                {
                    if (g != 7) printf("%d,",   lesIAs[indiv].checkpoints[g]);
                    if (g == 7)
                    {
                        printf("%d]\t(%.1f , %.1f)", lesIAs[indiv].checkpoints[g], lesIAs[indiv].position_x, lesIAs[indiv].position_z);
                        // printf("\t temps : %f\n", lesIAs[indiv].temps_victoire);
                        printf("\t mouvements : %d\n", lesIAs[indiv].mouvementEffectue);
                    } 
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