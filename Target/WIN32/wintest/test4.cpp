/* test4.cpp */
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

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Random.h>

#include "DrawArt.h"
#include "DrawAlgo.h"

namespace App4 {

/* using */ 

using namespace CCore;
using namespace CCore::Video;

/* class FileReport */

class FileReport : public ReportException
 {
   PrintFile out;
   
  private: 
 
   virtual void print(StrLen str)
    {
     Putobj(out,str);
    }
   
   virtual void end()
    {
     Printf(out,"\n\n#;\n\n",TextDivider());
    }
   
  public:
  
   FileReport() : out("exception-log.txt") {}
   
   ~FileReport() { Printf(out,"Done\n"); }
   
   bool show() { return true; }
 };

/* test1() */

void test1(unsigned sx,unsigned sy)
 {
  LineDriver driver(sx,sy);
  
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
  LineDriver driver(sx,sy);
  
  unsigned y=0;
  
  for(unsigned count=off; count ;count--)
    {
     y+=driver.step();
    }
  
  unsigned y0=y;
  
  LineDriver driver1(driver);
  
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

void test3(unsigned sx,unsigned sy,unsigned y)
 {
  LineDriver driver(sx,sy);
  LineDriver driver1(driver);
  
  unsigned x=driver.clipToX(y);
  
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
        unsigned sx=sy+random.select(100000);
     
        test1(sx,sy);
        
        test2(sx,sy,random.select(1,1000),random.select(1,1000));
        
        test3(sx,sy);
       }
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
} // namespace App4
 

