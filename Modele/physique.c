
#include <math.h>

float gravity=9.81;
float friction_coef=0.9;
float masse=1000;

const float ACCELERATION=2.0;
const float VITESSE_MAX=25.0;
const float TIME_STEP = 0.1;
float vitesse=0.0;

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

// void accelerate(){
//     acceleration = F_total()/masse;
// }

/*
####                          #### 
####    mise a jour vitesse   ####
####                          #### 
*/


void update_vitesse(){

    if(vitesse+ACCELERATION*TIME_STEP<VITESSE_MAX){
        vitesse+=ACCELERATION*TIME_STEP;
    }
    else vitesse=VITESSE_MAX;
    
    // vitesse += ACCELERATION * TIME_STEP;
}



