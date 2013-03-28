/* Tools.h */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Shift 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LR1Shift_Tools_h
#define LR1Shift_Tools_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/PrintSet.h>
#include <CCore/inc/FunctorType.h>

#include "DataMap.h" 

namespace App {

/* ...SortBy() */

template <class Ran,class Len,class Func>
void IncrSortBy(Ran ptr,Len len,Func by)
 {
  using T = decltype(*ptr) ; 
  
  IncrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <class Ran,class Len,class Func>
void DecrSortBy(Ran ptr,Len len,Func by)
 {
  using T = decltype(*ptr) ; 
  
  DecrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <class T,class Func>
void IncrSortBy(PtrLen<T> range,Func by) { IncrSortBy(range.ptr,range.len,by); }

template <class T,class Func>
void DecrSortBy(PtrLen<T> range,Func by) { DecrSortBy(range.ptr,range.len,by); }

/* ProcessUnique() */

template <class R,class FuncInit>
void ProcessUnique(R r,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  if( +r )
    {
     auto *last=&(*r);
     
     func(*last);
     
     for(++r; +r ;++r)
       {
        auto *next=&(*r);
       
        if( *last!=*next )
          {
           last=next;
           
           func(*last);
          }
       }
    }
 }

/* SortThenProcessUnique() */

template <class R,class FuncInit>
void SortThenProcessUnique(R r,FuncInit func_init)
 {
  Sort(r);
  ProcessUnique(r,func_init);
 }

/* ProcessUniqueBy() */

template <class R,class Func,class FuncInit>
void ProcessUniqueBy(R r,Func by,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  if( +r )
    {
     auto *last=&(*r);
     
     func(*last);
     
     for(++r; +r ;++r)
       {
        auto *next=&(*r);
       
        if( by(*last)!=by(*next) )
          {
           last=next;
           
           func(*last);
          }
       }
    }
 }

/* SortThenProcessUniqueBy() */

template <class R,class Func,class FuncInit>
void SortThenProcessUniqueBy(R r,Func by,FuncInit func_init)
 {
  IncrSortBy(r,by);
  ProcessUniqueBy(r,by,func_init);
 }
  
/* consts */

const ulen NoGroup = ulen(-1) ;

/* functions */

RefArray<TypeDef::Final *> BuildFinals(PtrLen<TypeDef::State *const> states);

/* classes */

struct NoThrowFlagsBase;

struct Atom;

struct Element;

struct ASet;

struct ShiftFinal;

struct StateGroup;

class StateCompressor;

/* struct NoThrowFlagsBase */

struct NoThrowFlagsBase
 {
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct Atom */

struct Atom : CmpComparable<Atom> , NoThrowFlagsBase
 {
  TypeDef::Element *atom;
  
  explicit Atom(TypeDef::Element *atom_) : atom(atom_) {}
  
  // cmp objects
  
  CmpResult objCmp(Atom obj) const
   {
    return Cmp(atom->element,obj.atom->element);
   }

  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( atom->element )
      Putobj(out,StrLen(atom->name.inner(2,1)));
    else
      Putobj(out,atom->name);
   }
 };

/* struct Element */

struct Element : CmpComparable<Element> , NoThrowFlagsBase
 {
  TypeDef::Element *element;
  
  explicit Element(TypeDef::Element *element_) : element(element_) {}
  
  // cmp objects
  
  CmpResult objCmp(Element obj) const
   {
    return Cmp(element->element,obj.element->element);
   }

  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( element->element<TypeDef::Element::AtomLim && element->element )
      {
       Putobj(out,StrLen(element->name.inner(2,1)));
      }
    else
      {
       Putobj(out,element->name);
      }
   }
 };

/* struct ASet */

struct ASet : CmpComparable<ASet> , NoThrowFlagsBase
 {
  RefArray<Atom> atoms; // sorted
  
  ASet() {}
  
  // cmp objects 
  
  CmpResult objCmp(const ASet &obj) const 
   {
    return RangeCmp(Range(atoms),Range(obj.atoms));
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,PrintSet(Range(atoms)));
   }
 };

/* struct ShiftFinal */

struct ShiftFinal : CmpComparable<ShiftFinal> , NoThrowFlagsBase
 {
  ASet aset;
  
  ShiftFinal() {}
  
  explicit ShiftFinal(const ASet &aset_) : aset(aset_) {}
  
  // cmp objects 
  
  CmpResult objCmp(const ShiftFinal &obj) const 
   { 
    return Cmp(aset,obj.aset);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,aset);
   }
 };

/* struct StateGroup */

struct StateGroup : NoThrowFlagsBase
 {
  struct Transition : CmpComparable<Transition> , NoThrowFlagsBase
   {
    TypeDef::Element *element;
    ulen group;
    
    Transition(TypeDef::Element *element_,ulen group_) : element(element_),group(group_) {}
    
    // cmp objects 
    
    CmpResult objCmp(Transition obj) const
     {
      return AlphaCmp(group,obj.group,element->element,obj.element->element);
     }
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#; -> #;)",Element(element),group);
     }
   };
  
  struct Track : NoThrowFlagsBase
   {
    ulen start;
    TypeDef::Rule *rule;
    RefArray<ulen> path;
    RefArray<TypeDef::State *> states;
    RefArray<TypeDef::Final *> finals;
    
    Track(ulen start,TypeDef::Rule *rule,const RefArray<ulen> &path,PtrLen<TypeDef::State *> states); 
    
    // print object
    
    template <class P>
    void print(P &out) const
     {
      Printf(out,"#;)",start);
      
      auto p=Range(path);
      
      for(auto *element : rule->args ) 
        {
         Printf(out," -> #; -> #;)",Element(element),*p);
         
         ++p;
        }
      
      if( finals.getLen()>1 )
        Printf(out,"\n  states = #; finals = #; #;",states.getLen(),finals.getLen(),rule->name);
      else
        Printf(out,"\n  states = #; #;",states.getLen(),rule->name);
     }
   };
  
  ulen group;
  RefArray<TypeDef::State *> states;
  RefArray<TypeDef::Final *> finals;
  RefArray<Transition> transitions;
  ShiftFinal shift;
  
  RefArray<Track> tracks;
  
  StateGroup() : group(0) {}
  
  void setTransitions(PtrLen<Transition> transitions);
  
  void build();
  
  void mapTransitions(PtrLen<ulen> ret);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( finals.getLen()>1 )
      Printf(out,"Group #;) states = #; finals = #;\n\n",group,states.getLen(),finals.getLen());
    else
      Printf(out,"Group #;) states = #;\n\n",group,states.getLen());
    
    for(auto &obj : transitions ) Printf(out,"#;\n",obj);
    
    Putch(out,'\n');
    
    Printf(out,"shift #;\n\n",shift);
    
    for(auto &obj : tracks ) Printf(out,"#;\n",obj);
   }
 };

/* class StateCompressor */

class StateCompressor : NoCopy
 {
   struct Fin : CmpComparable<Fin> , NoThrowFlagsBase
    {
     TypeDef::FinalIndex final;
     ShiftFinal shift;
     
     explicit Fin(const TypeDef::Final &final);
     
     // cmp objects
     
     CmpResult objCmp(const Fin &obj) const
      {
       return Cmp(shift,obj.shift);
      }
    };
  
   struct Map : NoThrowFlagsBase
    {
     DynArray<TypeDef::State *> transitions;
     ulen group;
     bool split_flag;
     bool flag;
     
     explicit Map(const TypeDef::State &state);
    };
   
   struct Group : NoThrowFlagsBase
    {
     ulen count[2];
     ulen next_group[2];
     
     void clean()
      {
       count[0]=0;
       count[1]=0;
      }
     
     bool needSplit() const
      {
       return count[0] && count[1] ;
      }
     
     void setBigSmall(ulen big,ulen small)
      {
       if( count[0]<count[1] )
         {
          next_group[0]=small;
          next_group[1]=big;
         }
       else
         {
          next_group[1]=small;
          next_group[0]=big;
         }
      }
     
     void set(ulen g0,ulen g1)
      {
       next_group[0]=g0;
       next_group[1]=g1;
      }
    };
  
   PtrLen<TypeDef::State> states;
   
   DynArray<ulen> shift_index;
   DynArray<ShiftFinal> shifts;
   DynArray<Map> maps;
   DynArray<Group> groups;
   
   ulen group_count;
   
  private:
   
   ulen initIndex(PtrLen<TypeDef::Final> finals);

   void setSplitFlags(ulen split);
   
   void setFlags(ulen element);
   
   void setCounts();
   
   void splitGroups(ulen split);
   
   void mapGroups();
   
   void checkGroups();
   
   void setGroup0(); 
   
  public:
  
   StateCompressor(PtrLen<TypeDef::Final> finals,PtrLen<TypeDef::State> states);
   
   ~StateCompressor() {}
   
   void run();
   
   void check();
   
   // result
   
   struct Result 
    {
     RefArray<StateGroup> state_groups;
     
     Result() {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"#;\n\n",Title("Large groups"));
       
       for(auto &sg : state_groups ) 
         {
          if( sg.finals.getLen()>1 )
            Printf(out,"#;\n\n",sg);
         }
       
       Printf(out,"#;\n\n",Title("Small groups"));
       
       for(auto &sg : state_groups ) 
         {
          if( sg.finals.getLen()<=1 )
            Printf(out,"#;\n\n",sg);
         }
      }
    };
   
   Result getResult(PtrLen<TypeDef::Rule> rules) const;
 };

} // namespace App

#endif

