/* ShiftStateTypes.ddl */
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

include <StateTypes.ddl>

struct ShiftState
 {
  StateIndex state;

  struct Transition { Element *element; ShiftState *state; } [] transitions;

  State * [] states;
  Final * [] finals;

  Element * [] shift;
 };
