/* HFSBase.h */ 
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

#ifndef CCore_inc_net_HFSBase_h
#define CCore_inc_net_HFSBase_h

#include <CCore/inc/net/PTPExtra.h>
 
namespace CCore {
namespace Net {
namespace HFS {

/* using */ 

using namespace PTP;

/* types */  

typedef uint64 FileLenType;

/* consts */ 

const ulen MaxPathLen    =  512 ;
const ulen DeltaReadLen  =   24 ;
const ulen MaxReadLen    = 1416 ;
const ulen DeltaWriteLen =   40 ;
const ulen MaxWriteLen   = 1400 ;
  
const ServiceIdType ServiceId = 2 ;
  
const FunctionIdType FunctionId_Open        =  1 ;
const FunctionIdType FunctionId_Read        =  2 ;
const FunctionIdType FunctionId_Write       =  3 ;
const FunctionIdType FunctionId_Close       =  4 ;
const FunctionIdType FunctionId_GetFileType =  5 ;
const FunctionIdType FunctionId_GetFileList =  6 ;
const FunctionIdType FunctionId_CreateFile  =  7 ;
const FunctionIdType FunctionId_DeleteFile  =  8 ;
const FunctionIdType FunctionId_CreateDir   =  9 ;
const FunctionIdType FunctionId_DeleteDir   = 10 ;
const FunctionIdType FunctionId_Rename      = 11 ;
const FunctionIdType FunctionId_Remove      = 12 ;
const FunctionIdType FunctionId_Exec        = 13 ;
const FunctionIdType FunctionId_Exec2       = 14 ;
  
const FlagType OpenFlag_Read       = 0x01 ;
const FlagType OpenFlag_Write      = 0x02 ;
const FlagType OpenFlag_Create     = 0x10 ;
const FlagType OpenFlag_Erase      = 0x20 ;
const FlagType OpenFlag_New        = 0x40 ;
const FlagType OpenFlag_AutoDelete = 0x80 ;
   
const FlagType FileType_none = 0 ;
const FlagType FileType_file = 1 ;
const FlagType FileType_dir  = 2 ;
 
const ErrorIdType ErrorBase = 100 ;

/* classes */  

struct FileId;

struct OpenInput;
struct OpenOutput;

struct ReadInput;
struct ReadOutput;

struct WriteInput;
struct WriteOutput;

struct CloseInput;
typedef Empty CloseOutput;

struct PathInput;

typedef PathInput GetFileTypeInput;
struct GetFileTypeOutput;

typedef PathInput GetFileListInput;
struct GetFileListOutput;

typedef PathInput CreateFileInput;
typedef Empty CreateFileOutput;

typedef PathInput DeleteFileInput;
typedef Empty DeleteFileOutput;

typedef PathInput CreateDirInput;
typedef Empty CreateDirOutput;

struct DeleteDirInput;
typedef Empty DeleteDirOutput;

struct SaveLoadPath;

struct RenameInput;
typedef Empty RenameOutput;

typedef PathInput RemoveInput;
typedef Empty RemoveOutput;

struct ExecInput;
typedef Empty ExecOutput; 

struct Exec2Input;
struct Exec2Output;

/* struct FileId */ 

struct FileId
 {
  uint32 slot;
  uint64 number;
  uint64 clock;
  
  // constructors
  
  FileId() : slot(),number(),clock() {}
  
  // methods
  
  friend bool operator == (const FileId &a,const FileId &b)
   { 
    return a.slot==b.slot && a.number==b.number && a.clock==b.clock ;
   }
  
  friend bool operator != (const FileId &a,const FileId &b) { return !(a==b); }
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<uint32,uint64,uint64>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(slot,number,clock);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(slot,number,clock);
   }
 };
 
/* struct OpenInput */ 

struct OpenInput // + uint8 path[len];
 {
  static const ulen MaxLen = MaxPathLen ;
 
  FlagType open_flags;
  LenType len;
  
  // constructors
  
  OpenInput() : open_flags(),len() {}
  
  OpenInput(FlagType open_flags_,LenType len_) : open_flags(open_flags_),len(len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FlagType,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(open_flags,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(open_flags,len);
   }
 };
 
/* struct OpenOutput */  
 
struct OpenOutput
 {
  FileId file_id;
  FileLenType file_len;
  
  // constructors
  
  OpenOutput() : file_id(),file_len() {}
  
  OpenOutput(const FileId &file_id_,FileLenType file_len_) : file_id(file_id_),file_len(file_len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
 };
 
/* struct ReadInput */ 
 
struct ReadInput
 {
  FileId file_id;
  FileLenType off;
  LenType len;

  // constructors
  
  ReadInput() : file_id(),off(),len() {}
  
  ReadInput(const FileId &file_id_,FileLenType off_,LenType len_) : file_id(file_id_),off(off_),len(len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType,LenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
 };
 
/* struct ReadOutput */ 

struct ReadOutput // + uint8 data[len];
 {
  static const ulen MaxLen = MaxReadLen ;
  
  FileLenType off;
  LenType len;
  
  // constructors
  
  ReadOutput() : off(),len() {}
  
  ReadOutput(FileLenType off_,LenType len_) : off(off_),len(len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileLenType,LenType>::SaveLoadLen }; 
   
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(off,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(off,len);
   }
 };
 
/* struct WriteInput */ 

struct WriteInput // + uint8 data[len];
 {
  static const ulen MaxLen = MaxWriteLen ;
  
  FileId file_id;
  FileLenType off;
  LenType len;
  
  // constructors
  
  WriteInput() : file_id(),off(),len() {}
  
  WriteInput(const FileId &file_id_,FileLenType off_,LenType len_) : file_id(file_id_),off(off_),len(len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType,LenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
 };
 
/* struct WriteOutput */ 

struct WriteOutput
 {
  FileLenType file_len;
  
  // constructors
  
  WriteOutput() : file_len() {}
  
  explicit WriteOutput(FileLenType file_len_) : file_len(file_len_) {}
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileLenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_len);
   }
 };
 
/* struct CloseInput */ 
 
struct CloseInput
 {
  BoolType preserve_file;
  FileId file_id;
  
  // constructors
  
  CloseInput() : preserve_file(),file_id() {}
  
  CloseInput(BoolType preserve_file_,const FileId &file_id_) : preserve_file(preserve_file_),file_id(file_id_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<BoolType,FileId>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(preserve_file,file_id);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(preserve_file,file_id);
   }
 };
 
/* struct PathInput */ 

struct PathInput // + uint8 path[len];
 {
  static const ulen MaxLen = MaxPathLen ;
 
  LenType len;
  
  // constructors
  
  PathInput() : len() {}
  
  explicit PathInput(LenType len_) : len(len_) {}
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<LenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };
 
/* struct GetFileTypeOutput */ 

struct GetFileTypeOutput
 {
  FlagType type;
  
  // constructors
  
  GetFileTypeOutput() : type() {}
  
  explicit GetFileTypeOutput(FlagType type_) : type(type_) {}
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FlagType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(type);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(type);
   }
 };
 
/* struct GetFileListOutput */ 

struct GetFileListOutput
 {
  FileId file_id;
  FileLenType file_len;
  
  // constructors
  
  GetFileListOutput() : file_id(),file_len() {}
  
  GetFileListOutput(const FileId &file_id_,FileLenType file_len_) : file_id(file_id_),file_len(file_len_) {}
   
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
 };
 
/* struct DeleteDirInput */ 

struct DeleteDirInput // + uint8 path[len];
 {
  static const ulen MaxLen = MaxPathLen ;
 
  BoolType recursive;
  LenType len;
  
  // constructors
  
  DeleteDirInput() : recursive(),len() {}
  
  DeleteDirInput(BoolType recursive_,LenType len_) : recursive(recursive_),len(len_) {}
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<BoolType,LenType>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(recursive,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(recursive,len);
   }
 };
 
/* struct SaveLoadPath */ 

struct SaveLoadPath
 {
  PtrLen<const uint8> path;
  
  // constructors
  
  SaveLoadPath() : path() {}
  
  explicit SaveLoadPath(PtrLen<const uint8> path_) : path(path_) {}
  
  // save/load object
   
  template <class Dev>
  void save(Dev &dev) const
   {
    LenType len=LenType(path.len);
    
    dev.template use<BeOrder>(len);
    
    dev.put(path);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    LenType len=0;
    
    dev.template use<BeOrder>(len);
    
    if( len>MaxPathLen )
      dev.fail(); 
    else
      path=dev.getRange(len);
   }
 };
 
/* struct RenameInput */ 

struct RenameInput
 {
  BoolType allow_overwrite;
  SaveLoadPath old_path;
  SaveLoadPath new_path;
  
  // constructors
  
  RenameInput() : allow_overwrite(),old_path(),new_path() {}
  
  RenameInput(bool allow_overwrite_,PtrLen<const uint8> old_path_,PtrLen<const uint8> new_path_)
   : allow_overwrite(allow_overwrite_),old_path(old_path_),new_path(new_path_) {}
  
  // save/load object
   
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(allow_overwrite,old_path,new_path);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(allow_overwrite,old_path,new_path);
   }
 };
 
/* struct ExecInput */ 

struct ExecInput
 {
  SaveLoadPath dir;
  SaveLoadPath program;
  SaveLoadPath arg;
  
  // constructors
  
  ExecInput() : dir(),program(),arg() {}
  
  ExecInput(PtrLen<const uint8> dir_,PtrLen<const uint8> program_,PtrLen<const uint8> arg_)
   : dir(dir_),program(program_),arg(arg_) {}
   
  // save/load object
   
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(dir,program,arg);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(dir,program,arg);
   }
 };
 
/* struct Exec2Input */ 

struct Exec2Input
 {
  SaveLoadPath dir;
  SaveLoadPath program;
  
  // constructors
  
  Exec2Input() : dir(),program() {}
  
  Exec2Input(PtrLen<const uint8> dir_,PtrLen<const uint8> program_) : dir(dir_),program(program_) {}
   
  // save/load object
   
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(dir,program);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(dir,program);
   }
 };
 
/* struct Exec2Output */ 

struct Exec2Output
 {
  FileId file_id;
  
  // constructors
  
  Exec2Output() : file_id() {}
  
  explicit Exec2Output(const FileId &file_id_) : file_id(file_id_) {}
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<FileId>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(file_id);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(file_id);
   }
 };
  
} // namespace HFS
} // namespace Net
} // namespace CCore
 
#endif
 

