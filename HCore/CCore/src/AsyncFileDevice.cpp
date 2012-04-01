/* AsyncFileDevice.cpp */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/AsyncFileDevice.h>
 
#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* struct AsyncFileProcessor::Slot */

void AsyncFileProcessor::Slot::init(ulen index_,Async async_)
 {
  index=index_;
  async=async_;
  work=0;
 }
  
bool AsyncFileProcessor::Slot::start() 
 { 
  if( work->start(async) ) return true;
  
  work=0;
  
  return false;
 }

void AsyncFileProcessor::Slot::complete()
 {
  work->complete(async);

  work=0;
 }

/* class AsyncFileProcessor::Completor */

auto AsyncFileProcessor::Completor::get() -> Slot *
 {
  Mutex::Lock lock(mutex);
  
  return active_list.del();
 }

AsyncFileProcessor::Completor::Completor(ulen max_slots,AsyncFileProcessor &proc_)
 : slots(max_slots),
   proc(proc_),
   mutex("AsyncFileProcessor::Completor")
 {
  if( auto fe=wait.init(max_slots) )
    {
     Printf(Exception,"CCore::AsyncFileProcessor::Completor::Completor(...) : #;",fe);
    }
  
  for(ulen i=0; i<max_slots ;i++) slots[i].init(i,wait.getAsync(i));
 }

AsyncFileProcessor::Completor::~Completor()
 {
  wait.exit();
 }

void AsyncFileProcessor::Completor::put(Slot *slot)
 {
  {
   Mutex::Lock lock(mutex);

   active_list.ins(slot);
  }

  wait.interrupt();
 }

void AsyncFileProcessor::Completor::objRun()
 {
  for(;;)
    {
     switch( auto ind=wait.wait(10_sec) )
       {
        case Sys::Wait_error : 
         {
          Abort("Fatal error : CCore::Sys::AsyncFileProcessor::Completor wait failed");
         }
        break;
        
        case Sys::Wait_timeout :
         {
          // do nothing
         }
        break;
        
        case Sys::Wait_interrupt :
         {
          Slot *slot=get();
          
          if( !slot ) return;
          
          wait.addWait(slot->index);
         }
        break;
        
        default:
         {
          Slot *slot=slots.getPtr()+ind;
          
          wait.delWait(ind);
          
          proc.complete(slot);
         }
       }
    }
 }

/* class AsyncFileProcessor::Pool */

AsyncFileProcessor::Pool::Pool(PtrLen<Slot> slots)
 {
  for(; +slots ;++slots) free(slots.ptr);
 }

AsyncFileProcessor::Pool::~Pool()
 {
 }

auto AsyncFileProcessor::Pool::alloc() -> Slot *
 {
  return avail_list.del();
 }

void AsyncFileProcessor::Pool::free(Slot *slot)
 {
  avail_list.ins(slot);
 }

/* class AsyncFileProcessor */

void AsyncFileProcessor::complete(Slot *slot)
 {
  slot->complete();
  
  free(slot);
 }

auto AsyncFileProcessor::alloc(Work *work) -> Slot *
 {
  {
   Mutex::Lock lock(mutex);
   
   if( Slot *ret=pool.alloc() )
     {
      ret->work=work;
      
      return ret;
     }
   else
     {
      if( work_delay->delay(work) ) return 0;
     }
  }
  
  work_delay->cancel(work);
  
  return 0;
 }

auto AsyncFileProcessor::try_free(Slot *slot) -> Slot *
 {
  Mutex::Lock lock(mutex);
  
  if( Work *work=work_delay->take() )
    {
     slot->work=work;
     
     return slot;
    }
  else
    {
     pool.free(slot);
     
     return 0;
    }
 }

void AsyncFileProcessor::free(Slot *slot)
 {
  for(;;)
    {
     slot=try_free(slot);
     
     if( !slot ) return;
     
     if( slot->start() )
       {
        completor.put(slot);
        
        return;
       }
    }
 }

AsyncFileProcessor::AsyncFileProcessor(ulen max_slots,WorkDelay *work_delay_)
 : completor(Min(max_slots,MaxSlots),*this),
   mutex("AsyncFileProcessor"),
   pool(completor.getSlots()),
   work_delay(work_delay_),
   start_stop(completor)
 {
 }

AsyncFileProcessor::~AsyncFileProcessor()
 {
 }

void AsyncFileProcessor::process(Work *work)
 {
  if( Slot *slot=alloc(work) )
    {
     if( slot->start() )
       {
        completor.put(slot);
       }
     else
       {
        free(slot);
       }
    }
 }

/* class AsyncFileDevice::Engine::ReadWork */

AsyncFileDevice::Engine::ReadWork::ReadWork(Sys::AltAsyncFile *file,PacketHeader *packet,FilePosType off)
 : WorkBase(file,packet,off)
 {
 }

AsyncFileDevice::Engine::ReadWork::~ReadWork() {}

bool AsyncFileDevice::Engine::ReadWork::start(Async async)
 {
  Packet<uint8,Sys::AsyncFile::ReadExt,ReadWork,WorkBase *> packet1=packet;  
  
  auto ext=packet1.getDeepExt<1>();
  
  PtrLen<uint8> buf=ext->buf;
  
  auto result=file->startRead(async,off,buf.ptr,buf.len);
  
  if( result.pending ) 
    {
     return true;
    }
  else
    {
     ext->error=result.error; // error or success
     
     packet1.popExt().popExt().complete();
     
     return false;
    }
 }

void AsyncFileDevice::Engine::ReadWork::complete(Async async)
 {
  Packet<uint8,Sys::AsyncFile::ReadExt,ReadWork,WorkBase *> packet1=packet;
  
  auto ext=packet1.getDeepExt<1>();
  
  ext->error=file->completeRead(async,ext->buf.len); // error or success
  
  packet1.popExt().popExt().complete();
 }

void AsyncFileDevice::Engine::ReadWork::cancel()
 {
  Packet<uint8,Sys::AsyncFile::ReadExt,ReadWork,WorkBase *> packet1=packet;
  
  auto ext=packet1.getDeepExt<1>();
  
  ext->setError(FileError_Cancelled);
  
  packet1.popExt().popExt().complete();
 }

/* class AsyncFileDevice::Engine::WriteWork */

AsyncFileDevice::Engine::WriteWork::WriteWork(Sys::AltAsyncFile *file,PacketHeader *packet,FilePosType off)
 : WorkBase(file,packet,off)
 {
 }

AsyncFileDevice::Engine::WriteWork::~WriteWork() {}

bool AsyncFileDevice::Engine::WriteWork::start(Async async)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt,WriteWork,WorkBase *> packet1=packet;  
  
  auto ext=packet1.getDeepExt<1>();
  
  const uint8 *buf=packet1.getData();
  ulen len=packet1.getDataLen();
  
  auto result=file->startWrite(async,off,buf,len);
  
  if( result.pending )
    {
     return true;
    }
  else
    {
     if( result.error ) ext->setError(result.error);
     
     packet1.popExt().popExt().complete();
     
     return false;
    }
 }

void AsyncFileDevice::Engine::WriteWork::complete(Async async)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt,WriteWork,WorkBase *> packet1=packet;  
  
  auto ext=packet1.getDeepExt<1>();
  
  if( auto fe=file->completeWrite(async,packet1.getDataLen()) ) ext->setError(fe);
  
  packet1.popExt().popExt().complete();
 }

void AsyncFileDevice::Engine::WriteWork::cancel()
 {
  Packet<uint8,Sys::AsyncFile::WriteExt,WriteWork,WorkBase *> packet1=packet;  
  
  auto ext=packet1.getDeepExt<1>();
  
  ext->setError(FileError_Cancelled);
  
  packet1.popExt().popExt().complete();
 }

/* class AsyncFileDevice::Engine::WorkDelay */

void AsyncFileDevice::Engine::WorkDelay::do_cancel(PacketHeader *packet)
 {
  Packet<uint8,WorkBase *> packet1=packet;
  
  WorkBase *work=*packet1.getExt();
  
  {
   Mutex::Lock lock(mutex);
   
   if( work->delayed ) delay_list.del(packet);
  }
  
  work->cancel();
 }

void AsyncFileDevice::Engine::WorkDelay::cancel(Work *work)
 {
  static_cast<WorkBase *>(work)->cancel();
 }

bool AsyncFileDevice::Engine::WorkDelay::delay(Work *work_)
 {
  WorkBase *work=static_cast<WorkBase *>(work_);
  
  auto packet=work->getPacket();

  Mutex::Lock lock(mutex);

  if( packet->setCancelFunction(function_cancel())==Packet_NoCancelFunction )
    {
     work->delayed=true;
     
     delay_list.put(packet);
       
     return true;
    }
    
  return false;
 }

auto AsyncFileDevice::Engine::WorkDelay::take() -> Work * 
 {
  for(;;)
    {
     Mutex::Lock lock(mutex);

     PacketHeader *packet=delay_list.get();

     if( !packet ) return 0;
     
     Packet<uint8,WorkBase *> packet1=packet;
     
     WorkBase *work=*packet1.getExt();

     work->delayed=false;
     
     if( packet->clearCancelFunction()!=Packet_Cancelled ) return work; 
    }
 }

AsyncFileDevice::Engine::WorkDelay::WorkDelay()
 : mutex("AsyncFileDevice")
 {
 }

AsyncFileDevice::Engine::WorkDelay::~WorkDelay()
 {
 }

/* class AsyncFileDevice::Engine */

AsyncFileDevice::Engine::Engine(ulen max_slots)
 : proc(max_slots,&work_delay)
 {
 }

AsyncFileDevice::Engine::~Engine()
 {
 }

void AsyncFileDevice::Engine::read(Sys::AltAsyncFile *file,Packet<uint8,Sys::AsyncFile::ReadExt> packet1,FilePosType off)
 {
  auto packet=packet1.getPtr();
  
  auto packet2=packet1.pushExt<ReadWork>(file,packet,off);

  auto ext=packet2.getExt();
  
  packet2.pushExt<WorkBase *>(ext);

  proc.process(ext);
 }

void AsyncFileDevice::Engine::write(Sys::AltAsyncFile *file,Packet<uint8,Sys::AsyncFile::WriteExt> packet1,FilePosType off)
 {
  auto packet=packet1.getPtr();
  
  auto packet2=packet1.pushExt<WriteWork>(file,packet,off);

  auto ext=packet2.getExt();
  
  packet2.pushExt<WorkBase *>(ext);

  proc.process(ext);
 }

/* class AsyncFileDevice::FileState */

void AsyncFileDevice::FileState::CompleteReadBuf(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::ReadBufExt,Sys::AsyncFile::ReadExt> packet=packet_;
  
  auto ext=packet.getExt();
  auto ext2=packet.getDeepExt<1>();
  
  if( ext->error )
    {
     ext2->setError(ext->error);
    }
  else
    {
     ext2->setData(ext->buf.ptr);
    }
  
  packet.popExt().complete();
 }

AsyncFileDevice::FileState::FileState(const ObjHook &hook,Engine &engine_)
 : Sys::AsyncFileState(hook),
   engine(engine_),
   is_opened(false)
 {
  write_format.prefix=0;
  write_format.max_data=MaxULen;
  write_format.suffix=0;
  
  max_read_len=MaxULen;
 }

AsyncFileDevice::FileState::~FileState()
 {
  if( is_opened ) file.close();
 }

void AsyncFileDevice::FileState::open(Packet<uint8,Sys::AsyncFile::OpenExt> packet,StrLen file_name,FileOpenFlags oflags)
 {
  auto ext=packet.getExt();
  
  auto result=file.open(file_name,oflags);
   
  if( result.error )
    {
     ext->setError(result.error);
    }
  else
    {
     is_opened=true;

     ext->setFileLen(result.file_len);
    }
  
  packet.complete();
 }

void AsyncFileDevice::FileState::close(Packet<uint8,Sys::AsyncFile::CloseExt> packet,bool preserve_file)
 {
  is_opened=false;
  
  FileMultiError errout;
  
  file.close(errout,preserve_file);
  
  packet.getExt()->setError(errout.getFirst());
  
  packet.complete();
 }

void AsyncFileDevice::FileState::write(Packet<uint8,Sys::AsyncFile::WriteExt> packet,FilePosType off)
 {
  auto ext=packet.getExt();
  
  ulen len=packet.getDataLen();
  
  auto result=file.setWrite(off,len);
  
  if( result.error )
    {
     ext->setError(result.error);
     
     packet.complete();
    }
  else
    {
     ext->setFileLen(result.file_len);
     
     engine.write(&file,packet,off);
    }
 }

void AsyncFileDevice::FileState::read(Packet<uint8,Sys::AsyncFile::ReadExt> packet)
 {
  auto ext=packet.getExt();
  
  FilePosType off=ext->off;
  ulen len=ext->buf.len;
  
  if( FileError fe=file.testRead(off,len) )
    {
     ext->setError(fe);
     
     packet.complete();
    }
  else
    {
     engine.read(&file,packet,off);
    }
 }

void AsyncFileDevice::FileState::read(Packet<uint8,Sys::AsyncFile::ReadBufExt> packet)
 {
  auto ext=packet.getExt();
  
  ulen len=ext->len;
  
  if( packet.provide(Max(len,DefaultPacketMaxDataLen)) )
    {
     PtrLen<uint8> buf=packet.setDataLen(len);
     
     Packet<uint8,Sys::AsyncFile::ReadBufExt,Sys::AsyncFile::ReadExt> packet2=packet.pushExt<Sys::AsyncFile::ReadExt>(ext->off,buf);
     
     packet2.pushCompleteFunction(CompleteReadBuf);
     
     read(packet2.forgetExt<1>());
    }
  else
    {
     ext->setError(FileError_SysOverload);
     
     packet.complete();
    }
 }

/* class AsyncFileDevice */ 

AsyncFileDevice::AsyncFileDevice(ulen max_slots)
 : engine(Min(max_slots,DefaultMaxSlots))
 {
 }

AsyncFileDevice::~AsyncFileDevice()
 {
 }

Sys::AsyncFileState * AsyncFileDevice::createState(const ObjHook &hook) noexcept(EnableNoExcept)
 {
  return new(JustTry) FileState(hook,engine);
 }

} // namespace CCore
 

