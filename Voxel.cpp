#include "Voxel.h"
 
// Constructors
Voxel::Voxel() {}
Voxel::~Voxel() {}
 
Voxel::Voxel(CPoint* ct, double l) {
    this->ct = ct;
    this->l = l;
    this->subCenterPoints = new std::vector<CPoint>();
    this->cornerPoints = new std::vector<CPoint>();
    computeDivision();
    computeCornerPoints();
}
 
CPoint*  Voxel::getCenter() {
    return ct;
}
double Voxel::getLength() {
    return l;
}
 
std::vector<CPoint>* Voxel::getCornerPoints() {
    return cornerPoints;
}
 
std::vector<CPoint>* Voxel::getSubCenterPoints() {
    return subCenterPoints;
}
 
void Voxel::tracePoint(CPoint *A, float x,float y,float z) {
  glColor3f(x,y,z);
  glBegin(GL_POINTS);
    glVertex3f(A->getX(),A->getY(),A->getZ());
    glEnd();
}
 
void  Voxel::traceQuad(CPoint* A, CPoint* B,CPoint* C,CPoint* D,  float x,float y,float z) {
  glColor3f(x,y,z);
  glBegin(GL_QUADS);
    glVertex3f(A->getX(),A->getY(),A->getZ());
    glVertex3f(B->getX(),B->getY(),B->getZ());
    glVertex3f(C->getX(),C->getY(),C->getZ());
    glVertex3f(D->getX(),D->getY(),D->getZ());
  glEnd();
}
 
void Voxel::displayV() { // Point center, double length
  CPoint* a = new CPoint(ct->getX()+l/2, ct->getY()-l/2, ct->getZ()-l/2);
  CPoint* b = new CPoint(ct->getX()+l/2, ct->getY()+l/2, ct->getZ()-l/2);
  CPoint* c = new CPoint(ct->getX()-l/2, ct->getY()-l/2, ct->getZ()-l/2);
  CPoint* d = new CPoint(ct->getX()-l/2, ct->getY()+l/2, ct->getZ()-l/2);
  CPoint* e = new CPoint(ct->getX()+l/2, ct->getY()-l/2, ct->getZ()+l/2);
  CPoint* f = new CPoint(ct->getX()+l/2, ct->getY()+l/2, ct->getZ()+l/2);
  CPoint* g = new CPoint(ct->getX()-l/2, ct->getY()-l/2, ct->getZ()+l/2);
  CPoint* h = new CPoint(ct->getX()-l/2, ct->getY()+l/2, ct->getZ()+l/2);
 
  traceQuad(a,b,d,c,255,0,0);
  traceQuad(a,c,g,e,255,0,0);
  traceQuad(d,c,g,h,255,0,0);
  traceQuad(b,d,h,f,255,0,0);
  traceQuad(a,b,f,e,255,0,0);
  traceQuad(e,f,h,g,255,0,0);
/*  traceQuad(a,b,d,c,Vector(255,255,255));
  traceQuad(a,c,g,e,Vector(255,255,255));
  traceQuad(d,c,g,h,Vector(255,255,255));
  traceQuad(b,d,h,f,Vector(255,255,255));
  traceQuad(a,b,f,e,Vector(255,255,255));
  traceQuad(e,f,h,g,Vector(255,255,255));*/
 
/*  tracePoint(ct,Vector(255,0,0));
  tracePoint(a,Vector(255,255,0));
  tracePoint(b,Vector(255,255,0));
  tracePoint(c,Vector(255,255,0));
  tracePoint(d,Vector(255,255,0));
  tracePoint(e,Vector(255,255,0));
  tracePoint(f,Vector(255,255,0));
  tracePoint(g,Vector(255,255,0));
  tracePoint(h,Vector(255,255,0));*/
}
 
void Voxel::computeDivision() {    
    subCenterPoints->push_back(CPoint(ct->getX()-l/4, ct->getY()+l/4, ct->getZ()-l/4));
    subCenterPoints->push_back(CPoint(ct->getX()-l/4, ct->getY()-l/4, ct->getZ()-l/4));
    subCenterPoints->push_back(CPoint(ct->getX()+l/4, ct->getY()-l/4, ct->getZ()-l/4));
    subCenterPoints->push_back(CPoint(ct->getX()+l/4, ct->getY()+l/4, ct->getZ()-l/4));
    subCenterPoints->push_back(CPoint(ct->getX()-l/4, ct->getY()-l/4, ct->getZ()+l/4));
    subCenterPoints->push_back(CPoint(ct->getX()-l/4, ct->getY()+l/4, ct->getZ()+l/4));
    subCenterPoints->push_back(CPoint(ct->getX()+l/4, ct->getY()-l/4, ct->getZ()+l/4));
    subCenterPoints->push_back(CPoint(ct->getX()+l/4, ct->getY()+l/4, ct->getZ()+l/4));
}
 
void Voxel::computeCornerPoints() {
   /* 
    CPoint* a = new 
    CPoint* b = new 
    CPoint* c = new 
    CPoint* d = new 
    CPoint* e = new 
    CPoint* f = new 
    CPoint* g = new 
    CPoint* h = new 
    /* */
    cornerPoints->push_back(CPoint(ct->getX()-l/2, ct->getY()+l/2, ct->getZ()-l/2));
    cornerPoints->push_back(CPoint(ct->getX()-l/2, ct->getY()-l/2, ct->getZ()-l/2));
    cornerPoints->push_back(CPoint(ct->getX()+l/2, ct->getY()-l/2, ct->getZ()-l/2));
    cornerPoints->push_back(CPoint(ct->getX()+l/2, ct->getY()+l/2, ct->getZ()-l/2));
    cornerPoints->push_back(CPoint(ct->getX()-l/2, ct->getY()-l/2, ct->getZ()+l/2));
    cornerPoints->push_back(CPoint(ct->getX()-l/2, ct->getY()+l/2, ct->getZ()+l/2));
    cornerPoints->push_back(CPoint(ct->getX()+l/2, ct->getY()-l/2, ct->getZ()+l/2));
    cornerPoints->push_back(CPoint(ct->getX()+l/2, ct->getY()+l/2, ct->getZ()+l/2));
}
 
void Voxel::displayDivision() {
    Voxel* temp;
    for(int i =0; i<8; i++)
    {
        temp = new Voxel(&subCenterPoints->at(i),(double)l/2.0);
        temp->displayV();
    }
}

void Voxel::drawCorners(){
  glColor3f(1,0,0);
  glBegin(GL_LINES);
  glVertex3f(cornerPoints->at(0).getX(), cornerPoints->at(0).getY(), cornerPoints->at(0).getZ());
  glVertex3f(cornerPoints->at(1).getX(), cornerPoints->at(1).getY(), cornerPoints->at(1).getZ());

  glVertex3f(cornerPoints->at(0).getX(), cornerPoints->at(0).getY(), cornerPoints->at(0).getZ());
 glVertex3f(cornerPoints->at(5).getX(), cornerPoints->at(5).getY(), cornerPoints->at(5).getZ());

 glVertex3f(cornerPoints->at(5).getX(), cornerPoints->at(5).getY(), cornerPoints->at(5).getZ());
 glVertex3f(cornerPoints->at(4).getX(), cornerPoints->at(4).getY(), cornerPoints->at(4).getZ());
 

 glVertex3f(cornerPoints->at(4).getX(), cornerPoints->at(4).getY(), cornerPoints->at(4).getZ());
 glVertex3f(cornerPoints->at(1).getX(), cornerPoints->at(1).getY(), cornerPoints->at(1).getZ());


glVertex3f(cornerPoints->at(7).getX(), cornerPoints->at(7).getY(), cornerPoints->at(7).getZ());
 glVertex3f(cornerPoints->at(5).getX(), cornerPoints->at(5).getY(), cornerPoints->at(5).getZ());

  glVertex3f(cornerPoints->at(7).getX(), cornerPoints->at(7).getY(), cornerPoints->at(7).getZ());
  glVertex3f(cornerPoints->at(6).getX(), cornerPoints->at(6).getY(), cornerPoints->at(6).getZ());

   glVertex3f(cornerPoints->at(5).getX(), cornerPoints->at(5).getY(), cornerPoints->at(5).getZ());
  glVertex3f(cornerPoints->at(4).getX(), cornerPoints->at(4).getY(), cornerPoints->at(4).getZ());

  glVertex3f(cornerPoints->at(4).getX(), cornerPoints->at(4).getY(), cornerPoints->at(4).getZ());
  glVertex3f(cornerPoints->at(6).getX(), cornerPoints->at(6).getY(), cornerPoints->at(6).getZ());


  glVertex3f(cornerPoints->at(2).getX(), cornerPoints->at(2).getY(), cornerPoints->at(2).getZ());
  glVertex3f(cornerPoints->at(1).getX(), cornerPoints->at(1).getY(), cornerPoints->at(1).getZ());

  glVertex3f(cornerPoints->at(2).getX(), cornerPoints->at(2).getY(), cornerPoints->at(2).getZ());
  glVertex3f(cornerPoints->at(3).getX(), cornerPoints->at(3).getY(), cornerPoints->at(3).getZ());

  glVertex3f(cornerPoints->at(2).getX(), cornerPoints->at(2).getY(), cornerPoints->at(2).getZ());
  glVertex3f(cornerPoints->at(6).getX(), cornerPoints->at(6).getY(), cornerPoints->at(6).getZ());

  glVertex3f(cornerPoints->at(3).getX(), cornerPoints->at(3).getY(), cornerPoints->at(3).getZ());
  glVertex3f(cornerPoints->at(7).getX(), cornerPoints->at(7).getY(), cornerPoints->at(7).getZ());
  glEnd();
}
 
int Voxel::isInsideSphere(CPoint* cts, double ray) { // return 1 if vox inside Sphere,
                                                    //  return 0 if outside
                                                    // return 2 if intersection
    int retour = 0;
    int cpt = 0;

    for(int k=0; k<8; k++)
    {
        if(cornerPoints->at(k).isInsideSphere(cts, ray)==1)
        {
            retour = 1;
            cpt++;
        }
    }
    if(cpt<7 && cpt>0)
        return 2;
    else
        return retour;
}


int Voxel::isInsideCylinder(CPoint* cts, CVector* v,double ray) { // return 1 if vox inside Sphere,
                                                    //  return 0 if outside
                                                    // return 2 if intersection
    int retour = 0;
    int cpt = 0;
    /*  if (ct->isInsideCylinder(cts,v,ray) == 1)
    {
      cpt++;
      retour = 2;
    }*/
    for(int k=0; k<8; k++)
    {
        if(cornerPoints->at(k).isInsideCylinder(cts,v,ray)==1)
        {
            retour = 1;
            cpt++;
        }
    }
    if(cpt<8 && cpt>0)
        return 2;
    else
        return retour;
}