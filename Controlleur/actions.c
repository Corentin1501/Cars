#include "actions.h"

#define M_PI 3.14159265358979323846

// importation des données

    extern int blend;
    extern int light;

// physique

    const float ACCELERATION = 2.0;
    const float VITESSE_MAX  = 25.0;
    const float VITESSE_MAX_ARRIERE  = 12.5;
    const float TIME_STEP    = 0.1;
    float vitesse_arriere=0.0;

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
//#                     PHYSIQUE                      #
//#####################################################

    // Augmente la vitesse de la voiture
    void accelerer(int numero_voiture)
    {
        if(les_voitures[numero_voiture].vitesse + ACCELERATION * TIME_STEP < VITESSE_MAX)
            les_voitures[numero_voiture].vitesse += ACCELERATION*TIME_STEP;
        else 
            les_voitures[numero_voiture].vitesse = VITESSE_MAX;
    }
    
    // Diminue la vitesse de la voiture
    void deceleration(int numero_voiture)
    {
        if (les_voitures[numero_voiture].vitesse - 0.1 > 0.0)
            les_voitures[numero_voiture].vitesse -= 0.08;
        else 
            les_voitures[numero_voiture].vitesse = 0;

        if(vitesse_arriere-0.1>0.0)
            vitesse_arriere -=0.1;
        else vitesse_arriere=0.0;
    }
        
    // Diminue fortement la vitesse de la voiture
    void freinage(int numero_voiture)
    {
        float forceDeFreinage = 0.6;

        if (les_voitures[numero_voiture].vitesse - forceDeFreinage > 0) 
            les_voitures[numero_voiture].vitesse -= forceDeFreinage;
        else 
            les_voitures[numero_voiture].vitesse = 0;
    }

    void reculer(int numero_voiture){
        if(vitesse_arriere+ ACCELERATION * TIME_STEP < VITESSE_MAX_ARRIERE)
            vitesse_arriere += ACCELERATION*TIME_STEP;
        else 
            vitesse_arriere = VITESSE_MAX_ARRIERE;
        
    }



//#####################################################
//#         BOUGER LA VOITURE SELON LES AXES          #
//#####################################################

    float avancer_voiture_x(int numero_voiture){ return les_voitures[numero_voiture].vitesse * TIME_STEP * sin((les_voitures[numero_voiture].orientation * M_PI) / 180); }
    float avancer_voiture_z(int numero_voiture){ return les_voitures[numero_voiture].vitesse * TIME_STEP * cos((les_voitures[numero_voiture].orientation * M_PI) / 180); }
    float reculer_voiture_x(int numero_voiture){ return (vitesse_arriere * TIME_STEP)/4.0 * sin((les_voitures[numero_voiture].orientation * M_PI) / 180); }
    float reculer_voiture_z(int numero_voiture){ return (vitesse_arriere * TIME_STEP)/4.0 * cos((les_voitures[numero_voiture].orientation * M_PI) / 180); }

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
    }

//#####################################################
//#                BOUGER LES VOITURES                #
//#####################################################

    void avancer_voiture(int numero_voiture)
    {
        // Avancer la voiture dans la direction de l'orientation
        les_voitures[numero_voiture].position_x += avancer_voiture_x(numero_voiture);
        les_voitures[numero_voiture].position_z += avancer_voiture_z(numero_voiture);

        // printf("x : %.2f z : %.2f\n", les_voitures[numero_voiture].position_x, les_voitures[numero_voiture].position_z);

        if (les_voitures[numero_voiture].IsVoitureDuJoueur)
        {
            // Calcul des coordonnées de la caméra FPS
            camera_FPS_x += avancer_voiture_x(numero_voiture);
            camera_FPS_z += avancer_voiture_z(numero_voiture);

            updateCameras();
        }
    }

    void reculer_voiture(int numero_voiture)
    {
        // Reculer la voiture dans la direction de l'orientation
        les_voitures[numero_voiture].position_x -= reculer_voiture_x(numero_voiture);
        les_voitures[numero_voiture].position_z -= reculer_voiture_z(numero_voiture);

        if (les_voitures[numero_voiture].IsVoitureDuJoueur)
        {
            // Calcul des coordonnées de la caméra FPS
            camera_FPS_x -= reculer_voiture_x(numero_voiture);
            camera_FPS_z -= reculer_voiture_z(numero_voiture);

            updateCameras();
        }
    }

    void tourner_voiture_gauche(int numero_voiture)
    {
        // Tourner la voiture vers la gauche
        les_voitures[numero_voiture].orientation += 5;

        if (les_voitures[numero_voiture].IsVoitureDuJoueur)
        {
            // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
            camera_orientation_x = sin((les_voitures[numero_voiture].orientation * M_PI) / 180);
            camera_orientation_z = cos((les_voitures[numero_voiture].orientation * M_PI) / 180);

            updateCameras();
        }
    }

    void tourner_voiture_droite(int numero_voiture)
    {
        // Tourner la voiture vers la droite
        les_voitures[numero_voiture].orientation -= 5;

        if (les_voitures[numero_voiture].IsVoitureDuJoueur)
        {
            // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
            camera_orientation_x = sin((les_voitures[numero_voiture].orientation * M_PI) / 180);
            camera_orientation_z = cos((les_voitures[numero_voiture].orientation * M_PI) / 180);

            updateCameras();
        }
    }

//#####################################################
//#          MAJ POSITION VOITURE DU JOUEUR           #
//#####################################################

    void mettre_a_jour_position_voiture()
    {
        if (etatTouches[TOUCHE_Z])
        { 
            accelerer(VOITURE_DU_JOUEUR);      // augmente la vitesse
            avancer_voiture(VOITURE_DU_JOUEUR);   // avance la voiture avec la nouvelle vitesse    
        }   
        if ((etatTouches[TOUCHE_Z]==false) && (etatTouches[TOUCHE_S] == false))
        {
            if (les_voitures[VOITURE_DU_JOUEUR].vitesse >0){
                deceleration(VOITURE_DU_JOUEUR);      // diminue la vitesse 
                avancer_voiture(VOITURE_DU_JOUEUR);   // avance la voiture avec la nouvelle vitesse    
            }
            else if(vitesse_arriere >0) {
                deceleration(VOITURE_DU_JOUEUR);
                reculer_voiture(VOITURE_DU_JOUEUR);
            }   
            
        }
        if (etatTouches[TOUCHE_S])
        { 
            if (les_voitures[VOITURE_DU_JOUEUR].vitesse >= 0)
            {
                freinage(VOITURE_DU_JOUEUR);          // diminue fortement la vitesse          
                avancer_voiture(VOITURE_DU_JOUEUR);   // avance la voiture avec la nouvelle vitesse    
            }
        if ( (etatTouches[TOUCHE_S])&&(les_voitures[VOITURE_DU_JOUEUR].vitesse == 0))
            {
                reculer(VOITURE_DU_JOUEUR);
                reculer_voiture(VOITURE_DU_JOUEUR);
            }
        } 
        if (etatTouches[ESPACE])  
        {
            freinage(VOITURE_DU_JOUEUR);          // diminue fortement la vitesse          
            avancer_voiture(VOITURE_DU_JOUEUR);   // avance la voiture avec la nouvelle vitesse    
        }
        if (etatTouches[TOUCHE_Q]){ tourner_voiture_gauche(VOITURE_DU_JOUEUR);   } 
        if (etatTouches[TOUCHE_D]){ tourner_voiture_droite(VOITURE_DU_JOUEUR);   } 

        verif_dehors(VOITURE_DU_JOUEUR);

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

//#####################################################
//#                 SORTIES DE PISTE                  #
//#####################################################

    /*
        Equation de l'ellipse du tour de stade :
            (x / 70)² + (y / 120)² = 1
        Equation de l'ellipse de la barrière au centre du stade :
            (x / 30)² + (y / 80)² = 1
    */

    void verif_dehors(int numero_voiture)
    {
        float Ellipse_exterieure = pow(les_voitures[numero_voiture].position_x / 70, 2) + pow(les_voitures[numero_voiture].position_z / 120, 2);
        float Ellipse_interieure = pow(les_voitures[numero_voiture].position_x / 30, 2) + pow(les_voitures[numero_voiture].position_z / 80, 2);

        if (Ellipse_exterieure > 1 || Ellipse_interieure < 1) {
            float projection_x, projection_z;
            float min_distance_exterieure = 1000000000;
            float min_distance_interieure = 1000000000;

            if (Ellipse_exterieure > 1) {
                for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
                    float x = cos(angle) * 70;
                    float z = sin(angle) * 120;
                    float distance = sqrt(pow(les_voitures[numero_voiture].position_x - x, 2) + pow(les_voitures[numero_voiture].position_z - z, 2));
                    if (distance < min_distance_exterieure) {
                        min_distance_exterieure = distance;
                        projection_x = x;
                        projection_z = z;
                    }
                }
            }

            if (Ellipse_interieure < 1) {
                for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
                    float x = cos(angle) * 30;
                    float z = sin(angle) * 80;
                    float distance = sqrt(pow(les_voitures[numero_voiture].position_x - x, 2) + pow(les_voitures[numero_voiture].position_z - z, 2));
                    if (distance < min_distance_interieure) {
                        min_distance_interieure = distance;
                        projection_x = x;
                        projection_z = z;
                    }
                }
            }

            les_voitures[numero_voiture].position_x = projection_x;
            les_voitures[numero_voiture].position_z = projection_z;
            if(les_voitures[numero_voiture].vitesse-0.8>0)
                 les_voitures[numero_voiture].vitesse-=0.8;
            else les_voitures[numero_voiture].vitesse=0;

            if (les_voitures[numero_voiture].IsVoitureDuJoueur) updateCameras();
        }
    }









