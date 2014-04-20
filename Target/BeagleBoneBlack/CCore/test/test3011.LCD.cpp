/* test3011.LCD.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/dev/DevHDMI.h>
#include <CCore/inc/dev/DevLCD.h>
#include <CCore/inc/sys/SysMemSpace.h>

#include <CCore/inc/Task.h>

namespace App {

namespace Private_3011 {

/* enum ColorName */

enum ColorName
 {
  Black     = 0x000000 ,
  Red       = 0xFF0000 ,
  Green     = 0x00FF00 ,
  Blue      = 0x0000FF ,
  Gray      = 0x808080 ,
  LightGray = 0xC0C0C0 ,
  White     = 0xFFFFFF
 };

/* struct Color */

struct Color
 {
  uint8 red;
  uint8 green;
  uint8 blue;
  
  Color() : red(0),green(0),blue(0) {}
  
  Color(ColorName cname) : red(cname>>16),green(cname>>8),blue(cname) {}
  
  Color(uint8 red_,uint8 green_,uint8 blue_) : red(red_),green(green_),blue(blue_) {}
  
  static uint16 Pack565(uint16 r,uint16 g,uint16 b) { return (r<<11)|(g<<5)|b; }
  
  uint16 pack565() const { return Pack565(red>>3,green>>2,blue>>3); }
 };

/* struct FrameBuf */

struct FrameBuf
 {
  uint16 *base;
  ulen dx;
  ulen dy;
  
  FrameBuf() : base(0),dx(0),dy(0) {}
  
  FrameBuf(uint16 *base_,ulen dx_,ulen dy_) : base(base_),dx(dx_),dy(dy_) {}
  
  void pixel(ulen x,ulen y,Color color)
   {
    base[x+y*dx]=color.pack565();
   }
  
  void hLine(ulen y,Color color)
   {
    for(ulen x=0; x<dx ;x++) pixel(x,y,color);
   }
  
  void vLine(ulen x,Color color)
   {
    for(ulen y=0; y<dy ;y++) pixel(x,y,color);
   }
  
  void erase(Color color)
   {
    for(ulen y=0; y<dy ;y++) hLine(y,color);
   }
 };

/* Test() */

void Test(uint16 *base,ulen dx,ulen dy)
 {
  FrameBuf out(base,dx,dy);
  
  out.erase(Black);
  
  for(ulen x=0; x<100 ;x++)
    {
     for(ulen y=x; y<out.dy-x ;y++) out.pixel(x,y,White);
    }
  
  for(ulen x=100; x<200 ;x++)
    {
     for(ulen y=x; y<out.dy-x ;y++) out.pixel(x,y,Red);
    }
  
  for(ulen x=200; x<300 ;x++)
    {
     for(ulen y=x; y<out.dy-x ;y++) out.pixel(x,y,Green);
    }
  
  for(ulen x=300; x<400 ;x++)
    {
     for(ulen y=x; y<out.dy-x ;y++) out.pixel(x,y,Blue);
    }

  out.vLine(0,Green);
  out.vLine(out.dx-1,White);
  
  out.hLine(0,Red);
  out.hLine(out.dy-1,Blue);
 }

} // namespace Private_3011
 
using namespace Private_3011; 
 
/* Testit<3011> */ 

template<>
const char *const Testit<3011>::Name="Test3011 LCD";

template<>
bool Testit<3011>::Main() 
 {
  // 1
  {
   Dev::I2C i2c(Dev::I2C_0);
  
   i2c.enable();
   i2c.reset();
  }

  Video::EDIDMode mode;
  
  // 2
  {
   Dev::HDMI hdmi;

   hdmi.init();
   
   uint8 block[Video::EDIDLen];
   
   hdmi.readEDID(block);
   
   mode=Video::EDIDMode(block);
   
   mode.pixel_clock=100000;
   
   hdmi.setMode(mode);
   
   hdmi.enableVIP();
  }
  
  // 3
  {
   Dev::LCD lcd;
   
   lcd.enable(200);
   
   lcd.reset_first();
   
   Space space=Sys::AllocVideoSpace();
   
   auto fb=lcd.init_first(mode,space);
   
   Test(fb.base,fb.dx,fb.dy);
  }
  
  return true;
 }
 
} // namespace App
 
