#include "stdbool.h"

#include "Regles.c" // pour le nombre de tours


void glutBitmapString(void *font, const unsigned char *string);

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
            glColor3f(1,1,0);
            char buffer[256];

            //####### Nombre de tours #######
                glRasterPos2f(10,windowHeight-20);
                sprintf(buffer,"Tours : %d", Current_Lap);
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);

            //####### Chronomètre #######

                updateChrono();

                glRasterPos2f(10,windowHeight-50);
                sprintf(buffer,"Chronometre : %.2f s", chronometre);
                glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}