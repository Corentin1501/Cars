#include "VM_init.h"


void lumieres()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_CULL_FACE);
    
    //#####################################################
    //#                  LUMIERE AMBIANTE                 #
    //#####################################################

        GLfloat light[4] = {0.1 , 0.1 , 0.1 , 1};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light);

    //#####################################################
    //#                       SPOTS                       #
    //#####################################################

        float spot_hauteur = 19;


        GLfloat spot_0_position[] =   {  70,    spot_hauteur,  -45, 1 };
        GLfloat spot_1_position[] =   {   0,    spot_hauteur, -125, 1 };
        GLfloat spot_2_position[] =   { -70,    spot_hauteur,  -45, 1 };
        GLfloat spot_3_position[] =   { -70,    spot_hauteur,   45, 1 };
        GLfloat spot_4_position[] =   {   0,    spot_hauteur,  125, 1 };
        GLfloat spot_5_position[] =   {  70,    spot_hauteur,   45, 1 };

        GLfloat spot_0_direction[] = {-0.5, -1, 0};     // direction du spot
        GLfloat spot_1_direction[] = {0, -1, 0.5};
        GLfloat spot_2_direction[] = {0.5, -1, 0};
        GLfloat spot_3_direction[] = {0.5, -1, 0};
        GLfloat spot_4_direction[] = {0, -1, -0.5};
        GLfloat spot_5_direction[] = {0, -1, 0.5};

        GLfloat spot_0_angle = 90.0f;     // angle du faisceau de la lumière
        GLfloat spot_1_angle = spot_0_angle;
        GLfloat spot_2_angle = spot_0_angle;
        GLfloat spot_3_angle = spot_0_angle;
        GLfloat spot_4_angle = spot_0_angle;
        GLfloat spot_5_angle = spot_0_angle;

        GLfloat spot_0_exponent = 1.0f;  // facteur d'atténuation
        GLfloat spot_1_exponent = spot_0_exponent;
        GLfloat spot_2_exponent = spot_0_exponent;
        GLfloat spot_3_exponent = spot_0_exponent;
        GLfloat spot_4_exponent = spot_0_exponent;
        GLfloat spot_5_exponent = spot_0_exponent;

        GLfloat spots_couleur[] = { 0.4, 0.4, 0.2, 0.4 };   // jaune


        //######### LUMIERE 0 (DIRECTIONNELLE) ######### en (0,10,0) blanche

            GLfloat light_0_ambient[]  = { 0.2,  0.2,  0.2,  1 }; // intensité de lumière ambiante
            GLfloat light_0_diffuse[]  = { 0.05,  0.05,  0.05,  1 }; // composante diffuse
            GLfloat light_0_specular[] = { 0.5,  0.5,  0.5,  1 }; // composante spéculaire
            GLfloat light_0_position[] = {   0,   10,    10,  0 }; // position de la lumière

            glEnable(GL_LIGHT1);
            glLightfv(GL_LIGHT1, GL_AMBIENT,  light_0_ambient); 
            glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_0_diffuse); 
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_0_specular); 
            glLightfv(GL_LIGHT1, GL_POSITION, light_0_position); 

        //============= SPOT 0 =============

            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, spot_0_position);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_0_direction);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_0_angle);
            glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_0_exponent);

        //============= SPOT 1 =============

            glEnable(GL_LIGHT1);
            glLightfv(GL_LIGHT1, GL_POSITION, spot_1_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_1_direction);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_1_angle);
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_1_exponent);

        //============= SPOT 2 =============

            glEnable(GL_LIGHT2);
            glLightfv(GL_LIGHT2, GL_POSITION, spot_2_position);
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_2_direction);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_2_angle);
            glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spot_2_exponent);

        //============= SPOT 3 =============

            glEnable(GL_LIGHT3);
            glLightfv(GL_LIGHT3, GL_POSITION, spot_3_position);
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_3_direction);
            glLightfv(GL_LIGHT3, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spot_3_angle);
            glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spot_3_exponent);

        //============= SPOT 4 =============

            glEnable(GL_LIGHT4);
            glLightfv(GL_LIGHT4, GL_POSITION, spot_4_position);
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_4_direction);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spot_4_angle);
            glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spot_4_exponent);

        //============= SPOT 5 =============

            glEnable(GL_LIGHT5);
            glLightfv(GL_LIGHT5, GL_POSITION, spot_5_position);
            glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_5_direction);
            glLightfv(GL_LIGHT5, GL_DIFFUSE, spots_couleur);
            glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spot_5_angle);
            glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, spot_5_exponent);

}

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
    //#                      LUMIERES                     #
    //#####################################################

        lumieres();

    //#####################################################
    //#                        IAs                        #
    //#####################################################

        glutTimerFunc(1000, jouer_les_IAs, 1000);


}