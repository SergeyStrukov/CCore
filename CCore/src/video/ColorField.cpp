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
  
  d.init(uDCoord(D));
 }

ColorName TwoField::operator () (MPoint point) const
 {
  DCoord P=Prod(point-a,b);
  
  if( P<=0 ) return ca;
  
  if( P>=D ) return cb;
  
  return Linear(ca,cb,d(uDCoord(P)),d);
 }

/* class RadioField */

RadioField::RadioField(MPoint center_,MCoord radius_,ColorName c_,ColorName a_)
 : center(center_),
   radius(radius_),
   c(c_),
   a(a_) 
 {
  IntGuard( radius>0 );
  
  d.init(uMCoord(radius));
 }

ColorName RadioField::operator () (MPoint point) const
 {
  DCoord len=Smooth::Length(center-point);
  
  if( len>=radius ) return a;
  
  return Linear(c,a,d(uMCoord(len)),d);
 }

} // namespace Video
} // namespace CCore
 

