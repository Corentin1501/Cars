// gcc opmat.c actions.c VM_init.c -c
// gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o -lm -lGL -lGLU -lglut -o executable

// COMPILER

// gcc opmat.c actions.c VM_init.c ppm.c -c; gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o switch_light.o VM_init.o opmat.o ppm.o -lm -lGL -lGLU -lglut -o executable -lassimp

#include "init.h"
#include "axes.h"
#include "VM_init.h"
#include "opmat.h"
#include "stdbool.h"
#include "ppm.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


GLvoid Modelisation()
{
    VM_init();

    const char* filePath = "/home/etud/Documents/S6/STAGE/ProjetSI/modeles/Camion/Camion.obj";
    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals;

    const struct aiScene* scene = aiImportFile(filePath, flags);
    if (!scene) {
        printf("Erreur lors du chargement du modèle : %s\n", aiGetErrorString());
    }
    else {
        glColor3f(1,0,0);
        // glRotatef(-90,1,0,0);
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const struct aiMesh* mesh = scene->mMeshes[i];

            // Boucle à travers les faces du maillage
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                struct aiFace face = mesh->mFaces[j];

                // Assurez-vous que la face est triangulaire (mNumIndices = 3)
                if (face.mNumIndices != 3) {
                    // Gérer les faces non triangulaires selon vos besoins
                    continue;
                }

                // Récupérer les indices de vertex pour la face triangulaire
                unsigned int index0 = face.mIndices[0];
                unsigned int index1 = face.mIndices[1];
                unsigned int index2 = face.mIndices[2];

                // Accéder aux coordonnées des vertices à partir des indices
                struct aiVector3D vertex0 = mesh->mVertices[index0];
                struct aiVector3D vertex1 = mesh->mVertices[index1];
                struct aiVector3D vertex2 = mesh->mVertices[index2];

                // Dessiner les triangles dans OpenGL


                glBegin(GL_TRIANGLES);
                    glVertex3f(vertex0.x, vertex0.y, vertex0.z);
                    glVertex3f(vertex1.x, vertex1.y, vertex1.z);
                    glVertex3f(vertex2.x, vertex2.y, vertex2.z);
                glEnd();
            }
        }
    }
    aiReleaseImport(scene);


    axes();
    glutSwapBuffers();
}

int main(int argc, char **argv) 
{  
    return notre_init(argc, argv, &Modelisation);
}
