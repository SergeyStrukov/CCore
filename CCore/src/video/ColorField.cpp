/* ColorField.cpp */ 
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
 
#include <CCore/inc/video/ColorField.h>

#include <CCore/inc/video/SmoothAlgo.h>
 
namespace CCore {
namespace Video {

/* class TwoField */

TwoField::TwoField(MPoint a_,ColorName ca_,MPoint b_,ColorName cb_) 
 : a(a_),
   ca(ca_),
   b(b_),
   cb(cb_) 
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

ColorName TwoField::operator () (MPoint point) const
 {
  DCoord P=Prod(point-a,b);
  
  if( P<=0 ) return ca;
  
  if( P>=D ) return cb;
  
  return Linear(ca,cb,uint16(uDCoord(P)>>shift),d);
 }

/* class RadioField */

RadioField::RadioField(MPoint center_,MCoord radius_,ColorName c_,ColorName a_)
 : center(center_),
   radius(radius_),
   c(c_),
   a(a_) 
 {
  uMCoord r=uMCoord(radius);
  
  unsigned n=Bits(r);
  
  if( n>16 )
    {
     shift=n-16;
     d=uint16(r>>shift);
    }
  else
    {
     shift=0;
     d=uint16(r);
    }
 }

ColorName RadioField::operator () (MPoint point) const
 {
  DCoord len=Smooth::Length(center-point);
  
  if( len>=radius ) return a;
  
  return Linear(c,a,uint16( uMCoord(len)>>shift ),d);
 }

} // namespace Video
} // namespace CCore
 

