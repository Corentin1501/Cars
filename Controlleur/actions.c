#include "actions.h"

#define M_PI 3.14159265358979323846

// importation des données

    extern int blend;
    extern int light;

// tableau des touches (pour appuyer sur plusieurs touches en même temps)

    bool etatTouches[256];

// les coordonées de la caméra 
    // vue FPS
        float camera_FPS_x = 35;              
        float camera_FPS_y = 0.65;       
        float camera_FPS_z = 0;       
    // vue TPS
        float camera_TPS_x = 35;              
        float camera_TPS_y = 1.5;      
        float camera_TPS_z = 7.2;      
    // son orientation
        float camera_orientation_x = 0;   
        float camera_orientation_z = -5;   
    // la vue
        bool vue_FPS = false;
        bool vue_TPS = true;
        bool vue_ARR = false;
// tableau des voitures        
    struct car les_voitures[10];

float TPS_en_arriere = 7.2; // nombre de blocs derriere la voiture où est la caméra TPS
float TPS_au_dessus = 1.5; // nombre de blocs au dessus de la voiture où est la caméra TPS
float FPS_au_dessus = 0.65; // nombre de blocs au dessus de la voiture où est la caméra FPS

const int VOITURE_DU_JOUEUR = 0;

//#####################################################
//#              INITIALISER LES VALEURS              #
//#####################################################

    void creer_toutes_les_voitures()
    {
        for (int i = 0; i < 10; i++)
        {
            les_voitures[i] = initialiser_voiture(i);
        }
    }

    void initialiser_touches()
    {
        for(int i=0; i<256; i++) etatTouches[i] = false;
    }

    void initialiser_voitures_et_touches()
    {
        creer_toutes_les_voitures();
        initialiser_touches();
    }

//#####################################################
//#          MAJ DES POSITIONS DE LA CAMERA           #
//#####################################################

    void updateCameraTPS()
    {
        camera_TPS_x = les_voitures[VOITURE_DU_JOUEUR].position_x - (TPS_en_arriere * (sin((les_voitures[VOITURE_DU_JOUEUR].orientation * M_PI) / 180)));
        camera_TPS_y = les_voitures[VOITURE_DU_JOUEUR].position_y + TPS_au_dessus;
        camera_TPS_z = les_voitures[VOITURE_DU_JOUEUR].position_z - (TPS_en_arriere * (cos((les_voitures[VOITURE_DU_JOUEUR].orientation * M_PI) / 180)));
    }

    void updateCameraFPS()
    {
        camera_FPS_x = les_voitures[VOITURE_DU_JOUEUR].position_x;
        camera_FPS_y = FPS_au_dessus;
        camera_FPS_z = les_voitures[VOITURE_DU_JOUEUR].position_z;
    }

    void updateCameras()
    {
        updateCameraFPS();
        updateCameraTPS();

        camera_orientation_x = sin((les_voitures[VOITURE_DU_JOUEUR].orientation * M_PI) / 180);
        camera_orientation_z = cos((les_voitures[VOITURE_DU_JOUEUR].orientation * M_PI) / 180);
    }

//#####################################################
//#          MAJ POSITION VOITURE DU JOUEUR           #
//#####################################################

    void mettre_a_jour_position_voiture()
    {
        if (etatTouches[TOUCHE_Z])
        { 
            accelerer(VOITURE_DU_JOUEUR, les_voitures);       // augmente la vitesse
            avancer_voiture(VOITURE_DU_JOUEUR, les_voitures); // avance la voiture avec la nouvelle vitesse    
        }   
        if ((etatTouches[TOUCHE_Z]==false) && (etatTouches[TOUCHE_S] == false))
        {
            deceleration(VOITURE_DU_JOUEUR, les_voitures);      // diminue la vitesse 
            if (les_voitures[VOITURE_DU_JOUEUR].vitesse > 0)        avancer_voiture(VOITURE_DU_JOUEUR, les_voitures);   // avance la voiture avec la nouvelle vitesse    
            else if(les_voitures[VOITURE_DU_JOUEUR].vitesse < 0)    reculer_voiture(VOITURE_DU_JOUEUR, les_voitures);
        }
        if (etatTouches[TOUCHE_S])
        { 
            if (les_voitures[VOITURE_DU_JOUEUR].vitesse > 0)    // si le joueur avance on freine la voiture
            {
                freinage(VOITURE_DU_JOUEUR, les_voitures);        // diminue fortement la vitesse          
                avancer_voiture(VOITURE_DU_JOUEUR, les_voitures); // avance la voiture avec la nouvelle vitesse    
            }
            else    // si la voiture est à l'arrêt ou recule on augmente la vitesse en marche arrière
            {
                marcheArriere(VOITURE_DU_JOUEUR, les_voitures);       // augmente la vitesse en arrière (vitesse négativement)
                reculer_voiture(VOITURE_DU_JOUEUR, les_voitures);     // fait reculer la voiture avec la nouvelle vitesse
            }
        } 

        if (etatTouches[TOUCHE_Q]){ tourner_voiture_gauche(VOITURE_DU_JOUEUR, les_voitures);   } 
        if (etatTouches[TOUCHE_D]){ tourner_voiture_droite(VOITURE_DU_JOUEUR, les_voitures);   } 

        verif_dehors(VOITURE_DU_JOUEUR, les_voitures);

        updateCameras();

        glutPostRedisplay();
        glutTimerFunc(10, mettre_a_jour_position_voiture, 10);
    }

//#####################################################
//#                GESTION DES TOUCHES                #
//#####################################################

    void touche_relachee(unsigned char key, int x, int y)
    {
        etatTouches[key] = false;   
    }


    void touche_pressee(unsigned char key, int x, int y) 
    {
        etatTouches[key] = true;

        switch (key)
        {    
            case ESCAPE: exit(1); break;                // la touche ECHAP quitte l'application

            case TAB:   
                vue_ARR = !vue_ARR;
                break;

            case TOUCHE_MIN_B: 
            case TOUCHE_MAJ_B: 
                blend =  switch_blend(blend);
                break;

            case TOUCHE_MIN_L: 
            case TOUCHE_MAJ_L: 
                light = switch_light(light);
                break;

            //####### VUE CAMERA #######

                case TOUCHE_W:
                    vue_FPS = !vue_FPS;
                    vue_TPS = !vue_TPS;
                    break;
        }	
    }

    void touche(int touche, int x, int y)
    {
        // touche spéciale (F1 - F12)
    }











