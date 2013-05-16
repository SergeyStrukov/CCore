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
#include <CCore/inc/List.h>
 
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
   
   static const ulen MaxSlots = 100 ;
   static const ulen MaxReadLen = 64_KByte ;
   
   struct Slot : NoCopy 
    {
     PacketBuf pbuf;
     FilePosType off;
     ulen len;
     const uint8 *data;
    };
   
   Slot slots[MaxSlots];
   
   FilePosType file_pos;
   FilePosType file_len;
   ulen max_read_len;
   
   Mutex mutex;
 
   ulen inuse_ind;
   ulen free_ind;
   ulen inuse_count;
   
  private: 
   
   void init_slots();
   
   Slot * getFreeSlot();
   
   void backFreeSlot(Slot *slot);
   
   void complete_read(PacketHeader *packet);
   
   PacketFunction function_complete_read() { return FunctionOf(this,&ScanAsyncFile::complete_read); }
   
   bool add_read();
   
   void pump_read();
   
  private:
  
   virtual PtrLen<const char> underflow();
  
  public:
  
   // constructors
 
   explicit ScanAsyncFile(MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
  
   explicit ScanAsyncFile(StrLen file_name,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
  
   ~ScanAsyncFile();
  
   // methods
  
   bool isOpened() const { return is_opened; }
  
   void open(StrLen file_name);
   
   void soft_close(FileMultiError &errout);
   
   void close();
 };

} // namespace CCore
 
#endif
 

