/* test0017.SpaceHeap.cpp */ 
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

#include <CCore/inc/MemSpaceHeap.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Counters.h>

namespace App {

namespace Private_0017 {

/* class Heap */

class Heap : NoCopy
 {
   class AllocSpace : public NoCopyBase<Space>
    {
     public:
     
      AllocSpace(ulen mem_len)
       {
        mem_len=AlignDown(mem_len);
 
        mem=MemAlloc(mem_len);
        len=mem_len;
       }
      
      ~AllocSpace()
       { 
        MemFree(mem); 
       }
    };
 
   AllocSpace space;
   RadixHeap<MemSpace> heap;
   
  private:
  
   void fail(const char *op,unsigned num)
    {
     Printf(Exception,"#; fail #;",op,num);
    }
  
   void check(const char *op)
    {
     if( unsigned num=RadixHeapBlock::Check(space.mem,space.len) ) fail(op,num);
    }
   
  public: 
  
   explicit Heap(ulen mem_len) : space(mem_len),heap(space) {}
   
   ~Heap() {}
   
   bool isEmpty() const { return heap.isEmpty(); }
   
   Space alloc(ulen len)
    {
     Space ret=heap.alloc(len);
     
     check("alloc"); 
     
     return ret; 
    }
  
   ulen getLen(const void *mem) { return heap.getLen(mem); }
  
   void free(void *mem)
    { 
     heap.free(mem); 
     
     check("free");
    }
  
   DeltaLen extend(void *mem,ulen len)
    { 
     DeltaLen ret=heap.extend(mem,len);
     
     check("extend");
     
     return ret; 
    }
  
   DeltaLen shrink(void *mem,ulen len)
    { 
     DeltaLen ret=heap.shrink(mem,len);
     
     check("shrink");
     
     return ret; 
    }
 };
 
/* struct Rec */

inline PtrLen<byte> ByteRange(Space space) { return Range(CastPtr(space.mem),space.len); }
 
struct Rec
 {
  Space space;
  byte fill;
  
  void init(Space space_,byte fill_)
   {
    space=space_;
    fill=fill_;
    
    ByteRange(space_).set(fill_);
   }
   
  void fail(unsigned num)
   {
    Printf(Exception,"fail #;",num);
   }
   
  void check(Heap &heap)
   {
    if( space.len!=heap.getLen(space.mem) ) fail(1);
   
    for(auto r=ByteRange(space); +r ;++r) if( *r!=fill ) fail(2);
   }
   
  bool extend(Heap &heap,ulen len)
   {
    DeltaLen result=heap.extend(space.mem,len);
    
    if( result.ok )
      {
       auto r=ByteRange(space);
    
       Range(r.ptr+r.len,result.delta).set(fill);
    
       space.len+=result.delta;
      
       return true;
      }
      
    return false;  
   }
   
  void shrink(Heap &heap,ulen len)
   {
    DeltaLen result=heap.shrink(space.mem,len);
   
    if( !result.ok ) fail(3);
    
    space.len-=result.delta;
   }
 };

/* enum Ops */
 
enum Ops
 {
  OpAlloc,
  OpAllocNoMem,
  OpFree,
  OpExtend,
  OpExtendDone,
  OpShrink,
  
  OpLim
 };
 
const char * GetTextDesc(Ops op)
 {
  static const char *const Table[OpLim]=
   {
    "alloc",
    "alloc nomem",
    "free",
    "extend",
    "extend done",
    "shrink"
   };
 
  return Table[op];
 }

/* class Engine */

class Engine : public MemBase_nocopy
 {
   static const ulen MemLen      = 64_MByte ;
   static const ulen Len         = 5000     ;
   static const ulen MaxAllocLen = 64_KByte ;

   Heap heap;
   Random random;
  
   Rec rec[Len];
   ulen rec_len;
   
   Counters<Ops,OpLim> stat;
   
  private:
  
   void check(Rec &rec)
    {
     rec.check(heap);
    }
  
   void alloc(ulen len)
    {
     Space space=heap.alloc(len);
        
     if( space.len )
       {
        rec[rec_len].init(space,random.next_uint<byte>());
        
        rec_len++;
        
        stat.count(OpAlloc);
       }
     else
       {
        stat.count(OpAllocNoMem);
       }  
    }
    
   void free(ulen ind)
    {
     heap.free(rec[ind].space.mem);
        
     if( ind<(--rec_len) ) rec[ind]=rec[rec_len];
     
     stat.count(OpFree);
    }
    
   void extend(Rec &rec)
    {
     ulen len=rec.space.len+random.select(0,rec.space.len/2);
     
     if( rec.extend(heap,len) ) stat.count(OpExtendDone);
       
     stat.count(OpExtend);  
    }
    
   void shrink(Rec &rec)
    {
     ulen len=random.select(0,rec.space.len);
     
     rec.shrink(heap,len);
     
     stat.count(OpShrink);
    }
    
   void clean()
    {
     while( rec_len )
       {
        ulen ind=rec_len-1;
        
        check(rec[ind]);
        free(ind);
       }
    }
    
   void showStat()
    {
     Printf(Con,"\n#15l;\n",stat);
    }
   
  public:
  
   Engine()
    : heap(MemLen),
      rec_len(0)
    {
    }
   
   ~Engine()
    {
     clean();
     
     showStat();
    }
    
   void step()
    {
     ulen ind=random.select(Len);
     
     if( ind<rec_len )
       {
        check(rec[ind]);
        
        switch( random.select(3) )
          {
           case 0 :
            {
             free(ind);
            }
           break;
           
           case 1 :
            {
             extend(rec[ind]);
            }
           break;
           
           case 2 :
            {
             shrink(rec[ind]);
            }
           break;
          }
       }
     else
       {
        alloc(random.select(0,MaxAllocLen));
       }  
    }
 };
   
} // namespace Private_0017
 
using namespace Private_0017; 
 
/* Testit<17> */ 

template<>
const char *const Testit<17>::Name="Test17 SpaceHeap";

template<>
bool Testit<17>::Main() 
 { 
  OwnPtr<Engine> engine(new Engine);
  
  for(ulen cnt=100000; cnt ;cnt--)
    {
     if( cnt%10000==0 ) Printf(Con,"cnt = #;\n",cnt);

     engine->step();
    }
   
  return true;
 }
 
} // namespace App
 
