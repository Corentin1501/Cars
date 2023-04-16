#include "VM_init.h"
#include <stdio.h>
#include "stdbool.h"
#include "opmat.h"

// angles de la caméra
float anglex = 0.0f;
float angley = 0.0f;

// coordonnées de la caméra
float camera_x = +0.0f;      
float camera_y = -1.0f; 
float camera_z = -5.0f;

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

        glTranslatef(camera_x, camera_y, camera_z);
        glRotatef(anglex, 1,0,0);
        glRotatef(angley, 0,1,0);

    //#####################################################
    //#                     LUMIERES                      #
    //#####################################################

        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);

        //######### LUMIERE AMBIANTE #########

            GLfloat light[4] = {0.1 , 0.1 , 0.1 , 1};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light);


        //######### LUMIERE 0 (DIRECTIONNELLE) ######### en (0,10,0) blanche

            GLfloat light_0_ambient[]  = { 0.2,  0.2,  0.2,  1 }; // intensité de lumière ambiante
            GLfloat light_0_diffuse[]  = { 0.8,  0.8,  0.8,  1 }; // composante diffuse
            GLfloat light_0_specular[] = { 0.5,  0.5,  0.5,  1 }; // composante spéculaire
            GLfloat light_0_position[] = {   0,   10,    0,  0 }; // position de la lumière

            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient); 
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_diffuse); 
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular); 
            glLightfv(GL_LIGHT0, GL_POSITION, light_0_position); 

        //######### LUMIERE 1 (POSITIONNELLE) ######### en (-13,10,-13) rouge

            GLfloat light_1_ambient[]  = { 0.1,   0,   0,  1 };
            GLfloat light_1_diffuse[]  = {   1,   0,   0,  1 };
            GLfloat light_1_specular[] = {   1,   1,   1,  1 };
            GLfloat light_1_position[] = { -13,  10, -13,  1 };

            glEnable(GL_LIGHT1);
            glLightfv(GL_LIGHT1, GL_AMBIENT,  light_1_ambient);
            glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_1_diffuse);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specular);
            glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);

        //######### LUMIERE 2 (POSITIONNELLE) ######### en (13,4,13) bleu

            GLfloat light_2_ambient[]  = { 0.05, 0.05, 0.05,  1 };
            GLfloat light_2_diffuse[]  = {    0,    1,    0,  1 };
            GLfloat light_2_specular[] = {    1,    1,    1,  1 };
            GLfloat light_2_position[] = {   13,    1,   13,  1 };

            glEnable(GL_LIGHT2);
            glLightfv(GL_LIGHT2, GL_AMBIENT,  light_2_ambient);
            glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_2_diffuse);
            glLightfv(GL_LIGHT2, GL_SPECULAR, light_2_specular);
            glLightfv(GL_LIGHT2, GL_POSITION, light_2_position);

}