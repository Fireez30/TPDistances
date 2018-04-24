#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "GL/glut.h" 

class CVector {
	
	private:
		double x;
		double y;
		double z;

	public:

    CVector();
    CVector(double x2,double y2,double z2);
    CVector(const CVector& p);
    CVector(double x1, double y1, double z1, double x2, double y2, double z2);
	double getX();
	double getY();
	double getZ();
	void setX(double x2);
	void setY(double y2);
	void setZ(double z2);

	double Norme();
	void Normalize();
    double Scalar(CVector* v2);
    CVector Vectoriel(CVector v2);
    double Angle(CVector* v2);
    void drawLine(double x1, double y1, double z1);
};
