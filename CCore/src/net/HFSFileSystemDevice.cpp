/* HFSFileSystemDevice.cpp */ 
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
 
#include <CCore/inc/net/HFSFileSystemDevice.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace HFS {

/* class FileSystemDevice */ 

bool FileSystemDevice::attach_state(ObjHook &hook,Packet<uint8,Sys::AsyncFileSystem::FileExt> packet)
 {
  auto ext=packet.getExt();
  
  if( FileState *state=new(JustTry) FileState(hook,dev) )
    {
     ext->file_state=state;
    
     return true;
    }
  else
    {
     ext->setError(FileError_SysOverload);
     
     packet.complete();
    
     return false;
    }  
 }
 
void FileSystemDevice::CompleteFile(Sys::AsyncFileSystem::FileExt *ext2,const FileId &file_id,FileLenType file_len)
 {
  FileState *state=static_cast<FileState *>(ext2->file_state);
  
  state->file_id=file_id;
  
  ext2->setFileLen(file_len);
 }
 
void FileSystemDevice::CompleteFile(Sys::AsyncFileSystem::FileExt *ext2,FileError fe)
 {
  delete ext2->file_state;
  
  ext2->setError(fe);
 }

void FileSystemDevice::complete_getFileType(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFileSystem::FileTypeExt,GetFileTypeExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->isOk() )
    {
     ext2->setFileType(FileType(ext->type));
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_OpFault));
    }
  
  packet.popExt().complete();
 }
 
void FileSystemDevice::complete_getFileList(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFileSystem::FileExt,GetFileListExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->isOk() )
    {
     CompleteFile(ext2,ext->file_id,ext->file_len);
    }
  else
    {
     CompleteFile(ext2,MakeError(ext,FileError_OpFault));
    }
  
  packet.popExt().complete();
 }
 
void FileSystemDevice::complete_exec2(PacketHeader *packet_) 
 {
  Packet<uint8,Sys::AsyncFileSystem::FileExt,Exec2Ext> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->isOk() )
    {
     CompleteFile(ext2,ext->file_id,0);
    }
  else
    {
     CompleteFile(ext2,MakeError(ext,FileError_OpFault));
    }
  
  packet.popExt().complete();
 }
 
FileSystemDevice::FileSystemDevice(StrLen hfs_dev_name)
 : hook(hfs_dev_name),
   dev(hook)
 {
 }
   
FileSystemDevice::~FileSystemDevice()
 {
 }
   
Sys::AsyncFileState * FileSystemDevice::createState(const ObjHook &hook) noexcept(EnableNoExcept)
 {
  return new(JustTry) FileState(hook,dev);
 }
 
void FileSystemDevice::getFileType(Packet<uint8,Sys::AsyncFileSystem::FileTypeExt> packet,StrLen path)
 {
  Packet<uint8,Sys::AsyncFileSystem::FileTypeExt,GetFileTypeExt> packet2=packet.pushExt<GetFileTypeExt>();
  
  packet2.pushCompleteFunction(function_complete_getFileType());

  dev->getFileType(packet2.forgetExt<1>(),path);
 }
  
void FileSystemDevice::getFileList(ObjHook &hook,Packet<uint8,Sys::AsyncFileSystem::FileExt> packet,StrLen path)
 {
  if( !attach_state(hook,packet) ) return;
  
  Packet<uint8,Sys::AsyncFileSystem::FileExt,GetFileListExt> packet2=packet.pushExt<GetFileListExt>();
  
  packet2.pushCompleteFunction(function_complete_getFileList());

  dev->getFileList(packet2.forgetExt<1>(),path);
 }
  
void FileSystemDevice::createFile(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen file_name)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,CreateFileExt> packet2=packet.pushExt<CreateFileExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<CreateFileExt>());

  dev->createFile(packet2.forgetExt<1>(),file_name);
 }
  
void FileSystemDevice::deleteFile(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen file_name)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,DeleteFileExt> packet2=packet.pushExt<DeleteFileExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<DeleteFileExt>());

  dev->deleteFile(packet2.forgetExt<1>(),file_name);
 }
  
void FileSystemDevice::createDir(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen dir_name)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,CreateDirExt> packet2=packet.pushExt<CreateDirExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<CreateDirExt>());

  dev->createDir(packet2.forgetExt<1>(),dir_name);
 }
  
void FileSystemDevice::deleteDir(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen dir_name,bool recursive)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,DeleteDirExt> packet2=packet.pushExt<DeleteDirExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<DeleteDirExt>());

  dev->deleteDir(packet2.forgetExt<1>(),dir_name,recursive);
 }
  
void FileSystemDevice::rename(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,RenameExt> packet2=packet.pushExt<RenameExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<RenameExt>());

  dev->rename(packet2.forgetExt<1>(),old_path,new_path,allow_overwrite);
 }
  
void FileSystemDevice::remove(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen path)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,RemoveExt> packet2=packet.pushExt<RemoveExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<RemoveExt>());

  dev->remove(packet2.forgetExt<1>(),path);
 }
  
void FileSystemDevice::exec(Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet,StrLen dir,StrLen program,StrLen arg)
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt,ExecExt> packet2=packet.pushExt<ExecExt>();
  
  packet2.pushCompleteFunction(function_complete_ext<ExecExt>());

  dev->exec(packet2.forgetExt<1>(),dir,program,arg);
 }
  
void FileSystemDevice::exec2(ObjHook &hook,Packet<uint8,Sys::AsyncFileSystem::FileExt> packet,StrLen dir,StrLen program)
 {
  if( !attach_state(hook,packet) ) return;
  
  Packet<uint8,Sys::AsyncFileSystem::FileExt,Exec2Ext> packet2=packet.pushExt<Exec2Ext>();
  
  packet2.pushCompleteFunction(function_complete_exec2());

  dev->exec2(packet2.forgetExt<1>(),dir,program);
 }
   
/* class FileSystemDevice::FileState */ 

void FileSystemDevice::FileState::complete_open(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::OpenExt,OpenExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->isOk() )
    {
     file_id=ext->file_id;
     
     ext2->setFileLen(ext->file_len);
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_OpenFault));
    }
  
  packet.popExt().complete();
 }
   
void FileSystemDevice::FileState::complete_close(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::CloseExt,CloseExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->isOk() )
    {
     ext2->noError();
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_CloseFault));
    }
  
  packet.popExt().complete();
 }
 
void FileSystemDevice::FileState::complete_write(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt,WriteExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();

  if( ext->isOk() )
    {
     ext2->setFileLen(ext->file_len);
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_WriteFault));
    }  
  
  packet.popExt().complete();
 }
 
void FileSystemDevice::FileState::complete_read(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::ReadExt,ReadExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();

  if( ext->isOk() )
    {
     if( ext->off==ext2->off )
       {
        if( ext->data.len==ext2->buf.len )
          {
           ext2->copyData(ext->data.ptr);
          }
        else
          {
           ext2->setError(FileError_ReadLenMismatch);
          }
       }
     else
       {
        ext2->setError(FileError_BadPosition);
       }
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_ReadFault));
    }  
  
  packet.popExt().complete();
 }
 
void FileSystemDevice::FileState::complete_readbuf(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::ReadBufExt,ReadExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();

  if( ext->isOk() )
    {
     if( ext->off==ext2->off )
       {
        if( ext->data.len==ext2->len )
          {
           ext2->setData(ext->data.ptr);
          }
        else
          {
           ext2->setError(FileError_ReadLenMismatch);
          }
       }
     else
       {
        ext2->setError(FileError_BadPosition);
       }
    }
  else
    {
     ext2->setError(MakeError(ext,FileError_ReadFault));
    }  
  
  packet.popExt().complete();
 }
 
FileSystemDevice::FileState::FileState(const ObjHook &hook,ClientDevice *dev_)
 : AsyncFileState(hook),
   dev(dev_)
 {
  write_format=dev->getWriteFormat();
  max_read_len=dev->getMaxReadLen();
 }
   
FileSystemDevice::FileState::~FileState()
 {
 }
   
void FileSystemDevice::FileState::open(Packet<uint8,Sys::AsyncFile::OpenExt> packet,StrLen file_name,FileOpenFlags oflags)
 {
  Packet<uint8,Sys::AsyncFile::OpenExt,OpenExt> packet2=packet.pushExt<OpenExt>();
  
  packet2.pushCompleteFunction(function_complete_open());
  
  dev->open(packet2.forgetExt<1>(),file_name,oflags);
 }
   
void FileSystemDevice::FileState::close(Packet<uint8,Sys::AsyncFile::CloseExt> packet,bool preserve_file)
 {
  Packet<uint8,Sys::AsyncFile::CloseExt,CloseExt> packet2=packet.pushExt<CloseExt>();

  packet2.pushCompleteFunction(function_complete_close());
  
  dev->close(packet2.forgetExt<1>(),file_id,preserve_file);
 }
   
void FileSystemDevice::FileState::write(Packet<uint8,Sys::AsyncFile::WriteExt> packet,FilePosType off)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt,WriteExt> packet2=packet.pushExt<WriteExt>();
  
  packet2.pushCompleteFunction(function_complete_write());
  
  dev->write(packet2.forgetExt<1>(),file_id,off);
 }
   
void FileSystemDevice::FileState::read(Packet<uint8,Sys::AsyncFile::ReadExt> packet)
 {
  auto ext=packet.getExt();
  
  FilePosType off=ext->off;
  ulen len=ext->buf.len;
  
  Packet<uint8,Sys::AsyncFile::ReadExt,ReadExt> packet2=packet.pushExt<ReadExt>(MoveNothing);
  
  packet2.pushCompleteFunction(function_complete_read());
  
  dev->read(packet2.forgetExt<1>(),file_id,off,len);
 }
   
void FileSystemDevice::FileState::read(Packet<uint8,Sys::AsyncFile::ReadBufExt> packet)
 {
  auto ext=packet.getExt();
  
  FilePosType off=ext->off;
  ulen len=ext->len;
  
  Packet<uint8,Sys::AsyncFile::ReadBufExt,ReadExt> packet2=packet.pushExt<ReadExt>(MovePacketBuf);
  
  packet2.pushCompleteFunction(function_complete_readbuf());
  
  dev->read(packet2.forgetExt<1>(),file_id,off,len);
 }
   
} // namespace HFS
} // namespace Net
} // namespace CCore
 

