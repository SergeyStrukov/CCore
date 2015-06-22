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

/* functions */

inline Clr Linear(Clr a,Clr b,uint16 c,uint16 d)
 {
  if( a<b ) return Clr( a+(uint32(b-a)*c)/d );
  
  if( a==b ) return a;
  
  return Clr( a-(uint32(a-b)*c)/d );
 }

inline ColorName Linear(ColorName a,ColorName b,uint16 c,uint16 d)
 {
  return RGBColor(Linear(RedOf(a),RedOf(b),c,d),Linear(GreenOf(a),GreenOf(b),c,d),Linear(BlueOf(a),BlueOf(b),c,d));
 }

/* classes */

struct AlphaColorName;

class ConstantField;

class ConstantAlphaField;

class TwoField;

class RadioField;

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
   DownBits<uint16> d;
   
  public:
  
   TwoField(MPoint a,ColorName ca,MPoint b,ColorName cb); 
  
   ColorName operator () (MPoint point) const;
 };

/* class RadioField */

class RadioField
 {
   MPoint center;
   MCoord radius;
   ColorName c;
   ColorName a;
   
   DownBits<uint16> d;
   
  public:
  
   RadioField(MPoint center,MCoord radius,ColorName c,ColorName a);
   
   ColorName operator () (MPoint point) const;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

