#include "actions.h"
#include "stdbool.h"    // pour utiliser les booléans
#include <time.h>

extern int blend;
extern int light;

// angle de la caméra
extern float anglex;    
extern float angley;    

// les coordonées de la caméra 
extern float camera_x;              
extern float camera_y;               
extern float camera_z;               

// les coordonées de la voiture
extern float voiture_x;              
extern float voiture_y;               
extern float voiture_z;               
extern float voiture_orientation;   
extern float camera_orientation_x;   
extern float camera_orientation_z;   

const float PI = 3.14159265359;


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

        //####### DEPLACEMENT VOITURE #######

            case TOUCHE_Z:
                // Avancer la voiture dans la direction de l'orientation
                voiture_x += 0.6 * sin((voiture_orientation * PI) / 180);
                voiture_z += 0.6 * cos((voiture_orientation * PI) / 180);

                // Déplacer la caméra avec la voiture
                camera_x += 0.6 * sin((voiture_orientation * PI) / 180);
                camera_z += 0.6 * cos((voiture_orientation * PI) / 180);
                break;

            case TOUCHE_S:
                // Reculer la voiture dans la direction opposée à l'orientation
                voiture_x -= 0.3 * sin((voiture_orientation * PI) / 180);
                voiture_z -= 0.3 * cos((voiture_orientation * PI) / 180);

                // Déplacer la caméra avec la voiture
                camera_x -= 0.3 * sin((voiture_orientation * PI) / 180);
                camera_z -= 0.3 * cos((voiture_orientation * PI) / 180);
                break;

            case TOUCHE_Q:
                // Tourner la voiture vers la gauche
                voiture_orientation += 10;

                // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
                camera_orientation_x = sin((voiture_orientation * PI) / 180);
                camera_orientation_z = cos((voiture_orientation * PI) / 180);
                break;

            case TOUCHE_D:
                // Tourner la voiture vers la droite
                voiture_orientation -= 10;

                // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
                camera_orientation_x = sin((voiture_orientation * PI) / 180);
                camera_orientation_z = cos((voiture_orientation * PI) / 180);
                break;

        //####### DEPLACEMENT CAMERA #######
            case TOUCHE_T:
                camera_z += 0.5;
                break;
            case TOUCHE_G:
                camera_z -= 0.5;
                break;
            case TOUCHE_F:
                camera_x += 0.5;
                break;
            case TOUCHE_H:
                camera_x -= 0.5;
                break;
            case TOUCHE_UP:
                camera_y -= 0.5;
                break;
            case TOUCHE_DOWN:
                camera_y += 0.5;
                break;
    }	
}

void touche(int touche, int x, int y)
{
    switch (touche) 
    {
        case GLUT_KEY_LEFT :
			angley -= 10;
			break;
		case GLUT_KEY_RIGHT :
			angley += 10;
			break;
		case GLUT_KEY_UP :
            anglex -= 10;
			break;
		case GLUT_KEY_DOWN :
			anglex += 10;
			break;
    }
}