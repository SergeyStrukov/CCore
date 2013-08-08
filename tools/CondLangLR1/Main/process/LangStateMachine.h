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

namespace App {

/* classes */

template <class Estimate> class LangStateMachine;

/* class LangStateMachine<Estimate> */

template <class Estimate> 
class LangStateMachine : NoCopy
 {
   using Context = typename Estimate::Context ;
   
   using Matrix = SparseMatrix<Vertex,Estimate> ;
   
   using Position = MatrixPosition<Vertex,Estimate> ;
   
   struct ArrowRec : NoThrowFlagsBaseFor<Position>
    {
     ArrowRec *next = 0 ;
     
     Position pos;
     
     ArrowRec() {}
     
     template <class E>
     void set(const Arrow &arrow,const E &estimate)
      {
       pos.i=arrow.dst;
       pos.j=arrow.src;
       pos.object=estimate(arrow.beta);
      }
    };
   
   struct Head : NoThrowFlagsBase
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
       typename Matrix::MonotonicFill fill(count);
       
       for(ArrowRec *ptr=top; ptr ;ptr=ptr->next) 
         {
          // Printf(Con,"#;\n",ptr->pos);
         
          fill.add(ptr->pos);
         }
       
       Matrix ret(fill);
       
       // Printf(Con,"\n#;\n",ret);
       
       return ret;
      }
    };
 
  private:
 
   LangStateMachine(const Lang &lang,ulen atom_count,const Context &ctx);
 
  public:
 
   LangStateMachine(const Lang &lang,const Context &ctx) : LangStateMachine(lang,lang.getAtomCount(),ctx) {}
   
   LangStateMachine(const ExtLang &lang,const Context &ctx) : LangStateMachine(lang,lang.getOriginalAtomCount(),ctx) {}
   
   ~LangStateMachine();
 };

template <class Estimate> 
LangStateMachine<Estimate>::LangStateMachine(const Lang &lang,ulen atom_count,const Context &ctx)
 {
  //--------------------------------------------------------------------------
  
  Printf(Con,"Estimate lang\n");
  
  LangEstimate<Estimate> estimate(lang,ctx);

  LangDiagram diagram(lang);
  
    //Printf(Con,"#;\n",diagram);
  
  //--------------------------------------------------------------------------
  
  Printf(Con,"Build matrix\n");

  ulen count=LenAdd(atom_count,lang.getSyntCount());
  
  Matrix N;
  
  DynArray<Matrix> T(count);
  
  {
   Head headN;
   
   DynArray<Head> headT(count);
   
   auto arrows=diagram.getArrows();
   
   DynArray<ArrowRec> buf(arrows.len);
   
   ArrowRec *ptr=buf.getPtr();
   
   for(auto &arrow : arrows )
     {
      ptr->set(arrow,estimate);
      
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
      
      ++ptr;
     }
   
   N=headN.build();
   
   for(ulen i=0; i<count ;i++) T[i]=headT[i].build();
  }
  
  //--------------------------------------------------------------------------
  
  Printf(Con,"Calculate matrix\n");
  
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
  
  //--------------------------------------------------------------------------
  
  
 }

template <class Estimate> 
LangStateMachine<Estimate>::~LangStateMachine() 
 {
 }

} // namespace App

#endif

