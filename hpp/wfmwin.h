#ifndef __WFMWIN__H
#define __WFMWIN__H

#include <Draw3D.h>
#include <Wfm3D.h>


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
// <<>>               Declaration of Class Wfm3D                           <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class WfmWin : public Draw3D
 {

   private:
     BOOL        Iconized;

   public :

     WfmWin();
     ~WfmWin();

   protected:
     void EvSize(UINT, TSize& Size);

   DECLARE_CASTABLE;
   DECLARE_RESPONSE_TABLE(WfmWin);
 };

#endif