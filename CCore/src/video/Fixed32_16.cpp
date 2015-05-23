/* Fixed32_16.cpp */ 
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
 
#include <CCore/inc/video/Fixed32_16.h>
 
namespace CCore {
namespace Video {

/* struct Fixed32_16 */

Fixed32_16 Fixed32_16::pow(unsigned deg) const
 {
  switch( deg )
    {
     case 0 : return Fixed32_16(1,0);
     
     case 1 : return *this;
     
     default:
      {
       Fixed32_16 a=pow(deg>>1);
       
       if( deg&1 )
         {
          return a*a*(*this);
         }
       else
         {
          return a*a;
         }
      }
    }
 }

} // namespace Video
} // namespace CCore
 

