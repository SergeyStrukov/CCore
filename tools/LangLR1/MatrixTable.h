/* MatrixTable.h */
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

#ifndef LangLR1_MatrixTable_h
#define LangLR1_MatrixTable_h

#include "Estimator.h"
#include "SparseMatrix.h"

namespace App {

/* classes */

template <class T> class MatrixTable;

/* class MatrixTable<T> */

template <class T> 
class MatrixTable : public Estimator<T> 
 {
  public:
   
   typedef SparseMatrix<VIndex,T> Matrix;
   
   typedef typename Matrix::MonotonicFill Fill;

  private:
   
   const Punct &punct;
  
   DynArray<Matrix> table;
   
  private:
   
   T buildExpr(PtrLen<const NTRIndex> expr) const;
   
   T buildExpr(PtrLen<const DynArray<NTRIndex> > expr) const;
   
   Matrix buildMatrix(PtrLen<const Punct::Rec> data);

  public:
   
   explicit MatrixTable(const Punct &punct);
   
   ~MatrixTable() {}
   
   using Estimator<T>::get;

   const Matrix & getMatrix(AlphaIndex a) const { return table[a]; }
 };

template <class T> 
T MatrixTable<T>::buildExpr(PtrLen<const NTRIndex> expr) const
 {
  if( +expr )
    {
     T ret=get(*expr);
     
     for(++expr; +expr ;++expr) ret=ret*get(*expr);
     
     return ret;
    }
  else
    {
     return T(true);
    }
 }

template <class T> 
T MatrixTable<T>::buildExpr(PtrLen<const DynArray<NTRIndex> > expr) const
 {
  if( +expr )
    {
     T ret=buildExpr(Range(*expr));
     
     for(++expr; +expr ;++expr) ret=ret+buildExpr(Range(*expr));

     return ret;
    }
  else
    {
     return T(false);
    }
 }

template <class T> 
auto MatrixTable<T>::buildMatrix(PtrLen<const Punct::Rec> data) -> Matrix
 {
  Fill fill(data.len);
  
  for(ulen ind=0; +data ;++data,++ind)
    {
     fill.set(ind,data->dst,data->src,buildExpr(Range(data->expr)));
    }
  
  fill.complete();
  
  return Matrix(fill);
 }

template <class T> 
MatrixTable<T>::MatrixTable(const Punct &punct_)
 : Estimator<T>(punct_.getLang()),
   punct(punct_),
   table(punct.getAlphaIndexLim())
 {
  for(auto p=punct.getAlphaRange(); +p ;++p) table[*p]=buildMatrix(punct.getData(*p));
 }

} // namespace App

#endif


