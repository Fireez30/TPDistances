///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>     
#include <stdlib.h>     
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
//#include "GL/freeglut.h"
#include "glad/glad.h"
#include <fstream>

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/


#include "CVector.h"
#include "CPoint.h"
#include "Voxel.h"

using namespace std;

// Définition de la taille de la fenêtre
#define WIDTH  480

#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define PRECISION 0.1

    //int ortho4 = -5;
    int ortho4 = -2;
    float x_min=999;
    float x_max=0;
    float y_min=999;
    float y_max=0;
    float z_min=999;
    float z_max=0;
    bool firstPass = true;
    // angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly = 0.0f;
// XZ position of the camera
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 


struct Triangle {
    unsigned indice1;
    unsigned indice2;
    unsigned indice3;


    //GL_UNSIGNED_BYTE indice1;
    //GL_UNSIGNED_BYTE indice2;
    //GL_UNSIGNED_BYTE indice3;
};

int main(int argc, char **argv) 
{  
    // initialisation  des paramètres de GLUT en fonction
    // des arguments sur la ligne de commande

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // définition et création de la fenêtre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Premier exemple : carré");

    // initialisation de OpenGL et de la scène
    initGL();
    init_scene();

    // choix des procédures de callback pour
    // le tracé graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fenêtre
    glutReshapeFunc(&window_reshape);
    // la gestion des événements clavier
    glutKeyboardFunc(&window_key);

    // la boucle prinicipale de gestion des événements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
    gladLoadGL();
    glClearColor(RED, GREEN, BLUE, ALPHA);
  //  glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
    // à une fonction (render_scene() ici) qui contient les informations
    // que l'on veut dessiner

    render_scene();

    // trace la scène grapnique qui vient juste d'être définie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
    // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
    // de trop grosse taille par rapport à la fenêtre.

    float x_min_f = x_min - (abs(x_max - x_min));
    float x_max_f = x_max + (abs(x_max - x_min));
    float y_min_f = y_min - (abs(y_max - y_min));
    float y_max_f = y_max + (abs(y_max - y_min));
    float z_min_f = z_min - (abs(z_max - z_min));
    float z_max_f = z_max + (abs(z_max - z_min));

    glOrtho(x_min_f, x_max_f, y_min_f, y_max_f, z_min_f, z_max_f);
    

    // toutes les transformations suivantes s´appliquent au modèle de vue
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
    float fraction = 0.1f;
    switch (key) {
    case KEY_ESC:
        exit(1);
        break;

    case 'z':;
        ortho4++;
        glutPostRedisplay();
        break;

    case 's':
        ortho4--;
        glutPostRedisplay();
        break;

        case 'j' :
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;
        case 'l' :
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;
        case 'i' :
            angle -= 0.01f;
            ly = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;
        case 'k' :
            angle += 0.01f;
            ly = sin(angle);
            lz = -cos(angle);
            glutPostRedisplay();
            break;

    default:
        printf ("La touche %d n´est pas active.\n", key);
        break;
    }
}


double rand_float(double a, double b) {
    return ((double)rand() / RAND_MAX) * (b - a) + a;
}

void fusion2sommets(float * tab,int * indices,int indice1,int indice2, int tailletabindices){
    float moyenneX = tab[3 * indice1] + tab[3 * indice2];
    moyenneX /= 2;

    float moyenneY = tab[3 * indice1 + 1] + tab[3 * indice2 + 2];
    moyenneY /= 2;

    float moyenneZ = tab[3 * indice1 + 2] + tab[3 * indice2 + 2];
    moyenneZ /= 2;

    tab[3 * indice1] = moyenneX;
    tab[3 * indice1 + 1] = moyenneY;
    tab[3 * indice1 + 2] = moyenneZ;

    for (int i = 0; i < tailletabindices; i++){
        if (indices[i] == indice2)
            indices[i] = indice1;
    }
}

void decoupeTriangle(float * Points,int * indices,int NbPoints,int NbTriangles,int indice1, int * nIndices,float* nTab){
    CPoint p1 = CPoint(Points[3*indices[3 * indice1]],Points[(3 * indices[3 * indice1]) + 1],Points[(3 * indices[3 * indice1]) + 2]);
    CPoint p2 = CPoint(Points[3*indices[3 * indice1 + 1]],Points[(3 * indices[3 * indice1 + 1]) + 1],Points[(3 * indices[3 * indice1 + 1]) + 2]);
    CPoint p3 = CPoint(Points[3*indices[3 * indice1 + 2]],Points[(3 * indices[3 * indice1 + 2]) + 1],Points[(3 * indices[3 * indice1 + 2]) + 2]);

    CPoint Ptmp1 = CPoint((p1.getX()+p2.getX())/2,(p1.getY()+p2.getY())/2,(p1.getZ()+p2.getZ())/2);
    CPoint Ptmp2 = CPoint((p1.getX()+p3.getX())/2,(p1.getY()+p3.getY())/2,(p1.getZ()+p3.getZ())/2);
    CPoint Ptmp3 = CPoint((p2.getX()+p3.getX())/2,(p2.getY()+p3.getY())/2,(p2.getZ()+p3.getZ())/2);


    for (int i = 0; i < NbPoints; i++){
        nTab[3 * i] = Points[3 * i];
        nTab[3 * i + 1] = Points[3 * i + 1];
        nTab[3 * i + 2] = Points[3 * i + 2];
    }

    for (int i = 0; i < NbTriangles; i++){
        nIndices[3 * i] = indices[3 * i];
        nIndices[3 * i + 1] = indices[3 * i + 1];
        nIndices[3 * i + 2] = indices[3 * i + 2];
    }

    nTab[3 * NbPoints] = Ptmp1.getX();
    nTab[3 * NbPoints + 1] = Ptmp1.getY();
    nTab[3 * NbPoints + 2] = Ptmp1.getZ();
    nTab[3 * NbPoints + 3] = Ptmp2.getX();
    nTab[3 * NbPoints + 4] = Ptmp2.getY();
    nTab[3 * NbPoints + 5] = Ptmp2.getZ();
    nTab[3 * NbPoints + 6] = Ptmp3.getX();
    nTab[3 * NbPoints + 7] = Ptmp3.getY();
    nTab[3 * NbPoints + 8] = Ptmp3.getZ();

    nIndices[3 * NbTriangles] = indice1;
    nIndices[3 * NbTriangles + 1] = NbPoints;
    nIndices[3 * NbTriangles + 2] = NbPoints+1;
    nIndices[3 * NbTriangles + 3] = NbPoints+1;
    nIndices[3 * NbTriangles + 4] = NbPoints + 2;
    nIndices[3 * NbTriangles + 5] = NbPoints;
    nIndices[3 * NbTriangles + 6] = NbPoints;
    nIndices[3 * NbTriangles + 7] = indice1 + 1;
    nIndices[3 * NbTriangles + 8] = NbPoints + 2;
    nIndices[3 * NbTriangles + 9] = NbPoints + 2;
    nIndices[3 * NbTriangles + 10] = indice1 + 2;
    nIndices[3 * NbTriangles + 11] = NbPoints + 1;
}

CPoint decoupeTriangleButterflyArete(float * Points,int * indices,int NbPoints,int NbTriangles,int indice1, int s1 , int s2){
    int s3;
    if (s1 == 0 && s2 == 1 || s1 == 1 && s2 == 0)
        s3 = 2;
    else if (s1 == 1 && s2 == 2 || s1 == 2 && s2 == 1)
        s3 = 0;
    else 
        s3 = 1;

    CPoint p1 = CPoint(Points[3*indices[3 * indice1 + s1]],Points[(3 * indices[3 * indice1 + s1]) + 1],Points[(3 * indices[3 * indice1 + s1]) + 2]);
    CPoint p2 = CPoint(Points[3*indices[3 * indice1 + s2]],Points[(3 * indices[3 * indice1 + s2]) + 1],Points[(3 * indices[3 * indice1 + s2]) + 2]);
    CPoint p3 = CPoint(Points[3*indices[3 * indice1 + s3]],Points[(3 * indices[3 * indice1 + s3]) + 1],Points[(3 * indices[3 * indice1 + s3]) + 2]);


    CPoint Extrem18 = CPoint(0,0,0);//debut calcul du premier extrem
    for (int i = 0 ; i < NbTriangles; i++){
        if (i != indice1){
            if (Points[indices[3 * i]] == p1.getX() && Points[indices[3 * i] + 1] == p1.getY() && Points[indices[3 * i]+2 ] == p1.getZ()){
                if (Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i + 1] + 1] == p2.getY() && Points[indices[3 * i + 1]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i + 2]]);
                    Extrem18.setY(Points[indices[3 * i + 2] + 1]);
                    Extrem18.setZ(Points[indices[3 * i + 2] + 2]);
               }
                else if (Points[indices[3 * i + 2]] == p2.getX() && Points[indices[3 * i + 2] + 1] == p2.getY() && Points[indices[3 * i + 2]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i + 1]]);
                    Extrem18.setY(Points[indices[3 * i + 1] + 1]);
                    Extrem18.setZ(Points[indices[3 * i + 1] + 2]);
                }
            }

            if (Points[indices[3 * i + 1]] == p1.getX() && Points[indices[3 * i + 1] + 1] == p1.getY() && Points[indices[3 * i + 1]+2 ] == p1.getZ()){
                if (Points[indices[3 * i ]] == p2.getX() && Points[indices[3 * i ] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i + 2]]);
                    Extrem18.setY(Points[indices[3 * i + 2] + 1]);
                    Extrem18.setZ(Points[indices[3 * i + 2] + 2]);
               }
                else if (Points[indices[3 * i + 2]] == p2.getX() && Points[indices[3 * i + 2] + 1] == p2.getY() && Points[indices[3 * i + 2]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i ]]);
                    Extrem18.setY(Points[indices[3 * i ] + 1]);
                    Extrem18.setZ(Points[indices[3 * i ] + 2]);
                }
            }

            if (Points[indices[3 * i + 2]] == p1.getX() && Points[indices[3 * i +2] + 1] == p1.getY() && Points[indices[3 * i + 2]+2 ] == p1.getZ()){
                if (Points[indices[3 * i]] == p2.getX() && Points[indices[3 * i] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i + 1]]);
                    Extrem18.setY(Points[indices[3 * i + 1] + 1]);
                    Extrem18.setZ(Points[indices[3 * i + 1] + 2]);
               }
                else if (Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i + 1] + 1] == p2.getY() && Points[indices[3 * i + 1]+2 ] == p2.getZ()){
                    Extrem18.setX(Points[indices[3 * i ]]);
                    Extrem18.setY(Points[indices[3 * i ] + 1]);
                    Extrem18.setZ(Points[indices[3 * i ] + 2]);
                }
            }

        }
    }//Fin calcul premier extrem

    
    float extrem16x = 0.0;//debut calculs des ponderation 1/16
    float extrem16y = 0.0;
    float extrem16z = 0.0;
    
    for (int i = 0 ; i < NbTriangles; i++){
        if (i != indice1){
            if (Points[indices[3 * i]] == p3.getX() && Points[indices[3 * i] + 1] == p3.getY() && Points[indices[3 * i]+2 ] == p3.getZ()){//si P3
                if ((Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i +1] + 1] == p2.getY() && Points[indices[3 * i+1]+2 ] == p2.getZ()) || (Points[indices[3 * i +1]] == p1.getX() && Points[indices[3 * i +1] + 1] == p1.getY() && Points[indices[3 * i+1]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 2]];
                    extrem16y += Points[indices[3 * i + 2] + 1];
                    extrem16z += Points[indices[3 * i + 2] + 2];
               }
                else if ((Points[indices[3 * i + 2]] == p2.getX() && Points[indices[3 * i +2] + 1] == p2.getY() && Points[indices[3 * i+2]+2 ] == p2.getZ()) || (Points[indices[3 * i +2]] == p1.getX() && Points[indices[3 * i +2] + 1] == p1.getY() && Points[indices[3 * i+2]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 1]];
                    extrem16y += Points[indices[3 * i + 1] + 1];
                    extrem16z += Points[indices[3 * i + 1] + 2];
                }
            }

            if (Points[indices[3 * i + 1]] == p3.getX() && Points[indices[3 * i + 1] + 1] == p3.getY() && Points[indices[3 * i + 1]+2 ] == p3.getZ()){
                if ((Points[indices[3 * i ]] == p2.getX() && Points[indices[3 * i ] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()) || (Points[indices[3 * i ]] == p1.getX() && Points[indices[3 * i ] + 1] == p1.getY() && Points[indices[3 * i]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 2]];
                    extrem16y += Points[indices[3 * i + 2] + 1];
                    extrem16z += Points[indices[3 * i + 2] + 2];
               }
                else if ((Points[indices[3 * i+2 ]] == p2.getX() && Points[indices[3 * i +2] + 1] == p2.getY() && Points[indices[3 * i+2]+2 ] == p2.getZ()) || (Points[indices[3 * i +2]] == p1.getX() && Points[indices[3 * i +2] + 1] == p1.getY() && Points[indices[3 * i+2]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i]];
                    extrem16y += Points[indices[3 * i] + 1];
                    extrem16z += Points[indices[3 * i] + 2];
                }
            }

            if (Points[indices[3 * i + 2]] == p3.getX() && Points[indices[3 * i +2] + 1] == p3.getY() && Points[indices[3 * i + 2]+2 ] == p3.getZ()){
                if ((Points[indices[3 * i ]] == p2.getX() && Points[indices[3 * i ] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()) || (Points[indices[3 * i ]] == p1.getX() && Points[indices[3 * i ] + 1] == p1.getY() && Points[indices[3 * i]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 1]];
                    extrem16y += Points[indices[3 * i + 1] + 1];
                    extrem16z += Points[indices[3 * i + 1] + 2];
               }
                else if ((Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i +1] + 1] == p2.getY() && Points[indices[3 * i+1]+2 ] == p2.getZ()) || (Points[indices[3 * i +1]] == p1.getX() && Points[indices[3 * i +1] + 1] == p1.getY() && Points[indices[3 * i+1]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i ]];
                    extrem16y += Points[indices[3 * i ] + 1];
                    extrem16z += Points[indices[3 * i ] + 2];
                }
            }//fin si p3
//si P8
            if (Points[indices[3 * i]] == Extrem18.getX() && Points[indices[3 * i] + 1] == Extrem18.getY() && Points[indices[3 * i]+2 ] == Extrem18.getZ()){//si P3
                if ((Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i +1] + 1] == p2.getY() && Points[indices[3 * i+1]+2 ] == p2.getZ()) || (Points[indices[3 * i +1]] == p1.getX() && Points[indices[3 * i +1] + 1] == p1.getY() && Points[indices[3 * i+1]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 2]];
                    extrem16y += Points[indices[3 * i + 2] + 1];
                    extrem16z += Points[indices[3 * i + 2] + 2];
               }
                else if ((Points[indices[3 * i + 2]] == p2.getX() && Points[indices[3 * i +2] + 1] == p2.getY() && Points[indices[3 * i+2]+2 ] == p2.getZ()) || (Points[indices[3 * i +2]] == p1.getX() && Points[indices[3 * i +2] + 1] == p1.getY() && Points[indices[3 * i+2]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 1]];
                    extrem16y += Points[indices[3 * i + 1] + 1];
                    extrem16z += Points[indices[3 * i + 1] + 2];
                }
            }

            if (Points[indices[3 * i + 1]] == Extrem18.getX() && Points[indices[3 * i + 1] + 1] == Extrem18.getY() && Points[indices[3 * i + 1]+2 ] == Extrem18.getZ()){
                if ((Points[indices[3 * i ]] == p2.getX() && Points[indices[3 * i ] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()) || (Points[indices[3 * i ]] == p1.getX() && Points[indices[3 * i ] + 1] == p1.getY() && Points[indices[3 * i]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 2]];
                    extrem16y += Points[indices[3 * i + 2] + 1];
                    extrem16z += Points[indices[3 * i + 2] + 2];
               }
                else if ((Points[indices[3 * i+2 ]] == p2.getX() && Points[indices[3 * i +2] + 1] == p2.getY() && Points[indices[3 * i+2]+2 ] == p2.getZ()) || (Points[indices[3 * i +2]] == p1.getX() && Points[indices[3 * i +2] + 1] == p1.getY() && Points[indices[3 * i+2]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i ]];
                    extrem16y += Points[indices[3 * i ] + 1];
                    extrem16z += Points[indices[3 * i ] + 2];
                }
            }

            if (Points[indices[3 * i + 2]] == Extrem18.getX() && Points[indices[3 * i +2] + 1] == Extrem18.getY() && Points[indices[3 * i + 2]+2 ] == Extrem18.getZ()){
                if ((Points[indices[3 * i ]] == p2.getX() && Points[indices[3 * i ] + 1] == p2.getY() && Points[indices[3 * i]+2 ] == p2.getZ()) || (Points[indices[3 * i ]] == p1.getX() && Points[indices[3 * i ] + 1] == p1.getY() && Points[indices[3 * i]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i + 1]];
                    extrem16y += Points[indices[3 * i + 1] + 1];
                    extrem16z += Points[indices[3 * i + 1] + 2];
               }
                else if ((Points[indices[3 * i + 1]] == p2.getX() && Points[indices[3 * i +1] + 1] == p2.getY() && Points[indices[3 * i+1]+2 ] == p2.getZ()) || (Points[indices[3 * i +1]] == p1.getX() && Points[indices[3 * i +1] + 1] == p1.getY() && Points[indices[3 * i+1]+2 ] == p1.getZ())){
                    extrem16x += Points[indices[3 * i ]];
                    extrem16y += Points[indices[3 * i ] + 1];
                    extrem16z += Points[indices[3 * i ] + 2];
                }
            }//fin si ex8

        }
    }//Fin calcul ponderations 1/16

    CPoint Ptmp1 = CPoint(((-1/16)* extrem16x + (1/8) * Extrem18.getX()+ (1/8) * p3.getX() + p1.getX()/2 + p2.getX()/2) ,((-1/16)* extrem16y + (1/8) * Extrem18.getY()+ (1/8) * p3.getY() + p1.getY()/2 + p2.getY()/2),((-1/16)* extrem16z + (1/8) * Extrem18.getZ()+ (1/8) * p3.getZ()+ p1.getZ()/2 + p2.getZ()/2));

    return Ptmp1;
}


void decoupeTriangleB(float * Points,int * indices,int NbPoints,int NbTriangles,int indice1, int * nIndices,float* nTab){

    CPoint Ptmp1 = decoupeTriangleButterflyArete(Points,indices,NbPoints,NbTriangles,indice1,0,1);
    CPoint Ptmp2 = decoupeTriangleButterflyArete(Points,indices,NbPoints,NbTriangles,indice1,1,2);
    CPoint Ptmp3 = decoupeTriangleButterflyArete(Points,indices,NbPoints,NbTriangles,indice1,0,2);

    for (int i = 0; i < NbPoints; i++){
        nTab[3 * i] = Points[3 * i];
        nTab[3 * i + 1] = Points[3 * i + 1];
        nTab[3 * i + 2] = Points[3 * i + 2];
    }

    for (int i = 0; i < NbTriangles; i++){
        nIndices[3 * i] = indices[3 * i];
        nIndices[3 * i + 1] = indices[3 * i + 1];
        nIndices[3 * i + 2] = indices[3 * i + 2];
    }

    nTab[3 * NbPoints] = Ptmp1.getX();
    nTab[3 * NbPoints + 1] = Ptmp1.getY();
    nTab[3 * NbPoints + 2] = Ptmp1.getZ();
    nTab[3 * NbPoints + 3] = Ptmp2.getX();
    nTab[3 * NbPoints + 4] = Ptmp2.getY();
    nTab[3 * NbPoints + 5] = Ptmp2.getZ();
    nTab[3 * NbPoints + 6] = Ptmp3.getX();
    nTab[3 * NbPoints + 7] = Ptmp3.getY();
    nTab[3 * NbPoints + 8] = Ptmp3.getZ();

    nIndices[3 * NbTriangles] = NbPoints;
    nIndices[3 * NbTriangles + 1] = NbPoints+1;
    nIndices[3 * NbTriangles + 2] = NbPoints+2;
}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{

    // Exercice 1
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //string fic;
    //cout << "Fichier ? " << endl;
   // cin >> fic;
   ifstream File ("triceratops.off");
    string Line;
    getline(File, Line);

    cout << Line << endl;

    unsigned NbPoints;
    unsigned NbTriangles;
    unsigned Zero;

    File >> NbPoints;
    File >> NbTriangles;
    File >> Zero;

    float* Points;
    Points = (float*) malloc(NbPoints*3 * sizeof(float));
    int *Indices;
    Indices = (int*) malloc(NbTriangles*3 * sizeof(int));
    int *Voisins;
    Voisins = (int*) malloc(NbTriangles*3 * sizeof(int));
    
    cout << NbPoints << " " << NbTriangles << " " << Zero << endl;
    float X;
    
    for (int i =0 ; i < 3 * NbPoints; i++) {
        File >> X;
        Points[i] = X;
    }
    


    for (int z = 0; z < NbPoints * 3; z++){
        if (z % 3 == 0){
            if (Points[z] < x_min)
                x_min = Points[z];
            else if (Points[z] > x_max)
                x_max = Points[z];
        }
        else if (z % 3 == 1){
             if (Points[z] < y_min)
                y_min = Points[z];
            else if (Points[z] > y_max)
                y_max = Points[z];
        }
        else if (z % 3 == 2){
             if (Points[z] < z_min)
                z_min = Points[z];
            else if (Points[z] > z_max)
                z_max = Points[z];
        }
    } 

    int I1;
    unsigned nbL = 0;
    float tmp;
    for (unsigned i (0); i < 3 * NbTriangles; i++) {
        if (nbL == 0) 
            File >> tmp;
        nbL++;
        File >> I1;
        cout << I1 << " "  << endl;

        Indices[i] = I1; 
        if (nbL == 3)
            nbL = 0;
    }
   

    File.close();

    cout << Indices[3 * NbTriangles-3];

    cout << Indices[3 * NbTriangles-2];

    cout << Indices[3 * NbTriangles-1];

    cout << "Fin parser lancement scence" << endl; 
    int backt = NbTriangles;
    int backp = NbPoints;
  for (int i = 0; i < backt;i++){
        float nTab[NbPoints * 3 +9];
        int nIndices[NbTriangles * 3 + 12];
      //  cout << "Avant decoupage" << endl;
        decoupeTriangleB(Points,Indices,NbPoints,NbTriangles,i,nIndices,nTab);
        //decoupeTriangle(Points,Indices,NbPoints,NbTriangles,i,nIndices,nTab);
        NbPoints+=3;
        NbTriangles+=1;
       // cout << "avant opoints"<< endl;
        Points = (float*) realloc(Points,(NbPoints * 3)*sizeof(float));
       // cout << "apres point avant indice" << endl;
        Indices = (int*) realloc(Indices,(NbTriangles * 3)*sizeof(int));
       // cout << "apres indices" << endl;

        for (int j = 0; j < NbPoints * 3; j++)
            Points[j] = nTab[j];

        for (int k = 0; k < NbTriangles * 3; k++)
            Indices[k] = nIndices[k];
    }

    
    cout << "fin" << endl;
/*
    GLfloat all_normal[NbTriangles * 3];

    for (int i = 0; i < NbTriangles; i++){
        CPoint p1 = CPoint(Points[Indices[3 * i] *3],Points[Indices[3 * i] *3 +1],Points[Indices[3 * i] *3 +2]);
        CPoint p2 = CPoint(Points[Indices[3 * i + 1] *3],Points[Indices[3 * i + 1] *3 +1],Points[Indices[3 * i + 1] *3 +2]);
        CPoint p3 = CPoint(Points[Indices[3 * i + 2] *3],Points[Indices[3 * i + 2] *3 +1],Points[Indices[3 * i + 2] *3 +2]);

        CVector v1 = CVector(p2.getX(),p2.getY(),p2.getZ(),p1.getX(),p1.getY(),p1.getZ());
        CVector v2 = CVector(p3.getX(),p3.getY(),p3.getZ(),p1.getX(),p1.getY(),p1.getZ());

       // v1.Normalize();
        //v2.Normalize();

    CVector normal = v1.Vectoriel(v2);
        normal.Normalize();

       all_normal[i * 3] = normal.getX();
        all_normal[i * 3 + 1] = normal.getY();
        all_normal[i * 3 + 2] = normal.getZ();

    }
/**/

    cout << "Ancien nombre de triangles : " << backt << endl;
    cout << "Nouveau nombre de triangles : " << NbTriangles << endl;
    cout << "Ancien nombre de points : " << backp << endl;
    cout << "Nouveau nombre de points : " << NbPoints << endl;

  /*  for (int i = 0; i < 3 * NbPoints; i++){
        cout << Points[i] << " ";
    }

        cout << "" << endl;

        for (int i = 0; i < 3 * NbTriangles; i++){
        cout << Indices[i] << " ";
    }

        cout << "" << endl;*/
  
int rayon = 10, hauteur =20;
   // gluLookAt(rayon + 5, hauteur / 2, rayon + 5, 0, 0, 0, 0, 1, 0);
    glOrtho(-ortho4, ortho4, -ortho4, ortho4, -ortho4, ortho4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //gluLookAt(  ortho4, ortho4, ortho4,
    //        ortho4+lx, ortho4+ly,  ortho4+lz,
    //        0.0f, 1.0f,  0.0f);
    //glOrtho(-3,3,-3,3,-3,3);
   // gluLookAt(0,0.0,0,0,0,0, 0, 1, 0);   // toutes les transformations suivantes s´appliquent au modèle de vue 
//  gluLookAt(x_max_f , y_max_f, z_max_f, (x_min + x_max) / 2.0, (y_min + y_max) / 2.0, (z_min+ z_max) / 2.0, 0, 1, 0);   // toutes les transformations suivantes s´appliquent au modèle de vue 


   /* GLfloat lightColor0[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat lightPos0[] = {20.0f,50.0f,20.0f,10.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor0);

    int MatSpec[4] = { 0,0,0,0 };
    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
    glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);*/

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Points);

    //glEnableClientState(GL_NORMAL_ARRAY);
    //glNormalPointer(GL_FLOAT, 0, all_normal);
    //glDrawElements(GL_TRIANGLES, 3 * NbTriangles, GL_UNSIGNED_INT, Indices);

    cout << "avant le nouveau draw elements" << endl;
        glColor3f(1.0,0.0,0.0);
        glDrawElements(GL_TRIANGLES,(3 * NbTriangles), GL_UNSIGNED_INT, Indices);
    cout << "apres le nouveau draw elements" << endl;
    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
     //glutSwapBuffers();
    free(Indices);
    free(Voisins);
    free(Points);
    /* */


}
