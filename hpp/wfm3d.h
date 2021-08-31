#ifndef __WFM3D_H
#define __WFM3D_H

#include <Draw3D.H>

#define WireFrame      0x8000
#define Overlapped     0x4000
#define LoopBackInner  0x2000
#define LoopBackOuter  0x1000

#define InnerCurves    0x0800
#define OuterCurves    0x0400
#define ShowCtrlPts    0x0200
#define ShowEdges      0x0100
#define MaskObjOff     0xF1FF
#define ShowObject     0x0C00

#define CuboidIn3D     0xEC01
#define PyramidIn3D    0xEC02
#define ConeIn3D       0xEC03
#define CylinderIn3D   0xEC04
#define TorusIn3D      0xFC05
#define EllipsoidIn3D  0xFC06
#define ChessPawnIn3D  0xEC07
#define VaseIn3D       0xEC08

#define ObjType        0x00FF
#define Cuboid3D       0x0001
#define Pyramid3D      0x0002
#define Cone3D         0x0003
#define Cylinder3D     0x0004
#define Torus3D        0x0005
#define Ellipsoid3D    0x0006
#define ChessPawn3D    0x0007
#define Vase3D         0x0008

#define Trn3D  0
#define Scl3D  1
#define Rot3D  2
#define Arb3D  3
#define Apply  5
#define Clear  6
#define Poly   8
#define ObOnly 9
#define ObPoly 10

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>  Class Name    : Wfm3D                                             <<>>
// <<>>  Derived from  :                                                   <<>>
// <<>>  Purpose       : Wire frame object creation and display            <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


class Wfm3D
 {
   public :
     Vector Centre;          // Vector for centre of object
     Vector Normal;          // Vector for Normal for object

     int    M,N,             // For M x N Control Points
            Size;            // For number of Total points = M*N
     int    Nu,Nv;           // Precision or Solidity of Object
     int    GrpM,GrpN;       // for Grouping

     word   swWfm3D;
     byte   cSurface,
            cPolyNet,
            cNetEdge;

     int    icCnt,ocCnt,SrfSiz;
     Vector *S;

     Wfm3D();
     Wfm3D(int m,int n);
     ~Wfm3D();

     void   WfmCreate(int m,int n);
     void   SetProperties(word PrWfm);
     void   SetDisplayColours(byte cSrf,byte cNet,byte cEdg);
     void   SetPrecision(int m,int n);
     void   SetGroups(int m,int n);

     void   SetCentreAndNormal(Vector C, Vector N);
     void   ResetControls();
     void   SetNormal();

     void   CreateObject();
     void   ApplyTransform(XForm XF);
     Vector CentreOfObject(XForm XF);
     void   ZAxisToNormal();

     void   RegularPoly(int About,int i,float x,float y,float z);
     void   Elliptical(int About,int i,int Grp,float x,float y,float z);

     Vector SurfacePt(float u,float v,int mOff,int nOff);
     void   PolygonNet(Draw3D& Pen,TDC& Canvas,int mOff,int nOff);
     void   DisplayObject(Draw3D& Pen,TDC& Canvas);
     void   Draw(Draw3D& Pen);
 };

#endif
