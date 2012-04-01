/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: EllipticPi 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>

#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/Integer.h>

#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintTime.h>

#include "SimpleSpan.h"

namespace App {

/* type Int */

typedef Math::Integer<Math::IntegerFastAlgo> Int;

/* type Span */

typedef SimpleSpan<Int> Span;

/* Sqrt() */

Span Sqrt(Span a,Span x)
 {
  for(ulen step=1;;step++)
    {
     Printf(Con,"  step = #;\n",step);
     
     Span x1=(x+a/x).div2pow(1);
  
     if( x==x1 )  
       {
        return x|x1;
       }
  
     x=x1;
    }
 }

Span Sqrt(Span a) { return Sqrt(a,Int(1)); }

/* EllipticPi() */

Span EllipticPi(unsigned exp)
 {
  Printf(Con,"start exp = #;\n",exp);
  
  Span a=Int(1);
  Span b=Sqrt(Span(Int(2),exp));
  Span s=Int(0);
  unsigned n=0;
  
  while( a<b )
    {
     Printf(Con,"n = #;\n",n);
     
     Span c=((b-a)*(b+a)).mul2pow(n);
     
     s=s+c;
     
     Span b1=(a+b).div2pow(1);
     Span a1=Sqrt(a*b,b1);
     
     a=a1;
     b=b1;
     n++;
    }
  
  Printf(Con,"finish n = #;\n\n",n);
  
  Span t=a|b;
  Span tmin=t.min();
  Span tmax=t.max();
  
  s = s|(s+( ((tmax-tmin)*(tmax+tmin)).mul2pow(n+1) )) ;
  
  return t.sq().mul2pow(1)/(Int(2)-s);
 }

/* Run() */

void Run(unsigned exp)
 {
  SecTimer timer;
  
  Span pi=EllipticPi(exp);
  
  auto time=timer.get();

  Printf(Con,"exp = #;\n",exp);
  Printf(Con,"precision = #;\n",pi.precision());
  Printf(Con,"time = #;\n\n",PrintTime(time));
  
  String file_name=Stringf("pi#;.txt",exp);
  PrintFile out(Range(file_name));
  
  Printf(out,"#;\n\ntime = #;\n",pi,PrintTime(time));
 }

} // namespace App
 
/* main() */ 

using namespace App;

int main()
 {
  ReportException report;
  
  try
    {
     {
      Putobj(Con,"--- EllipticPi 1.00 ---\n--- Copyright (c) 2011 Sergey Strukov. All rights reserved. ---\n\n");

      Run(1000);
      //Run(10000);
      //Run(100000);
      //Run(400000);
      //Run(1000000);
      //Run(4000000);
     }
     
     report.guard();
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
