/* test6.cpp */
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

#include <CCore/inc/video/Desktop.h>

#include <cmath>

namespace App6 {

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

/* class AlphaFunc */

using UInt = unsigned ;

const unsigned AlphaBits = 8 ; 

class AlphaFunc
 {
   double tau,a,b;
  
   double tau2,M,S;
  
 private:
  
  static unsigned Map(double f)
   {
    f=Cap<double>(0,f,1);
    
    return unsigned(f*(1u<<AlphaBits));
   }
  
  public:
  
   AlphaFunc(UInt sx,UInt sy)
    {
     tau=double(sy)/sx;
     
     double c=std::sqrt(1+Sq(tau))-1;
     
     c=Cap<double>(0,c,tau);
     
     b=(tau+c)/2;
     a=(tau-c)/2;
     
     tau2=2*tau;
     M=1-Sq(a)/tau;
     S=1-tau/2+b;
    }
   
   unsigned alpha0(UInt d,UInt sx,UInt sy) const // d in [0,sx]
    {
     Used(sy);
     
     double t=double(d)/sx;
     
     if( t<a )
       {
        return Map( M-Sq(t)/tau );
       }
     
     if( t<b )
       {
        return Map( 1-Sq(t+a)/tau2 );
       }
     
     if( t<1-a )
       {
        return Map( S-t );
       }
     
     return Map( Sq(b+1-t)/tau2 );
    }
   
   unsigned alpha1(UInt d,UInt sx,UInt sy) const // d in [0,sx]
    {
     Used(sy);
     
     double t=double(d)/sx;
     
     if( t>b ) return 0;
     
     return Map( Sq(b-t)/tau2 );
    }
 };

/* test1() */

void test1(unsigned sx,unsigned sy)
 {
  
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
        unsigned sy=random.select(1,10000);
        unsigned sx=sy+random.select(10000);
     
        test1(sx,sy);
       }
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
} // namespace App6
 

