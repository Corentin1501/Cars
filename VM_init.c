#include "VM_init.h"
#include <stdio.h>
#include "stdbool.h"
#include "opmat.h"

//########## CAMERA ##########

    // angles de la caméra
    float anglex = 0.0f;
    float angley = 0.0f;

    // coordonnées de la caméra
        // vue FPS
            float camera_FPS_x = 9.625*1.5;
            float camera_FPS_y = 0.6*1.5; 
            float camera_FPS_z = 0;

        // vue TPS
            float camera_TPS_x = 9.625*1.5;
            float camera_TPS_y = 1*1.5;
            float camera_TPS_z = 4.8*1.5;

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


        //######### LAMPADAIRE 5 (POSITIONNELLE) ######### cyan x

            GLfloat light_5_diffuse[]  = { 0, 1, 1, 1 };
            GLfloat light_5_position[] = { (-14.5*echelleStade), hauteurLampadaire, 0, 1 };

            glEnable(GL_LIGHT5);
            glLightfv(GL_LIGHT5, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT5, GL_DIFFUSE,  light_5_diffuse);
            glLightfv(GL_LIGHT5, GL_POSITION, light_5_position);


}