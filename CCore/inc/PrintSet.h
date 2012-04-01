/* PrintSet.h */ 
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

#ifndef CCore_inc_PrintSet_h
#define CCore_inc_PrintSet_h

#include <CCore/inc/Printf.h>
 
namespace CCore {

/* classes */ 

template <class R,class T=Meta::RangeObjType<R> > class PrintSetType;

/* class PrintSetType<R,T> */ 

template <class R,class T>
class PrintSetType : public PrintOptAdapter<T>
 {
   R range;
   
  private: 
   
   template <class S>
   static const T & Cast(const S &obj) { return obj; }
   
  public: 
 
   explicit PrintSetType(const R &range_) : range(range_) {}
  
   template <class P>
   void print(P &out) const
    {
     R r=range;
     
     if( +r )
       {
        Putobj(out,"{ ",Cast(*r));
        
        for(++r; +r ;++r) Putobj(out," , ",Cast(*r));
    
        Putobj(out," }");
       }
     else
       {
        Putobj(out,"{ }");
       }  
    }
   
   template <class P,class Opt>
   void print(P &out,const Opt &opt) const
    {
     R r=range;
     
     if( +r )
       {
        Putobj(out,"{ ",BindOpt(opt,Cast(*r)));
        
        for(++r; +r ;++r) Putobj(out," , ",BindOpt(opt,Cast(*r)));
    
        Putobj(out," }");
       }
     else
       {
        Putobj(out,"{ }");
       }  
    }
 };
 
/* PrintSet() */  
 
template <class R>
PrintSetType<R> PrintSet(const R &range) { return PrintSetType<R>(range); }
 
} // namespace CCore
 
#endif
 

