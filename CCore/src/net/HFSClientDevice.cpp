/* HFSClientDevice.cpp */ 
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
 
#include <CCore/inc/net/HFSClientDevice.h>
 
namespace CCore {
namespace Net {
namespace HFS {

/* class ClientDevice */ 

ClientDevice::ClientDevice(StrLen ptp_dev_name)
 : hook(ptp_dev_name),
   ptp(hook)
 {
  max_outbound_info_len=ptp->getMaxOutboundInfoLen();
  max_inbound_info_len=ptp->getMaxInboundInfoLen();
  
  const char *name="CCore::Net::HFS::ClientDevice::ClientDevice(...)";
  
  max_read_len=LenSub(name,max_inbound_info_len,DeltaReadLen);
  
  open_format=ptp->getFormat_guarded<OpenExt>(name);
  write_format=ptp->getFormat_guarded<WriteExt>(name);
  
  getFileType_format=ptp->getFormat_guarded<GetFileTypeExt>(name);
  getFileList_format=ptp->getFormat_guarded<GetFileListExt>(name);
  createFile_format=ptp->getFormat_guarded<CreateFileExt>(name);
  deleteFile_format=ptp->getFormat_guarded<DeleteFileExt>(name);
  createDir_format=ptp->getFormat_guarded<CreateDirExt>(name);
  deleteDir_format=ptp->getFormat_guarded<DeleteDirExt>(name);
  remove_format=ptp->getFormat_guarded<RemoveExt>(name);
 }
    
ClientDevice::~ClientDevice()
 {
 }
 
void ClientDevice::open(Packet<uint8,OpenExt> packet,FlagType open_flags)
 {
  auto sub=packet.getDataLen(open_format);
  
  if( sub.notFitFormat() )
    {
     packet.getExt()->fail(Trans_BadDataLen);
        
     packet.complete();
    }
  else
    {
     OpenInput input(open_flags,sub.len);
  
     ptp->start_format(packet,input);
    }  
 }
 
void ClientDevice::open(Packet<uint8,OpenExt> packet,StrLen file_name,FlagType open_flags)
 {
  if( packet.checkDataLen(open_format,file_name.len) )
    {
     packet.setDataLen(open_format,file_name.len).copyFrom(file_name.ptr);
 
     OpenInput input(open_flags,file_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::read(Packet<uint8,ReadExt> packet,const FileId &file_id,FileLenType off,ulen len)
 {
  if( len>max_read_len )
    {
     packet.getExt()->fail(Trans_BadDataLen);
        
     packet.complete();
    }
  else
    {
     ReadInput input(file_id,off,(LenType)len);
  
     ptp->start(packet,input);
    }
 }
 
void ClientDevice::write(Packet<uint8,WriteExt> packet,const FileId &file_id,FileLenType off)
 {
  auto sub=packet.getDataLen(write_format);
  
  if( sub.notFitFormat() )
    {
     packet.getExt()->fail(Trans_BadDataLen);
        
     packet.complete();
    }
  else
    {
     WriteInput input(file_id,off,sub.len);
  
     ptp->start_format(packet,input);
    }
 }
 
void ClientDevice::close(Packet<uint8,CloseExt> packet,const FileId &file_id,bool preserve_file)
 {
  CloseInput input(preserve_file,file_id);
  
  ptp->start(packet,input);
 }
 
void ClientDevice::getFileType(Packet<uint8,GetFileTypeExt> packet,StrLen path)
 {
  if( packet.checkDataLen(getFileType_format,path.len) )
    {
     packet.setDataLen(getFileType_format,path.len).copyFrom(path.ptr);
 
     GetFileTypeInput input(path.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::getFileList(Packet<uint8,GetFileListExt> packet,StrLen dir_name)
 {
  if( packet.checkDataLen(getFileList_format,dir_name.len) )
    {
     packet.setDataLen(getFileList_format,dir_name.len).copyFrom(dir_name.ptr);
 
     GetFileListInput input(dir_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::createFile(Packet<uint8,CreateFileExt> packet,StrLen file_name)
 {
  if( packet.checkDataLen(createFile_format,file_name.len) )
    {
     packet.setDataLen(createFile_format,file_name.len).copyFrom(file_name.ptr);
 
     CreateFileInput input(file_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::deleteFile(Packet<uint8,DeleteFileExt> packet,StrLen file_name)
 {
  if( packet.checkDataLen(deleteFile_format,file_name.len) )
    {
     packet.setDataLen(deleteFile_format,file_name.len).copyFrom(file_name.ptr);
 
     DeleteFileInput input(file_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::createDir(Packet<uint8,CreateDirExt> packet,StrLen dir_name)
 {
  if( packet.checkDataLen(createDir_format,dir_name.len) )
    {
     packet.setDataLen(createDir_format,dir_name.len).copyFrom(dir_name.ptr);
 
     CreateDirInput input(dir_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
  
void ClientDevice::deleteDir(Packet<uint8,DeleteDirExt> packet,StrLen dir_name,bool recursive)
 {
  if( packet.checkDataLen(deleteDir_format,dir_name.len) )
    {
     packet.setDataLen(deleteDir_format,dir_name.len).copyFrom(dir_name.ptr);
 
     DeleteDirInput input(recursive,dir_name.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
 
void ClientDevice::rename(Packet<uint8,RenameExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite)
 {
  if( old_path.len>MaxPathLen || new_path.len>MaxPathLen )
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }
  else
    {
     RenameInput input(allow_overwrite,Mutate<const uint8>(old_path),Mutate<const uint8>(new_path));
     
     ptp->start(packet,input);
    }
 }
   
void ClientDevice::remove(Packet<uint8,RemoveExt> packet,StrLen path)
 {
  if( packet.checkDataLen(remove_format,path.len) )
    {
     packet.setDataLen(remove_format,path.len).copyFrom(path.ptr);
 
     RemoveInput input(path.len);
  
     ptp->start_format(packet,input);
    } 
  else
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }  
 }
   
void ClientDevice::exec(Packet<uint8,ExecExt> packet,StrLen dir,StrLen program,StrLen arg)
 {
  if( dir.len>MaxPathLen || program.len>MaxPathLen || arg.len>MaxPathLen )
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }
  else
    {
     ExecInput input(Mutate<const uint8>(dir),Mutate<const uint8>(program),Mutate<const uint8>(arg));
     
     ptp->start(packet,input);
    }
 }
   
void ClientDevice::exec2(Packet<uint8,Exec2Ext> packet,StrLen dir,StrLen program)
 {
  if( dir.len>MaxPathLen || program.len>MaxPathLen )
    {
     packet.getExt()->fail(Trans_BadDataLen);
    
     packet.complete();
    }
  else
    {
     Exec2Input input(Mutate<const uint8>(dir),Mutate<const uint8>(program));
     
     ptp->start(packet,input);
    }
 }
  
} // namespace HFS
} // namespace Net
} // namespace CCore
 

