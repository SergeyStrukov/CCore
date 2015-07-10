/* Life.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Life 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Life.h>

#include <CCore/inc/video/CommonDrawArt.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class Life::Map */

bool Life::Map::Cell(bool b00,bool b10,bool b20,
                     bool b01,bool b11,bool b21,
                     bool b02,bool b12,bool b22)
 {
  int sum=b00+b10+b20+
          b01    +b21+
          b02+b12+b22;
  
  if( b11 )
    {
     return sum==2 || sum==3 ;
    }
  else
    {
     return sum==3;
    }
 }

Life::Map::Map(Coord cx_,Coord cy_)
 : cx(cx_),
   cy(cy_)
 {
  if( cx_<=0 || cy_<=0 )
    {
     Printf(Exception,"ShapeEditor::Life::Map::Map(#;,#;) : bad dimensions",cx_,cy_);
    }
  
  ulen len=Area(cx_,cy_);
  
  buf.extend_default(len);
  next_buf.extend_default(len);
  
  reset();
 }

Life::Map::~Map()
 {
 }

void Life::Map::reset(unsigned percent)
 {
  for(bool &x : buf ) x=bit(percent);
  
  step_number=0;
 }

void Life::Map::step()
 {
  const bool *src=buf.getPtr();
  bool *dst=next_buf.getPtr();
  
  Coord cx=this->cx;
  Coord cy=this->cy;
  
  Pos pos=getPos();
  
  for(Coord x=0; x<cx ;x++)
    for(Coord y=0; y<cy ;y++)
      {
       Coord x0=x?(x-1):(cx-1);
       Coord x1=x;
       Coord x2=(x<cx-1)?x+1:0;
       
       Coord y0=y?(y-1):(cy-1);
       Coord y1=y;
       Coord y2=(y<cy-1)?y+1:0;
      
       dst[pos(x,y)]=Cell(src[pos(x0,y0)],src[pos(x1,y0)],src[pos(x2,y0)],
                          src[pos(x0,y1)],src[pos(x1,y1)],src[pos(x2,y1)],
                          src[pos(x0,y2)],src[pos(x1,y2)],src[pos(x2,y2)]);
      }
  
  Swap(buf,next_buf);
  
  step_number++;
 }

/* class Life */

void Life::setStart()
 {
  sec_scope.start(1_sec);
  
  step_number=map.getStepNumber();
 }

void Life::tick()
 {
  if( running && has_focus )
    {
     if( sec_scope.nextScope_skip() )
       {
        speed=Diff(step_number,map.getStepNumber());
       }
     
     if( divider.tick() )
       {
        map.step();
    
        redraw();
       }
    }
 }

Life::Life(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),
   map(cfg.cx,cfg.cy),
   sec_scope(1_sec),
   input(this)
 {
  defer_tick=input.create(&Life::tick);
 }

Life::~Life()
 {
 }

 // drawing

void Life::layout()
 {
  dxy=cfg.cell_dxy+cfg.space_dxy;
  
  Point size=getSize();
  FontSize font_size=cfg.font->getSize();
  
  Coord dy=font_size.dy+2*cfg.outer_dxy;
  
  status=Pane(cfg.outer_dxy,0,size.x-cfg.outer_dxy,dy);
  
  arena=Pane(cfg.outer_dxy,dy,cfg.cx*dxy+cfg.space_dxy,cfg.cy*dxy+cfg.space_dxy);
 }

void Life::draw(DrawBuf buf,bool) const
 {
  try
    {
     CommonDrawArt art(buf);
     
     art.erase(cfg.outer);
     
     // status
     {
      char temp[TextBufLen];
      PrintBuf out(Range(temp));
     
      Printf(out,"Step #; per second #; div = #;",map.getStepNumber(),speed,divider.getDiv());
     
      cfg.font->text(buf,status,TextPlace(AlignX_Left,AlignY_Center),out.close(),cfg.text);
     } 
     
     // arena
     {
      art.block(arena,cfg.back);
     
      PaneBorder border(arena.expand(1));
     
      art.path(cfg.border_up,border.bottomLeft(),border.topLeft(),border.topRight());
      art.path(cfg.border_down,border.bottomLeft(),border.bottomRight(),border.topRight());
     } 
     
     // cells
     {
      Coord dxy=this->dxy;
      
      const bool *src=map.getPtr();
      
      Coord cx=cfg.cx;
      Coord cy=cfg.cy;
      
      Pos pos=map.getPos();
      
      Coord x0=arena.x+cfg.space_dxy;
      Coord y0=arena.y+cfg.space_dxy;
        
      for(Coord x=0; x<cx ;x++)
        for(Coord y=0; y<cy ;y++)
          {
           if( src[pos(x,y)] )
             {
              art.block(Pane(x0+x*dxy,y0+y*dxy,cfg.cell_dxy,cfg.cell_dxy),cfg.cell);
             }
          }
     }
    }
  catch(CatchType)
    {
    }
 }

 // base

void Life::open()
 {
  has_focus=false;
  
  defer_tick.start();
 }

 // keyboard

void Life::gainFocus()
 {
  has_focus=true;
  
  if( running ) setStart();
  
  redraw();
 }

void Life::looseFocus()
 {
  has_focus=false;
  
  redraw();
 }

 // user input

void Life::react(UserAction action)
 {
  action.dispatch(*this);
 }

void Life::react_Key(VKey vkey,KeyMod kmod)
 {
  Used(kmod);
  
  switch( vkey )
    {
     case VKey_Space :
      {
       running=!running;
       
       if( running && has_focus ) setStart();
      }
     break;
     
     case VKey_NumPlus :
      {
       divider.dec();
      }
     break; 
      
     case VKey_NumMinus :
      {
       divider.inc();
      }
     break; 
     
     case VKey_Enter :
      {
       if( !running )
         {
          if( sec_scope.nextScope_skip() )
            {
             speed=Diff(step_number,map.getStepNumber());
            }
          
          map.step();
          
          redraw();
         }
      }
     break;
     
     case VKey_F5 :
      {
       map.reset();
       
       running=false;
       
       redraw();
      }
     break; 
     
#if 0     
     
     case VKey_F10 :
      {
       if( kmod&KeyMod_Alt )
         {
          Printf(Exception,"test");
         }
      }
     break;
     
#endif     
    }
 }

} // namespace App

