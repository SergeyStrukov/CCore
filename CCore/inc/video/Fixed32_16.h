/* Fixed32_16.h */ 
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

#ifndef CCore_inc_video_Fixed32_16_h
#define CCore_inc_video_Fixed32_16_h

#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Video {

/* classes */

struct Fixed32_16;

/* struct Fixed32_16 */

struct Fixed32_16
 {
  static const unsigned Precision = 16 ;
  
  sint32 value;
  
  Fixed32_16() : value(0) {}
  
  explicit Fixed32_16(sint32 value_) : value(value_) {}
  
  Fixed32_16(sint32 value_,unsigned prec) : value( IntLShift(value_,Precision-prec) ) {} // prec<=Precision
  
  Fixed32_16 pow(unsigned deg) const;
  
  friend Fixed32_16 operator * (Fixed32_16 a,Fixed32_16 b)
   {
    return Fixed32_16( IntRShift((sint64(a.value)*b.value),32) );
   }
  
  friend sint32 operator * (Fixed32_16 a,sint32 b)
   {
    return sint32( IntRShift(sint64(a.value)*b,16) );
   }
  
  friend MilliPoint operator * (Fixed32_16 a,MilliPoint point)
   {
    return MilliPoint(a*point.x,a*point.y);
   }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

