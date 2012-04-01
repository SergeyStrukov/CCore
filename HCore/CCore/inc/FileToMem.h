/* FileToMem.h */ 
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

#ifndef CCore_inc_FileToMem_h
#define CCore_inc_FileToMem_h

#include <CCore/inc/ToMemBase.h>

#include <CCore/inc/sys/SysFile.h>

namespace CCore {

/* classes */ 

class RawFileToRead;

class FileToMem;

/* class RawFileToRead */ 

class RawFileToRead : NoCopy
 {
   Sys::File file;
 
  public:
  
   explicit RawFileToRead(StrLen file_name,FileOpenFlags oflags=Open_Read);
    
   ~RawFileToRead();
    
   FilePosType getLen();
    
   ulen read(uint8 *buf,ulen len); 
   
   void read_all(uint8 *buf,ulen len); 
 };
 
/* class FileToMem */ 

class FileToMem : public ToMemBase
 {
  public:

   explicit FileToMem(StrLen file_name,ulen max_len=MaxULen);

   ~FileToMem();
   
   // swap/move objects
   
   void objSwap(FileToMem &obj)
    {
     Swap<ToMemBase>(*this,obj);
    }
   
   explicit FileToMem(ToMoveCtor<FileToMem> obj) : ToMemBase(obj.cast<ToMemBase>()) {}
   
   FileToMem * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    }
 };
 
} // namespace CCore
 
#endif



