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
#include <CCore/inc/Cmp.h>
#include <CCore/inc/PrintSet.h>

#include "DataMap.h" 

namespace App {

/* consts */

const ulen NoGroup = ulen(-1) ;

/* functions */

RefArray<TypeDef::Final *> BuildFinals(PtrLen<TypeDef::State *const> states);

/* classes */

struct Atom;

struct Element;

struct ASet;

struct ShiftFinal;

struct StateGroup;

class StateCompressor;

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
  
  ASet() : atoms(DoReserve,100) {}
  
  void sort();
  
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
  
  ulen group;
  RefArray<TypeDef::State *> states;
  RefArray<TypeDef::Final *> finals;
  RefArray<Transition> transitions;
  ShiftFinal shift;
  
  StateGroup() : group(0),states(DoReserve,100) {}
  
  void setTransitions(PtrLen<Transition> transitions);
  
  void build();
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( finals.getLen()>1 )
      Printf(out,"Group #;) states = #; finals = #;\n\n",group,states.getLen(),finals.getLen());
    else
      Printf(out,"Group #;) states = #;\n\n",group,states.getLen());
    
    for(auto *state : states ) Printf(out,"#; ",state->state);
    
    Putobj(out,"\n\n");
    
    for(auto &obj : transitions ) 
      {
       Printf(out,"#;\n",obj);
       
       for(auto *state : states )
         {
          for(auto t : state->transitions )
            if( t.element->element==obj.element->element )
              Printf(out,"  #;) -> #;)\n",state->state,t.state->state);
         }
      }
    
    Putch(out,'\n');
    
    Printf(out,"shift #;\n\n",shift);
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
   
   void initIndex(PtrLen<TypeDef::Final> finals);

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
   
   Result getResult() const;
 };

} // namespace App

#endif

