#include "actions.h"
#include "stdbool.h"    // pour utiliser les booléans
#include <time.h>

extern int blend;
extern int light;

// les coordonées de la caméra 
    // vue FPS
        extern float camera_FPS_x;              
        extern float camera_FPS_z;      
    // vue TPS
        extern float camera_TPS_x;              
        extern float camera_TPS_y;      
        extern float camera_TPS_z;      

extern bool vue_FPS;
extern bool vue_TPS;
extern bool vue_ARR;

// les coordonées de la voiture
extern float voiture_x;              
extern float voiture_y;               
extern float voiture_z;               
extern float voiture_orientation;   
extern float camera_orientation_x;   
extern float camera_orientation_z;   

const float PI = 3.14159265359;

int TPS_en_arriere = 8; // nombre de blocs derriere la voiture où est la caméra TPS
int TPS_au_dessus = 1.5; // nombre de blocs derriere la voiture où est la caméra TPS

float avancer_voiture_x(){ return 0.6 * sin((voiture_orientation * PI) / 180); }
float avancer_voiture_z(){ return 0.6 * cos((voiture_orientation * PI) / 180); }
float reculer_voiture_x(){ return 0.3 * sin((voiture_orientation * PI) / 180); }
float reculer_voiture_z(){ return 0.3 * cos((voiture_orientation * PI) / 180); }

void touche_pressee(unsigned char key, int x, int y) 
{
    usleep(100);

    switch (key)
    {    
        case ESCAPE: exit(1); break;                // la touche ECHAP quitte l'application

        case ESPACE:     
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

        //####### DEPLACEMENT VOITURE #######

            case TOUCHE_Z:
                // Avancer la voiture dans la direction de l'orientation
                voiture_x += avancer_voiture_x();
                voiture_z += avancer_voiture_z();

                // Calcul des coordonnées de la caméra FPS
                camera_FPS_x += avancer_voiture_x();
                camera_FPS_z += avancer_voiture_z();

                // Calcul des coordonnées de la caméra TPS
                camera_TPS_x = voiture_x - (TPS_en_arriere * avancer_voiture_x());
                camera_TPS_y = voiture_y + TPS_au_dessus;
                camera_TPS_z = voiture_z - (TPS_en_arriere * avancer_voiture_z());

                break;

            case TOUCHE_S:
                // Reculer la voiture dans la direction opposée à l'orientation
                voiture_x -= reculer_voiture_x();
                voiture_z -= reculer_voiture_z();

                // Calcul des coordonnées de la caméra FPS
                camera_FPS_x -= reculer_voiture_x();
                camera_FPS_z -= reculer_voiture_z();

                // Calcul des coordonnées de la caméra TPS
                camera_TPS_x = voiture_x - (TPS_en_arriere * avancer_voiture_x());
                camera_TPS_y = voiture_y + TPS_au_dessus;
                camera_TPS_z = voiture_z - (TPS_en_arriere * avancer_voiture_z());

                break;

            case TOUCHE_Q:
                // Tourner la voiture vers la gauche
                voiture_orientation += 10;

                // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
                camera_orientation_x = sin((voiture_orientation * PI) / 180);
                camera_orientation_z = cos((voiture_orientation * PI) / 180);

                // Calcul des coordonnées de la caméra TPS
                camera_TPS_x = voiture_x - (TPS_en_arriere * avancer_voiture_x());
                camera_TPS_y = voiture_y + TPS_au_dessus;
                camera_TPS_z = voiture_z - (TPS_en_arriere * avancer_voiture_z());

                break;

            case TOUCHE_D:
                // Tourner la voiture vers la droite
                voiture_orientation -= 10;

                // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
                camera_orientation_x = sin((voiture_orientation * PI) / 180);
                camera_orientation_z = cos((voiture_orientation * PI) / 180);

                // Calcul des coordonnées de la caméra TPS
                camera_TPS_x = voiture_x - (TPS_en_arriere * avancer_voiture_x());
                camera_TPS_y = voiture_y + TPS_au_dessus;
                camera_TPS_z = voiture_z - (TPS_en_arriere * avancer_voiture_z());

                break;


        //####### DEPLACEMENT CAMERA #######
            case TOUCHE_T:
                camera_FPS_z += 0.5;
                break;
            case TOUCHE_G:
                camera_FPS_z -= 0.5;
                break;
            case TOUCHE_F:
                camera_FPS_x += 0.5;
                break;
            case TOUCHE_H:
                camera_FPS_x -= 0.5;
                break;
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