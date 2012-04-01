/* SysAsyncFile.h */ 
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

#ifndef CCore_inc_sys_SysAsyncFile_h
#define CCore_inc_sys_SysAsyncFile_h
 
#include <CCore/inc/GenFile.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Packet.h>

namespace CCore {
namespace Sys {

/* classes */ 

struct AsyncFile;

class AsyncFileState;

struct AsyncFileDevice;

/* struct AsyncFile */ 

struct AsyncFile
 {
  // public
  
  struct OpenExt
   {
    PacketFormat write_format; // output
    ulen max_read_len;         // output
    
    FilePosType file_len;      // output
    
    FileError error;           // output
    
    // methods
    
    void setFileLen(FilePosType file_len_)
     {
      file_len=file_len_;
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      write_format=Nothing;
      max_read_len=0;
      file_len=0;
      error=error_;
     }
   };
   
  struct CloseExt
   {
    FileError error;           // output
    
    // methods
    
    void noError()
     {
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      error=error_;
     }
   };
   
  struct WriteExt
   {
    FilePosType file_len;      // output
    
    FileError error;           // output
    
    // methods
    
    void setFileLen(FilePosType file_len_)
     {
      file_len=file_len_;
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      file_len=0;
      error=error_;
     }
   };
   
  struct ReadExt
   {
    FilePosType off;           // input, preserved
    PtrLen<uint8> buf;         // input, preserved, read all
   
    FileError error;           // output
    
    // methods
    
    ReadExt(FilePosType off_,PtrLen<uint8> buf_) : off(off_),buf(buf_) {}
    
    void copyData(const uint8 *data)
     {
      buf.copy(data);
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      error=error_;
     }
   };
  
  struct ReadBufExt
   {
    FilePosType off;           // input, preserved
    ulen len;                  // input, preserved, read all
    
    const uint8 *data;         // output
    
    FileError error;           // output
    
    // methods
    
    ReadBufExt(FilePosType off_,ulen len_) : off(off_),len(len_) {}
    
    PtrLen<const uint8> getData() const { return Range(data,len); }
    
    void setData(const uint8 *data_)
     {
      data=data_;
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      data=0;
      error=error_;
     }
   };
   
  // private data
  
  AsyncFileState *file_state;
  FileOpenFlags oflags;
  
  // public
  
  void open(AsyncFileState *file_state_,FileOpenFlags oflags_) 
   { 
    file_state=file_state_;
    oflags=oflags_;
   }
  
  void open(Packet<uint8,OpenExt> packet,StrLen file_name,FileOpenFlags oflags);
  
   //
   // open is successfully finished, no pending operations, last operation
   //
 
  void close(Packet<uint8,CloseExt> packet,bool preserve_file=false);
  
   //
   // after close or open with error
   //
  
  void closeState();
  
   //
   // open is successfully finished
   //
  
  void write(Packet<uint8,WriteExt> packet,FilePosType off);
  
  void read(Packet<uint8,ReadExt> packet);
  
  void read(Packet<uint8,ReadBufExt> packet);
 };
 
/* class AsyncFileState */ 

class AsyncFileState : public MemBase_nocopy
 {
   ObjHook hook;
   
  protected:  
   
   PacketFormat write_format;
   ulen max_read_len;
   
  public: 
  
   explicit AsyncFileState(const ObjHook &hook_) : hook(hook_) {}
   
   virtual ~AsyncFileState() {}
   
   PacketFormat getWriteFormat() const { return write_format; }
   
   ulen getMaxReadLen() const { return max_read_len; }
   
   virtual void open(Packet<uint8,AsyncFile::OpenExt> packet,StrLen file_name,FileOpenFlags oflags)=0;
   
   virtual void close(Packet<uint8,AsyncFile::CloseExt> packet,bool preserve_file)=0;
   
   virtual void write(Packet<uint8,AsyncFile::WriteExt> packet,FilePosType off)=0;
   
   virtual void read(Packet<uint8,AsyncFile::ReadExt> packet)=0;
   
   virtual void read(Packet<uint8,AsyncFile::ReadBufExt> packet)=0;
 };
 
/* struct AsyncFileDevice */ 

struct AsyncFileDevice
 {
  virtual AsyncFileState * createState(const ObjHook &hook) noexcept(EnableNoExcept) =0;
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

