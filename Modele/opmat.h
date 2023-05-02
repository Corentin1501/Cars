#include <stdio.h>     
#include <stdlib.h>     
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLfloat * mxm(GLfloat * m1, GLfloat * m2);

GLfloat * mxv(GLfloat * m, GLfloat * v);

void pretty_printer(GLfloat *m);

GLfloat * translation(GLfloat x, GLfloat y, GLfloat z);
GLfloat * homotethie(GLfloat x, GLfloat y, GLfloat z);
GLfloat * rotation_x(GLfloat angle);
GLfloat * rotation_y(GLfloat angle);

GLfloat * identite();
