/* LangStateMachine.h */
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

#ifndef CondLangLR1_process_LangStateMachine_h
#define CondLangLR1_process_LangStateMachine_h

#include "lang/Lang.h"
#include "LangEstimate.h"
#include "LangDiagram.h"
#include "SparseMatrix.h"

#include <CCore/inc/List.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/NodeAllocator.h>

namespace App {

/* consts */

const ulen StateCap = 1000000 ;

/* functions */

void GuardStateCap();

/* classes */

template <class Estimate> class LangStateMachine;

/* class LangStateMachine<Estimate> */

template <class Estimate> 
class LangStateMachine : NoCopy
 {
   using Context = typename Estimate::Context ;
   
   using Matrix = SparseMatrix<Vertex,Estimate> ;
   
   using Vector = SparseVector<Vertex,Estimate> ;
   
   using Position = MatrixPosition<Vertex,Estimate> ;
   
   struct ArrowRec : NoThrowFlagsBaseFor<Position>
    {
     ArrowRec *next = 0 ;
     
     Position pos;
     
     template <class E>
     ArrowRec(const Arrow &arrow,const E &estimate) : pos(arrow.dst,arrow.src,estimate(arrow.beta)) {}
    };
   
   struct Head : NoCopy , NoThrowFlagsBase
    {
     ArrowRec *top = 0 ;
     ulen count = 0 ;
     
     Head() {}
     
     void ins(ArrowRec *ptr)
      {
       ptr->next=top;
       top=ptr;
       count++;
      }
     
     Matrix build()
      {
       typename Matrix::PosFill fill(count);
       
       for(ArrowRec *ptr=top; ptr ;ptr=ptr->next) 
         {
          fill.add(ptr->pos);
         }
       
       Matrix ret(fill);
       
       return ret;
      }
    };
   
   struct State : NoCopy
    {
     // links
     
     SLink<State> list_link;
     RBTreeLink<State,Vector> tree_link;
     
     // data
     
     ulen index;
     Estimate est;
     DynArray<State *> transitions;
     
     // methods
     
     State(ulen index_,ulen transition_count) : index(index_),transitions(transition_count) {}
     
     void complete(Vertex stop)
      {
       est=tree_link.key[stop];
      }
     
     const Vector & getVector() const { return tree_link.key; }
    };
   
   using ListAlgo = typename SLink<State>::template LinearAlgo<&State::list_link> ; 
   using TreeAlgo = typename RBTreeLink<State,Vector>::template Algo<&State::tree_link,const Vector &> ;
   
   using StateCur = typename ListAlgo::Cur ;
   
   class StateStorage : NoCopy
    {
      typename ListAlgo::FirstLast list;
      typename TreeAlgo::Root root;
      
      NodePoolAllocator<State> allocator;
      
      ulen transition_count;
      Vertex stop;
      
     public:
     
      StateStorage(ulen transition_count_,Vertex stop_) 
       : allocator(1000),
         transition_count(transition_count_),
         stop(stop_)
       {
       }
      
      ~StateStorage()
       {
        while( State *state=list.del_first() ) allocator.free_nonnull(state);
       }
      
      State * find_or_add(const Vector &vstate)
       {
        typename TreeAlgo::PrepareIns prepare(root,vstate);
        
        if( prepare.found ) return prepare.found;
        
        ulen index=allocator.getCount();
        
        if( index>=StateCap )
          {
           GuardStateCap();
          }
        
        State *ret=allocator.alloc(index,transition_count);
        
        prepare.complete(ret);
        
        list.ins_last(ret);
        
        ret->complete(stop);
        
        return ret;
       }
    
      ulen getCount() const { return allocator.getCount(); }
      
      StateCur getStart() const { return list.start(); }
    };
   
  public:
   
   struct StateDesc : NoCopy , NoThrowFlagsBase
    {
     ulen index;
     Estimate est;
     PtrLen<const StateDesc *> transitions;
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"#;) #;\n",index,est);
       
       for(auto *dst : transitions ) Printf(out,"  #3;",dst->index);
      }
    };
   
  private:
   
   DynArray<StateDesc> state_table;
   DynArray<const StateDesc *> transitions_buf;
 
  private:
 
   LangStateMachine(const Lang &lang,ulen atom_count,const Context &ctx);
 
  public:
 
   // constructors
   
   LangStateMachine(const Lang &lang,const Context &ctx) : LangStateMachine(lang,lang.getAtomCount(),ctx) {}
   
   LangStateMachine(const ExtLang &lang,const Context &ctx) : LangStateMachine(lang,lang.getOriginalAtomCount(),ctx) {}
   
   ~LangStateMachine();
   
   // description
   
   PtrLen<const StateDesc> getStateTable() const { return Range_const(state_table); }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Putobj(out,"-----\n");
     
     for(auto &state : getStateTable() )
       {
        Printf(out,"#;\n",state);
        Putobj(out,"-----\n");
       }
    }
 };

template <class Estimate> 
LangStateMachine<Estimate>::LangStateMachine(const Lang &lang,ulen atom_count,const Context &ctx)
 {
  //--------------------------------------------------------------------------
  
  TrackStage("Estimate lang");
  
  LangEstimate<Estimate> estimate(lang,ctx);

  LangDiagram diagram(lang);
  
  //--------------------------------------------------------------------------
  
  TrackStage("Build matrix");

  ulen count=LenAdd(atom_count,lang.getSyntCount());
  
  Matrix N;
  
  DynArray<Matrix> T(count);
  
  {
   Head headN;
   
   DynArray<Head> headT(count);
   
   auto arrows=diagram.getArrows();
   
   DynArray<ArrowRec> buf(DoReserve,arrows.len);
   
   for(auto &arrow : arrows )
     {
      ArrowRec *ptr=buf.append_fill(arrow,estimate);
     
      if( !arrow.alpha )
        {
         headN.ins(ptr);
        }
      else
        {
         arrow.alpha.apply( [&] (Atom atom) {
                                             ulen index=atom.getIndex();
                                             
                                             if( index<atom_count ) headT[index].ins(ptr); 
                                            } ,
           
                            [&] (Synt synt) { 
                                             headT[synt.getIndex()+atom_count].ins(ptr); 
                                            } 
                          );
        }
     }
   
   N=headN.build();
   
   for(ulen i=0; i<count ;i++) T[i]=headT[i].build();
  }
  
  //--------------------------------------------------------------------------
  
  TrackStage("Calculate matrix");
  
  Matrix F=N;
  
  {
   TrackStep track;
   
   for(;;)
     {
      Matrix X=F+F*F;
      
      if( F==X ) 
        {
         track.finish();
        
         break;
        }
     
      F=X;
      
      track.step();
     }
  }
  
  {
   for(Matrix &X : T ) X=X+F*X;
  }
  
  Vector S;
  
  {
   auto range=diagram.getStart();
   
   DynArray<typename Vector::Cell> buf(DoReserve,range.len);
   
   for(; +range ;++range) buf.append_fill(*range,Estimate(ElementOne)); 
   
   S=Vector(Range_const(buf));
  }
  
  {
   S=S+F*S;
  }
  
  //--------------------------------------------------------------------------
  
  TrackStage("Calculate states");
  
  StateStorage storage(count,diagram.getStop());
  
  TrackStep track;
  
  for(StateCur cur(storage.find_or_add(S)); +cur ;++cur)
    {
     const Vector &V=cur->getVector();
     
     for(ulen i=0; i<count ;i++)
       {
        State *dst=storage.find_or_add(T[i]*V);
        
        cur->transitions[i]=dst;
       }
     
     track.step();
    }
  
  track.finish();
  
  //--------------------------------------------------------------------------
  
  ulen state_count=storage.getCount();
  
  DynArray<StateDesc> state_table(state_count);
  DynArray<const StateDesc *> transitions_buf(LenOf(count,state_count));
  
  auto tbuf=Range(transitions_buf);
  
  for(StateCur cur(storage.getStart()); +cur ;++cur)
    {
     ulen index=cur->index;
     
     auto &desc=state_table[index];
     
     desc.index=index;
     desc.est=cur->est;
     desc.transitions=tbuf.part(index*count,count);
     
     for(ulen i=0; i<count ;i++)
       {
        ulen dst=cur->transitions[i]->index;
        
        desc.transitions[i]=state_table.getPtr()+dst;
       }
    }
  
  Swap(state_table,this->state_table);
  Swap(transitions_buf,this->transitions_buf);
 }

template <class Estimate> 
LangStateMachine<Estimate>::~LangStateMachine() 
 {
 }

} // namespace App

#endif

