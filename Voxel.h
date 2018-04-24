#ifndef VOXEL_H
#define VOXEL_H

#include <math.h>
#include <stdio.h>      
#include <stdlib.h>  
#include <vector> 
#include "CPoint.h"
#include <GL/glut.h>


class Voxel {

private:

    CPoint* ct;
    double l;
    std::vector<CPoint>* cornerPoints;
    std::vector<CPoint>* subCenterPoints;

public:

	Voxel();
	~Voxel();
	Voxel(CPoint* c, double length);

	CPoint* getCenter();
	double getLength();
	std::vector<CPoint>* getCornerPoints();
	std::vector<CPoint>* getSubCenterPoints();

	void tracePoint(CPoint *A, float x,float y,float z);
	void traceQuad(CPoint* A, CPoint* B,CPoint* C,CPoint* D, float x,float y,float z);
	void drawCorners();
	void displayV();
	void computeDivision();	
	void computeCornerPoints();
	void displayDivision();	
	int isInsideSphere(CPoint* cts, double ray);
	int isInsideCylinder(CPoint* cts, CVector* v,double ray);
};

#endif