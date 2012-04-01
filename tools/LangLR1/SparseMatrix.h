/* SparseMatrix.h */ 
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

#ifndef LangLR1_SparseMatrix_h
#define LangLR1_SparseMatrix_h

#include "Set.h"

namespace App {

/* functions */

template <class T,class I,class R>
T * FindIndex(I i,R p)
 {
  for(; +p ;++p)
    switch( Cmp(i,p->index) )
      {
       case CmpLess : return 0;
       
       case CmpEqual : return &p->object;
      }
      
  return 0;    
 }

/* classes */ 

template <class I,class T,class Row,class Cell> class MatrixMulBuilder;

template <class I,class T> class SparseMatrix;

/* class MatrixMulBuilder<I,T,Row,Cell> */ 

template <class I,class T,class Row,class Cell> 
class MatrixMulBuilder
 {
   PtrLen<const Row> a;
   PtrLen<const Row> b;
   
  private: 
   
   class FillRow : NoCopy
    {
      DynArray<Cell> array;
       
      PtrLen<Cell> result;
      
     private: 
  
      static Cell * Join(Cell *out,PtrLen<Cell> a,PtrLen<Cell> b);
      
      static PtrLen<Cell> Sort(Cell *buf,Cell *spare,ulen len);
    
     public:
        
      FillRow(PtrLen<const Cell> a,PtrLen<const Row> b);
      
      ~FillRow() {}
         
      PtrLen<const Cell> getResult() const { return Range_const(result); }
    };
    
  public:
     
   MatrixMulBuilder(PtrLen<const Row> a_,PtrLen<const Row> b_) : a(a_),b(b_) {}
      
   ulen getLen() const { return a.len; }
      
   PtrLen<Row> operator () (Place<void> place) const;
 };
 
template <class I,class T,class Row,class Cell> 
Cell * MatrixMulBuilder<I,T,Row,Cell>::FillRow::Join(Cell *out,PtrLen<Cell> a,PtrLen<Cell> b)
 {
  while( +a && +b )
    switch( (*a).weakCmp(*b) )
      {
       case CmpLess : 
        {
         *(out++)=*a; 
         
         ++a; 
        }
       break;
       
       case CmpGreater :
        {
         *(out++)=*b; 
         
         ++b;
        }
       break; 
        
       default: // case CmpEqual 
        {
         *(out++)=(*a).join(*b); 
         
         ++a; 
         ++b;
        }
      }
      
  for(; +a ;++a) *(out++)=*a; 

  if( b.ptr!=out )  
    for(; +b ;++b) *(out++)=*b; 
  else
    out=b.ptr+b.len;
    
  return out;  
 }

template <class I,class T,class Row,class Cell> 
PtrLen<Cell> MatrixMulBuilder<I,T,Row,Cell>::FillRow::Sort(Cell *buf,Cell *spare,ulen len)
 {
  if( len<2 ) return Range(buf,len);
    
  ulen len2=len/2;
  ulen len1=len-len2;  
  
  PtrLen<Cell> ret1=Sort(buf,spare,len1);
  PtrLen<Cell> ret2=Sort(buf+len1,spare+len1,len2);
  
  Cell *out=(ret1.ptr==buf)?spare:buf;
  Cell *lim=Join(out,ret1,ret2);
  
  return Range(out,lim);
 }

template <class I,class T,class Row,class Cell> 
MatrixMulBuilder<I,T,Row,Cell>::FillRow::FillRow(PtrLen<const Cell> a,PtrLen<const Row> b)
 {
  for(; +a && +b ;)
    switch( Cmp(a->index,b->index) )
      {
       case CmpLess :
        {
         ++a;
        }
       break;
       
       case CmpGreater :
        {
         ++b;
        }
       break;
       
       default: // case CmpEqual
        {
         T ma=a->object;
        
         for(auto p=b->object.read(); +p ;++p)
           array.append_fill(p->index,ma*p->object);
       
         ++a;
         ++b;
        }
    }

  ulen len=array.getLen();
  
  array.extend_default(len);
  
  result=Sort(array.getPtr(),array.getPtr()+len,len);
 }
         
template <class I,class T,class Row,class Cell> 
PtrLen<Row> MatrixMulBuilder<I,T,Row,Cell>::operator () (Place<void> place) const
 {
  typename ArrayAlgo<Row>::BuildGuard guard(place);
  
  for(auto p=a; +p ;++p)
    {
     FillRow fill(p->object.read(),b);
     
     Set<Cell,Joiner> set(fill.getResult());

     if( set.nonEmpty() )
       {
        new(guard.at()) Row(p->index,set);
     
        ++guard;
       }
    }
 
  return guard.disarm();  
 }
      
/* class SparseMatrix<I,T> */ 

template <class I,class T>
class SparseMatrix : public CmpComparable<SparseMatrix<I,T> >
 {
  public:
   
   typedef IndexPair<I,T> Cell;
    
   typedef IndexPair<I,Set<Cell,Joiner> > Row;
   
  private: 
   
   Set<Row,Joiner> rowset;
   
  private: 
   
   explicit SparseMatrix(const Set<Row,Joiner> &rowset_) : rowset(rowset_) {}
 
   template <class Builder>
   SparseMatrix(DoBuildType,Builder builder) : rowset(DoBuild,builder) {}
      
  public:
   
   // constructors
  
   class MonotonicFill;
    
   SparseMatrix() {}
   
   explicit SparseMatrix(const MonotonicFill &fill);
   
   ~SparseMatrix() {}
   
   // methods
   
   bool isEmpty() const { return rowset.isEmpty(); }
   
   bool nonEmpty() const { return rowset.nonEmpty(); }
   
   PtrLen<const Row> getRowset() const { return rowset.read(); }
   
   PtrLen<const Cell> findRow(I i) const
    {
     auto ptr=FindIndex<const Set<Cell,Joiner> >(i,rowset.read());
     
     if( ptr ) return ptr->read();
     
     return Nothing;    
    }
   
   const T * findCell(I i,I j) const
    {
     return FindIndex<const T>(j,findRow(i));
    }
   
   CmpResult objCmp(const SparseMatrix<I,T> &obj) const
    {
     return rowset.objCmp(obj.rowset);
    }
   
   // operators
   
   friend SparseMatrix<I,T> operator + (const SparseMatrix<I,T> &a,const SparseMatrix<I,T> &b)
    {
     return SparseMatrix<I,T>(a.rowset+b.rowset);
    }
    
   friend SparseMatrix<I,T> operator * (const SparseMatrix<I,T> &a,const SparseMatrix<I,T> &b)
    {
     return SparseMatrix<I,T>(DoBuild,MatrixMulBuilder<I,T,Row,Cell>(a.rowset.read(),b.rowset.read()));
    }
    
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

 // class SparseMatrix<I,T>::MonotonicFill
    
template <class I,class T>
class SparseMatrix<I,T>::MonotonicFill : NoCopy
 {
   struct Rec
    {
     I i;
     I j;
     T object;
     
     Rec() : i(),j(),object() {}
     
     void set(const I &i_,const I &j_,const T &object_)
      {
       i=i_;
       j=j_;
       object=object_;
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = NoThrowFlags<I>::Default_no_throw && NoThrowFlags<T>::Default_no_throw ,
       Copy_no_throw = NoThrowFlags<I>::Default_no_throw && NoThrowFlags<T>::Default_no_throw
      };
    };
    
   DynArray<Rec> buf;
   DynArray<PtrLen<const Rec> > rows;
   
  private: 
      
   class RowBuilder
    {
      PtrLen<const Rec> row;
      
     public:
     
      explicit RowBuilder(PtrLen<const Rec> row_) : row(row_) {}
      
      ulen getLen() const { return row.len; }
      
      PtrLen<Cell> operator () (Place<void> place) const
       {
        typename ArrayAlgo<Cell>::template CreateGuardNoThrow<NoThrowFlags<Cell>::Copy_no_throw> guard(place,getLen());
        
        for(auto p=row; +p ;++p,++guard) new(guard.at()) Cell(p->j,p->object);
             
        return guard.disarm();  
       }
    };
   
   class Builder
    {
      PtrLen<const PtrLen<const Rec> > rows;
      
     public:
      
      explicit Builder(PtrLen<const PtrLen<const Rec> > rows_) : rows(rows_) {}
     
      ulen getLen() const { return rows.len; }
        
      PtrLen<Row> operator () (Place<void> place) const;
    };
    
  public:
     
   explicit MonotonicFill(ulen len) : buf(len) {}
   
   ~MonotonicFill() {}
      
   void set(ulen ind,const I &i,const I &j,const T &object) { buf[ind].set(i,j,object); }
   
   void complete();
   
   Builder getBuilder() const { return Builder(Range(rows)); }
 };
    
template <class I,class T>
PtrLen<typename SparseMatrix<I,T>::Row> SparseMatrix<I,T>::MonotonicFill::Builder::operator () (Place<void> place) const
 {
  typename ArrayAlgo<Row>::CreateGuard guard(place,getLen());
  
  for(auto p=rows; +p ;++p,++guard) new(guard.at()) Row((*p)->i,Set<Cell,Joiner>(DoBuild,RowBuilder(*p)));
    
  return guard.disarm();  
 }
      
template <class I,class T>
void SparseMatrix<I,T>::MonotonicFill::complete()
 {
  auto data=Range_const(buf);
  
  while( +data )
    {
     I i=data->i;
     
     auto p=data;
     
     for(++p; +p && p->i==i ;++p);
     
     rows.append_copy(data.prefix(p));
     
     data=p;
    }
 }

template <class I,class T>
SparseMatrix<I,T>::SparseMatrix(const MonotonicFill &fill) : rowset(DoBuild,fill.getBuilder()) {}

} // namespace App

#endif

