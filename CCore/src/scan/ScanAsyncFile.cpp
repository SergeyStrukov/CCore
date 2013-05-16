/* ScanAsyncFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
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
 
#include <CCore/inc/scan/ScanAsyncFile.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class ScanAsyncFile */

void ScanAsyncFile::init_slots()
 {
 }

#if 0  
  
void ScanAsyncFile::complete_read(PacketHeader *packet_)
 {
  Packet<uint8,Slot *,Sys::AsyncFile::ReadBufExt> packet=packet_;
  
  Sys::AsyncFile::ReadBufExt *ext=packet.getExt();

  if( FileError error=ext->error )
    {
     parent->complete(this,error);
    }
  else
    {
     data=ext->data;
     len=ext->len;
     off=ext->off;
     
     packet->detach(pbuf);
     
     parent->complete(this);
    }
  
  packet.popExt().complete();
 }

#endif  
  
bool ScanAsyncFile::add_read()
 {
  if( file_pos>=file_len ) return false;
  
  Slot *slot=getFreeSlot();
  
  if( !slot ) return false;
  
  Packet<uint8> packet=pset.try_get();
  
  if( !packet )
    {
     backFreeSlot(slot);
    
     return false;
    }
  
  ulen len=(ulen)Min<FilePosType>(file_len-file_pos,max_read_len);
  
  FilePosType off=file_pos;
  
  file_pos+=len;

  Packet<uint8,Slot *,Sys::AsyncFile::ReadBufExt> packet2=packet.pushExt<Slot *>(slot).pushExt<Sys::AsyncFile::ReadBufExt>(off,len);
  
  packet2.pushCompleteFunction(function_complete_read());
  
  file.read(packet2.forgetExt<1>());
  
  return true;
 }

void ScanAsyncFile::pump_read()
 {
  for(ulen cap=MaxSlots; cap && add_read() ;cap--);
 }

#if 0

PtrLen<const char> ScanAsyncFile::underflow()
 {
  if( !is_opened )
    {
     fail();
    
     Printf(Exception,"CCore::ScanAsyncFile::underflow() : file is not opened");
    
     return Nothing;
    }
  
  pump_read();
  
  // TODO
 }

#endif
  
ScanAsyncFile::ScanAsyncFile(MSec timeout_,ulen max_packets)
 : pset("ScanAsyncFile.pset",max_packets),
   timeout(timeout_),
   final_timeout(3*timeout_),
   mutex("ScanAsyncFile")
 {
  init_slots();
 }
  
ScanAsyncFile::ScanAsyncFile(StrLen file_name,MSec timeout,ulen max_packets)
 : ScanAsyncFile(timeout,max_packets)
 {
  open(file_name);
 }
  
ScanAsyncFile::~ScanAsyncFile()
 {
  if( is_opened )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"CCore::ScanAsyncFile::~ScanAsyncFile() : #;",errout);
       }
    }
 }
  
#if 0
  
void ScanAsyncFile::open(StrLen file_name)
 {
  file_len=file.open(file_name,Open_ToRead);  
  file_pos=0;
  max_read_len=Min(MaxReadLen,file.getMaxReadLen());
  
  reset();
  pump();
  
  // TODO
 }
   
void ScanAsyncFile::soft_close(FileMultiError &errout)
 {
  // TODO
  
 }
   
#endif  
  
void ScanAsyncFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"CCore::ScanAsyncFile::close() : #;",errout);
    }
 }

} // namespace CCore
 

