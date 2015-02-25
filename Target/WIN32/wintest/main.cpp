/* main.cpp */ 

#include <CCore/inc/video/Desktop.h>
#include <CCore/inc/video/FrameBuf.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/CharProp.h>

#include "main.rh"

namespace App {

/* using */ 

using namespace CCore;
using namespace CCore::Video;

/* Log */

PrintFile Log("log.txt");

void ELog()
 {
  Printf(Log,"\n\n#;\n\n",TextDivider());
 }

/* classes */

class FileReport;

class MainWindow;

/* class FileReport */

class FileReport : public ReportException
 {
  private: 
 
   virtual void print(StrLen str)
    {
     Putobj(Log,str);
    }
   
   virtual void end()
    {
     ELog();
    }
   
  public:
  
   FileReport() {}
   
   ~FileReport() {}
 };

/* class MainWindow */

class MainWindow : public FrameWindow
 {
  private:

   const int DragWidth = 20 ;
   const int BtnWidth  = 16 ;
  
   Pane dragUL;
   Pane dragL;
   Pane dragDL;
   Pane dragD;
   Pane dragDR;
   Pane dragR;
   Pane dragUR;
   Pane dragBar;
   
   Pane btnMin;
   Pane btnMax;
   Pane btnClose;
   
   Pane client;
   
   bool has_focus = false ;
   bool max_button = true ;
   
   enum DragType
    {
     Drag_None,
     
     Drag_UL,
     Drag_L,
     Drag_DL,
     Drag_D,
     Drag_DR,
     Drag_R,
     Drag_UR,
     Drag_Bar
    };
   
   DragType drag_type = Drag_None ;
   Point drag_from;

  private: 
   
   void layout(Point size)
    {
     if( size>Point(2*DragWidth,2*DragWidth) )
       {
        int x1=DragWidth;
        int x2=size.x-DragWidth;
        int x3=size.x;
        
        int y1=DragWidth;
        int y2=size.y-DragWidth;
        int y3=size.y;
       
        dragUL=Pane(Null,Point(x1,y1));
        dragL =Pane(Point(0,y1),Point(x1,y2));
        dragDL=Pane(Point(0,y2),Point(x1,y3));
        
        dragD =Pane(Point(x1,y2),Point(x2,y3));
        
        dragDR=Pane(Point(x2,y2),Point(x3,y3));
        dragR =Pane(Point(x2,y1),Point(x3,y2));
        dragUR=Pane(Point(x2,0),Point(x3,y1));
        
        dragBar=Pane(Point(x1,0),Point(x2,y1));
        
        client=Pane(Point(x1,y1),Point(x2,y2));
        
        int yb=(DragWidth-BtnWidth)/2;
        
        if( size.x>=(3*BtnWidth+2*yb)+4*DragWidth )
          {
           int xb=(size.x-(3*BtnWidth+2*yb))/2; // >= 2*DragWidth 
           
           btnMin=Pane(xb,yb,BtnWidth,BtnWidth);
           btnMax=Pane(xb+BtnWidth+yb,yb,BtnWidth,BtnWidth);
           btnClose=Pane(xb+2*BtnWidth+2*yb,yb,BtnWidth,BtnWidth);
          }
        else
          {
           btnMin=Null;
           btnMax=Null;
           btnClose=Null;
          }
       }
     else
       {
        dragUL=Null;
        dragL =Null;
        dragDL=Null;
        
        dragD =Null;
        
        dragDR=Pane(Null,size);
        dragR =Null;
        dragUR=Null;
        
        dragBar=Null;
        
        client=Null;
        
        btnMin=Null;
        btnMax=Null;
        btnClose=Null;
       }
    }
  
   void draw(FrameBuf<DesktopColor> buf)
    {
     Printf(Log,"draw(...)"); ELog();
     
     if( drag_type )
       {
        buf.block(dragUL,Olive);
        buf.block(dragL,Olive);
        buf.block(dragDL,Olive);
        buf.block(dragD,Olive);
        buf.block(dragDR,Olive);
        buf.block(dragR,Olive);
        buf.block(dragUR,Olive);
        buf.block(dragBar,Olive);
       }
     else
       {
        buf.block(dragUL,Silver);
        buf.block(dragL,Gray);
        buf.block(dragDL,Silver);
        buf.block(dragD,Gray);
        buf.block(dragDR,Silver);
        buf.block(dragR,Gray);
        buf.block(dragUR,Silver);
        buf.block(dragBar,has_focus?Blue:Gray);
       }
     
     buf.block(btnMin,Green);
     buf.block(btnMax,max_button?Red:Yellow);
     buf.block(btnClose,Black);
     
     buf.cut(client).test();
    }
   
   void redraw()
    {
     draw(win->getDrawPlane());
     
     win->invalidate(1);
    }

   void startDrag(Point point,DragType drag_type_)
    {
     win->captureMouse();
    
     Pane place=win->getPlacement();
     
     drag_type=drag_type_;
     drag_from=point+place.getBase();
     
     redraw();
    }
   
   void dragTo_(Point point)
    {
     Pane place=win->getPlacement();
     Point delta=Diff(drag_from,point+place.getBase());
     
     switch( drag_type )
       {
        case Drag_UL :
         {
          place.x+=delta.x;
          place.dx-=delta.x;
          
          place.y+=delta.y;
          place.dy-=delta.y;
         }
        break;
        
        case Drag_L :
         {
          place.x+=delta.x;
          place.dx-=delta.x;
         }
        break;
        
        case Drag_DL :
         {
          place.x+=delta.x;
          place.dx-=delta.x;
          
          place.dy+=delta.y;
         }
        break;
        
        case Drag_D :
         {
          place.dy+=delta.y;
         }
        break;
        
        case Drag_DR :
         {
          place.dx+=delta.x;
          
          place.dy+=delta.y;
         }
        break;
        
        case Drag_R :
         {
          place.dx+=delta.x;
         }
        break;
        
        case Drag_UR :
         {
          place.dx+=delta.x;
          
          place.y+=delta.y;
          place.dy-=delta.y;
         }
        break;
        
        case Drag_Bar :
         {
          place.x+=delta.x;
          
          place.y+=delta.y;
         }
        break;
       }
     
     Point new_size(place.dx,place.dy);
     
     if( new_size>Null && new_size<=win->getMaxSize() )
       {
        win->move(place);
       }
    }
   
   void dragTo(Point point)
    {
     if( win->getToken() ) return;
     
     dragTo_(point);
    }
   
   void endDrag(Point point)
    {
     dragTo_(point);
     
     win->releaseMouse();
     
     drag_type=Drag_None;
     
     redraw();
    }
   
  public:
  
   MainWindow() : FrameWindow(DefaultDesktop) {}
   
   virtual ~MainWindow() {}
   
   void create(CmdDisplay cmd_display)
    {
     Printf(Log,"create(#;)",cmd_display); ELog();
     
     max_button=( cmd_display!=CmdDisplay_Maximized );
     
     win->createMain(DefaultDesktop->getScreenSize());
     
     win->display(cmd_display);
     win->update();
     
     Printf(Log,"create(...) finished"); ELog();
    }
   
   virtual void gainFocus()
    {
     Printf(Log,"gainFocus()"); ELog();
     
     has_focus=true;
     
     redraw();
     
     Printf(Log,"gainFocus() finished"); ELog();
    }
   
   virtual void looseFocus()
    {
     Printf(Log,"looseFocus()"); ELog();
     
     has_focus=false;
     
     redraw();
     
     Printf(Log,"looseFocus() finished"); ELog();
    }
   
   virtual void setSize(Point size,bool buf_dirty)
    {
     Printf(Log,"setSize(#;,#;)",size,buf_dirty); ELog();
     
     layout(size);
     
     redraw();
     
     Printf(Log,"setSize() finished"); ELog();
    }
   
   virtual void clickLeft(Point point,MouseKey mkey)
    {
     Printf(Log,"clickLeft(#;,#;)",point,mkey); ELog();
     
     if( dragUL.contains(point) )
       {
        startDrag(point,Drag_UL);
       }
     else if( dragL.contains(point) )
       {
        startDrag(point,Drag_L);
       }
     else if( dragDL.contains(point) )
       {
        startDrag(point,Drag_DL);
       }
     else if( dragD.contains(point) )
       {
        startDrag(point,Drag_D);
       }
     else if( dragDR.contains(point) )
       {
        startDrag(point,Drag_DR);
       }
     else if( dragR.contains(point) )
       {
        startDrag(point,Drag_R);
       }
     else if( dragUR.contains(point) )
       {
        startDrag(point,Drag_UR);
       }
     else if( dragBar.contains(point) )
       {
        if( btnMin.contains(point) )
          {
           win->display(CmdDisplay_Minimized);
          }
        else if( btnMax.contains(point) )
          {
           if( max_button )
             {
              max_button=false;
              
              win->display(CmdDisplay_Maximized);
             } 
           else
             {
              max_button=true;
              
              win->display(CmdDisplay_Restore);
             } 
           
           redraw();
          }
        else if( btnClose.contains(point) )
          {
           win->destroy();
          }
        else
          {
           startDrag(point,Drag_Bar);
          }
       }
     else
       {
        // do nothing
       }
     
     Printf(Log,"clickLeft(...) finished"); ELog();
    }
   
   virtual void upLeft(Point point,MouseKey mkey)
    {
     Printf(Log,"upLeft(#;,#;)",point,mkey); ELog();
     
     if( drag_type )
       {
        endDrag(point);
       }
     
     Printf(Log,"upLeft(...) finished"); ELog();
    }
 
   virtual void move(Point point,MouseKey mkey)
    {
     Printf(Log,"move(#;,#;)",point,mkey); ELog();
     
     if( drag_type )
       {
        if( mkey&MouseKey_Left )
          dragTo(point);
        else
          endDrag(point);
       }
     
     Printf(Log,"move(...) finished"); ELog();
    }
   
   virtual void setMouseShape(Point point)
    {
     if( dragUL.contains(point) )
       {
        win->setMouseShape(Mouse_SizeUpLeft);
       }
     else if( dragL.contains(point) )
       {
        win->setMouseShape(Mouse_SizeLeftRight);
       }
     else if( dragDL.contains(point) )
       {
        win->setMouseShape(Mouse_SizeUpRight);
       }
     else if( dragD.contains(point) )
       {
        win->setMouseShape(Mouse_SizeUpDown);
       }
     else if( dragDR.contains(point) )
       {
        win->setMouseShape(Mouse_SizeUpLeft);
       }
     else if( dragR.contains(point) )
       {
        win->setMouseShape(Mouse_SizeLeftRight);
       }
     else if( dragUR.contains(point) )
       {
        win->setMouseShape(Mouse_SizeUpRight);
       }
     else if( dragBar.contains(point) )
       {
        if( btnMin.contains(point) )
          {
           win->setMouseShape(Mouse_Arrow);
          }
        else if( btnMax.contains(point) )
          {
           win->setMouseShape(Mouse_Arrow);
          }
        else if( btnClose.contains(point) )
          {
           win->setMouseShape(Mouse_Arrow);
          }
        else
          {
           win->setMouseShape(Mouse_SizeAll);
          }
       }
     else
       {
        win->setMouseShape(Mouse_Arrow);
       }
    }
   
   virtual void key(VKey vkey,KeyMod kmod)
    {
     Printf(Log,"key(#;,#;)",vkey,kmod); ELog();
    }
   
   virtual void putch(char ch)
    {
     Printf(Log,"putch(#.c;)",CharCode(ch)); ELog();
    }
 };

/* Main() */

int Main(CmdDisplay cmd_display)
 {
  FileReport report;
  
  try
    {
     MainWindow main_win;
     
     main_win.create(cmd_display);
     
     while( DefaultDesktop->pump() )
       {
        DefaultDesktop->wait(10_msec);
       }
     
     return 0;
    }
  catch(...)
    {
     return 1;
    }
 }
 
} // namespace App
 
/* WinMain() */ 

CCore::Video::DesktopConfig CCore::Video::AppDesktopConfig={IDI_APP,IDI_SMALL_APP};

#include <CCore/inc/win32/Win32gui.h>

//const CCore::AbortMsgFuncType CCore::AbortMsgFunc=CCore::Rawin::MainWindowProp::AbortMsgBox;

extern "C" int WIN32_CALLTYPE WinMain(Win32::HModule,Win32::HModule,char *,unsigned cmd_show)
 {
  return App::Main(CCore::Video::MapCmdShow(cmd_show)); 
 }
 
 


