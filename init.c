#include "init.h"
#include "Regles.c"


GLuint blend = 0;
GLuint light = 0;


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
    glClearColor(0,0,0,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glutTimerFunc(1000, refresh, 0);  // Appelle la fonction refresh() toutes les 1000 ms (1 seconde)

    glutMainLoop();
    return 1;
}



