/* ScanAsyncFile.h */ 
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

#ifndef CCore_inc_scan_ScanAsyncFile_h
#define CCore_inc_scan_ScanAsyncFile_h
 
#include <CCore/inc/Scanf.h>
 
#include <CCore/inc/PacketSet.h>

#include <CCore/inc/sys/SysAsyncFile.h>

namespace CCore {

/* classes */

class ScanAsyncFile;

/* class ScanAsyncFile */

class ScanAsyncFile : public ScanBase , public Funchor
 {
   Sys::AsyncFile file;

   bool is_opened = false ;
   
   PacketSet<uint8> pset;
   MSec timeout;
   MSec final_timeout;
   
   // read engine
   
   FilePosType file_pos;
   FilePosType file_len;
   ulen max_read_len;
   
   FilePosType remaining_len;
   
   PacketBuf pbuf;
   
   static const ulen MaxSlots = 100 ;
   static const ulen MaxReadLen = 64_KByte ;
   
   struct Slot : NoCopy 
    {
     PacketBuf pbuf;
     FilePosType off;
     ulen len;
     const uint8 *data;
     bool done;
     FileError error;
     
     PtrLen<const char> getRange() const { return Range(MutatePtr<const char>(data),len);}
    };
   
   Slot slots[MaxSlots];
   
   Mutex mutex;
   Sem sem;
 
   ulen done_ind;
   ulen done_count;
   ulen op_ind;
   ulen op_count;
   ulen free_ind;
   ulen free_count;
   
   FileError error;
   
  private: 
   
   void init_slots();
   
   void clean_slots();
   
   static ulen NextInd(ulen ind) { return (ind<MaxSlots-1)?ind+1:0; }
   
   static ulen PrevInd(ulen ind) { return (ind>0)?ind-1:(MaxSlots-1); }
   
   Slot * getFreeSlot();
   
   void backFreeSlot();
   
   void setError(FileError error);
   
   FileError getError();
   
   void complete(Slot *slot);
   
   void complete_read(PacketHeader *packet);
   
   PacketFunction function_complete_read() { return FunctionOf(this,&ScanAsyncFile::complete_read); }
   
   bool add_read(TimeScope time_scope);
   
   void pump_read(TimeScope time_scope);
   
  private: 
   
   void complete_open(PacketHeader *packet);
   
   PacketFunction function_complete_open() { return FunctionOf(this,&ScanAsyncFile::complete_open); }
   
   void complete_close(PacketHeader *packet);
   
   PacketFunction function_complete_close() { return FunctionOf(this,&ScanAsyncFile::complete_close); }
   
  private:
  
   virtual PtrLen<const char> underflow();
  
  public:
  
   // constructors
 
   explicit ScanAsyncFile(MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
  
   explicit ScanAsyncFile(StrLen file_name,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
  
   ~ScanAsyncFile();
  
   // methods
  
   bool isOpened() const { return is_opened; }
  
   void setFinalTimeout(MSec t) { final_timeout=t; }
   
   void open(StrLen file_name);
   
   void soft_close(FileMultiError &errout);
   
   void close();
 };

} // namespace CCore
 
#endif
 

