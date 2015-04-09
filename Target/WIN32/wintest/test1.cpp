/* test1.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/Win32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

//#include <CCore/inc/video/DrawArt.h>
#include "DrawArt.h"
//#include <CCore/inc/video/DrawAlgo.h>
#include "DrawAlgo.h"

#include <CCore/inc/Random.h>

#include "FileReport.h"

namespace App1 {

/* using */ 

using namespace App;
using namespace CCore::Video;

/* test1() */

void test1(unsigned sx,unsigned sy)
 {
  LineDriverBase<unsigned> driver(sx,sy);
  
  unsigned x=0;
  unsigned y=0;
  
  for(unsigned count=sx; count ;count--)
    {
     y+=driver.step();
     x++;
     
     UIntFunc<unsigned>::Mul mul(x,sy);
     UIntFunc<unsigned>::DivMod divmod(mul.hi,mul.lo,sx);
     
     unsigned z=divmod.div;
     
     if( divmod.mod>sx/2 ) z++;
     
     if( y!=z ) 
       {
        Printf(Exception,"1 failed #; #;",sx,sy);
       }
    }
 }

/* test2() */

void test2(unsigned sx,unsigned sy,unsigned off,unsigned len)
 {
  LineDriverBase<unsigned> driver(sx,sy);
  
  unsigned y=0;
  
  for(unsigned count=off; count ;count--)
    {
     y+=driver.step();
    }
  
  unsigned y0=y;
  
  LineDriverBase<unsigned> driver1(driver);
  
  for(unsigned count=len; count ;count--)
    {
     y+=driver.step();
    }
  
  unsigned y1=y;
  
  if( driver1.step(len)!=y1-y0 )
    {
     Printf(Exception,"2 failed #; #;",sx,sy);
    }
 }

/* test3() */

void test3(uCoord sx,uCoord sy,uCoord y)
 {
  LineDriver driver(sx,sy);
  LineDriver driver1(driver);
  
  uCoord x=driver.clipToX(y);
  
  if( driver.step(x)<y || x==0 )
    {
     Printf(Exception,"3 failed #; #; #;",sx,sy,y);
    }
  
  if( driver1.step(x-1)>=y )
    {
     Printf(Exception,"4 failed #; #; #;",sx,sy,y);
    }
 }

void test3(unsigned sx,unsigned sy)
 {
  for(unsigned y=1; y<=sy ;y++) test3(sx,sy,y);
 }

/* testmain() */

int testmain(CmdDisplay)
 {
  FileReport report;
  
  try
    {
     Random random;
     
     for(ulen count=10000; count ;count--)
       {
        unsigned sy=random.select(1,1000);
        unsigned sx=sy+random.select(10000);
     
        test1(sx,sy);
        
        test2(sx,sy,random.select(1,1000),random.select(1,1000));
        
        test3((uCoord)sx,(uCoord)sy);
       }
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
} // namespace App1
 

