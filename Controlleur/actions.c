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

int TPS_en_arriere = 8; // nombre de blocs derriere la voiture où est la caméra TPS
int TPS_au_dessus = 1.5; // nombre de blocs derriere la voiture où est la caméra TPS

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

void avancer_voiture()
{
    // Avancer la voiture dans la direction de l'orientation
    voiture_x += avancer_voiture_x();
    voiture_z += avancer_voiture_z();

    // printf("x : %.2f z : %.2f\n", voiture_x, voiture_z);

    // Calcul des coordonnées de la caméra FPS
    camera_FPS_x += avancer_voiture_x();
    camera_FPS_z += avancer_voiture_z();

    updateCameraTPS();
}

void reculer_voiture()
{
    // Avancer la voiture dans la direction de l'orientation
    voiture_x -= avancer_voiture_x();
    voiture_z -= avancer_voiture_z();

    // Calcul des coordonnées de la caméra FPS
    camera_FPS_x -= avancer_voiture_x();
    camera_FPS_z -= avancer_voiture_z();

    updateCameraTPS();
}

void tourner_voiture_gauche()
{
    // Tourner la voiture vers la gauche
    voiture_orientation += 10;

    // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
    camera_orientation_x = sin((voiture_orientation * PI) / 180);
    camera_orientation_z = cos((voiture_orientation * PI) / 180);

    updateCameraTPS();
}

void tourner_voiture_droite()
{
    // Tourner la voiture vers la gauche
    voiture_orientation -= 10;

    // Mettre à jour la direction de la caméra pour qu'elle regarde vers l'avant de la voiture
    camera_orientation_x = sin((voiture_orientation * PI) / 180);
    camera_orientation_z = cos((voiture_orientation * PI) / 180);

    updateCameraTPS();
}


void touche_relachee(unsigned char key, int x, int y)
{
    etatTouches[key] = false;
}

void touche_pressee(unsigned char key, int x, int y) 
{
    // usleep(100);

    etatTouches[key] = true;

    // si plusieurs touches de deplacement sont pressées en même temps
    if (etatTouches[TOUCHE_Z] && etatTouches[TOUCHE_D]) 
    {
        tourner_voiture_droite();
        avancer_voiture();
    } 
    else if (etatTouches[TOUCHE_Z] && etatTouches[TOUCHE_G])
    {
        tourner_voiture_gauche();
        avancer_voiture();
    } 
    else if (etatTouches[TOUCHE_S] && etatTouches[TOUCHE_G])
    {
        tourner_voiture_gauche();
        reculer_voiture();
    } 
    else if (etatTouches[TOUCHE_S] && etatTouches[TOUCHE_G])
    {
        tourner_voiture_gauche();
        reculer_voiture();
    } 
    else // si aucune touches n'est pressé en même temps, on regarde normalement les autres
    {
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

            //####### DEPLACEMENT VOITURE #######

                case TOUCHE_Z: if(verif_dehors(true)) avancer_voiture(); break;
                case TOUCHE_S: if(verif_dehors(false)) reculer_voiture(); break;
                case TOUCHE_Q: tourner_voiture_gauche(); break;
                case TOUCHE_D: tourner_voiture_droite(); break;

            //####### DEPLACEMENT CAMERA #######
                case TOUCHE_T: camera_FPS_z += 0.5; break;
                case TOUCHE_G: camera_FPS_z -= 0.5; break;
                case TOUCHE_F: camera_FPS_x += 0.5; break;
                case TOUCHE_H: camera_FPS_x -= 0.5; break;
        }	
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

    bool verif_dehors(bool en_avancant)
    {
        // printf("x : %.1f z : %.1f\n", voiture_x, voiture_z);
        float voiture_x_futur, voiture_z_futur;

        if (en_avancant)    // on verifie si en avançant elle ne sort pas du circuit
        {
            voiture_x_futur = voiture_x + avancer_voiture_x();
            voiture_z_futur = voiture_z + avancer_voiture_z();
        }
        else    // si c'est pas en avançant c'est en reculant
        {
            voiture_x_futur = voiture_x - avancer_voiture_x();
            voiture_z_futur = voiture_z - avancer_voiture_z();
        }

        float Ellipse_exterieure = pow(voiture_x_futur / 70, 2) + pow(voiture_z_futur / 120, 2);
        float Ellipse_interieure = pow(voiture_x_futur / 30, 2) + pow(voiture_z_futur / 80, 2);

        // printf("xf : %.1f zf : %.1f\n", voiture_x_futur, voiture_x_futur);
        // printf("dans Ellipse_exterieure : %f\n", Ellipse_exterieure);
        // printf("dans Ellipse_interieure : %f\n", Ellipse_interieure);

        return (Ellipse_exterieure <= 1 && Ellipse_interieure >= 1);    // retourne si la voiture est entre les deux ellipses du circuit
    }








