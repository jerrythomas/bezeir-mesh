#ifndef  __DRAW3D_H
#define  __DRAW3D_H

#include <owl\owlpch.h>
#include <owl\mdichild.h>
#include <owl\dc.h>
#include <XForm3D.h>

#define csMapCavalier    0x01
#define csMapCabinet     0x02
#define csMapPerspective 0x03

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>  Class Name    : Draw3D                                            <<>>
// <<>>  Purpose       : Providing 3D drawing functionality                <<>>
// <<>>                                                                    <<>>
// <<>>  Derived from  : TWindow                                           <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Draw3D : public TWindow
 {
   protected:
     float     Theta;               //Angle used for projection
     byte      WhichView3D;         //Type of projection
     Vector    Eye3D;               //Position of Eye for perspective projection

     Vector    Max3D,               //Value for maximum intensity
               Min3D,               //Value for Minimum intensity
               Cur3D;               //Current cursor position in 3D

     byte      Red,Grn,Blu;         //RGB factors for display.

     XForm     Map3D;               //3D Mapping transformation matrix

   public :

     Draw3D();
     ~Draw3D();

     void   SetBaseRGB(byte RGBTriplet);
     void   SetLimitsFor3D(float x, float y, float z);
     void   Setup3D(byte MapingType,float Angle,Vector Eye);

     byte   ShadeOf(TColor Col);
     byte   Shade3D(Vector V);
     TColor Color3D(Vector V);

     void   Plot3D(TDC& Canvas,Vector V);
     void   MoveTo3D(TDC& Canvas,Vector V);
     void   LineTo3D(TDC& Canvas,Vector V);
     void   Line3D(TDC& Canvas,Vector Src, Vector Dst);
     void   LineRel3D(TDC& Canvas,Vector Dv);

   protected :

     void EvSize(UINT sizeType, TSize& size);

   DECLARE_CASTABLE;
   DECLARE_RESPONSE_TABLE(Draw3D);
 };


#endif

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                          Typesafe Downcasting                      <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

DEFINE_RESPONSE_TABLE1(Draw3D, TWindow)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

IMPLEMENT_CASTABLE1(Draw3D, TWindow);


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                          constructor                               <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

Draw3D::Draw3D():TWindow(0,0,0)
 {
   SetBkgndColor(RGB(0,0,0));
   SetBaseRGB(csGreen);
   SetLimitsFor3D(200,200,400);
   Map3D.Cavalier(200,200,45);
 }

Draw3D::~Draw3D()
 {

 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                          Basic controlerrs                         <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void Draw3D::SetBaseRGB(byte RGBTriplet)
 {
   Red = (byte)(RGBTriplet&0x04) >> 2;
   Grn = (byte)(RGBTriplet&0x02) >> 1;
   Blu = (byte)(RGBTriplet&0x01);
 }

void Draw3D::SetLimitsFor3D(float x,float y,float z)
 {
   x = fabs(x);
   y = fabs(y);
   z = fabs(z);
   Max3D.Vectorise(x,y,z);
   Min3D.Vectorise(-x,-y,-z);
 }

void Draw3D::Setup3D(byte MappingType,float Angle,Vector Eye)
 {
   TRect MyDrawArea;
   GetClientRect(MyDrawArea);
   if (MappingType == csMapCavalier)
      Map3D.Cavalier(MyDrawArea.right/2,MyDrawArea.bottom/2,Angle);
   else if (MappingType == csMapCabinet)
      Map3D.Cabinet(MyDrawArea.right/2,MyDrawArea.bottom/2,Angle);
   else if (MappingType == csMapPerspective)
      Map3D.Perspective(MyDrawArea.right/2,MyDrawArea.bottom/2,Eye);

   Theta = Angle;
   Eye3D = Eye;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>   Zbuffering Colour control routines                               <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

byte Draw3D::ShadeOf(TColor Col)
 {
    return (BYTE)(Col.Green()) ;//Col.Red()*3.2 + Col.Green()*4.36 + Col.Blue()*1.76);
 }
byte Draw3D::Shade3D(Vector V)
 {
   byte   inten=(byte)min(255,max(0,Round((256.0*(V.z+Max3D.z)/(Max3D.z-Min3D.z)))));
   return inten;
 }

TColor Draw3D::Color3D(Vector V)
 {
   int inten3D;

   inten3D = Shade3D(V);
   return RGB(Red*inten3D,Grn*inten3D,Blu*inten3D);
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>   3D Drawing routines                                              <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void Draw3D::Plot3D(TDC& Canvas,Vector V)
 {
   byte   Shade = Shade3D(V);
   TColor Color = Color3D(V);

   V *= Map3D;

   if (ShadeOf(Canvas.GetPixel(V.x,V.y)) <= Shade)
      Canvas.SetPixel(V.x,V.y,Color);
   Canvas.MoveTo(V.x,V.y);
 }

void Draw3D::Line3D(TDC& Canvas,Vector A,Vector B)
 {
   Vector Dv  = (A > B) ? A-B:B-A;
   float  Max = Dv.Len();
   float  i;

   A = (A > B) ? B:A;
   Dv.UnitVector();

   for (i=0;i<=Max;i++,A += Dv)
     //Plot3D(Canvas,A);
     Plot3D(TClientDC(*this),A);
 }

void Draw3D::MoveTo3D(TDC& Canvas,Vector V)
 {
   Cur3D = V;
   V *= Map3D;
   Canvas.MoveTo(V.x,V.y);
 }

void Draw3D::LineTo3D(TDC& Canvas,Vector V)
 {
   Line3D(Canvas,Cur3D,V);
   MoveTo3D(Canvas,V);
 }

void Draw3D::LineRel3D(TDC& Canvas,Vector Dv)
 {
   Line3D(Canvas,Cur3D,Cur3D+Dv);
   MoveTo3D(Canvas,Cur3D+Dv);
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>               Basic Window events                                  <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void Draw3D::EvSize(UINT sizeType, TSize& size)
 {
   TRect WrkSpace;
   GetClientRect(WrkSpace);
   Map3D.Cavalier(WrkSpace.right/2,WrkSpace.bottom/2,45);
 }
