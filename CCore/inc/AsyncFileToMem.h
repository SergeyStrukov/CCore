/* AsyncFileToMem.h */ 
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

#ifndef CCore_inc_AsyncFileToMem_h
#define CCore_inc_AsyncFileToMem_h
 
#include <CCore/inc/AsyncFile.h>
#include <CCore/inc/ToMemBase.h>

namespace CCore {

/* classes */ 

class AsyncFileToMem;

class AsyncFileListToMem;

/* class AsyncFileToMem */ 

class AsyncFileToMem : public ToMemBase
 {
  public:

   explicit AsyncFileToMem(StrLen file_name,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   ~AsyncFileToMem();
   
   // swap/move objects
   
   void objSwap(AsyncFileToMem &obj)
    {
     Swap<ToMemBase>(*this,obj);
    }
   
   explicit AsyncFileToMem(ToMoveCtor<AsyncFileToMem> obj) : ToMemBase(obj.cast<ToMemBase>()) {}
   
   AsyncFileToMem * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
 };
 
/* class AsyncFileListToMem */  

class AsyncFileListToMem : public ToMemBase
 {
   PtrLen<const uint8> data;
   
   PtrLen<const uint8> file_name;
   
   FileType file_type;
 
  private: 
  
   void build(AsyncFileSystem &fs,StrLen dev_path,ulen max_len,MSec timeout,ulen max_packets);
   
  public:

   explicit AsyncFileListToMem(StrLen path,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   AsyncFileListToMem(AsyncFileSystem &fs,StrLen dev_path,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   ~AsyncFileListToMem();
   
   bool next();
   
   StrLen getFileName() const { return Mutate<const char>(file_name); }
   
   FileType getFileType() const { return file_type; }
 };
 
} // namespace CCore
 
#endif
 

