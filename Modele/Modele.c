#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SOIL/SOIL.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

struct modele {
    const struct aiScene* scene;  // Structure contenant la scène chargée
};

// Fonction pour créer un objet modèle à partir d'un fichier
struct modele creerModele(const char* fichier);

// Fonction pour afficher un modèle à l'écran
void afficherModele(struct modele modele);

struct modele creerModele(const char* fichier){
    // Flags pour la fonction d'importation de la scène
    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals;

    // Chargement de la scène à partir du fichier avec les flags spécifiés
    const struct aiScene* scene = aiImportFile(fichier, flags);
    if (!scene) {  // Si le chargement échoue, afficher un message d'erreur
        printf("Erreur lors du chargement du modèle : %s\n", aiGetErrorString());
    }

    // Création de l'objet modèle à partir de la scène chargée
    struct modele un_modele;
    un_modele.scene = scene;

    return un_modele;  // Retourner l'objet modèle créé
}

// variables globales
GLuint* textures;
int num_textures;

// fonction pour charger les textures
void chargerTextures(struct modele* modele) {
    // allouer de la mémoire pour les identifiants de texture
    num_textures = modele->scene->mNumMaterials;
    textures = (GLuint*)malloc(sizeof(GLuint) * num_textures);

    for (unsigned int i = 0; i < modele->scene->mNumMaterials; ++i) {
        // charger l'image de texture
        struct aiString chemin_texture;
        aiGetMaterialString(modele->scene->mMaterials[i], AI_MATKEY_TEXTURE_DIFFUSE(0), &chemin_texture);
        GLuint id_texture = SOIL_load_OGL_texture(chemin_texture.data, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

        if (id_texture == 0) {  // si la texture n'a pas été chargée correctement
            printf("Erreur lors du chargement de la texture : %s\n", SOIL_last_result());
            textures[i] = 0;
        } else {
            // configurer la texture
            glBindTexture(GL_TEXTURE_2D, id_texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            textures[i] = id_texture;
        }
    }
}





void afficherModele(struct modele modele){

    if (modele.scene)   // Vérifier que la structure de scène est valide
    { 
        for (unsigned int i = 0; i < modele.scene->mNumMeshes; ++i) // Parcourir les maillages dans la structure de scène
        {
            const struct aiMesh* mesh = modele.scene->mMeshes[i];   // Récupérer le maillage actuel

            for (unsigned int j = 0; j < mesh->mNumFaces; ++j)  // Boucler à travers les faces du maillage
            {
                struct aiFace face = mesh->mFaces[j];   // Récupérer la face actuelle

                if (face.mNumIndices == 3)  // Vérifier que la face est triangulaire (mNumIndices = 3)
                {

                    // Récupérer les indices de vertex pour la face triangulaire
                    unsigned int index0 = face.mIndices[0];
                    unsigned int index1 = face.mIndices[1];
                    unsigned int index2 = face.mIndices[2];

                    // Accéder aux coordonnées des vertices à partir des indices
                    struct aiVector3D vertex0 = mesh->mVertices[index0];
                    struct aiVector3D vertex1 = mesh->mVertices[index1];
                    struct aiVector3D vertex2 = mesh->mVertices[index2];

                    // Dessiner les triangles dans OpenGL
                    glEnable(GL_NORMALIZE);     // normaliser les vecteurs normaux
                    glShadeModel(GL_SMOOTH);    // activer le lissage des ombres
                    glBegin(GL_TRIANGLES);      // commencer un rendu de triangles

                        // Spécifier les vecteurs normaux et les coordonnées des vertices pour chaque triangle
                        glNormal3f(mesh->mNormals[index0].x, mesh->mNormals[index0].y, mesh->mNormals[index0].z);
                        glVertex3f(vertex0.x, vertex0.y, vertex0.z);

                        glNormal3f(mesh->mNormals[index1].x, mesh->mNormals[index1].y, mesh->mNormals[index1].z);
                        glVertex3f(vertex1.x, vertex1.y, vertex1.z);

                        glNormal3f(mesh->mNormals[index2].x, mesh->mNormals[index2].y, mesh->mNormals[index2].z);
                        glVertex3f(vertex2.x, vertex2.y, vertex2.z);

                    glEnd();                    // fin du rendu des triangles
                }
            }
        }
    }
}

void afficherModeleAvecTextures(struct modele modele){

    if (modele.scene)   // Vérifier que la structure de scène est valide
    { 
        // Activer l'utilisation des textures
        glEnable(GL_TEXTURE_2D);

        for (unsigned int i = 0; i < modele.scene->mNumMeshes; ++i)
        {
            const struct aiMesh* mesh = modele.scene->mMeshes[i];   // Récupérer le maillage actuel

            // Vérifier si le maillage a une texture associée
            if(mesh->mTextureCoords[0] != NULL)
            {
                // Activer la texture pour le maillage actuel
                glBindTexture(GL_TEXTURE_2D, mesh->mMaterialIndex);

                for (unsigned int j = 0; j < mesh->mNumFaces; ++j)  // Boucler à travers les faces du maillage
                {
                    struct aiFace face = mesh->mFaces[j];   // Récupérer la face actuelle

                    if (face.mNumIndices == 3)  // Vérifier que la face est triangulaire (mNumIndices = 3)
                    {

                        // Récupérer les indices de vertex pour la face triangulaire
                        unsigned int index0 = face.mIndices[0];
                        unsigned int index1 = face.mIndices[1];
                        unsigned int index2 = face.mIndices[2];

                        // Accéder aux coordonnées des vertices à partir des indices
                        struct aiVector3D vertex0 = mesh->mVertices[index0];
                        struct aiVector3D vertex1 = mesh->mVertices[index1];
                        struct aiVector3D vertex2 = mesh->mVertices[index2];

                        // Accéder aux coordonnées de texture à partir des indices
                        struct aiVector3D texCoord0 = mesh->mTextureCoords[0][index0];
                        struct aiVector3D texCoord1 = mesh->mTextureCoords[0][index1];
                        struct aiVector3D texCoord2 = mesh->mTextureCoords[0][index2];

                        // Dessiner les triangles dans OpenGL
                        glEnable(GL_NORMALIZE);     // normaliser les vecteurs normaux
                        glShadeModel(GL_SMOOTH);    // activer le lissage des ombres
                        glBegin(GL_TRIANGLES);      // commencer un rendu de triangles

                            // Spécifier les vecteurs normaux, les coordonnées de texture et les coordonnées des vertices pour chaque triangle
                            glNormal3f(mesh->mNormals[index0].x, mesh->mNormals[index0].y, mesh->mNormals[index0].z);
                            glTexCoord2f(texCoord0.x, texCoord0.y);
                            glVertex3f(vertex0.x, vertex0.y, vertex0.z);

                            glNormal3f(mesh->mNormals[index1].x, mesh->mNormals[index1].y, mesh->mNormals[index1].z);
                            glTexCoord2f(texCoord1.x, texCoord1.y);
                            glVertex3f(vertex1.x, vertex1.y, vertex1.z);

                            glNormal3f(mesh->mNormals[index2].x, mesh->mNormals[index2].y, mesh->mNormals[index2].z);
                            glTexCoord2f(texCoord2.x, texCoord2.y);
                            glVertex3f(vertex2.x, vertex2.y, vertex2.z);

                        glEnd();                    // fin du rendu des triangles
                    }
                }
            }
        }
        glDisable(GL_TEXTURE_2D);
    }
}