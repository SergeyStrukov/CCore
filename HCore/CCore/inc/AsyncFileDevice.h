/* AsyncFileDevice.h */ 
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

#ifndef CCore_inc_AsyncFileDevice_h
#define CCore_inc_AsyncFileDevice_h
 
#include <CCore/inc/sys/SysAsyncFile.h>
#include <CCore/inc/sys/SysFile.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/StartStop.h>

namespace CCore {

/* classes */

class AsyncFileProcessor;

class AsyncFileDevice;

/* class AsyncFileProcessor */

class AsyncFileProcessor : NoCopy
 {
  public:
   
   typedef Sys::AltAsyncFile::Async Async;
  
   struct Work
    {
     virtual bool/* pending */ start(Async async)=0; 
     
     virtual void complete(Async async)=0;
    };
   
   struct WorkDelay
    {
     virtual void cancel(Work *work)=0;
     
     // locked
     
     virtual bool delay(Work *work)=0;
     
     virtual Work * take()=0;
    };
  
  private:
  
   struct Slot : NoCopy
    {
     // data
     
     SLink<Slot> link;
     
     ulen index;
     Async async;
     Work *work;
     
     // methods
     
     void init(ulen index,Async async);
     
     bool/* pending */ start();
     
     void complete();
    };
   
   typedef SLink<Slot>::LinearAlgo<&Slot::link>::Top SlotTop;
   
   class Completor : NoCopy
    {
      SimpleArray<Slot> slots;
     
      AsyncFileProcessor &proc;
      
      Mutex mutex;
     
      SlotTop active_list;
      
      Sys::AsyncFileWait wait;     
     
     private: 
      
      Slot * get();
      
     public:
      
      Completor(ulen max_slots,AsyncFileProcessor &proc);
      
      ~Completor();
      
      // getSlots()
      
      PtrLen<Slot> getSlots() { return Range(slots); }
      
      // put
      
      void put(Slot *slot);
      
      // object run
      
      void prepareRun() {}
      
      void objRun();
      
      void completeRun() {}
      
      void signalStop() { wait.interrupt(); }
      
      void completeStop() {}
    };
  
   class Pool
    {
      SlotTop avail_list;
      
     public:
     
      explicit Pool(PtrLen<Slot> slots);
      
      ~Pool();
      
      Slot * alloc();
      
      void free(Slot *slot);
    };

  private: 
   
   Completor completor;
   
   Mutex mutex;
   
   Pool pool;
   WorkDelay *work_delay;
   
   StartStopObject<Completor> start_stop;
   
  private: 
   
   void complete(Slot *slot);
   
   Slot * alloc(Work *work);
   
   Slot * try_free(Slot *slot);
   
   void free(Slot *slot);
   
  public:
   
   static const ulen MaxSlots = Sys::AsyncFileWait::MaxAsyncs ;
   
   AsyncFileProcessor(ulen max_slots,WorkDelay *work_delay);
   
   ~AsyncFileProcessor();
   
   void process(Work *work);
 };

/* class AsyncFileDevice */ 

class AsyncFileDevice : public ObjBase , public Sys::AsyncFileDevice
 {
   class Engine : public NoCopy
    {
      typedef AsyncFileProcessor::Work Work;
      typedef AsyncFileProcessor::Async Async;
     
      class WorkBase : public NoCopyBase<Work>
       {
        protected:
         
         Sys::AltAsyncFile *file;
         PacketHeader *packet;
         FilePosType off;
         
        public: 
         
         bool delayed;
         
         WorkBase(Sys::AltAsyncFile *file_,PacketHeader *packet_,FilePosType off_) 
          : file(file_),
            packet(packet_),
            off(off_),
            delayed(false) 
          {
          }
         
         PacketHeader * getPacket() { return packet; }
         
         virtual void cancel()=0;
       };
     
      class ReadWork : public WorkBase
       {
        public:
         
         ReadWork(Sys::AltAsyncFile *file,PacketHeader *packet,FilePosType off);
         
         ~ReadWork();
         
         // Work
         
         virtual bool/* pending */ start(Async async); 
         
         virtual void complete(Async async);
         
         // WorkBase
         
         virtual void cancel();
       };
     
      class WriteWork : public WorkBase
       {
        public:
         
         WriteWork(Sys::AltAsyncFile *file,PacketHeader *packet,FilePosType off);
         
         ~WriteWork();
         
         // Work
         
         virtual bool/* pending */ start(Async async); 
         
         virtual void complete(Async async);
         
         // WorkBase
         
         virtual void cancel();
       };
      
      class WorkDelay : public Funchor_nocopy , public AsyncFileProcessor::WorkDelay 
       {
         Mutex mutex;
         
         PacketList delay_list;
        
        private:
         
         void do_cancel(PacketHeader *packet);
         
         PacketFunction function_cancel() { return FunctionOf(this,&WorkDelay::do_cancel); }
         
         // AsyncFileProcessor::WorkDelay
         
         virtual void cancel(Work *work);
        
         virtual bool delay(Work *work);
        
         virtual Work * take();
         
        public: 
         
         WorkDelay();
         
         ~WorkDelay();
       };
     
      WorkDelay work_delay;
      
      AsyncFileProcessor proc;
      
     public:
      
      explicit Engine(ulen max_slots);
      
      ~Engine();
      
      void read(Sys::AltAsyncFile *file,Packet<uint8,Sys::AsyncFile::ReadExt> packet,FilePosType off);
      
      void write(Sys::AltAsyncFile *file,Packet<uint8,Sys::AsyncFile::WriteExt> packet,FilePosType off);
    };
  
   class FileState;
  
  private:
   
   Engine engine;
   
  public:
   
   static const ulen DefaultMaxSlots = AsyncFileProcessor::MaxSlots ;
   
   explicit AsyncFileDevice(ulen max_slots=DefaultMaxSlots);
   
   virtual ~AsyncFileDevice();
   
   // Sys::AsyncFileDevice
  
   virtual Sys::AsyncFileState * createState(const ObjHook &hook) noexcept(EnableNoExcept) ;
 };

/* class AsyncFileDevice::FileState */

class AsyncFileDevice::FileState : public Sys::AsyncFileState
 {
   Engine &engine;
   
   Sys::AltAsyncFile file;
   bool is_opened;
   
  private:
   
   static void CompleteReadBuf(PacketHeader *packet);
   
  public:
   
   FileState(const ObjHook &hook,Engine &engine);
   
   virtual ~FileState();
   
   // Sys::AsyncFileState
   
   virtual void open(Packet<uint8,Sys::AsyncFile::OpenExt> packet,StrLen file_name,FileOpenFlags oflags);
   
   virtual void close(Packet<uint8,Sys::AsyncFile::CloseExt> packet,bool preserve_file);
   
   virtual void write(Packet<uint8,Sys::AsyncFile::WriteExt> packet,FilePosType off);
   
   virtual void read(Packet<uint8,Sys::AsyncFile::ReadExt> packet);
   
   virtual void read(Packet<uint8,Sys::AsyncFile::ReadBufExt> packet);
 };

} // namespace CCore
 
#endif
 

