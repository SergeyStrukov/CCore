/* AutoText.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_AutoText_h
#define CCore_inc_task_AutoText_h

#include <CCore/inc/TextLabel.h>
 
namespace CCore {

/* types */

typedef const char *const AutoTextNameType;

/* functions */

unsigned AutoTextAtomicGetNumber(unsigned &Next);

/* classes */

template <AutoTextNameType &Name> class AutoText;

/* class AutoText<AutoTextNameType &Name> */

template <AutoTextNameType &Name>
class AutoText
 {
   static unsigned Next;
   
  public: 

   static const char * GetText() { return Name; }
  
   static unsigned GetNumber() { return AutoTextAtomicGetNumber(Next); }
 };

template <AutoTextNameType &Name>
unsigned AutoText<Name>::Next=0;

/* GetAutoText() */
  
template <AutoTextNameType &Name>
TextLabel GetAutoText() { return NumTextLabel<AutoText<Name> >(); }

} // namespace CCore
 
#endif
 

