#include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\mdi.h>
#include <string.h>
#include <Wfm3D.h>
#include <Draw3D.h>


// Menu bar constants
const int MenuId            =  100;  // Resource Id of the menubar
const int IconId            =  100;  // Resource Id of the program icon

const int DrawCuboidID      = 0x2000;
const int DrawPyramidID     = 0x2100;
const int DrawConeID        = 0x2200;
const int DrawCylinderID    = 0x2300;
const int DrawTorusID       = 0x2400;
const int DrawEllipsoidID   = 0x2500;
const int DrawPawnID        = 0x2600;
const int DrawVaseID        = 0x2700;

const int FileNewID         = 0x1000;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


class App3DWindow : public TMDIClient
 {
    public:
      TMDIChild  *Child;
      Draw3D     *Pen;
      XForm      XF;

    public:
      App3DWindow() : TMDIClient() { Attr.Style |= WS_TABSTOP; }

    protected:
      void SetupWindow();

      void MnuFileNew();
      void MnuDrawCuboid();
      void MnuDrawPyramid();
      void MnuDrawCone();
      void MnuDrawCylinder();
      void MnuDrawTorus();
      void MnuDrawEllipsoid();
      void MnuDrawPawn();
      void MnuDrawVase();

      //void EvTimer(UINT TimerId);
      void EvDestroy();

    DECLARE_RESPONSE_TABLE(App3DWindow);
};

DEFINE_RESPONSE_TABLE1(App3DWindow, TMDIClient)
  EV_COMMAND(FileNewID  ,MnuFileNew),

  EV_COMMAND(DrawCuboidID  ,MnuDrawCuboid),
  EV_COMMAND(DrawPyramidID ,MnuDrawPyramid),
  EV_COMMAND(DrawConeID    ,MnuDrawCone),
  EV_COMMAND(DrawCylinderID,MnuDrawCylinder),
  EV_COMMAND(DrawTorusID,MnuDrawTorus),
  EV_COMMAND(DrawEllipsoidID,MnuDrawEllipsoid),
  EV_COMMAND(DrawPawnID,MnuDrawPawn),
  EV_COMMAND(DrawVaseID,MnuDrawVase),

  //EV_WM_TIMER,
  EV_WM_DESTROY,
END_RESPONSE_TABLE;


//
// Setup the main demo window, and try to allocate its timer
//
void App3DWindow::SetupWindow()
 {
    TMDIClient::SetupWindow();
    Child = (TMDIChild*)NULL;
    Pen   = (Draw3D*)NULL;
 }

void App3DWindow::MnuFileNew()
 {
    //if (Child == (TMDIChild*)NULL)
    // {
       Pen   = new Draw3D;
       Child = new TMDIChild(*this, "Drawing window",Pen);
       Child->SetIcon(0, 0);
       Child->Create();
       Child->Show(SW_SHOWMAXIMIZED);
       Pen->Setup3D(csMapCavalier,45,Vector(0,0,0));
    // }
 }
void App3DWindow::MnuDrawCuboid()
 {
    Wfm3D   Cub3D;
    Vector  D;

    Cub3D.SetProperties(CuboidIn3D);
    Cub3D.WfmCreate(4,4);
    Cub3D.SetGroups(2,2);
    Cub3D.SetPrecision(20,20);
    Cub3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,0,1));
    Cub3D.ResetControls();

    D.Vectorise(200,200,200);
    D /= 2;
    Cub3D.RegularPoly(Z_Axis,0,0,0,D.z);
    Cub3D.RegularPoly(Z_Axis,1,D.x,D.y,D.z);
    Cub3D.RegularPoly(Z_Axis,2,D.x,D.y,-D.z);
    Cub3D.RegularPoly(Z_Axis,3,0,0,-D.z);
    Cub3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->SetCaption("Cuboid");
        Cub3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawPyramid()
 {
    Wfm3D   Pyr3D;
    Vector  D;

    Pyr3D.SetProperties(PyramidIn3D);
    Pyr3D.WfmCreate(3,4);
    Pyr3D.SetGroups(2,2);
    Pyr3D.SetPrecision(20,20);
    Pyr3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,1,0));
    Pyr3D.ResetControls();

    D.Vectorise(120,120,250);

    Pyr3D.RegularPoly(Z_Axis,0,  0,   0, D.z/2);
    Pyr3D.RegularPoly(Z_Axis,1,D.x, D.y,-D.z/2);
    Pyr3D.RegularPoly(Z_Axis,2,  0,   0,-D.z/2);
    Pyr3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->SetCaption("Pyramid");
        Pyr3D.Draw(*Pen);
     }

 }

void App3DWindow::MnuDrawCylinder()
 {
    int N = 8;
    Wfm3D   Cyl3D;
    Vector  D;

    Cyl3D.SetProperties(CylinderIn3D);
    Cyl3D.WfmCreate(4,8);
    Cyl3D.SetGroups(2,3);
    Cyl3D.SetPrecision(20,30);

    Cyl3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,1,0));
    Cyl3D.ResetControls();

    D.Vectorise(120,120,250);
    Cyl3D.Elliptical(Z_Axis,  0,1,  0,  0, D.z/2);
    Cyl3D.Elliptical(Z_Axis,  N,1,D.x,D.y, D.z/2);
    Cyl3D.Elliptical(Z_Axis,2*N,1,D.x,D.y,-D.z/2);
    Cyl3D.Elliptical(Z_Axis,3*N,1,  0,  0,-D.z/2);
    Cyl3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->SetCaption("Cylinder");
        Cyl3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawCone()
 {
    int N = 8;

    Wfm3D   Con3D;
    Vector  D;

    Con3D.SetProperties(ConeIn3D);
    Con3D.WfmCreate(3,8);
    Con3D.SetGroups(2,3);
    Con3D.SetPrecision(10,20);

    Con3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,1,0));
    Con3D.ResetControls();

    D.Vectorise(200,200,300);
    Con3D.Elliptical(Z_Axis,0  ,1,  0,  0, D.z/2);
    Con3D.Elliptical(Z_Axis,N  ,1,D.x,D.y,-D.z/2);
    Con3D.Elliptical(Z_Axis,2*N,1,  0,  0,-D.z/2);
    Con3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->Invalidate(FALSE);
        Child->SetCaption("Cone");
        Con3D.SetDisplayColours(csCyan,csMagenta,csRed);
        Con3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawTorus()
 {
    int i,j;
    int N = 8;
    int M = 8;

    Wfm3D   Tor3D;
    Vector  D;

    Tor3D.SetProperties(TorusIn3D);
    Tor3D.WfmCreate(8,8);
    Tor3D.SetGroups(3,3);
    Tor3D.SetPrecision(40,5);

    Tor3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,1,0));
    Tor3D.ResetControls();

    D.Vectorise(170,70,70);

    Tor3D.Elliptical(Y_Axis,0,1,D.y,0,D.z);
    Tor3D.Elliptical(Y_Axis,N,1,sqrt(2)*D.y,0,D.z);
    XF.Identity();
    XF.RotateAbout(Z_Axis,45);
    for (i=N;i<2*N;i++)
      Tor3D.S[i] *= XF;
    XF.Identity();
    XF.RotateAbout(Z_Axis,90);
    for (i=2;i<M;i++)
      for (j=0;j<N;j++)
        Tor3D.S[i*N+j] = Tor3D.S[(i-2)*N+j]*XF;
    XF.Identity();
    Tor3D.Elliptical(Z_Axis,0,N,D.x,D.x,0);
    Tor3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->Invalidate(FALSE);
        Child->SetCaption("Torus");
        Tor3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawEllipsoid()
 {
    float R;
    int   i,j;
    int   N = 8;

    Wfm3D   Ell3D;
    Vector  D;

    Ell3D.SetProperties(EllipsoidIn3D);
    Ell3D.WfmCreate(5,8);
    Ell3D.SetGroups(3,3);
    Ell3D.SetPrecision(20,20);

    Ell3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,1,0));
    Ell3D.ResetControls();

    D.Vectorise(200,200,200);
    R = (float)sqrt(D.x*D.x+D.y*D.y);
    Ell3D.Elliptical(Y_Axis,0  ,1,D.x,0,D.z);
    Ell3D.Elliptical(Y_Axis,N  ,1,R  ,0,D.z);
    Ell3D.Elliptical(Y_Axis,N+N,1,D.y,0,D.z);
    XF.Identity();
    XF.RotateAbout(Z_Axis,atan(D.y/D.x)*PiUnder180);

    for (i=N;i<N+N;i++)
      Ell3D.S[i] *= XF;
    XF.Identity();
    XF.RotateAbout(Z_Axis,90);
    for (i=N+N;i<3*N;i++)
      Ell3D.S[i] *= XF;
    XF.Identity();
    D.Vectorise(-1,1,1);
    XF.Scale3D(D);

    for (i=1;i<3;i++)
      for (j=0;j<N;j++)
        Ell3D.S[(i+2)*N+j] = Ell3D.S[(2-i)*N+j]*XF;
    XF.Identity();
    Ell3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Ell3D.SetDisplayColours(csYellow,csMagenta,csRed);
        Child->SetCaption("Ellipsoid");
        Ell3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawPawn()
 {
    int N = 8;
    Wfm3D   Pwn3D;
    Vector  D;

    Pwn3D.SetProperties(ChessPawnIn3D);
    Pwn3D.WfmCreate(13,8);
    Pwn3D.SetGroups(3,3);
    Pwn3D.SetPrecision(10,10);

    Pwn3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,0,1));
    Pwn3D.ResetControls();

    Pwn3D.Elliptical(Y_Axis,   0,1,  0,-200,  0);
    Pwn3D.Elliptical(Y_Axis,   N,1, 40,-200, 40);
    Pwn3D.Elliptical(Y_Axis, 2*N,1, 80,-200, 80);
    Pwn3D.Elliptical(Y_Axis, 3*N,1,100,-150,100);
    Pwn3D.Elliptical(Y_Axis, 4*N,1, 40, -70, 40);
    Pwn3D.Elliptical(Y_Axis, 5*N,1, 60, -60, 60);
    Pwn3D.Elliptical(Y_Axis, 6*N,1, 40, -50, 40);
    Pwn3D.Elliptical(Y_Axis, 7*N,1, 60,   0, 60);
    Pwn3D.Elliptical(Y_Axis, 8*N,1, 20,  80, 20);
    Pwn3D.Elliptical(Y_Axis, 9*N,1, 50,  90, 50);
    Pwn3D.Elliptical(Y_Axis,10*N,1, 20, 100, 20);
    Pwn3D.Elliptical(Y_Axis,11*N,1, 30, 130, 30);
    Pwn3D.Elliptical(Y_Axis,12*N,1,  0, 200, 0);
    Pwn3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->SetCaption("Chess Pawn");
        Pwn3D.SetDisplayColours(csGray,csMagenta,csRed);
        Pwn3D.Draw(*Pen);
     }
 }

void App3DWindow::MnuDrawVase()
 {
    int N = 8;

    Wfm3D   Vas3D;
    Vector  D;

    Vas3D.SetProperties(VaseIn3D);
    Vas3D.WfmCreate(11,8);
    Vas3D.SetGroups(2,3);
    Vas3D.SetPrecision(10,10);

    Vas3D.SetCentreAndNormal(Vector(0,0,0),Vector(0,0,1));
    Vas3D.ResetControls();

    Vas3D.Elliptical(Y_Axis,  0,1, 60,-150, 60);
    Vas3D.Elliptical(Y_Axis,  N,1, 50,-150, 50);
    Vas3D.Elliptical(Y_Axis,2*N,1, 30,-130, 30);
    Vas3D.Elliptical(Y_Axis,3*N,1,  0,-130,  0);
    Vas3D.Elliptical(Y_Axis,4*N,1, 30,-130, 30);
    Vas3D.Elliptical(Y_Axis,5*N,1, 30,-110, 30);
    Vas3D.Elliptical(Y_Axis,6*N,1,100, 130,100);
    Vas3D.Elliptical(Y_Axis,7*N,1, 80, 180, 80);
    Vas3D.Elliptical(Y_Axis,8*N,1, 20, 180, 20);
    Vas3D.Elliptical(Y_Axis,9*N,1, 20, 200, 20);
    Vas3D.Elliptical(Y_Axis,10*N,1, 40, 240, 40);
    Vas3D.ZAxisToNormal();

    if (Child != (TMDIChild*)NULL)
     {
        Child->Invalidate(TRUE);
        Child->SetCaption("Vase");
        Pen->SetBaseRGB(csMagenta);
        Vas3D.Draw(*Pen);
     }
 }

//
// Get client demo window from mdi child frame using typesafe downcasting
//
/*void ChildTimers(TWindow* p, void*)
 {
    TFrameWindow* frame = TYPESAFE_DOWNCAST(p, TFrameWindow);
    CHECK(frame);
    TBaseDemoWindow* demoWin = TYPESAFE_DOWNCAST(frame->GetClientWindow(), TBaseDemoWindow);
    CHECK(demoWin);
    demoWin->TimerTick();
 } */

//
// In response to WMTimer messages, each MDI child window's TimerTick
// Method is called.
//
/*void App3DWindow::EvTimer(UINT)
 {
    ForEach(ChildTimers, 0);
 } */


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>                                                                    <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>


void App3DWindow::EvDestroy()
 {
    KillTimer(0);
    TMDIClient::EvDestroy();
 }

//----------------------------------------------------------------------------

class App3DApp : public TApplication
 {
    public:
      App3DApp() : TApplication() {}
      void InitMainWindow();
 };

void App3DApp::InitMainWindow()
 {
    MainWindow = new TMDIFrame("3D Wireframe Objects", MenuId, *new App3DWindow);
    MainWindow->SetIcon(this, IconId);
 }

int OwlMain(int /*argc*/, char* /*argv*/ [])
 {
    return App3DApp().Run();
 }