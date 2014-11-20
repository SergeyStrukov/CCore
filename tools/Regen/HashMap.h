/* HashMap.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Regen_HashMap_h
#define Regen_HashMap_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Cmp.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

struct HashBase;

template <class T> class HashMap;

/* struct HashBase */

struct HashBase
 {
  static const ulen KeyLim = ulen(1)<<16 ;
 
  static ulen Key(StrLen str);
 };

/* class HashMap<T> */

template <class T> 
class HashMap : NoCopy , HashBase
 {
   struct Data
    {
     ulen key;
     StrLen str;
     T obj;
     
     Data(StrLen str_,const T &obj_) : key(Key(str_)),str(str_),obj(obj_) {}
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = NoThrowFlags<T>::Copy_no_throw
      };
    };
   
   Collector<Data> data;
   
   struct Rec
    {
     StrLen str;
     T obj;
     
     Rec() : str(),obj() {}
     
     void set(const Data &d) { str=d.str; obj=d.obj; }
     
     friend bool operator < (const Rec &a,const Rec &b)
      {
       return StrLess(a.str,b.str);
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = NoThrowFlags<T>::Default_no_throw,
       Copy_no_throw = NoThrowFlags<T>::Copy_no_throw
      };
    };
   
   DynArray<Rec> pool;
  
   struct Frame
    {
     ulen off;
     ulen count;
     
     Frame() : off(0),count(0) {}
     
     void setOff(ulen &lim)
      {
       off=lim;
       lim+=count;
      }

     void put(Rec *base,const Data &d)
      {
       base[off++].set(d);
      }
     
     template <class Func> 
     bool complete(Rec *base,Func func) 
      {
       if( !count ) return true;
       
       off-=count;
       
       if( count==1 ) return true;
       
       base+=off;
       
       Sort(base,count);
       
       bool ret=true;
       
       for(ulen cnt=count-1; cnt ;cnt--,base++)
         if( !( base[0] < base[1] ) )
           {
            func(base[0].str,base[0].obj,base[1].obj);
            
            ret=false;
           }
       
       return ret;
      }
     
     PtrLen<const Rec> get(const Rec *base) const
      {
       return Range(base+off,count);
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
   
   DynArray<Frame> frames;
   
   bool ok;
   
  public:
   
   HashMap() : ok(false) {}
   
   ~HashMap() {}
   
   // build
   
   void add(StrLen str,const T &obj)
    {
     data.append_fill(str,obj);
    }
   
   template <class Func> 
   bool complete(Func func); // func(str,obj1,obj2); 
   
   // use
   
   struct Result
    {
     T obj;
     bool found;

     Result(NothingType) : obj(),found(false) {}
 
     Result(const T &obj_) : obj(obj_),found(true) {}
    };
   
   static Result Find(PtrLen<const Rec> range,StrLen str)
    {
     while( ulen off=range.len/2 )
       {
        switch( StrCmp(str,range[off].str) )
          {
           case CmpLess :
            {
             range=range.prefix(off);
            }
           break;
           
           case CmpGreater :
            {
             range=range.part(off+1);
            }
           break;
           
           default: // case CmpEqual :
            {
             return range[off].obj;
            }
          }
       }
     
     if( range.len==1 )
       {
        if( range[0].str.equal(str) ) return range[0].obj;
        
        return Nothing;
       }
     
     return Nothing;
    }
   
   Result find(StrLen str) const
    {
     if( !ok ) return Nothing;
     
     return Find(frames[Key(str)].get(pool.getPtr()),str);
    }
 };

template <class T> 
template <class Func> 
bool HashMap<T>::complete(Func func) 
 {
  ok=false;
  
  pool.erase();
  frames.erase();
  
  DynArray<Data> temp;
  
  data.extractTo(temp);
  
  pool.extend_default(temp.getLen());
  frames.extend_default(KeyLim);
  
  for(const Data &d : temp) frames[d.key].count++;
  
  ulen lim=0;

  for(Frame &f : frames) f.setOff(lim);
  
  for(const Data &d : temp) frames[d.key].put(pool.getPtr(),d);
  
  bool ret=true;
  
  for(Frame &f : frames) if( !f.complete(pool.getPtr(),func) ) ret=false;
  
  return ok=ret; 
 }

} // namespace App
 
#endif
