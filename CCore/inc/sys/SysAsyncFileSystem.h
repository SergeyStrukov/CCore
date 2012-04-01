/* SysAsyncFileSystem.h */ 
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

#ifndef CCore_inc_SysAsyncFileSystem_h
#define CCore_inc_SysAsyncFileSystem_h
 
#include <CCore/inc/sys/SysAsyncFile.h>

namespace CCore {
namespace Sys {

/* classes */ 

struct AsyncFileSystem;

struct AsyncFileSystemDevice;

/* struct AsyncFileSystem */ 

struct AsyncFileSystem
 {
  // public
  
  struct FileTypeExt
   {
    FileType file_type;         // output
    
    FileError error;            // output
    
    // methods
    
    void setFileType(FileType file_type_)
     {
      file_type=file_type_;
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      file_type=FileType_none;
      error=error_;
     }
   };
 
  struct ErrorExt
   {
    FileError error;            // output
    
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
 
  struct FileExt
   {
    AsyncFileState *file_state; // output
    
    FilePosType file_len;       // output
    
    FileError error;            // output
    
    // methods
    
    void setFileLen(FilePosType file_len_)
     {
      file_len=file_len_;
      error=FileError_Ok;
     }
    
    void setError(FileError error_)
     {
      file_state=0;
      file_len=0;
      error=error_;
     }
   };
 
  // private data
  
  struct State : NoCopy
   {
    ObjHook hook;
    
    explicit State(StrLen dev_name) : hook(JustTry,dev_name) {}
    
    operator AsyncFileSystemDevice * () { return hook.cast<AsyncFileSystemDevice>(); }
   };
   
  InitStorage<sizeof (State)> storage;
  State *state;
  AsyncFileSystemDevice *dev;
  
  // public
  
  FileError init(StrLen dev_name);
  
  void exit();
  
  void getFileType(Packet<uint8,FileTypeExt> packet,StrLen path);
  
  void getFileList(Packet<uint8,FileExt> packet,StrLen dir_name);
  
  void createFile(Packet<uint8,ErrorExt> packet,StrLen file_name);
  
  void deleteFile(Packet<uint8,ErrorExt> packet,StrLen file_name);
  
  void createDir(Packet<uint8,ErrorExt> packet,StrLen dir_name);
  
  void deleteDir(Packet<uint8,ErrorExt> packet,StrLen dir_name,bool recursive);
  
  void rename(Packet<uint8,ErrorExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite);
  
  void remove(Packet<uint8,ErrorExt> packet,StrLen path);
  
  void exec(Packet<uint8,ErrorExt> packet,StrLen dir,StrLen program,StrLen arg);
  
  void exec2(Packet<uint8,FileExt> packet,StrLen dir,StrLen program);
 };
 
/* struct AsyncFileSystemDevice */  

struct AsyncFileSystemDevice
 {
  virtual void getFileType(Packet<uint8,AsyncFileSystem::FileTypeExt> packet,StrLen path)=0;
  
  virtual void getFileList(ObjHook &hook,Packet<uint8,AsyncFileSystem::FileExt> packet,StrLen dir_name)=0;
  
  virtual void createFile(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen file_name)=0;
  
  virtual void deleteFile(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen file_name)=0;
  
  virtual void createDir(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen dir_name)=0;
  
  virtual void deleteDir(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen dir_name,bool recursive)=0;
  
  virtual void rename(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite)=0;
  
  virtual void remove(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen path)=0;
  
  virtual void exec(Packet<uint8,AsyncFileSystem::ErrorExt> packet,StrLen dir,StrLen program,StrLen arg)=0;
  
  virtual void exec2(ObjHook &hook,Packet<uint8,AsyncFileSystem::FileExt> packet,StrLen dir,StrLen program)=0;
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

