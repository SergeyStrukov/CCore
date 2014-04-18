/* DevLCD.h */
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

#ifndef CCore_inc_dev_DevLCD_h
#define CCore_inc_dev_DevLCD_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Dev {

/* classes */

class LCD;

/* class LCD */

class LCD : NoCopy
 {
  public:
  
   struct Geometry
    {
     uint32 hlen;   // 16-2048 multiple of 16
     uint32 hfront; // 1-1024
     uint32 hsync;  // 1-1024
     uint32 hback;  // 1-1024
    
     uint32 vlen;   // 1-2048 
     uint32 vfront; // 0-255
     uint32 vsync;  // 1-64
     uint32 vback;  // 0-255
    
     Geometry() {}
    };
   
   struct MainFrame
    {
     using Color = uint16 ;
     
     Color *base;
     ulen dx;
     ulen dy;
    };
  
   LCD();
   
   // init
   
   void enable(uint32 clock); // MHz
   
   void first_reset();
   
   void setClock(uint32 clock); // MHz
   
   MainFrame init(const Geometry &geom,Space video_space);
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

