/* FileName.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_FileName_h
#define CCore_inc_FileName_h

#include <CCore/inc/TextTools.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Path.h>
 
namespace CCore {

/* classes */

class FileName;

/* class FileName */

class FileName : NoCopy
 {
   DynArray<char> buf;
   ulen off;
   bool ok;
   
  private:
   
   static bool IsRooted(StrLen name)
    {
     return name.len && PathBase::IsSlash(name[0]) ;
    }
   
   struct PathUp;
   
   class Out;
   
   void setAbs(StrLen file_name,SplitPath split_dev,SplitPathName split_file);
  
   void setRel(StrLen path,SplitPathName split_file);
   
  public: 
   
   // constructors
  
   FileName() : off(0),ok(false) {}
   
   FileName(NothingType) : FileName() {}
  
   explicit FileName(StrLen file_name);
  
   FileName(StrLen path,StrLen file_name);
   
   ~FileName() {}
   
   // methods
   
   bool operator + () const { return ok; }
   
   bool operator ! () const { return !ok; }
  
   StrLen getStr() const { return Range(buf); }
  
   StrLen getPath() const { return getStr().prefix(off); }
   
   StrLen getFile() const { return getStr().part(off); }
   
   template <class P>
   void printPos(P &out,TextPos pos) { Putobj(out,getFile(),pos); }
  
   // swap/move objects
  
   void objSwap(FileName &obj)
    {
     Swap(buf,obj.buf);
     Swap(off,obj.off);
     Swap(ok,obj.ok);
    }
   
   explicit FileName(ToMoveCtor<FileName> obj)
    : buf(ObjToMove(obj->buf)),
      off(obj->off),
      ok(obj->ok)
    {
    }
   
   FileName * objMove(Place<void> place)
    {
     return CtorMove(this,place);
    }
 };

} // namespace CCore
 
#endif
 

