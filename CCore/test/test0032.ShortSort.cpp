/* test0032.ShortSort.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_0032 {

/* consts */

const ulen Count = 1000000 ;

/* class Engine */

class Engine
 {
   typedef unsigned Type; 
 
   Random random;
   
  private:
  
   Type next() { return random.select(100,200); }
  
   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) *(ptr++)=next();
    }
 
   bool sort(Type *ptr,ulen len)
    {
     return ShortSort<Type *>::Sort(ptr,len);
    }
    
   void test(const Type *ptr,ulen len)
    {
     for(; len>1 ;len--,ptr++)
       if( ptr[0] > ptr[1] )
         Printf(Exception,"test failed");
    } 
    
   void show(const Type *ptr,ulen len) 
    {
     Printf(Con,"#;\n",PrintSet(Range(ptr,len)));
    }
   
  public:
  
   Engine() {}
   
   ~Engine() {}
   
   bool run(ulen len)
    {
     Printf(Con,"len = #;\n",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();

     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);
        
        if( cnt==Count ) show(ptr,len);
        
        if( !sort(ptr,len) ) return false;
        
        if( cnt==Count ) show(ptr,len);
        
        test(ptr,len);
       }
       
     return true;   
    }
 };
 
/* class IndexEngine */

class IndexEngine
 {
   typedef unsigned Type; 
   typedef int IndexType; 
 
   Random random;
   
  private:
  
   Type next() { return random.next_uint<unsigned>(); }
  
   void fill(Type *ptr,IndexType *ind,ulen len)
    {
     IndexType i=0;
    
     for(; len ;len--) 
       {
        *(ptr++)=next();
        *(ind++)=(i++);
       }
    }
 
   bool sort(const Type *ptr,IndexType *ind,ulen len)
    {
     return ShortSort<IndexType *,SortIndexCtx<const Type> >::Sort(ind,len,ptr);
    }
    
   void test(const Type *ptr,const IndexType *ind,ulen len)
    {
     for(; len>1 ;len--,ind++)
       if( ptr[ind[0]]>ptr[ind[1]] )
         Printf(Exception,"test failed");
    } 
   
  public:
  
   IndexEngine() {}
   
   ~IndexEngine() {}
   
   bool run(ulen len)
    {
     Printf(Con,"len = #;\n",len);
    
     SimpleArray<Type> a(len);
     SimpleArray<IndexType> b(len);
     
     Type *ptr=a.getPtr();
     IndexType *ind=b.getPtr();

     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,ind,len);
        
        if( !sort(ptr,ind,len) ) return false;
        
        test(ptr,ind,len);
       }
       
     return true;   
    }
 };
 
} // namespace Private_0032
 
using namespace Private_0032; 
 
/* Testit<32> */ 

template<>
const char *const Testit<32>::Name="Test32 ShortSort";

template<>
bool Testit<32>::Main() 
 { 
  {
   Engine engine;
  
   for(ulen len=0; engine.run(len) ;len++);
  } 
 
  {
   IndexEngine engine;
  
   for(ulen len=0; engine.run(len) ;len++);
  } 
 
  return true;
 }
 
} // namespace App
 
