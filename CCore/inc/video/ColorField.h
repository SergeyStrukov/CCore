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

} // namespace Video
} // namespace CCore
 
#endif
 

