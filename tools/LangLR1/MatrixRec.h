/* MatrixRec.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_MatrixRec_h
#define LangLR1_MatrixRec_h

#include "LR1Estimate.h"
#include "SparseMatrix.h"
#include "Punct.h"

namespace App {

/* types */ 

typedef LR1<TIndex,RIndex,RIndexShift> Estimate;

typedef SparseMatrix<VIndex,Estimate> EMatrix;

typedef Estimate::Rec StateFinal;

typedef Estimate::BetaSet FinalSet;

typedef IndexPair<AlphaIndex,ulen> StateTransition;

typedef Set<StateTransition,Joiner> TransitionSet;

/* classes */

class PrintEstimate;

class PrintEMatrix;

class PrintFinalSet;

class MatrixRec;

class MatrixRecSet; 

/* class PrintEstimate */

class PrintEstimate
 {
   const Punct &punct;
   const Estimate &obj;
   
  public: 
  
   PrintEstimate(const Punct &punct_,const Estimate &obj_) : punct(punct_),obj(obj_) {}
  
   class PrintBeta
    {
      const Punct &punct;
      PtrLen<const Estimate::Rec> beta;
     
     public: 
      
      PrintBeta(const Punct &punct_,PtrLen<const Estimate::Rec> beta_) : punct(punct_),beta(beta_) {}
     
      template <class P>
      void print(P &out) const
       {
        auto p=beta;
        
        if( +p )
          {
           Printf(out,"( #; #;",punct.getTextDesc(p->index),punct.printStr(p->object.read()));
           
           for(++p; +p ;++p) Printf(out," , #; #;",punct.getTextDesc(p->index),punct.printStr(p->object.read()));
           
           Putobj(out," )");
          }
        else
          {
           Putobj(out,"( )");
          }
       }
    };
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"(#;,#;,#;,#;)",obj.getEmpty(),obj.getNull(),punct.printStr(obj.getAlpha().read()),PrintBeta(punct,obj.getBeta().read()));
    }
 };

/* class PrintEMatrix */

class PrintEMatrix
 {
   const Punct &punct;
   const EMatrix &obj;
  
  public:
  
   PrintEMatrix(const Punct &punct_,const EMatrix &obj_) : punct(punct_),obj(obj_) {}
  
   template <class P>
   void print(P &out) const
    {
     Putobj(out,"\n {\n");
     
     for(auto p=obj.getRowset(); +p ;++p)
       {
        Printf(out,"  #; : \n   {\n",punct.getTextDesc(p->index));
        
        for(auto q=p->object.read(); +q ;++q)
          Printf(out,"    #; : #;\n",punct.getTextDesc(q->index),PrintEstimate(punct,q->object));
 
        Putobj(out,"   }\n");
       }
       
     Putobj(out," }\n");  
    }
 };

/* class PrintFinalSet */

class PrintFinalSet
 {
   const Punct &punct;
   const FinalSet &obj;
   ulen number;
   
  public:
   
   PrintFinalSet(const Punct &punct_,const FinalSet &obj_,ulen number_) : punct(punct_),obj(obj_),number(number_) {}
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"\nFinal #;\n {\n",number);
     
     for(auto p=obj.read(); +p ;++p)       
       Printf(out,"  #; -> #;\n",punct.getTextDesc(p->index),punct.printStr(p->object.read()));
       
     Putobj(out," }\n");
    }
 };

/* class MatrixRec */ 

class MatrixRec : public MemBase_nocopy
 {
   bool number_flag;
   ulen number;
   
   RBTreeLink<MatrixRec,EMatrix> link;
   
   FinalSet finals;
   
  private: 

   static void GuardNoNumber();
   
   friend class MatrixRecSet;
   
  public:
  
   explicit MatrixRec(const EMatrix &state) 
    : number_flag(false),
      number(0)
    {
     if( const Estimate *ptr=state.findCell(VIndexFinish,VIndexStart) ) finals=ptr->getBeta();
    }
   
   bool setNumber(ulen number_)
    {
     if( number_flag ) return false;
     
     number=number_;
     
     return number_flag=true;
    }
    
   ulen getNumber() const 
    {
     if( !number_flag ) GuardNoNumber();
    
     return number;
    }
   
   const EMatrix & getMatrix() const { return link.key; }
   
   const FinalSet & getFinals() const { return finals; }
 };

/* class MatrixRecSet */

class MatrixRecSet : NoCopy
 {
   typedef RBTreeLink<MatrixRec,EMatrix>::Algo<&MatrixRec::link,const EMatrix &> Algo;
  
   Algo::Root root;
   
  private:
   
   static void Destroy(MatrixRec *rec);
  
  public: 
   
   MatrixRecSet() {}
   
   ~MatrixRecSet() { Destroy(root.root); }
   
   MatrixRec & find_or_add(const EMatrix &M);
 };

} // namespace App

#endif

