/* Info.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Info_h
#define CCore_inc_video_Info_h
 
#include <CCore/inc/String.h>

#include <CCore/inc/task/Atomic.h>

namespace CCore {
namespace Video {

/* classes */

struct AbstractInfo;

class InfoBase;

class Info;

class InfoFromString;

/* struct AbstractInfo */

struct AbstractInfo
 {
  virtual ulen getLineCount() const =0;
  
  virtual StrLen getLine(ulen index) const =0;
 };

/* class InfoBase */

class InfoBase : public MemBase_nocopy , public AbstractInfo
 {
   Atomic refs;
 
  public:
 
   InfoBase() { refs=1; }
 
   virtual ~InfoBase() {}
  
   void incRef() { refs++; }
  
   bool decRef() { return (refs--)==1; }
  
   void destroy() { delete this; }
 };

/* class Info */

class Info
 {
   RefPtr<InfoBase> ptr;
  
  protected:
  
   explicit Info(InfoBase *info) : ptr(info) {}
  
  public:
  
   Info();
   
   ~Info() {}
  
   AbstractInfo * operator -> () const { return ptr.getPtr(); }
 };

/* class InfoFromString */

class InfoFromString : public Info
 {
   class Impl : public InfoBase
    {
      DynArray<String> buf;
      
     private:
      
      static StrLen CutLine(StrLen &str); 
      
     public:
     
      explicit Impl(StrLen str);
      
      virtual ~Impl();
      
      // AbstractInfo
      
      virtual ulen getLineCount() const;
      
      virtual StrLen getLine(ulen index) const;
    };
  
  public:
  
   explicit InfoFromString(StrLen str);
   
   ~InfoFromString();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

