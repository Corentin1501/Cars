#ifndef MODELE_H
#define MODELE_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#include "../Vue/init.h"    // pour les textures

struct modele {
    const struct aiScene* scene;  // Structure contenant la scène chargée
};


struct modele creerModele(const char* fichier); // Fonction pour créer un objet modèle à partir d'un fichier

void afficherModele(struct modele modele); // Fonction pour afficher un modèle à l'écran
void afficherModeleAvecTextures(struct modele modele, GLuint texture);

#endif // MODELE_H