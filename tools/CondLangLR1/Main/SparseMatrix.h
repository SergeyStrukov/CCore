/* SparseMatrix.h */
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

#ifndef CondLangLR1_SparseMatrix_h
#define CondLangLR1_SparseMatrix_h

#include "Set.h"

#include <CCore/inc/algon/BinarySearch.h>
#include <CCore/inc/algon/SortUnique.h>

namespace App {

/* functions */

template <class I,class T>
const T * FindIndex(I index,PtrLen<const IndexPair<I,T> > range)
 {
  Algon::BinarySearch_if(range, [=] (const IndexPair<I,T> &obj) { return index<=obj.index; } );
  
  if( +range && index==range->index ) return &range->object;
  
  return 0;    
 }

/* classes */ 

template <class I,class T,class Row,class Cell> class MatrixMulBuilder;

template <class I,class T> struct MatrixPosition;

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
 : array(DoReserve,1024)
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
           {
            T prod=ma*p->object;
            
            if( +prod ) array.append_fill(p->index,prod);
           } 
       
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
     
     auto result=fill.getResult();
     
     if( +result )
       {
        new(guard.at()) Row(p->index,Set<Cell,Joiner>(result));
     
        ++guard;
       }
    }
 
  return guard.disarm();  
 }

/* struct MatrixPosition<I,T> */

template <class I,class T> 
struct MatrixPosition : CmpComparable<MatrixPosition<I,T> > , NoThrowFlagsBaseFor<I,T>
 {
  I i;
  I j;
  T object;
  
  // constuctors
  
  MatrixPosition() : i(),j(),object() {}
  
  // cmp objects
  
  CmpResult objCmp(const MatrixPosition<I,T> &obj) const 
   { 
    return AlphaCmp(i,obj.i,j,obj.j);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;) #;",i,j,object);
   }
 };

/* class SparseMatrix<I,T> */ 

template <class I,class T>
class SparseMatrix : public CmpComparable<SparseMatrix<I,T> > , public NoThrowFlagsBase
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
   
   explicit SparseMatrix(MonotonicFill &fill);
   
   ~SparseMatrix() {}
   
   // methods
   
   PtrLen<const Row> getRowset() const { return rowset.read(); }
   
   PtrLen<const Cell> findRow(I i) const
    {
     auto ptr=FindIndex(i,rowset.read());
     
     if( ptr ) return ptr->read();
     
     return Nothing;    
    }
   
   const T * findCell(I i,I j) const
    {
     return FindIndex(j,findRow(i));
    }
   
   // cmp objects
   
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

   // print object
   
   template <class P>
   void print(P &out) const
    {
     for(auto &row : rowset.read() )
       {
        Printf(out,"#; -----\n",row.index);
        
        for(auto &cell : row.object.read() ) Printf(out,"  #; #;\n",cell.index,cell.object);
       }
     
     Printf(out,"-----\n");
    }
 };

/* class SparseMatrix<I,T>::MonotonicFill */
    
template <class I,class T>
class SparseMatrix<I,T>::MonotonicFill : NoCopy
 {
   using Pos = MatrixPosition<I,T> ;
  
   DynArray<Pos> buf;
   DynArray<PtrLen<const Pos> > rows;
   
  private: 
      
   class RowBuilder
    {
      PtrLen<const Pos> row;
      
     private:
      
      static T SumOf(PtrLen<const Pos> range)
       {
        T ret(range->object);
        
        for(++range; +range ;++range) ret=ret+(range->object);
         
        return ret; 
       }
      
     public:
     
      explicit RowBuilder(PtrLen<const Pos> row_) : row(row_) {}
      
      ulen getLen() const { return row.len; }
      
      PtrLen<Cell> operator () (Place<void> place) const
       {
        typename ArrayAlgo<Cell>::BuildGuard guard(place);
        
        Algon::ApplyUniqueRangeBy(row, [] (const Pos &pos) { return pos.j; } ,
                                       [&] (PtrLen<const Pos> toadd) 
                                           { 
                                            new(guard.at()) Cell(toadd->j,RowBuilder::SumOf(toadd));
                                            
                                            ++guard;
                                           } 
                                 );
        
        return guard.disarm();  
       }
    };
   
   class Builder
    {
      PtrLen<const PtrLen<const Pos> > rows;
      
     public:
      
      explicit Builder(PtrLen<const PtrLen<const Pos> > rows_) : rows(rows_) {}
     
      ulen getLen() const { return rows.len; }
        
      PtrLen<Row> operator () (Place<void> place) const
       {
        typename ArrayAlgo<Row>::CreateGuard guard(place,getLen());
        
        for(auto p=rows; +p ;++p,++guard) new(guard.at()) Row((*p)->i,Set<Cell,Joiner>(DoBuild,RowBuilder(*p)));
          
        return guard.disarm();  
       }
    };
    
   void complete()
    {
     rows.erase();
     
     auto range=Range(buf);
     
     Sort(range);
     
     Algon::ApplyUniqueRangeBy(range, [] (const Pos &pos) { return pos.i; } , 
                                      [this] (PtrLen<Pos> row) { rows.append_copy(Range_const(row)); } );
    }
   
  public:
     
   explicit MonotonicFill(ulen capacity) : buf(DoReserve,capacity) {}
   
   ~MonotonicFill() {}
      
   void add(const Pos &pos) { if( +pos.object ) buf.append_copy(pos); }
   
   Builder getBuilder()
    {
     complete();
     
     return Builder(Range_const(rows));
    }
 };
    
template <class I,class T>
SparseMatrix<I,T>::SparseMatrix(MonotonicFill &fill) : rowset(DoBuild,fill.getBuilder()) {}

} // namespace App

#endif

