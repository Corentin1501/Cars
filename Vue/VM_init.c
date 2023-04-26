#include "VM_init.h"
#include <stdio.h>
#include "stdbool.h"
#include "../Modele/opmat.h"

// angles de la caméra
float anglex = 0.0f;
float angley = 0.0f;

// coordonnées de la caméra
    // vue FPS
        float camera_FPS_x = 9.625;
        float camera_FPS_y = 0.6; 
        float camera_FPS_z = 0;

    // vue TPS
        float camera_TPS_x = 9.625;
        float camera_TPS_y = 1;
        float camera_TPS_z = 4.8;

float camera_orientation_x = 0;
float camera_orientation_z = -5;

bool vue_FPS = true;
bool vue_TPS = false;
bool vue_ARR = false;

void VM_init(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    


    //#####################################################
    //#                      CAMERA                       #
    //#####################################################

        if (vue_ARR)
        {
            gluLookAt(  camera_FPS_x, camera_FPS_y, camera_FPS_z + 2,
                        camera_TPS_x, camera_TPS_y, camera_TPS_z,
                        0, 1, 0);
        }
        else
        {
            if (vue_FPS)
            {
                gluLookAt(  camera_FPS_x, camera_FPS_y, camera_FPS_z,
                            camera_FPS_x + camera_orientation_x, camera_FPS_y, camera_FPS_z + camera_orientation_z,
                            0, 1, 0);
            } 
            else if (vue_TPS)
            {
                gluLookAt(  camera_TPS_x, camera_TPS_y, camera_TPS_z,
                            camera_TPS_x + camera_orientation_x, camera_TPS_y, camera_TPS_z + camera_orientation_z,
                            0, 1, 0);
            }
        }


    //#####################################################
    //#                     LUMIERES                      #
    //#####################################################

        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);

        GLfloat light_ambient[]  = { 0, 0, 0,  1 };
        GLfloat light_specular[] = {    0,    0,    0,  1 };

        float echelleStade = 1.5;
        float hauteurLampadaire = 3.3;


        //######### LUMIERE AMBIANTE #########

            GLfloat light[4] = {0.1 , 0.1 , 0.1 , 1};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light);


        // //######### LUMIERE 0 (DIRECTIONNELLE) ######### en (0,10,0) blanche

        //     GLfloat light_0_ambient[]  = { 0.2,  0.2,  0.2,  1 }; // intensité de lumière ambiante
        //     GLfloat light_0_diffuse[]  = { 0.05,  0.05,  0.05,  1 }; // composante diffuse
        //     GLfloat light_0_specular[] = { 0.5,  0.5,  0.5,  1 }; // composante spéculaire
        //     GLfloat light_0_position[] = {   0,   10,    0,  0 }; // position de la lumière

        //     // glEnable(GL_LIGHT0);
        //     glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient); 
        //     glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_diffuse); 
        //     glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular); 
        //     glLightfv(GL_LIGHT0, GL_POSITION, light_0_position); 

        //######### LAMPADAIRE 1 (POSITIONNELLE) ######### rouge x

            GLfloat light_1_diffuse[]  = {   1,   0,   0,  1 };
            GLfloat light_1_position[] = { (14.5*echelleStade),  hauteurLampadaire,   0,  1 };

            glEnable(GL_LIGHT1);
            glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_1_diffuse);
            glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);

        //######### LAMPADAIRE 2 (POSITIONNELLE) ######### orange x

            GLfloat light_2_diffuse[]  = { 1, 0.5, 0, 1 };
            GLfloat light_2_position[] = { (11*echelleStade), hauteurLampadaire, (-15*echelleStade), 1 };

            glEnable(GL_LIGHT2);
            glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_2_diffuse);
            glLightfv(GL_LIGHT2, GL_POSITION, light_2_position);

        //######### LAMPADAIRE 3 (POSITIONNELLE) ######### jaune x

            GLfloat light_3_diffuse[]  = { 1, 1, 0, 1 };
            GLfloat light_3_position[] = { 0, hauteurLampadaire, (-25*echelleStade), 1 };

            glEnable(GL_LIGHT3);
            glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_3_diffuse);
            glLightfv(GL_LIGHT3, GL_POSITION, light_3_position);

        //######### LAMPADAIRE 4 (POSITIONNELLE) ######### vert x

            GLfloat light_4_diffuse[]  = { 0, 1, 0, 1 };
            GLfloat light_4_position[] = { (-11*echelleStade), hauteurLampadaire, (-15*echelleStade), 1 };

            glEnable(GL_LIGHT4);
            glLightfv(GL_LIGHT4, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT4, GL_DIFFUSE,  light_4_diffuse);
            glLightfv(GL_LIGHT4, GL_POSITION, light_4_position);

        //######### LAMPADAIRE 5 (POSITIONNELLE) ######### cyan x

            GLfloat light_5_diffuse[]  = { 0, 1, 1, 1 };
            GLfloat light_5_position[] = { (-14.5*echelleStade), hauteurLampadaire, 0, 1 };

            glEnable(GL_LIGHT5);
            glLightfv(GL_LIGHT5, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT5, GL_DIFFUSE,  light_5_diffuse);
            glLightfv(GL_LIGHT5, GL_POSITION, light_5_position);

        //######### LAMPADAIRE 6 (POSITIONNELLE) ######### bleu x

            GLfloat light_6_diffuse[]  = { 0, 0, 1, 1 };
            GLfloat light_6_position[] = { (-11*echelleStade), hauteurLampadaire, (15*echelleStade), 1 };

            glEnable(GL_LIGHT6);
            glLightfv(GL_LIGHT6, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT6, GL_DIFFUSE,  light_6_diffuse);
            glLightfv(GL_LIGHT6, GL_POSITION, light_6_position);

        //######### LAMPADAIRE 7 (POSITIONNELLE) ######### violet x

            GLfloat light_7_diffuse[]  = { 0.5, 0, 1, 1 };
            GLfloat light_7_position[] = { 0, hauteurLampadaire, (25*echelleStade), 1 };

            glEnable(GL_LIGHT7);
            glLightfv(GL_LIGHT7, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT7, GL_DIFFUSE,  light_7_diffuse);
            glLightfv(GL_LIGHT7, GL_POSITION, light_7_position);

        //######### LAMPADAIRE 8 (POSITIONNELLE) ######### rose

            GLfloat light_8_diffuse[]  = { 1, 0, 1, 1 };
            GLfloat light_8_position[] = { (11*echelleStade), hauteurLampadaire, (15*echelleStade), 1 };

            glEnable(GL_LIGHT0);    // pas assez de lumiere donc la 8 est la 0
            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_8_diffuse);
            glLightfv(GL_LIGHT0, GL_POSITION, light_8_position);

}