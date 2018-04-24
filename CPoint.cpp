#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "CPoint.h"
#include "CVector.h"

using namespace std;

CPoint::CPoint(){}
CPoint::CPoint(double x2,double y2,double z2) : x (x2), y (y2), z (z2) {}
CPoint::CPoint(const CPoint &p){
    x = p.x;
    y = p.y;
    z = p.z;
}
double CPoint::getX(){
    return x;
}
double CPoint::getY(){
    return y;
}
double CPoint::getZ(){
    return z;
}
void CPoint::setX(double x2){
    x=x2;
}
void CPoint::setY(double y2){
    y=y2;
}
void CPoint::setZ(double z2){
    z=z2;
}

double CPoint::distance(CPoint p){
    return sqrt(pow(p.getX() - x,2.0)+pow(p.getY() - y,2.0)+pow(p.getZ() - z,2.0));
}


int CPoint::isInsideSphere(CPoint* c,double r){
    double dist =  sqrt(pow(this->x - c->getX() ,2)+pow(this->y - c->getY(),2)+pow(this->z - c->getZ(),2));

    if (dist <= r)
        return 1;
    else return 0;

}

int CPoint::isInsideCylinder(CPoint* c,CVector* v,double r){
    CPoint proj = c->ProjectOnLine(v,this);
    CPoint tmp = CPoint(c->getX(),c->getY(),c->getZ());

    double dist =  this->distance(proj);
    double dist2 = proj.distance(tmp);

    if (dist <= r && dist2 <= v->Norme()/2)  {

        return 1;
    }
    else {
        return 0;
}
}

/*
CPoint CPoint::ProjectOnLine(CPoint pl1,CPoint pl2){
    CVector v = CVector(pl1.getX(), pl1.getY(), pl1.getZ(), pl2.getX(), pl2.getY(), pl2.getZ());
    return ProjectOnLine(v,pl1);
}
*/

CPoint CPoint::ProjectOnLine(CVector* v,CPoint* pl){

    CVector* v3= new CVector(pl->getX()-x,pl->getY()-y,pl->getZ()-z);//vecteur point a projeter
    v->Normalize();

    double dist = v3->Scalar(v)/v->Norme();

    double _x = x+v->getX()*dist;
    double _y = y+v->getY()*dist;
    double _z = z+v->getZ()*dist;
    return CPoint(_x,_y,_z);
}

CPoint CPoint::ProjectOnPlan(CPoint pplan,CVector* normalplan){
    CVector v2 = CVector(x, y, z, pplan.getX(), pplan.getY(), pplan.getZ());
    double dist = v2.Scalar(normalplan)/normalplan->Norme();

    double xtmp = x-normalplan->getX()*dist;
    double ytmp = y-normalplan->getY()*dist;
    double ztmp = z-normalplan->getZ()*dist;

    CPoint r = CPoint(xtmp,ytmp,ztmp);
    return r;
}

void CPoint::drawPoint(){
    //glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    //glEnd();
}

