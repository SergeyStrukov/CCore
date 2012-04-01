/* test1001.PageHeap.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/MemPageHeap.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Counters.h>

#include <CCore/inc/sys/SysMemPage.h>

namespace App {

namespace Private_1001 {

/* class Heap */ 

class Heap : NoCopy
 {
   RadixHeap<MemPage> heap;
   
  public: 
  
   Heap() : heap(Sys::MemPageLen) {}
   
   ~Heap() {}
   
   bool isEmpty() const { return heap.isEmpty(); }
   
   Space alloc(ulen len) 
    {
     Space ret=heap.alloc(len);
     
     // 1
     
     return ret; 
    }
  
   ulen getLen(const void *mem) 
    {
     ulen ret=heap.getLen(mem);
     
     // 2
     
     return ret; 
    }
  
   void free(void *mem) 
    { 
     heap.free(mem);
     
     // 3
    }
  
   DeltaLen extend(void *mem,ulen len) 
    { 
     DeltaLen ret=heap.extend(mem,len);
     
     // 4
     
     return ret; 
    }
  
   DeltaLen shrink(void *mem,ulen len) 
    { 
     DeltaLen ret=heap.shrink(mem,len);
     
     // 5
     
     return ret; 
    }
 };

/* struct Rec */ 
 
inline PtrLen<byte> ByteRange(Space mem) { return Range(CastPtr(mem.mem),mem.len); }
 
struct Rec
 {
  Space mem;
  byte fill;
  
  void init(Space mem_,byte fill_)
   {
    mem=mem_;
    fill=fill_;
    
    ByteRange(mem_).set(fill_);
   }
   
  void fail(unsigned num) 
   {
    Printf(Exception,"fail #;",num);
   }
   
  void check(Heap &heap)
   {
    if( mem.len!=heap.getLen(mem.mem) ) fail(1);
   
    for(auto r=ByteRange(mem); +r ;++r) if( *r!=fill ) fail(2);
   }
   
  bool extend(Heap &heap,ulen len) 
   {
    DeltaLen result=heap.extend(mem.mem,len);
    
    if( result.ok )
      {
       auto r=ByteRange(mem);
    
       Range(r.ptr+r.len,result.delta).set(fill);
    
       mem.len+=result.delta;
      
       return true;
      }
      
    return false;  
   }
   
  void shrink(Heap &heap,ulen len) 
   {
    DeltaLen result=heap.shrink(mem.mem,len);
   
    if( !result.ok ) fail(3);
    
    mem.len-=result.delta;
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
  static const char *const Table[]=
   {
    "alloc",
    "alloc nomem",
    "free",
    "extend",
    "extend done",
    "shrink",
    
    ""
   };
 
  return Table[op];
 }

/* class Engine */

class Engine : public MemBase
 {
   static const ulen Len         = 5000     ;
   static const ulen MaxAllocLen = 80_KByte ;

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
     Space mem=heap.alloc(len);
        
     if( mem.len )
       {
        rec[rec_len].init(mem,random.next_uint<byte>());
        
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
     heap.free(rec[ind].mem.mem);
     
     rec_len--;
        
     if( ind<rec_len ) rec[ind]=rec[rec_len];
     
     stat.count(OpFree);
    }
    
   void extend(Rec &rec) 
    {
     ulen len=random.select(rec.mem.len,rec.mem.len+rec.mem.len/2);
     
     if( rec.extend(heap,len) ) stat.count(OpExtendDone);
       
     stat.count(OpExtend);  
    }
    
   void shrink(Rec &rec) 
    {
     ulen len=random.select(0,rec.mem.len);
     
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
    : rec_len(0)
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
   
} // namespace Private_1001
 
using namespace Private_1001; 
 
/* Testit<1001> */ 

template<>
const char *const Testit<1001>::Name="Test1001 PageHeap";

template<>
bool Testit<1001>::Main() 
 { 
  OwnPtr<Engine> engine(new Engine);
  
  for(ulen cnt=1000000; cnt ;cnt--)
    {
     if( cnt%10000==0 ) Printf(Con,"cnt = #;\n",cnt);

     engine->step();
    }
   
  return true;
 }
 
} // namespace App
 
