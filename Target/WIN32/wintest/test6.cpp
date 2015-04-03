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

/* class AlphaFunc2 */

class AlphaFunc2
 {
   enum OneType
    {
     One = 1
    };
  
   class Num // [0,2)
    {
      static const unsigned Precision = 15 ;
      
      static const uint16 One = uint16(1)<<Precision ;
     
      uint16 value;
      
     private: 
     
      Num(uint16 value_) : value(value_) {}
      
     public:
      
      Num() : value(0) {}
      
      Num(OneType) : value(One) {}
      
      Num(UInt a,UInt b) // a<=b , a/b TODO
       {
        value=(a<<Precision)/b;
       }
      
      unsigned map() const { return value>>(Precision-AlphaBits); }
      
      bool below_1() const { return !(value&One); }
      
      Num div_2() const { return value>>1; }
      
      friend bool operator < (Num a,Num b) { return a.value<b.value; }
      
      friend bool operator > (Num a,Num b) { return a.value>b.value; } 
      
      friend bool operator <= (Num a,Num b) { return a.value<=b.value; }
      
      friend bool operator >= (Num a,Num b) { return a.value>=b.value; }
      
      friend Num operator + (Num a,Num b) { return a.value+b.value; }
      
      friend Num operator - (Num a,Num b) { return a.value-b.value; }
      
      friend Num operator * (Num a,Num b) { return uint16( (uint32(a.value)*b.value)>>Precision ); }
    };
  
   static unsigned Map(Num a) { return a.map(); }
   
  private: 
   
   Num T,A,B;
   
   Num T2,M,S;
  
  public:
  
   AlphaFunc2(UInt sx,UInt sy)
    {
     T=Num(sy,sx);

     double t=double(sy)/sx;
     
     double c=(std::sqrt(1+Sq(t))-1)/t;
     
     Num C(UInt(c*(1u<<15)),1u<<15); // TODO
     
     B=(One+C).div_2();
     
     A=(One-C).div_2();
     
     T2=T.div_2();
     
     M=One-Sq(A)*T;
     
     S=One+T2*C;
    }
   
   unsigned alpha0(UInt d,UInt sx,UInt sy) const // d in [0,sx]
    {
     if( d<sy )
       {
        Num t(d,sy);
        
        if( t<=A ) return Map( M-T*Sq(t) );
        
        if( t<=B ) return Map( One-T2*Sq(t+A) );
       }
     
     UInt e=sx-d;
     
     if( e<sy )
       {
        Num t(e,sy);
        
        if( t<=A ) return Map( T2*Sq(B+t) );
       }
     
     Num t(d,sx);
     
     return Map( S-t );
    }
 
   unsigned alpha1(UInt d,UInt sx,UInt sy) const // d in [0,sx]
    {
     Used(sx);
     
     if( d>=sy ) return 0;
     
     Num t(d,sy);
     
     if( t>=B ) return 0;
     
     return Map( Sq(B-t)*T2 );
    }
 };

/* test1() */

inline unsigned Delta(unsigned a,unsigned b) { return (a<=b)?(b-a):(a-b); }

unsigned test1(unsigned sx,unsigned sy)
 {
  AlphaFunc func1(sx,sy);
  AlphaFunc2 func2(sx,sy);
  
  unsigned ret=0;
  
  for(UInt d=0; d<=sx ;d++)
    {
     Replace_max(ret,Delta(func1.alpha0(d,sx,sy),func2.alpha0(d,sx,sy)));
     Replace_max(ret,Delta(func1.alpha1(d,sx,sy),func2.alpha1(d,sx,sy)));
    }
  
  return ret;
 }

/* testmain() */

int testmain(CmdDisplay)
 {
  FileReport report;
  
  try
    {
     Random random;
     
     unsigned delta=0;
     
     for(ulen count=10000; count ;count--)
       {
        unsigned sy=random.select(1,10000);
        unsigned sx=sy+random.select(10000);
     
        Replace_max(delta,test1(sx,sy));
       }
     
     Printf(NoException,"delta = #;",delta);
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
} // namespace App6
 
