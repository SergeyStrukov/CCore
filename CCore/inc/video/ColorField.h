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

class ConstantField;

/* class ConstantField */

class ConstantField
 {
   ColorName cname;
   
  public: 
   
   explicit ConstantField(ColorName cname_) : cname(cname_) {}
   
   ColorName operator () (MPoint) const { return cname; }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

