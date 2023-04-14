#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

struct modele {
    const struct aiScene* scene;
};
struct modele creerModele(const char* fichier);
void afficherModele(struct modele modele);

struct modele creerModele(const char* fichier){
    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals;

    const struct aiScene* scene = aiImportFile(fichier, flags);
    if (!scene) {
        printf("Erreur lors du chargement du modèle : %s\n", aiGetErrorString());
    }

    struct modele un_modele;
    un_modele.scene = scene;

    return un_modele;
}


void afficherModele(struct modele modele){
    if (modele.scene){
        for (unsigned int i = 0; i < modele.scene->mNumMeshes; ++i) {
            const struct aiMesh* mesh = modele.scene->mMeshes[i];

            // Boucle à travers les faces du maillage
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                struct aiFace face = mesh->mFaces[j];

                // Vérification que la face est triangulaire (mNumIndices = 3)
                if (face.mNumIndices == 3) {
                    // Récupérer les indices de vertex pour la face triangulaire
                    unsigned int index0 = face.mIndices[0];
                    unsigned int index1 = face.mIndices[1];
                    unsigned int index2 = face.mIndices[2];

                    // Accéder aux coordonnées des vertices à partir des indices
                    struct aiVector3D vertex0 = mesh->mVertices[index0];
                    struct aiVector3D vertex1 = mesh->mVertices[index1];
                    struct aiVector3D vertex2 = mesh->mVertices[index2];

                    // Dessiner les triangles dans OpenGL

                    glEnable(GL_NORMALIZE);
                    glShadeModel(GL_SMOOTH);

                    glBegin(GL_TRIANGLES);
                        glNormal3f(mesh->mNormals[index0].x, mesh->mNormals[index0].y, mesh->mNormals[index0].z);
                        glVertex3f(vertex0.x, vertex0.y, vertex0.z);
                        glNormal3f(mesh->mNormals[index1].x, mesh->mNormals[index1].y, mesh->mNormals[index1].z);
                        glVertex3f(vertex1.x, vertex1.y, vertex1.z);
                        glNormal3f(mesh->mNormals[index2].x, mesh->mNormals[index2].y, mesh->mNormals[index2].z);
                        glVertex3f(vertex2.x, vertex2.y, vertex2.z);
                    glEnd();

                    // continue;
                }

            }
        }
    }
};