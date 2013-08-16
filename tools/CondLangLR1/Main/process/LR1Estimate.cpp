/* LR1Estimate.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "LR1Estimate.h"

namespace App {

/* class LR1Estimate */

LR1Estimate::ExtRuleSet::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  flag=true;
  
  StrParse dev(ptr,lim);
  
  ParseChar(dev,'.');
  ParseChar(dev,'s');
  
  if( !dev.finish() ) setDefault();
 }

} // namespace App

