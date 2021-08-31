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
