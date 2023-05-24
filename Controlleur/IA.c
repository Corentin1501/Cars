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
            case 0: avancer_voiture(numVoiture, voitures);                                                      break;
            case 1: avancer_voiture(numVoiture, voitures);        tourner_voiture_droite(numVoiture, voitures); break;
            case 2: tourner_voiture_droite(numVoiture, voitures);                                               break;
            case 3: reculer_voiture(numVoiture, voitures);        tourner_voiture_droite(numVoiture, voitures); break;
            case 4: reculer_voiture(numVoiture, voitures);                                                      break;
            case 5: reculer_voiture(numVoiture, voitures);        tourner_voiture_gauche(numVoiture, voitures); break;
            case 6: tourner_voiture_gauche(numVoiture, voitures);                                               break;
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
            if      ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (-17.5 <= tab[numVoiture].position_z) && (tab[numVoiture].position_z <=   0.0)) return 0;
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
            else if ((0 <= tab[numVoiture].position_x)  && (tab[numVoiture].position_x <= 75)   && (  0.0 < tab[numVoiture].position_z) && (tab[numVoiture].position_z < 17.5)) return 31;

            else return 666;
        }

        /*
            @param move le numéro du mouvement
            @return la chaine de caractère correspondant
        */
        char* afficherMove(int move)
        {
            switch (move)
            {
                case 0:  return "accelere";         break;
                case 1:  return "rien faire";       break;
                case 2:  return "freine";           break;
                case 3:  return "tourne à gauche";  break;
                case 4:  return "tourne à droite";  break;
                default: return "inconnu";          break;
            }
        }

        /*
            Affiche les infos d'une voiture :
            - sa position
            - le gène dans lequel elle est
            - le mouvement choisi dans son dernier gène
            @param numVoiture Numéro de la voiture
            @param voitures Tableau contenant les voitures
            @geneAAtteindre le gène à atteindre
        */
        void afficherStatsIA(int numeroIA, struct car* tableauIA, int geneAAtteindre)
        {
            printf("individu n°%d :", numeroIA);
                printf("\t(%.1f , %.1f)", tableauIA[numeroIA].position_x, tableauIA[numeroIA].position_z);
                printf("\t current gene : %d", getCurrentGene(numeroIA, tableauIA));
                    printf("\t gene n°%d [", geneAAtteindre - 1);
                    for (int move = 0; move < 5; move++)
                    {
                        if (tableauIA[numeroIA].genes[geneAAtteindre - 1][move]) printf("%s ; ", afficherMove(move));
                    }
                    printf("]\n");

        }

        /*
            Met à jour le chronomètre dédié à l'entrainement des IAs
        */
        void updateChronoDesIAs() 
        {
            chronometre = glutGet(GLUT_ELAPSED_TIME) - start_time_des_IAs;  // temps en millisecondes
            chronometre = chronometre / 1000.0;                             // temps en secondes
        }

        /*
            Vérifie si un mouvement a été choisi dans le gène en cours
        */
        void verifierMouvementDansGene(int numVoiture, struct car* voitures)
        {
            // On récupère le gène / position à laquelle est la voiture
            int currentGene = getCurrentGene(numVoiture, voitures);

            // On va vérifier s'il y a au moins un mouvement de choisis
            bool aucunMouvementInitialise = true;
            for (int move = 0; move < 5; move++) if(voitures[numVoiture].genes[currentGene][move]) aucunMouvementInitialise = false; 

            if(aucunMouvementInitialise)
            {
                srand((unsigned int)time(NULL));

                int mouvement_aleatoire;

                // Si on est dans une ligne droite, l'IA ne pourra que accélérer, freiner ou ne rien faire
                if((29 <= currentGene && currentGene <= 1) || (13 <= currentGene && currentGene <= 18)) 
                {
                    // Générer un nombre aléatoire entre 0 et 2
                    mouvement_aleatoire = rand() % 2;
                }
                else 
                {
                    // Générer un nombre aléatoire entre 0 et 4
                    mouvement_aleatoire = rand() % 4;
                }

                // si la vitesse n'est pas suffisante pour freiner et passer au prochain gène, on ne va pas freiner
                while (voitures[numVoiture].vitesse < 15 && mouvement_aleatoire == 2) mouvement_aleatoire = rand() % 5;

                // le mouvement choisis aléatoirement est choisis et on le met dans le gène
                voitures[numVoiture].genes[currentGene][mouvement_aleatoire] = true;

                // si le mouvement choisis est de tourner on fais aussi accélerer
                if (mouvement_aleatoire == 3 || mouvement_aleatoire == 4) voitures[numVoiture].genes[currentGene][0] = true;
            }
        }

    //=================================================
    //=             SAVE / LOAD LES GENES             =
    //=================================================

        /*
            Sauvegarde dans un fichier les gènes d'une voiture
            @param filePath chemin du fichier dans lequel sauvegarder
            @param numVoiture Numéro de la voiture
            @param voitures Tableau contenant les voitures
        */
        void saveDatasIA(char * filePath, int numVoiture, struct car * voitures)
        {
            FILE *fichier;
            fichier = fopen(filePath, "w");

            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier.\n");
                exit(1);
            }

            fprintf(fichier, "");

            for (int g = 0; g < NOMBRE_DE_GENES; g++)
            {   
                // pour garder 2 chiffres à chaque gène et lire plus facilement le fichier par la suite :
                if (g < 10) fprintf(fichier, "0%d : ", g);
                else        fprintf(fichier, "%d : ", g);

                for (int move = 0; move < 5; move++)
                {
                    fprintf(fichier, "%d ", voitures[numVoiture].genes[g][move]);
                }
                fprintf(fichier, "\n");
            }
            fprintf(fichier, "\n");

            fclose(fichier);
        }

        /*
            Charge dans une voiture les gènes sauvegarder dans un fichier
            @param filePath chemin du fichier duquel charger les gènes
            @param numVoiture Numéro de la voiture
            @param voitures Tableau contenant les voitures
        */
        void loadDataInIA(char * filePath, int numVoiture, struct car* voitures)
        {
            FILE *fichier;
            fichier = fopen(filePath, "r");

            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier.\n");
                exit(1);
            }

            const int MAXIMUM_DE_LIGNES = 32;
            char ligne[MAXIMUM_DE_LIGNES];

            int currentLine = 0;
            int currentMove = 0;
            char * currentChar;

            while (fgets(ligne, sizeof(ligne), fichier) != NULL) 
            {
                currentChar = strtok(ligne, ":");  // Découper la ligne en utilisant ":"

                if (currentChar != NULL) 
                {
                    currentChar = strtok(NULL, " ");  // Découper la partie après ":" en utilisant l'espace

                    while (currentChar != NULL) 
                    {
                        int move = atoi(currentChar);  // Convertir la sous-chaîne en entier

                        voitures[numVoiture].genes[currentLine][currentMove] = move;

                        currentChar = strtok(NULL, " ");  // Passer à la sous-chaîne suivante
                        
                        currentMove++;
                    }
                }

                currentMove = 0;
                currentLine++;
            }
            fclose(fichier);
        }

    //=================================================
    //=               MOUVEMENT DE L'IA               =
    //=================================================

        /*
            Va bouger la voiture de l'IA en fonction des mouvements définis dans ses gènes
            @param numVoiture Numéro de la voiture
            @param voitures Tableau contenant les voitures
        */
        void bougerIA(int numVoiture, struct car* voitures)
        {
            // On récupère le gène / position à laquelle est la voiture
            int currentGene = getCurrentGene(numVoiture, voitures);

            // On va vérifier s'il y a au moins un mouvement de choisis
            verifierMouvementDansGene(numVoiture, voitures);

            // Pour ce gène, on va regarder chaque mouvement / touches activé et choisis

            //----------------- appuie sur Z - accélère -----------------

                if (voitures[numVoiture].genes[currentGene][0])
                {
                    accelerer(numVoiture, voitures);  
                    avancer_voiture(numVoiture, voitures);
                }

            //----------------- appuie sur rien - décélère -----------------
            

                if (voitures[numVoiture].genes[currentGene][1])
                {
                    deceleration(numVoiture, voitures);      // diminue la vitesse 
                    if (voitures[numVoiture].vitesse > 0)        avancer_voiture(numVoiture, voitures);   // avance la voiture avec la nouvelle vitesse    
                    else if(voitures[numVoiture].vitesse < 0)    reculer_voiture(numVoiture, voitures);
                }

            //----------------- // appuie sur S - freine -----------------

                if (voitures[numVoiture].genes[currentGene][2])
                {
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
                }

            //----------------- appuie sur Q - tourne à gauche -----------------

                if (voitures[numVoiture].genes[currentGene][3])
                {
                    tourner_voiture_gauche(numVoiture, voitures); 
                }

            //----------------- appuie sur D - tourne à droite -----------------

                if (voitures[numVoiture].genes[currentGene][4])
                {
                    tourner_voiture_droite(numVoiture, voitures);
                }

            //------------------------------------------------------------------

            verif_dehors(numVoiture, voitures);
        }


    /*
        Va initialiser toutes les valeurs des voitures et faire accélrer dans le premier gène
    */
    void initialiserIA()
    {
        // initialiser les paramètres des IAs

            for (int ia = 0; ia < NOMBRE_IA; ia++) lesIAs[ia] = initialiser_voiture(ia + 3);    // les 3 premieres places des voitures sont deja prises     
        
        // changer les valeurs de départ des IAs

            for (int ia = 0; ia < NOMBRE_IA; ia++)
            {
                lesIAs[ia].genes[0][0] = true;  // le premier gène va faire accélerer toutes les IAs
            } 
    }

    //=================================================
    //=              ENTRAINEMENT DE L'IA             =
    //=================================================

        /*
            Entraîne les IAs à atteindre un gène donné
            @param geneAAtteindre gène que les IAs doivent atteindre
            @return le nombre de voiture qui ont réussi à atteindre ce gène
        */
        int entrainerIAsSurUnGene(int geneAAtteindre)
        {
            float tempsEntrainementDeDepart = glutGet(GLUT_ELAPSED_TIME) - start_time_des_IAs;
            int nombreVoitureFinis = 0;

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)    // on entraine chaque individus
            {
                int   currentGene   = getCurrentGene(indiv, lesIAs);
                float tempsDeDepart = glutGet(GLUT_ELAPSED_TIME) - start_time_des_IAs;
                float departChronometre = chronometre;


                // on entraine jusqu'a ce que l'individu atteigne le gene donné dans le temps donné
                // (notre tour le plus rapide est en 6.5s, donc une moyenne de 0.20 par gène, si l'IA met plus d'0.5 secondes par gène on arrête)
                while ((currentGene != geneAAtteindre) && ((chronometre - departChronometre) <= (0.5 * geneAAtteindre)))   
                {
                    currentGene = getCurrentGene(indiv, lesIAs);
                    updateChronoDesIAs();

                    ++ lesIAs[indiv].mouvementEffectue;
                
                    verifier_checkpoints(indiv, lesIAs);
                    bougerIA(indiv, lesIAs);
                }

                if(currentGene == geneAAtteindre) ++ nombreVoitureFinis;

                lesIAs[indiv].temps_victoire = glutGet(GLUT_ELAPSED_TIME) - tempsDeDepart;

                afficherStatsIA(indiv, lesIAs, geneAAtteindre);
            }

            printf("\tNombre de voiture qui ont réussis : %d\n\n", nombreVoitureFinis);
            return nombreVoitureFinis;
        }

    //=================================================
    //=               EVALUATION DE L'IA              =
    //=================================================

        /*
            Va donner une note à chaque IAs en fonction du nombre de mouvements effectué
        */
        void evaluerLesIAs(int geneAAtteindre)
        {
            int minMouvements = 10000000;
            int maxMouvements = 0;

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
            {
                if (getCurrentGene(indiv, lesIAs) == geneAAtteindre)
                {
                    if (lesIAs[indiv].mouvementEffectue > maxMouvements) maxMouvements = lesIAs[indiv].mouvementEffectue;
                    if (lesIAs[indiv].mouvementEffectue < minMouvements) minMouvements = lesIAs[indiv].mouvementEffectue;
                }
            }

            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
            {
                int note = 10.0;
                float moves = lesIAs[indiv].mouvementEffectue;

                if (getCurrentGene(indiv, lesIAs) == geneAAtteindre)
                {
                    while (moves > minMouvements)
                    {
                        note--;
                        moves -= 5;
                    }
                    lesIAs[indiv].note = note;
                }
                else lesIAs[indiv].note = 0;
            }
        }

    //=================================================
    //=                  CLONER L'IA                  =
    //=================================================

        /*
            Clone les gènes des 2 meilleurs IAs
            @param geneEtape gène qui est actuellement en entrainement
            @param nombreVoitureFinis nombre de voiture qui ont atteint le gène à atteindre
            @param nombreDIAQuiDoiventReussir nombre de voiture qui doivent réussir pour passer au prochain gène
            @param nombreDEssais nombre d'essais autorisé avant de passer au prochain gène
            @return le gène suivant à entrainer
        */
        int clonerLesIAs(int geneEtape, int nombreVoitureFinis, int nombreDIAQuiDoiventReussir, int nombreDEssais)
        {
            int individu_1er = 666;
            int individu_2e = 666;

            bool gene_du_1er[NOMBRE_DE_GENES][5];
            bool gene_du_2e[NOMBRE_DE_GENES][5];

            // On récupère les meileurs individus
            for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
            {
                if (lesIAs[indiv].note == 10) individu_1er = indiv;
                if (lesIAs[indiv].note == 9 || lesIAs[indiv].note == 8) individu_2e = indiv;
            }
            
            
            // Si on a au moins un individu qui a réussi
            if(individu_1er != 666 && nombreVoitureFinis >= nombreDIAQuiDoiventReussir)
            {
                // si on a pas de 2e alors le 2e sera le même que le 1er
                if (individu_2e == 666) individu_2e = individu_1er;

                // On sauvegarde temporairement les gènes des deux meilleurs
                for (int g = 0; g < NOMBRE_DE_GENES; g++) 
                {
                    for (int move = 0; move < 5; move++)
                    {
                        gene_du_1er[g][move] = lesIAs[individu_1er].genes[g][move];
                        gene_du_2e[g][move] = lesIAs[individu_2e].genes[g][move];
                    }
                }

                // On copie les gènes des meilleurs individus dans les autres individus
                for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
                {
                    for (int g = 0; g < geneEtape; g++)
                    {
                        for (int move = 0; move < 5; move++)
                        {   
                            // les 3 premiers individus seront comme le meilleur individu
                            if(indiv < 3)   lesIAs[indiv].genes[g][move] = gene_du_1er[g][move];
                            // le reste des individus seront comme le deuxième meilleur individu
                            else            lesIAs[indiv].genes[g][move] = gene_du_2e[g][move];
                        }
                    }
                }
                return geneEtape;
            }
            else // si aucun ou pas assez d'individus n'ont pas réussi alors on recommence le gène en cours
            {
                if (nombreDEssais > 0)
                {
                    for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
                    {
                        if (getCurrentGene(indiv, lesIAs) != geneEtape)
                        {
                            for (int move = 0; move < 5; move++)
                            {
                                lesIAs[indiv].genes[geneEtape-1][move] = false;
                            }
                        }
                    }
                    return geneEtape - 1;
                }
            }
        }

    //=================================================
    //=      ENTRAINER, EVALUER ET CLONER LES IAS     =
    //=================================================

        void jouer_IA_smart()
        {
            initialiserIA();

            int geneAAtteindre = 8;
            int nombreVoitureFinis = 0;
            float tauxDeReussite = 0.5;
            float nombreDIAQuiDoiventReussir = NOMBRE_IA * tauxDeReussite;
            int nombreDEssais = 3;
            int dernierGeneEntraine = 666;

            printf("\nNombre D'IA qui doivent réussir : %.0f\n\n", nombreDIAQuiDoiventReussir);

            for (int geneEtape = 1; geneEtape < geneAAtteindre; geneEtape++)
            {
                if (geneEtape == dernierGeneEntraine)   nombreDEssais--;
                else                                    nombreDEssais = 3;

                dernierGeneEntraine = geneEtape;

                printf("----------- Gene à atteindre en entrainement : %d -----------\n", geneEtape);
                
                // On remet toutes les IAs au début de la courses mais on garde les gènes

                    for (int indiv = 0; indiv < NOMBRE_IA; indiv++) resetVoiture(indiv, lesIAs);

                // entrainement 
                
                    nombreVoitureFinis = entrainerIAsSurUnGene(geneEtape);
                
                // évaluation des résultats
                
                    evaluerLesIAs(geneEtape);

                // Clonage des meilleurs individu

                    geneEtape = clonerLesIAs(geneEtape, nombreVoitureFinis, nombreDIAQuiDoiventReussir, nombreDEssais);
            }

            // Afficher les résultats / données des IAs

                bool afficherLesResultats = !true;

                int meilleurIndividu = 0;

                if (afficherLesResultats)
                {
                    for (int indiv = 0; indiv < NOMBRE_IA; indiv++)
                    {
                        if(lesIAs[indiv].note > lesIAs[meilleurIndividu].note) meilleurIndividu = indiv;    // on garde en mémoire le meilleur individu pour sauvegarder ses gènes plus tard
                        printf("individu n°%d :", indiv);
                            printf("\t(%.1f , %.1f)", lesIAs[indiv].position_x, lesIAs[indiv].position_z);
                            printf("\t current gene : %d", getCurrentGene(indiv, lesIAs));
                            printf("\t mouvements : %d", lesIAs[indiv].mouvementEffectue);
                            printf("\t note : %d", lesIAs[indiv].note);
                            printf("\t temps : %.2f", lesIAs[indiv].temps_victoire);
                            printf("\n");
                            for (int g = 0; g < geneAAtteindre; g++)
                            {
                                printf("\t\t gene n°%d [", g);
                                for (int move = 0; move < 5; move++)
                                {
                                    if (lesIAs[indiv].genes[g][move]) printf("%s ; ", afficherMove(move));
                                }
                                printf("]\n");
                            }
                            
                    }
                }

                // sauvegarde des meilleurs gènes dans le fichier "bestGenes.txt"

                    saveDatasIA("bestGenes.txt", meilleurIndividu, lesIAs);

        }



//##########################################
//#          JOUER TOUTES LES IAS          #
//##########################################

    void jouer_les_IAs(int tempsEcoule)
    {
        jouer_IA_carre(1, les_voitures);    
        jouer_IA_ellipse(2, les_voitures);  
        jouer_IA_aleatoire(3, les_voitures);  
        bougerIA(4, les_voitures);
    }