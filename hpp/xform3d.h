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
// <<>>                                                                    <<>>
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
// <<>>  Purpose       : Providing 3D drawing functionality                <<>>
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
