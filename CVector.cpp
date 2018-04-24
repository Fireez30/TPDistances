#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "CVector.h"
#include "GL/glut.h"

CVector::CVector(){}
CVector::CVector(double x2,double y2,double z2) : x (x2), y (y2), z (z2) {}//vector via coordonnees
CVector::CVector(const CVector & p) {
   x = p.x;
   y = p.y;
   z = p.z;
}

CVector::CVector(double x1, double y1, double z1, double x2, double y2, double z2){//vector via point
    x=x1-x2;
    y=y1-y2;
    z=z1-z2;
}

//getters
double CVector::getX(){
    return x;
}
double CVector::getY(){
    return y;
}
double CVector::getZ(){
    return z;
}
//setters
void CVector::setX(double xcoord){
        x=xcoord;
}
void CVector::setY(double ycoord){
        y=ycoord;
}
void CVector::setZ(double zcoord){
        z=zcoord;
}

//methodes tp1
double CVector::Norme(){
    return sqrt(x*x+y*y+z*z);
}

void CVector::Normalize(){//normaliser le vecteur
    double norme = Norme();
    x /= norme;
    y /= norme;
    z /= norme;
}

double CVector::Scalar(CVector* v2){//produit scalaire
    return x*v2->getX()+y*v2->getY()+z*v2->getZ();
}

CVector CVector::Vectoriel(CVector v2){//produit vectoriel
    double xt = y*v2.getZ()-z*v2.getY();
    double yt = z*v2.getX()-x*v2.getZ();
    double zt = x*v2.getY()-y*v2.getX();

        CVector tmp = CVector(xt,yt,zt);

	return tmp;
}

double CVector::Angle(CVector* v2){//angle entre 2 vectors
    return acos(this->Scalar(v2)/(Norme()*v2->Norme()));
}

void CVector::drawLine(double x1, double y1, double z1){//affichage dans OpenGL
	glBegin(GL_LINES);
        glVertex3f(x1,y1,z1);
        glVertex3f(x1+x,y1+y,z1+z);
	glEnd();
}
