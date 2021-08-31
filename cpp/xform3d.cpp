#ifndef __XFORM_H
#define __XFORM_H

#include <AdvMath.h>
#include <stdio.h>
#include <string.h>

#define X_Axis     0x00
#define Y_Axis     0x01
#define Z_Axis     0x02

#define yz_Plane   0x00
#define zx_Plane   0x01
#define xy_Plane   0x02

typedef unsigned char byte;
typedef unsigned int  word;

class XForm;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>  Class Name    : XForm                                             <<>>
// <<>>  Purpose       : 3D Transformation & control                       <<>>

// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


// <<>>   <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>          Vector Class Declaration          <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Vector
 {
   public :
     float x,y,z;

   public :
     Vector();
     Vector(float X,float Y,float Z);
     void  Vectorise(float X,float Y,float Z);

     float  Len();
     void   UnitVector();
     Vector cross(Vector V);
     float  dot(Vector V);
     int    IsZeroVector();
     void   Abs();
     Vector ProjectionOn(byte Plane);
     byte   ClosestProjectionPlane(Vector A,Vector B);
     float  Angle(Vector V);

     // Operators
     int    operator >(Vector V);
     Vector operator *(float i);
     Vector operator /(float i);

     Vector operator +(Vector V);
     Vector operator -(Vector V);

     Vector operator *=(float i);
     Vector operator /=(float i);

     Vector operator +=(Vector V);
     Vector operator -=(Vector V);

     Vector operator *(XForm M);
     Vector operator *=(XForm M);

     //void   OutVector();
     friend class XForm;
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>  Class Name    : XForm                                             <<>>
// <<>>  Purpose       : 3D Transformation & control                       <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class XForm
 {
   protected :

     float Mat[4][4];

   private :

     void Assign(float f);

   public :

     XForm();
     XForm(float f);

     float Matrix(byte R, byte C);
     XForm Zero();
     XForm Identity();
     XForm Scale3D(Vector Scale);
     XForm Translate3D(Vector Tran);
     XForm RotateAbout(byte About, float Theta);
     XForm ShearAbout(byte About,float Shear);
     XForm Rotate3D(Vector SolidAngle);
     XForm Shear3D(Vector Shear);
     XForm NormalToAxisZ(Vector Normal);
     XForm zAxisToNormal(Vector Normal);
     XForm Perspective(int Cx,int Cy,Vector Eye);
     XForm Parallel(int Cx,int Cy,double Alpha,double Phi,byte Deg);
     XForm Cavalier(int Cx,int Cy,float Phi);
     XForm Cabinet(int Cx,int Cy,float Phi);

     char* ToString(char *Dst);
     XForm operator *(float f);
     XForm operator /(float f);

     XForm operator *(XForm M);

     XForm operator *=(float f);
     XForm operator /=(float f);

     XForm operator *=(XForm M);

     friend class Vector;
 };

extern XForm Map3D;
#endif

XForm Map3D(1);

Vector xAxis(1,0,0),
       yAxis(0,1,0),
       zAxis(0,0,1);

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>   Operators of class Vector                                        <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

int Vector::operator >(Vector V)
 {
   return z > V.z;
 }

Vector Vector::operator *(float f)
 {
   Vector rvVec;
   rvVec.x = x*f;
   rvVec.y = y*f;
   rvVec.z = z*f;
   return rvVec;
 }

Vector Vector::operator /(float f)
 {
  Vector rvVec(MAXFLOAT,MAXFLOAT,MAXFLOAT);
  if (f)
   {
    rvVec.x = x/f;
    rvVec.y = y/f;
    rvVec.z = z/f;
   }
  return rvVec;
 }

Vector Vector::operator +(Vector V)
 {
  Vector rvVec;
  rvVec.x = x + V.x;
  rvVec.y = y + V.y;
  rvVec.z = z + V.z;
  return(rvVec);
 }

Vector Vector::operator -(Vector V)
 {
  Vector rvVec;
  rvVec.x = x - V.x;
  rvVec.y = y - V.y;
  rvVec.z = z - V.z;
  return(rvVec);
 }

Vector Vector::operator *=(float f)
 {
  x *= f;
  y *= f;
  z *= f;
  return *this;
 }

Vector Vector::operator /=(float f)
 {
  if (f)
   {
    x /= f;
    y /= f;
    z /= f;
   }
  else
    x = y = z = MAXFLOAT;
  return *this;
 }
Vector Vector::operator +=(Vector V)
 {
  x += V.x;
  y += V.y;
  z += V.z;
  return *this;
 }
Vector Vector::operator -=(Vector V)
 {
  x -= V.x;
  y -= V.y;
  z -= V.z;
  return *this;
 }

Vector Vector::operator *(XForm M)
 {
  Vector rvVec;
  float H = x*M.Mat[0][3] + y*M.Mat[1][3] + z*M.Mat[2][3] + M.Mat[3][3];
  rvVec.x = x*M.Mat[0][0] + y*M.Mat[1][0] + z*M.Mat[2][0] + M.Mat[3][0];
  rvVec.y = x*M.Mat[0][1] + y*M.Mat[1][1] + z*M.Mat[2][1] + M.Mat[3][1];
  rvVec.z = x*M.Mat[0][2] + y*M.Mat[1][2] + z*M.Mat[2][2] + M.Mat[3][2];

  rvVec /= H;
  return rvVec;
 }

Vector Vector::operator *=(XForm M)
 {
  Vector rvVec(x,y,z);
  *this = rvVec * M;
  return *this;
 }
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>      Member functions of Class Vector      <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

Vector::Vector()
 {
   x = y = z = 0.0;
 }

Vector::Vector(float X,float Y,float Z)
 {
  x = X;
  y = Y;
  z = Z;
 }

void Vector::Vectorise(float X,float Y,float Z)
 {
   x = X;
   y = Y;
   z = Z;
 }

float Vector::Len()
 {
   return (float)sqrt(x*x + y*y + z*z);
 }

void Vector::UnitVector()
 {
   float Magnitude = (float)sqrt(x*x + y*y + z*z);
   if (Magnitude > 0)
    {
      x /= Magnitude;
      y /= Magnitude;
      z /= Magnitude;
    }
 }

Vector Vector::cross(Vector V)
 {
   Vector rvVec;
   rvVec.x = y*V.z - z*V.y;
   rvVec.y = z*V.x - x*V.z;
   rvVec.z = x*V.y - y*V.x;
   return rvVec;
 }

float Vector::dot(Vector V)
 {
   return (x*V.x + y*V.y + z*V.z);
 }

Vector Vector::ProjectionOn(byte Plane)
 {
   Vector rvVec(x,y,z);
   if (Plane==yz_Plane)
      rvVec.x = 0;
   else if (Plane == zx_Plane)
      rvVec.y = 0;
   else
      rvVec.z = 0;
   return rvVec;
 }

int Vector::IsZeroVector()
 {
   return (x==0 && y==0 && z==0);
 }

void Vector::Abs()
 {
   x = fabs(x);
   y = fabs(y);
   z = fabs(z);
 }

byte Vector::ClosestProjectionPlane(Vector A,Vector B)
 {
   byte Plane;
   Plane = (byte)(A.x == 0.0 && B.x == 0.0) ? yz_Plane :
                 (A.y == 0.0 && B.y == 0.0) ? zx_Plane :
                 (A.z == 0.0 && B.z == 0.0) ? xy_Plane : 3;

   if (Plane == 3)
    {
      A.Abs();
      B.Abs();
      Plane = ((A.y>=A.x && B.y>=B.x) ||(A.z>=A.x && B.z>=B.x)) ? yz_Plane:3;
    }
   if (Plane == 3)
      Plane = ((A.z>=A.y && B.z>=B.y) ||(A.x>=A.y && B.x>=B.y)) ? zx_Plane:3;
   return (Plane == 3) ? xy_Plane : Plane;
 }

float Vector::Angle(Vector V)
 {
   byte   Plane;
   Vector A(x,y,z),
          B(V.x,V.y,V.z),
          C;
   float  Theta;

   if (A.IsZeroVector() || B.IsZeroVector())
      return 0;

   A.UnitVector();
   B.UnitVector();
   Theta = acos(A.dot(B))*PiUnder180;

   C = A.cross(B);
   if (!C.IsZeroVector())
    {
      Plane = ClosestProjectionPlane(*this,V);
      A = ProjectionOn(Plane);
      B = V.ProjectionOn(Plane);
      C = A.cross(B);
      if (Plane == yz_Plane)
        return (C.x >= 0.0) ? Theta:360.0-Theta;
      else if (Plane == zx_Plane)
        return (C.y >= 0.0) ? Theta:360.0-Theta;
      else
        return (C.z >= 0.0) ? Theta:360.0-Theta;
    }
   return Theta;
 }
/*
void Vector::VecStatus()
 {
  ViewPortType V;
  GetViewPort(V);
  ViewPort(0,0,xMax(),yMax());

  SetColor(Red+7);
  int W = Width("W");

  ViewPort(xMax()-20*W-6,yMax()-30,xMax(),yMax());
  Box(xMax()-20*W-9,yMax()-27,xMax()-3-2*W,yMax()-3,Cyan+12);
  Justify(CenterText,CenterText);
  gPrintf(xMax()-11*W-3,yMax()-15,"%4.0f,%4.0f,%4.0f",x,y,z);
  Justify(LeftText,TopText);

  ViewPort(V);
 }

void Vector::Get(char **S,Vector vMin,Vector vMax)
 {
  int H  = 30;
  int W  = Width("W");
  int Wd = yMax()-66;
  int L = Wd+2;
  int T = H+2;
  int R = xMax();
  int B = T+10*Height();

  ViewPortType V;
  GetViewPort(V);
  ViewPort(0,0,xMax(),yMax());

  SetColor(0);
  Box(L,T,R,B,0);
 // Box(L+=3,T+=3,R-=3,B-=(H+3),0);
  Panel(L,T,R,B-H,Gray+22,Gray+17);
  Label(L,B-H+2,R,B,S[0],Gray+17,Green+7);


  W = max(Width(S[1]),Width(S[2]));
  W = max(W,Width(S[3]));
  H = Height();
  L = L + (R-L-W-10*Width("W"))/2;
  T = T + (B-T-5*H-30)/2;

  SetColor(Green+7);
  Justify(LeftText,TopText);
  gPrintf(L,T    ,S[1]);
  gPrintf(L,T+2*H,S[2]);
  gPrintf(L,T+4*H,S[3]);
  gScanf(L+W,T    ,"%7.3f",&x,vMin.x,vMax.x,Gray+17);
  gScanf(L+W,T+2*H,"%7.3f",&y,vMin.y,vMax.y,Gray+17);
  gScanf(L+W,T+4*H,"%7.3f",&z,vMin.z,vMax.z,Gray+17);

  ViewPort(V);
 }
  */
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>          Operators of class XForm          <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


XForm XForm::operator *(float f)
 {
   XForm rvMat;
   byte i,j;
   for (i=0;i<4;i++)
     for (j=0;j<4;j++)
       rvMat.Mat[i][j] = Mat[i][j]*f;
   return rvMat;
 }

XForm XForm::operator /(float f)
 {
   XForm rvMat;
   byte i,j;
   if (f)
   for (i=0;i<4;i++)
     for (j=0;j<4;j++)
       rvMat.Mat[i][j] = Mat[i][j]/f;
   else
    rvMat = MAXFLOAT;
   return rvMat;
 }

XForm XForm::operator *(XForm M)
 {
   XForm Result(0);
   byte i,j,k;
   for (i=0;i<4;i++)
    for (j=0;j<4;j++)
     for (k=0;k<4;k++)
      Result.Mat[i][k] += Mat[i][j]*M.Mat[j][k];
   return Result;
 }

XForm XForm::operator *=(float f)
 {
   byte i,j;
   for (i=0;i<4;i++)
     for (j=0;j<4;j++)
       Mat[i][j] *= f;
   return *this;
 }

XForm XForm::operator /=(float f)
 {
   byte i,j;
   if (f)
   for (i=0;i<4;i++)
     for (j=0;j<4;j++)
       Mat[i][j] /= f;
   else
    *this = MAXFLOAT;
   return *this;
 }

XForm XForm::operator *=(XForm M)
 {
   XForm Result=*this;
   *this = Result * M;
   return *this;
 }
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>      Member functions of Class XForm       <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void XForm::Assign(float f)
 {
  if (f==1)
   {
     Mat[0][1] = Mat[0][2] = Mat[0][3] = 0.0;
     Mat[1][0] = Mat[1][2] = Mat[1][3] = 0.0;
     Mat[2][0] = Mat[2][1] = Mat[2][3] = 0.0;
     Mat[3][0] = Mat[3][1] = Mat[3][2] = 0.0;
     Mat[0][0] = Mat[1][1] = Mat[2][2] = Mat[3][3] = 1.0;
   }
  else
   {
     Mat[0][0] = Mat[0][1] = Mat[0][2] = Mat[0][3] = f;
     Mat[1][0] = Mat[1][1] = Mat[1][2] = Mat[1][3] = f;
     Mat[2][0] = Mat[2][1] = Mat[2][2] = Mat[2][3] = f;
     Mat[3][0] = Mat[3][1] = Mat[3][2] = Mat[3][3] = f;
   }
 }

XForm::XForm()
 {
   Identity();
 }

XForm::XForm(float f)
 {
   Assign(f);
 }

float XForm::Matrix(byte R, byte C)
 {
   return  (R < 4 && C < 4)? Mat[R][C]:0;
 }
XForm XForm::Zero()
 {
   Mat[0][0] = Mat[0][1] = Mat[0][2] = Mat[0][3] = 0.0;
   Mat[1][0] = Mat[1][1] = Mat[1][2] = Mat[1][3] = 0.0;
   Mat[2][0] = Mat[2][1] = Mat[2][2] = Mat[2][3] = 0.0;
   Mat[3][0] = Mat[3][1] = Mat[3][2] = Mat[3][3] = 0.0;

   return *this;
 }

XForm XForm::Identity()
 {
   Mat[0][1] = Mat[0][2] = Mat[0][3] = 0.0;
   Mat[1][0] = Mat[1][2] = Mat[1][3] = 0.0;
   Mat[2][0] = Mat[2][1] = Mat[2][3] = 0.0;
   Mat[3][0] = Mat[3][1] = Mat[3][2] = 0.0;
   Mat[0][0] = Mat[1][1] = Mat[2][2] = Mat[3][3] = 1.0;

   return *this;
 }

XForm XForm::Scale3D(Vector Scale)
 {
   XForm Tx(1);
   Tx.Mat[0][0] = Scale.x;
   Tx.Mat[1][1] = Scale.y;
   Tx.Mat[2][2] = Scale.z;
   *this *= Tx;
   return *this;
 }

XForm XForm::Translate3D(Vector Tran)
 {
   XForm Tx(1);              // Identity Matrix
   Tx.Mat[3][0] = Tran.x;
   Tx.Mat[3][1] = Tran.y;
   Tx.Mat[3][2] = Tran.z;
   *this *= Tx;
   return *this;
 }

XForm XForm::RotateAbout(byte About, float Theta)
 {
   float ThetaInRadians = Radians(Theta);
   int   i,j;
   XForm Tx(1);

   i       = (About+1)%3;
   j       = (About+2)%3;
   Tx.Mat[i][i] =  cos(ThetaInRadians);
   Tx.Mat[i][j] =  sin(ThetaInRadians);
   Tx.Mat[j][i] = -sin(ThetaInRadians);
   Tx.Mat[j][j] =  cos(ThetaInRadians);

   *this *= Tx;
   return *this;
 }

XForm XForm::ShearAbout(byte About,float Shear)
 {
   int i,j;
   XForm Tx(1);
   i = (About+1)%3;
   j = (About+2)%3;
   Tx.Mat[i][(i+1)%3] = Tx.Mat[i][(i+2)%3] = Shear;
   Tx.Mat[j][(j+1)%3] = Tx.Mat[j][(j+2)%3] = Shear;
   *this *= Tx;
   return *this;
 }

XForm XForm::Rotate3D(Vector SolidAngle)
 {
   RotateAbout(X_Axis,SolidAngle.x);
   RotateAbout(Y_Axis,SolidAngle.y);
   RotateAbout(Z_Axis,SolidAngle.z);

  return *this;
 }

XForm XForm::Shear3D(Vector Shear)
 {
   ShearAbout(X_Axis,Shear.x);
   ShearAbout(Y_Axis,Shear.x);
   ShearAbout(Z_Axis,Shear.x);

  return *this;
 }

XForm XForm::NormalToAxisZ(Vector Normal)
 {
  Vector Proj;

  Normal.UnitVector();
  Proj   = Normal.ProjectionOn(yz_Plane);
  RotateAbout(X_Axis,Proj.Angle(zAxis));

  Proj   = Normal.ProjectionOn(zx_Plane);
  RotateAbout(Y_Axis,Proj.Angle(zAxis));
  return *this;
 }

XForm XForm::zAxisToNormal(Vector Normal)
 {
  Vector Proj;

  Normal.UnitVector();
  Proj   = Normal.ProjectionOn(zx_Plane);
  RotateAbout(Y_Axis,zAxis.Angle(Proj));

  Proj   = Normal.ProjectionOn(yz_Plane);
  RotateAbout(X_Axis,zAxis.Angle(Proj));

  return *this;
 }

XForm XForm::Perspective(int Cx,int Cy,Vector Eye)
 {
  Vector S(1,-1,1),
         T(Cx,Cy,0);
  Zero();
  Mat[0][0] = Mat[1][1] = Mat[3][3] = - Eye.z;
  Mat[2][3] = 1;
  Mat[3][0] = Eye.x*(1+Eye.z);
  Mat[3][1] = Eye.y*(1+Eye.z);
  Scale3D(S);
  Translate3D(T);
  return *this;
 }

XForm XForm::Parallel(int Cx,int Cy,double Alpha,double Phi,byte Deg)
 {
  Vector S(1,-1,1),
         T(Cx,Cy,0);

  Identity();
  if (Deg)
   {
     Alpha = Radians(Alpha);
     Phi   = Radians(Phi);
   }
  Mat[2][0] = -tan(Alpha)*cos(Phi);
  Mat[2][1] = -tan(Alpha)*sin(Phi);
  Scale3D(S);
  Translate3D(T);
  return *this;
 }

XForm XForm::Cavalier(int Cx,int Cy,float Phi)
 {
  Parallel(Cx,Cy,Cavalier_Alpha,Radians(Phi),0);
  return(*this);
 }

XForm XForm::Cabinet(int Cx,int Cy,float Phi)
 {
  Parallel(Cx,Cy,Cabinet_Alpha,Radians(Phi),0);
  return(*this);
 }

char* XForm::ToString(char *Dst)
 {
   int  i,j;
   char n[50];
   Dst[0] = '\0';
   for (i=0;i<4;i++)
    {
     for (j=0;j<4;j++)
      {
        sprintf(n,"%8.3f ",Mat[i][j]);
        strcat(Dst,n);
      }
     strcat(Dst,"\n");
    }
   return Dst;
 }
