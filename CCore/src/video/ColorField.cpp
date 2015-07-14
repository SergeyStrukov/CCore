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

TwoField::TwoField(MPoint a_,VColor va_,MPoint b_,VColor vb_) 
 : a(a_),
   va(va_),
   b(b_),
   vb(vb_) 
 { 
  b-=a; 
  
  D=Prod(b,b);
  
  IntGuard( D>0 );
  
  d.init(uDCoord(D));
 }

VColor TwoField::operator () (MPoint point) const
 {
  DCoord P=Prod(point-a,b);
  
  if( P<=0 ) return va;
  
  if( P>=D ) return vb;
  
  return Linear(va,vb,d(uDCoord(P)),d);
 }

/* class RadioField */

RadioField::RadioField(MPoint center_,MCoord radius_,VColor vc_,VColor va_)
 : center(center_),
   radius(radius_),
   vc(vc_),
   va(va_) 
 {
  IntGuard( radius>0 );
  
  d.init(uMCoord(radius));
 }

VColor RadioField::operator () (MPoint point) const
 {
  DCoord len=Smooth::Length(center-point);
  
  if( len>=radius ) return va;
  
  return Linear(vc,va,d(uMCoord(len)),d);
 }

} // namespace Video
} // namespace CCore
 

