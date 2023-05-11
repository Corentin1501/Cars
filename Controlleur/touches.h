#ifndef __TOUCHES
#define __TOUCHES
#include <unistd.h>
/* ascii codes for various special keys */


#define TOUCHE_MIN_B 98
#define TOUCHE_MAJ_B 66

#define TOUCHE_MIN_L 108
#define TOUCHE_MAJ_L 76

// deplacement voiture
    #define TOUCHE_Z 122
    #define TOUCHE_Q 113    
    #define TOUCHE_S 115
    #define TOUCHE_D 100

// deplacement camera 
    #define TOUCHE_T 116
    #define TOUCHE_F 102
    #define TOUCHE_H 104
    #define TOUCHE_G 103
    #define TOUCHE_UP 43
    #define TOUCHE_DOWN 45

// basculer vue FPS / TPS / Arrière
    #define TOUCHE_W 119    // FPS / TPS
    #define ESPACE 32   
    #define TAB 9    // Arrière

    
#define ESCAPE 27

#define RETURN 13
#define DELETE 8

// GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT sont définis dans glut.h
#endif
