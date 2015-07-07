/* Life.h */
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

#ifndef Life_h
#define Life_h

#include <inc/Application.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/PlatformRandom.h>

namespace App {

/* classes */

class Life;

/* class Life */

class Life : public SubWindow
 {
  public:
  
   struct Config
    {
     Coord cell_dxy  =   8 ;
     Coord space_dxy =   1 ;
     
     Coord cx        = 150 ;
     Coord cy        = 100 ;
     
     Coord outer_dxy =   5 ;

     ColorName outer       =     Wheat ;
     ColorName text        = DarkGreen ; 
     
     ColorName back        =    Silver ;
     ColorName cell        =      Blue ;
     ColorName border_up   =     White ;
     ColorName border_down =      Gray ;
     
     Font font;
     
     Config() {}
    };
  
  private:
   
   Config cfg;
   
   struct Pos
    {
     Coord cx;
     
     Pos(Coord cx_,Coord cy_) : cx(cx_) { Used(cy_); }
     
     AreaType operator () (Coord x,Coord y) const { return x+Area(y,cx); }
    };
   
   class Map : NoCopy
    {
      PlatformRandom random;
      
      DynArray<bool> buf;
      DynArray<bool> next_buf;
      Coord cx;
      Coord cy;
      
      ulen step_number = 0 ;
      
     private:
      
      bool bit(unsigned percent)
       {
        return random.select(100)<percent;
       }
      
      static bool Cell(bool b00,bool b10,bool b20,
                       bool b01,bool b11,bool b21,
                       bool b02,bool b12,bool b22);
      
     public:
     
      Map(Coord cx,Coord cy);
      
      ~Map();
      
      const bool * getPtr() const { return buf.getPtr(); }
      
      Pos getPos() const { return Pos(cx,cy); }
      
      ulen getStepNumber() const { return step_number; }
      
      void reset(unsigned percent=25);
      
      void step();
    };
   
   Map map;
   
   bool has_focus = false ;
   bool running = false ;
   
   Coord dxy;
   Pane status;
   Pane arena;
   
   TimeScope sec_scope;
   ulen step_number = 0 ;
   ulen speed = 0 ;
   
   class Divider : NoCopy
    {
      static const unsigned MaxDiv = 100 ;
     
      unsigned div = 10 ;
      unsigned count = 0 ;
      
     public:
      
      Divider() {}
      
      unsigned getDiv() const { return div; }
      
      void inc()
       {
        if( div<MaxDiv ) div++;
       }
      
      void dec()
       {
        if( div>1 ) 
          {
           div--;
           
           if( count>=div ) count=div-1;
          }
       }
      
      bool tick()
       {
        if( !count ) 
          {
           count=div-1;
           
           return true;
          }
        else
          {
           count--;
          
           return false;
          }
       }
    };

   Divider divider;
   
  private: 
  
   void setStart();
   
   void tick();
   
  public:
  
   Life(SubWindowHost &host,const Config &cfg={});
   
   virtual ~Life();
   
   // drawing
   
   virtual void layout();
   
   virtual void draw(DrawBuf buf,bool drag_active) const;
   
   // base
   
   virtual void open();
   
   // keyboard
   
   virtual void gainFocus();
   
   virtual void looseFocus();
   
   // user input
   
   virtual void react(UserAction action);
   
   void react_Key(VKey vkey,KeyMod kmod);

   // DeferInput
   
   class Input : DeferInput<Life>
    {
      friend class Life;
      
      explicit Input(Life *window) : DeferInput<Life>(window) {}
      
      ~Input() {}
    };
   
   Input input;
   
  private:
   
   DeferTick defer_tick;
 };

} // namespace App

#endif

