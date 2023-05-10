#include "actions.h"
#include "stdbool.h"    // pour utiliser les booléans
#include <time.h>
#include "../Modele/physique.c"

extern int blend;
extern int light;

//vitesse et time step
extern float acceleration;
extern float vitesse;
extern float time_step;


// tableau des touches (pour appuyer sur plusieurs touches en même temps)
    bool etatTouches[256];

// les coordonées de la caméra 
    // vue FPS
        extern float camera_FPS_x;              
        extern float camera_FPS_y;       
        extern float camera_FPS_z;       
    // vue TPS
        extern float camera_TPS_x;              
        extern float camera_TPS_y;      
        extern float camera_TPS_z;      
    // son orientation
        extern float camera_orientation_x;   
        extern float camera_orientation_z;   

extern bool vue_FPS;
extern bool vue_TPS;
extern bool vue_ARR;

// les coordonnées de la voiture
    extern float voiture_x;              
    extern float voiture_y;               
    extern float voiture_z;               
    extern float voiture_orientation;   

const float PI = 3.14159265359;
const int ECHELLE_STADE_OUT = 6;

float TPS_en_arriere = 8; // nombre de blocs derriere la voiture où est la caméra TPS
float TPS_au_dessus = 1.5; // nombre de blocs au dessus de la voiture où est la caméra TPS

float FPS_au_dessus = 0.65; // nombre de blocs au dessus de la voiture où est la caméra FPS


float avancer_voiture_x(){ return 0.6 * sin((voiture_orientation * PI) / 180); }
float avancer_voiture_z(){ return 0.6 * cos((voiture_orientation * PI) / 180); }
float reculer_voiture_x(){ return 0.3 * sin((voiture_orientation * PI) / 180); }
float reculer_voiture_z(){ return 0.3 * cos((voiture_orientation * PI) / 180); }

void updateCameraTPS()
{
    camera_TPS_x = voiture_x - (TPS_en_arriere * avancer_voiture_x());
    camera_TPS_y = voiture_y + TPS_au_dessus;
    camera_TPS_z = voiture_z - (TPS_en_arriere * avancer_voiture_z());
}

void updateCameraFPS()
{
    camera_FPS_x = voiture_x;
    camera_FPS_y = FPS_au_dessus;
    camera_FPS_z = voiture_z;
}

void updateCameras()
{
    updateCameraFPS();
    updateCameraTPS();
}

void avancer_voiture()
{
    // Avancer la voiture dans la direction de l'orientation
    voiture_x += avancer_voiture_x();
    voiture_z += avancer_voiture_z();

    // printf("x : %.2f z : %.2f\n", voiture_x, voiture_z);

    // Calcul des coordonnées de la caméra FPS
    camera_FPS_x += avancer_voiture_x();
    camera_FPS_z += avancer_voiture_z();

    updateCameras();
}

void reculer_voiture()
{
    // Avancer la voiture dans la direction de l'orientation
    voiture_x -= avancer_voiture_x();
    voiture_z -= avancer_voiture_z();

    // Calcul des coordonnées de la caméra FPS
    camera_FPS_x -= avancer_voiture_x();
    camera_FPS_z -= avancer_voiture_z();

    updateCameras();
}

void tourner_voiture_gauche()
{
    // Tourner la voiture vers la gauche
    voiture_orientation += 5;

    // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
    camera_orientation_x = sin((voiture_orientation * PI) / 180);
    camera_orientation_z = cos((voiture_orientation * PI) / 180);

    updateCameras();
}

void tourner_voiture_droite()
{
    // Tourner la voiture vers la gauche
    voiture_orientation -= 5;

    // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
    camera_orientation_x = sin((voiture_orientation * PI) / 180);
    camera_orientation_z = cos((voiture_orientation * PI) / 180);

    updateCameras();
}

void mettre_a_jour_position_voiture(int tempsEcoule)
{
    if (etatTouches[TOUCHE_Z]){ avancer_voiture();          } 
    if (etatTouches[TOUCHE_S]){ reculer_voiture();          } 
    if (etatTouches[TOUCHE_Q]){ tourner_voiture_gauche();   } 
    if (etatTouches[TOUCHE_D]){ tourner_voiture_droite();   } 

    verif_dehors();

    glutPostRedisplay();
    glutTimerFunc(10, mettre_a_jour_position_voiture, 10);
}

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

        case ESPACE:   
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

        //####### DEPLACEMENT CAMERA #######
            case TOUCHE_T: camera_FPS_z += 0.5; break;
            case TOUCHE_G: camera_FPS_z -= 0.5; break;
            case TOUCHE_F: camera_FPS_x += 0.5; break;
            case TOUCHE_H: camera_FPS_x -= 0.5; break;
    }	
}

void touche(int touche, int x, int y)
{
    // switch (touche) 
    // {
    //     case GLUT_KEY_LEFT :
	// 		angley -= 10;
	// 		break;
	// 	case GLUT_KEY_RIGHT :
	// 		angley += 10;
	// 		break;
	// 	case GLUT_KEY_UP :
    //         anglex -= 10;
	// 		break;
	// 	case GLUT_KEY_DOWN :
	// 		anglex += 10;
	// 		break;
    // }
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

    void verif_dehors()
    {
        float Ellipse_exterieure = pow(voiture_x / 70, 2) + pow(voiture_z / 120, 2);
        float Ellipse_interieure = pow(voiture_x / 30, 2) + pow(voiture_z / 80, 2);

        if ((Ellipse_exterieure > 1) || (Ellipse_interieure < 1)) {
            // La voiture est en dehors de la zone délimitée par les ellipses, on doit la replacer au point le plus proche
            float projection_x, projection_z;
            float dist_exterieure = fabs(pow(voiture_x / 70, 2) + pow(voiture_z / 120, 2) - 1);
            float dist_interieure = fabs(1 - pow(voiture_x / 30, 2) - pow(voiture_z / 80, 2));

            if (dist_exterieure < dist_interieure) {
                // La voiture est plus proche de l'ellipse exterieure, on la projette sur cette ellipse
                projection_x = voiture_x * 70 / sqrt(pow(voiture_x, 2) + pow(voiture_z, 2));
                projection_z = voiture_z * 120 / sqrt(pow(voiture_x, 2) + pow(voiture_z, 2));
            } else {
                // La voiture est plus proche de l'ellipse interieure, on la projette sur cette ellipse
                projection_x = voiture_x * 30 / sqrt(pow(voiture_x, 2) + pow(voiture_z, 2));
                projection_z = voiture_z * 80 / sqrt(pow(voiture_x, 2) + pow(voiture_z, 2));
            }

            voiture_x = projection_x;
            voiture_z = projection_z;

            updateCameras();
        }
    }








