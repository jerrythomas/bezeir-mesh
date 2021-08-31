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


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>  Member functions of Class Wfm3D                                   <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

Wfm3D::Wfm3D()
 {
    swWfm3D = 0xFC00;
    S = (Vector*) NULL;
    SetDisplayColours(csGreen,csRed,csCyan);
 }

Wfm3D::Wfm3D(int m,int n)
 {
   swWfm3D = 0xFC00;
   S = (Vector*) NULL;
   WfmCreate(m,n);
   S = new Vector[Size];
   SetDisplayColours(csGreen,csRed,csCyan);
 }

Wfm3D::~Wfm3D()
 {
   delete S;
 }

void Wfm3D::WfmCreate(int m,int n)
 {
   M= GrpM = m;
   N= GrpN = n;
   Size    = M*N;
   Nu      = 2;
   Nv      = 2;

   if (S != (Vector*)NULL) delete S;
   S  = new Vector[Size];
 }
void Wfm3D::SetProperties(word PrWfm)
 {
   swWfm3D = PrWfm;
 }
void Wfm3D::SetDisplayColours(byte cSrf,byte cNet,byte cEdg)
 {
   cSurface = cSrf;
   cPolyNet = cNet;
   cNetEdge = cEdg;
 }
void Wfm3D::SetPrecision(int m,int n)
 {
   Nu = abs(n);
   Nv = abs(m);
 }

void Wfm3D::SetGroups(int m,int n)
 {
   GrpM = (m >1 && m<= M)? m:M;
   GrpN = (n >1 && n<= N)? n:N;
 }

void Wfm3D::SetCentreAndNormal(Vector C, Vector N)
 {
   Centre = C;
   Normal = N;
 }

void Wfm3D::ResetControls()
 {
   for (int i=0;i<Size;i++)
    S[i].Vectorise(0,0,0);
 }

void Wfm3D::SetNormal()
 {
  Normal -= Centre;
  Normal.UnitVector();
 }


void Wfm3D::ApplyTransform(XForm XF)
 {
   for (int i=0;i<Size;i++)
     S[i] *= XF;
 }

Vector Wfm3D::CentreOfObject(XForm XF)
 {
  Vector Cntr;
  for (int i=0;i<Size;i++)
    Cntr += S[i]*XF;
  Cntr /= (Size>0) ? Size:1;
  return Cntr;
 }

void Wfm3D::ZAxisToNormal()
 {
   XForm XF;
   XF.Identity();
   XF.zAxisToNormal(Normal);
   XF.Translate3D(Centre);
   for (int i=0;i<Size;i++)
     S[i] *= XF;
   XF.Identity();
 }

void Wfm3D::RegularPoly(int About,int i,float x,float y,float z)
 {
   XForm XF;
  About %=3;
  int n=i*N;
  if (N==4)
   {
    switch(About)
     {
       case X_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,-y,z);
                     S[n+2].Vectorise(x,-y,-z);
                     S[n+3].Vectorise(x,y,-z);
                     break;
       case Y_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,y,-z);
                     S[n+2].Vectorise(-x,y,-z);
                     S[n+3].Vectorise(-x,y,z);
                     break;
       case Z_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,-y,z);
                     S[n+2].Vectorise(-x,-y,z);
                     S[n+3].Vectorise(-x,y,z);
                     break;
     }
   }
  else
   {
     S[n].Vectorise(x,y,z);
     for (i=1;i<N;i++)
      {
        XF.Identity();
        XF.RotateAbout(About,(float)i*360/(N-1));
        S[n+i] = S[n]*XF;
      }
     XF.Identity();
   }
 }

void Wfm3D::Elliptical(int About,int i,int Grp,float x,float y,float z)
 {
  About %= 3;
  int j,k,n=i,l;
  Vector V;
  int SgnA,SgnB;
  switch(About)
   {
     case X_Axis: if (swWfm3D&Overlapped)
                    for (i=0,k=2;i<8;i++,k=(k+1)%8)
                     {
                       SgnA = -((k%4+2)%6)/3*((k/4)*2-1);
                       SgnB = -((i%4+2)%6)/3*((i/4)*2-1);
                       V.Vectorise(x,SgnA*y,SgnB*z);
                       for (l=0;l<Grp;l++)
                         S[n++] += V;
                     }
                  else
                   {
                     for (j=-1;j<=1;j+=2)
                       for (i=0,k=3;i<6;i++,k++)
                        {
                          V.Vectorise(x,(i/2-1)*j*y,((k%8)/4)*j*z);
                          for (l=0;l<Grp;l++)
                            S[n++] += V;
                        }
                   }
                  break;
     case Y_Axis: if (swWfm3D&Overlapped)
                    for (i=0,k=2;i<8;i++,k=(k+1)%8)
                     {
                       SgnA = -((k%4+2)%6)/3*((k/4)*2-1);
                       SgnB = -((i%4+2)%6)/3*((i/4)*2-1);
                       V.Vectorise(SgnA*x,y,SgnB*z);
                       for (l=0;l<Grp;l++)
                         S[n++] += V;
                     }
                  else
                   {
                     for (j=-1;j<=1;j+=2)
                       for (i=0,k=3;i<6;i++,k++)
                        {
                          V.Vectorise((i/2-1)*j*x,y,((k%8)/4)*j*-z);
                          for (l=0;l<Grp;l++)
                            S[n++] += V;
                        }
                   }
                  break;
     case Z_Axis: if (swWfm3D&Overlapped)
                     for (i=0,k=2;i<8;i++,k=(k+1)%8)
                      {
                        SgnA = -(((k%4+2)%6)/3)*((k/4)*2-1);
                        SgnB = -(((i%4+2)%6)/3)*((i/4)*2-1);
                        V.Vectorise(SgnA*x,SgnB*y,z);
                        for (l=0;l<Grp;l++)
                          S[n++] += V;
                      }
                  else
                   {
                     for (j=1;j>=-1;j-=2)
                       for (i=0,k=3;i<6;i++,k++)
                        {
                          V.Vectorise((i/2-1)*j*-x,((k%8)/4)*j*y,z);
                          for (l=0;l<Grp;l++)
                            S[n++] += V;
                        }
                   }
                  break;
    }
 }


Vector Wfm3D::SurfacePt(float u,float v,int mOff,int nOff)
 {
  Vector rvVec(0,0,0);
  int    m,n;

  for (m=0;m<GrpM;m++,++mOff%=M)
  for (n=0;n<GrpN;n++)
   rvVec = rvVec + S[mOff*N + (nOff+n)%N]*(Bez(GrpN-1,u,n)*Bez(GrpM-1,v,m));

  return rvVec ;
 }


/*
void Wfm3D::CreateObjectPoints(Draw3D& Pen,TDC& Canvas)
 {
  if (swWfm3D&WireFrame)
   {
    float v,u;
    int   Offset=0,i,j;
    float Dv = (float)1.0/Nv;
    float Du = (float)1.0/Nu;
    int MaxM,MaxN,mOff,nOff;
    if (swWfm3D&Overlapped)
     {
      MaxM   = (M==GrpM) ? 1:(GrpM==2) ? M-1:M/(GrpM-1);
      mOff   = (M==GrpM) ? 1:(GrpM-1);
      MaxN   = (N==GrpN) ? 1:(GrpN==2) ? N-1:N/(GrpN-1);
      nOff   = (N==GrpN) ? GrpN:GrpN-1;
      if (swWfm3D&LoopBackOuter)
    MaxM = (M!=GrpM && GrpM==2) ? M:MaxM;
      if (swWfm3D&LoopBackInner)
    MaxN = (N!=GrpN && GrpN==2) ? N:MaxN;
     }
    else
     {
      MaxM   = M/GrpM;
      MaxN   = N/GrpN;
      mOff   = GrpM;
      nOff   = GrpN;

     }
  //  if (swWfm3D&ShowCtrlPts)
  //   {
  //    for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
  //     for(j=0;j<MaxN;j++)
  //  PolygonNet(Offset,j*nOff);
  //   }
  //  if (swWfm3D&InnerCurves)
  //   {
      icCnt = MaxN*(Nu+1);
      ocCnt = MaxM*(Nv+1);
      SrfSiz = icCnt*ocCnt;
      Srf = new Vector[SrfSiz];
      int idx;
      for (idx=0,i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for (v=0.0; v < 1.0+Dv ;v += Dv)
    for(j=0;j<MaxN;j++)
      for (u=0.0;u < 1.0+Du;u+=Du)
        Srf[idx++] = Surface(u,v,Offset,j*nOff);//Green);
//      for(j=0;j<MaxN;j++)
//      for (u=0.0;u< 1.0+Du;u +=Du)
//  for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
//    for (v=0.0;v < 1+Dv;v+=Dv)
//     Srf[idx++]=Surface(u,v,Offset,j*nOff);//,cSurface);//Green);
   }
 } */

void Wfm3D::PolygonNet(Draw3D& Pen,TDC& Canvas,int mOff,int nOff)
 {
  int i,j,Offset;

  Pen.SetBaseRGB(cPolyNet);
  for (i=0,Offset=mOff*N;i<GrpM;i++,Offset=((mOff+i)%M)*N)
   {
     Pen.MoveTo3D(Canvas,S[Offset+nOff%N]);
     //Pen.Block3D (S[Offset+nOff%N],cNetEdge);//Cyan);
    for (j=1;j<GrpN;j++)
     {
       Pen.LineTo3D(Canvas,S[Offset+(nOff+j)%N]);//,cPolyNet);//Cyan);
      //Pen.Block3D (S[Offset+(nOff+j)%N],cNetEdge);//Cyan);
     }
   }
  for (i=0,nOff%=N;i<GrpN;i++,++nOff%=N)
   {
     Offset = N*(mOff%M);
     Pen.MoveTo3D(Canvas,S[Offset+nOff]);
     //Pen.Block3D (S[Offset+nOff],cNetEdge);//Cyan);
     for (j=1,Offset=((mOff+1)%M)*N;j<GrpM;j++,Offset=((mOff+j)%M)*N)
      {
        Pen.LineTo3D(Canvas,S[Offset+nOff]);//,cPolyNet);//,Cyan);
      //Pen.Block3D (S[Offset+nOff],cNetEdge);//,Cyan);
      }
   }
 }

void Wfm3D::DisplayObject(Draw3D& Pen,TDC& Canvas)
 {
//  WorkArea();
  if (swWfm3D&WireFrame)
   {
    float v,u;
    int   Offset=0,i,j;
    float Dv = (float)1.0/Nv;
    float Du = (float)1.0/Nu;
    int   MaxM,MaxN,mOff,nOff;

    if (swWfm3D&Overlapped)
     {

      MaxM   = (M==GrpM) ? 1:(GrpM==2) ? M-1:M/(GrpM-1);
      mOff   = (M==GrpM) ? 1:(GrpM-1);
      MaxN   = (N==GrpN) ? 1:(GrpN==2) ? N-1:N/(GrpN-1);
      nOff   = (N==GrpN) ? GrpN:GrpN-1;
      if (swWfm3D&LoopBackOuter)
         MaxM = (M!=GrpM && GrpM==2) ? M:MaxM;
      if (swWfm3D&LoopBackInner)
         MaxN = (N!=GrpN && GrpN==2) ? N:MaxN;

     }
    else
     {
      MaxM   = M/GrpM;
      MaxN   = N/GrpN;
      mOff   = GrpM;
      nOff   = GrpN;
     }
    if (swWfm3D&ShowCtrlPts)
     {

      for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for(j=0;j<MaxN;j++)
         PolygonNet(Pen,Canvas,Offset,j*nOff);
     }

    Pen.SetBaseRGB(cSurface);
    if (swWfm3D&InnerCurves)
     {

      for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for (v=0.0; v < 1.0+Dv ;v += Dv)
        {
          for(j=0;j<MaxN;j++)
           {
             Pen.MoveTo3D(Canvas,SurfacePt(0.0,v,Offset,j*nOff));
             for (u=Du;u < 1.0+Du;u+=Du)
               Pen.LineTo3D(Canvas,SurfacePt(u,v,Offset,j*nOff)); //,cSurface);//Green);
           }
        }
     }
    if (swWfm3D&OuterCurves)
     {
      for(j=0;j<MaxN;j++)
       for (u=0.0;u< 1.0+Du;u +=Du)
         {
           for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
            {
              Pen.MoveTo3D(Canvas,SurfacePt(u,0.0,Offset,j*nOff));
              for (v=Dv;v < 1+Dv;v+=Dv)
                Pen.LineTo3D(Canvas,SurfacePt(u,v,Offset,j*nOff));//,cSurface);//Green);
            }
         }
     }
   }
 }

void Wfm3D::Draw(Draw3D& Pen)
 {

/*   Pen.SetBaseRGB(csBlue);
   Pen.Line3D(TClientDC(Pen),Vector(0,0,0),Vector(0,0,300));
   Pen.Line3D(TClientDC(Pen),Vector(0,0,0),Vector(0,300,0));
   Pen.Line3D(TClientDC(Pen),Vector(0,0,0),Vector(300,0,0));

   Pen.SetBaseRGB(csGreen);*/
   DisplayObject(Pen,TClientDC(Pen));
 }
/*void Wfm3D::DrawWireFrame(TDC& Canvas,Wfm3D *Obj)
 {
  int i,j,offset;

  SetBaseRGB(cSurface);
  for (i=0;i<icCnt;i++)
   for (j=1,offset = icCnt;j<ocCnt;j++,offset+= icCnt)
     Pen.Line3D(Canvas,Srf[offset+i-icCnt],Srf[offset+i]);//,cSurface);

  for (i=0,offset = 0;i<ocCnt;j++,offset+=icCnt)
   for (j=1;j<icCnt;j++)
     Pen.Line3D(Canvas,Srf[offset+j],Srf[offset+j-1]);//,cSurface);
 } */
