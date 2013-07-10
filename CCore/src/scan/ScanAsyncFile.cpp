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
  done_ind=0;
  done_count=0;
  op_ind=0;
  op_count=0;
  free_ind=0;
  free_count=MaxSlots;
 }

void ScanAsyncFile::clean_slots()
 {
  pbuf.detach();
  
  while( done_count )
    {
     slots[done_ind].pbuf.detach();
   
     done_ind=NextInd(done_ind);
     done_count--;
    }
 }

auto ScanAsyncFile::getFreeSlot() -> Slot *
 {
  Mutex::Lock lock(mutex);
  
  if( free_count==0 ) return 0;
  
  Slot *ret=slots+free_ind;
  
  free_ind=NextInd(free_ind);
  free_count--;
  op_count++;
  
  ret->done=false;
  
  return ret;
 }

void ScanAsyncFile::backFreeSlot()
 {
  Mutex::Lock lock(mutex);
  
  free_ind=PrevInd(free_ind);
  free_count++;
  op_count--;
 }

void ScanAsyncFile::setError(FileError error_)
 {
  Mutex::Lock lock(mutex);
  
  if( !error ) error=error_;
 }

FileError ScanAsyncFile::getError()
 {
  Mutex::Lock lock(mutex);
  
  return error;
 }

void ScanAsyncFile::complete(Slot *slot)
 {
  ulen ind=Dist(slots,slot);
  ulen delta=0;
  
  {
   Mutex::Lock lock(mutex);
    
   slot->done=true;
    
   if( ind==op_ind )
     {
      while( op_count && slots[op_ind].done )
        {
         op_ind=NextInd(op_ind);
         op_count--;
         done_count++;
         delta++;
        }
     }
  }

  sem.give_many(delta);
 }

void ScanAsyncFile::complete_read(PacketHeader *packet_)
 {
  Packet<uint8,Slot *,Sys::AsyncFile::ReadBufExt> packet=packet_;
  
  auto *ext=packet.getExt();
  Slot *slot=*packet.getDeepExt<1>();
  
  FileError error=ext->error;
  
  slot->error=error;
  
  if( error )
    {
     setError(error);
    }
  else
    {
     packet.detach(slot->pbuf);
    
     slot->data=ext->data;
     slot->off=ext->off;
     slot->len=ext->len;
    }
  
  complete(slot);
  
  packet.popExt().popExt().complete();
 }
  
bool ScanAsyncFile::add_read()
 {
  if( file_pos>=file_len ) return false;
  
  Slot *slot=getFreeSlot();
  
  if( !slot ) return false;
  
  Packet<uint8> packet=pset.try_get();
  
  if( !packet )
    {
     backFreeSlot();
    
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

void ScanAsyncFile::complete_open(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::OpenExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  if( !error )
    {
     is_opened=true;
     
     file_pos=0;
     file_len=ext->file_len;
     max_read_len=Min(MaxReadLen,ext->max_read_len);
     
     remaining_len=file_len;
    }
  
  packet.popExt().complete();
 }

void ScanAsyncFile::complete_close(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::CloseExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  packet.popExt().complete();
 }

PtrLen<const char> ScanAsyncFile::underflow()
 {
  if( !is_opened )
    {
     fail();
    
     Printf(Exception,"CCore::ScanAsyncFile::underflow() : file is not opened");
    
     return Nothing;
    }
  
  if( !remaining_len ) return Nothing;
  
  pump_read();
  
  if( sem.take(timeout) )
    {
     Mutex::Lock lock(mutex);
    
     Slot *slot=slots+done_ind;
    
     done_ind=NextInd(done_ind);
     done_count--;
     free_count++;
    
     if( !slot->error )
       {
        slot->pbuf.moveTo(pbuf);
       
        remaining_len-=slot->len;
       
        return slot->getRange(); 
       }
    }
  else
    {
     setError(FileError_ReadFault);
    }
  
  pset.cancel_and_wait();
  
  fail();
  
  Printf(Exception,"CCore::ScanAsyncFile::underflow() : #;",getError());
  
  return Nothing;
 }
  
ScanAsyncFile::ScanAsyncFile(MSec timeout_,ulen max_packets)
 : pset("ScanAsyncFile.pset",max_packets),
   timeout(timeout_),
   final_timeout(3*timeout_),
   mutex("ScanAsyncFile"),
   sem("ScanAsyncFile")
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
  
void ScanAsyncFile::open(StrLen file_name)
 {
  if( is_opened )
    {
     Printf(Exception,"CCore::ScanAsyncFile::open(...) : file is already opened");
    }

  TimeScope time_scope(timeout);
    
  Packet<uint8> packet=pset.get(time_scope); 
  
  if( !packet )
    {
     Printf(Exception,"CCore::ScanAsyncFile::open(...) : no packet");
    }
    
  Packet<uint8,Sys::AsyncFile::OpenExt> packet2=packet.pushExt<Sys::AsyncFile::OpenExt>();  
  
  packet2.pushCompleteFunction(function_complete_open());
    
  file.open(packet2,file_name,Open_ToRead);  
  
  pset.wait(time_scope);
  
  if( !is_opened )
    {
     file.closeState();
     
     Printf(Exception,"CCore::ScanAsyncFile::open(#.q;) : #;",file_name,error);
    }  
  
  init_slots();
  
  reset();
  pump();
 }
   
void ScanAsyncFile::soft_close(FileMultiError &errout)
 {
  if( !is_opened ) 
    {
     errout.add(FileError_NoMethod);
     
     return;
    }
  
  is_opened=false;
    
  pset.wait(final_timeout);
  
  errout.add(error);
  
  clean_slots();
  
  Packet<uint8> packet=pset.get(timeout);
  
  if( !packet )
    {
     errout.add(FileError_SysOverload);
     
     file.closeState();
     
     reset();
    
     return;
    }
    
  Packet<uint8,Sys::AsyncFile::CloseExt> packet2=packet.pushExt<Sys::AsyncFile::CloseExt>(); 
  
  packet2.pushCompleteFunction(function_complete_close());
  
  file.close(packet2);
  
  pset.wait(timeout);
  
  file.closeState();
  
  errout.add(error);
  
  reset();
 }
   
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
 

