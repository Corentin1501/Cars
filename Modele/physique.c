
#include <math.h>

float gravity=9.81;
float friction_coef=0.9;
float masse=1000;

float acceleration=0.0;
float vitesse=0.0;

float time_step=0.1;

extern float voiture_x;
extern float voiture_y;
extern float voiture_z;

extern float voiture_orientation;



/*
####             #### 
####    FORCES   ####
####             #### 
*/

//Calcule la force de gravité 

float F_gravity(){
    if (voiture_y!=0)return masse*gravity*sin(11);
    else return masse*gravity;
}

//calcule la force de friction 

float F_friction(){
    return friction_coef*F_gravity();
}

//calcule la force totale 

float F_total(){
    return F_gravity()-F_friction();
}

/*
####                   #### 
####    ACCELERATION   ####
####                   #### 
*/

void accelerate(){
    acceleration = F_total()/masse;
}

/*
####                          #### 
####    mise a jour vitesse   ####
####                          #### 
*/


void update_vitesse(){
    vitesse+=acceleration*time_step;
}



