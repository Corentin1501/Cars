#include "HUD.h"


void drawHUD()
{
    float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float windowWidth = glutGet(GLUT_WINDOW_WIDTH);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glLoadIdentity();

            // dessin du HUD
            glColor3f(1,1,1);
            char buffer[256];

            //####### Nombre de tours #######
                glRasterPos2f(10,windowHeight-20);
                sprintf(buffer,"Tours : %d", les_voitures[VOITURE_DU_JOUEUR].currentLap);
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);

            //####### Chronomètre #######

                updateChrono();

                glRasterPos2f(10,windowHeight-50);
                sprintf(buffer,"Chronometre : %.3f s", chronometre);
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
            
            //####### Checkpoints #######
                glRasterPos2f(10,windowHeight-80);
                sprintf(buffer,"Checkpoint actuel : %d", (les_voitures[VOITURE_DU_JOUEUR].currentCP % NOMBRE_CHECKPOINTS));
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);

            //####### Victoire #######

                float win_message_width = windowWidth/4.0;

                if (les_voitures[VOITURE_DU_JOUEUR].aGagne){
                    glRasterPos2f((windowWidth/2.0 - win_message_width/2.0) , (windowHeight/2.0));
                    sprintf(buffer,"Victoire ! Temps : %.3f", les_voitures[VOITURE_DU_JOUEUR].temps_victoire);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
                }

            //####### Vitesse #######

                glRasterPos2f(10,windowHeight-110);
                sprintf(buffer,"Vitesse : %.0f", (les_voitures[VOITURE_DU_JOUEUR].vitesse * 10));
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
            
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}