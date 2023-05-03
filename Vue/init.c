#include "init.h"
#include "stdbool.h"
#include "ppm.h"

GLuint blend = 0;
GLuint light = 0;

extern float start_time;

extern GLuint textures[10];


GLvoid Redimensionne(GLsizei Width, GLsizei Height)
{
        glViewport(0,0,Width, Height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (float)16/(float)9, 0.1, 500);
        glMatrixMode(GL_MODELVIEW);
}

int window = 1;
int notre_init(int argc, char** argv, void (*Modelisation)())
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glutInitWindowSize(900, 500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cars");
    glutDisplayFunc(Modelisation);
    glutIdleFunc(Modelisation);
    glutReshapeFunc(&Redimensionne);    
    glutKeyboardFunc(&touche_pressee);
    glutKeyboardUpFunc(&touche_relachee);
    glutSpecialFunc(&touche);
    glClearColor(0.3,0.3,0.3,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    //------------------ Chronomètre ------------------

        start_time = (float)glutGet(GLUT_ELAPSED_TIME);

    //------------------- Textures -------------------

        glGenTextures(1,textures);
        TEXTURE_STRUCT * bitume = readPpm("./Vue/textures/bitume.ppm");
        glBindTexture(GL_TEXTURE_2D,textures[0]);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitume->width, bitume->height, 0, GL_RGB, GL_UNSIGNED_BYTE,  bitume->data);
        free(bitume->data);
        free(bitume);
        glEnable(GL_TEXTURE_2D);

    //------------------------------------------------
    glutMainLoop();
    return 1;
}