/* SimpleSpan.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: EllipticPi 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "SimpleSpan.h"

#include <CCore/inc/Exception.h>

namespace App {

/* functions */

void GuardSpanZeroDivisor()
 {
  Printf(Exception,"App::operator / (SimpleSpan<Int>,SimpleSpan<Int>) : zero divisor");
 }

void GuardSpanBrokenLimits()
 {
  Printf(Exception,"App::SimpleSpan<Int>::SimpleSpan(Int lo,Int hi,unsigned exp) : hi<lo");
 }

void GuardSpanExactDivision()
 {
  Printf(Exception,"App::SimpleSpan<Int>::Div(...) : exact division");
 }

} // namespace App
