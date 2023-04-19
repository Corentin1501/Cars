#include "init.h"
#include "stdbool.h"

GLuint blend = 0;
GLuint light = 0;

extern float start_time;

GLvoid Redimensionne(GLsizei Width, GLsizei Height)
{
        glViewport(0,0,Width, Height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (float)16/(float)9, 0.1, 100);
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
    glutSpecialFunc(&touche);
    glClearColor(0.3,0.3,0.3,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    start_time = (float)glutGet(GLUT_ELAPSED_TIME); // pour le chronometre

    glutMainLoop();
    return 1;
}