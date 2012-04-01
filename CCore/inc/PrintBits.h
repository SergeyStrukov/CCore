/* PrintBits.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintBits_h
#define CCore_inc_PrintBits_h
 
#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */ 

template <class P,class UInt> class PrintBitsType;

/* class PrintBitsType<P,UInt> */ 

template <class P,class UInt> 
class PrintBitsType
 {
   P &out;
   UInt value;
   bool empty;
   
  public: 
  
   PrintBitsType(P &out_,UInt value_) : out(out_),value(value_),empty(true) {}
   
   PrintBitsType<P,UInt> & operator () (UInt flag,StrLen name)
    {
     if( value&flag )
       {
        BitClear(value,flag);
        
        if( !empty ) out.put('|');
        
        Putobj(out,name);
        
        empty=false;
       }
    
     return *this;
    }
    
   void complete()
    {
     if( empty ) out.put('0');
    }
 };
 
/* PrintBits() */  
 
template <class UInt,class P> 
PrintBitsType<P,UInt> PrintBits(P &out,UInt value) { return PrintBitsType<P,UInt>(out,value); }
 
} // namespace CCore
 
#endif
 

