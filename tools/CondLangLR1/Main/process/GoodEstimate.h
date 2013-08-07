/* GoodEstimate.h */
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

#ifndef CondLangLR1_process_GoodEstimate_h
#define CondLangLR1_process_GoodEstimate_h

#include "lang/Lang.h"

namespace App {

/* classes */

struct GoodEstimate;

class GoodTest;

/* struct GoodEstimate */ 

struct GoodEstimate : NoCopy
 {
  enum Const
   {
    Empty,Null,Good
   };
 
  enum SetResult
   {
    NoChange,Change,ChangeToMax
   };
 
  class Type : public NoThrowFlagsBase
   {
     int value;
     
    private: 
     
     explicit Type(int value_) : value(value_) {}
  
    public: 
  
     Type(Const c=Empty) : value(c) {}
     
     // methods
  
     bool isBad() const { return value!=Good; }
  
     const char * badDesc() const { return (value==Empty)?"empty":"only null string"; }
  
     SetResult set(Type t)
      {
       if( value==t.value ) return NoChange;
    
       value=t.value;
    
       return (value==Good)?ChangeToMax:Change;
      }
     
     // operators
      
     friend Type operator + (Type a,Type b) { return Type(Max(a.value,b.value)); }
     
     friend Type operator * (Type a,Type b) { return Type(Min(a.value*b.value,2)); }
   };
 };

/* class GoodTest */

class GoodTest : GoodEstimate
 {
   const Lang &lang;
 
   DynArray<Type> flags;
   DynArray<ulen> list;
   ulen list_len;
   
   DynArray<ulen> mul_pool;
   
   struct MulRec : OffLen
    {
     Type first;
     
     MulRec() {}
     
     MulRec(ulen off,ulen len,bool good) : OffLen(off,len),first(good?Good:Null) {}
    };
   
   DynArray<MulRec> step_pool;
   
   DynArray<OffLen> step_list;
   
  private:
   
   PtrLen<const ulen> getMul(MulRec rec) const { return rec.cut(mul_pool.getPtr()); }
   
   PtrLen<const MulRec> getStep(OffLen rec) const { return rec.cut(step_pool.getPtr()); }
   
   Type mul(MulRec rec) const;
   
   SetResult step(ulen synt_index);
   
   MulRec buildMul(PtrLen<const LangBase::Element> args);
   
   OffLen buildStep(const LangBase::SyntDesc &synt);
   
  public:
   
   explicit GoodTest(const Lang &lang);
   
   ~GoodTest();
   
   bool step();
   
   template <class P>
   bool check(P &out) const;
 };

template <class P>
bool GoodTest::check(P &out) const
 {
  bool ret=true;

  for(auto synts=lang.getSynts(); +synts ;++synts)
    if( flags[synts->index].isBad() )
      {
       Printf(out,"Bad syntax class #; : #;\n",synts->name,flags[synts->index].badDesc());
     
       ret=false;
      }

  return ret;
 }

} // namespace App

#endif


