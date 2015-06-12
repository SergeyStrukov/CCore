/* ColorField.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_ColorField_h
#define CCore_inc_video_ColorField_h

#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Color.h>
 
namespace CCore {
namespace Video {

/* classes */

struct AlphaColorName;

class ConstantField;

class ConstantAlphaField;

class TwoField;

/* struct AlphaColorName */

struct AlphaColorName
 {
  ColorName cname;
  unsigned alpha;
 };

/* class ConstantField */

class ConstantField
 {
   ColorName cname;
   
  public: 
   
   explicit ConstantField(ColorName cname_) : cname(cname_) {}
   
   ColorName operator () (MPoint) const { return cname; }
 };

/* class ConstantAlphaField */

class ConstantAlphaField
 {
   AlphaColorName aname;
   
  public: 
   
   explicit ConstantAlphaField(ColorName cname,unsigned alpha) : aname{cname,alpha} {}
   
   AlphaColorName operator () (MPoint) const { return aname; }
 };

/* class TwoField */

class TwoField
 {
   MPoint a;
   ColorName ca;
   MPoint b;
   ColorName cb;
   
   DCoord D;
   uint16 d;
   unsigned shift;
   
  private:
   
   static unsigned Bits(uDCoord D)
    {
     using Algo = UIntFunc<uDCoord> ;
    
     return Algo::Bits-Algo::CountZeroMSB(D);
    }
   
   static Clr Lin(Clr a,Clr b,uint16 p,uint16 d)
    {
     if( a<b ) return Clr( a+(uint32(b-a)*p)/d );
     
     if( a==b ) return a;
     
     return Clr( a-(uint32(a-b)*p)/d );
    }
   
   static ColorName Lin(ColorName ca,ColorName cb,uint16 p,uint16 d)
    {
     return RGBColor(Lin(RedOf(ca),RedOf(cb),p,d),Lin(GreenOf(ca),GreenOf(cb),p,d),Lin(BlueOf(ca),BlueOf(cb),p,d));
    }
   
  public:
  
   TwoField(MPoint a_,ColorName ca_,MPoint b_,ColorName cb_) 
    : a(a_),ca(ca_),b(b_),cb(cb_) 
    { 
     b-=a; 
     
     D=Prod(b,b);
     
     IntGuard( D>0 );
     
     unsigned n=Bits(D);
     
     if( n>16 )
       {
        shift=n-16;
        d=uint16(D>>shift);
       }
     else
       {
        shift=0;
        d=uint16(D);
       }
    }
  
   ColorName operator () (MPoint point) const
    {
     DCoord P=Prod(point-a,b);
     
     if( P<=0 ) return ca;
     
     if( P>=D ) return cb;
     
     return Lin(ca,cb,uint16(uDCoord(P)>>shift),d);
    }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

