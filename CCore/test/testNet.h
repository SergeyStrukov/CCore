/* testNet.h */ 
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

#ifndef CCore_test_testNet_h
#define CCore_test_testNet_h

#include <CCore/test/testRun.h>
 
#include <CCore/inc/Print.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/Counters.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/StartStop.h>
#include <CCore/inc/AsyncFileToMem.h>
#include <CCore/inc/CmdInput.h>
#include <CCore/inc/String.h>

#include <CCore/inc/net/CheckedData.h>
#include <CCore/inc/net/PacketEndpointDevice.h>
#include <CCore/inc/net/PTPEchoTest.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/PTPConDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>

namespace App {

/* ShowStat() */ 

template <class T>
void ShowStat(T &dev,StrLen title)
 {
  typename T::StatInfo info;
  
  dev.getStat(info);
  
  Printf(Con,"#;\n\n#15;\n\n",Title(title),info);
 }
 
/* classes */  

class PacketEchoTest;

class PTPEchoTest;

class PacketRead;

class PTPServerTest;

/* class PacketEchoTest */ 

class PacketEchoTest : NoCopy , Net::PacketEndpointDevice::InboundProc
 {
  public:
  
   enum Event
    {
     Event_inbound,
     Event_outbound,
     
     Event_broken,
     Event_nosem,
    
     EventLim
    };
    
   typedef Counters<Event,EventLim> StatInfo;
   
   friend const char * GetTextDesc(Event ev);
   
  private: 
  
   ObjHook hook;
 
   Net::PacketEndpointDevice *ep;
   
   PacketFormat format;
   
   Net::CheckedData cdata;
   
   Sem sem;
   
   Mutex mutex;
   
   StatInfo stat;
   
   MSecTimer timer;
   
   ulen packet_count;
   uint64 total_data;
   MSecTimer::ValueType run_time;
   
  private: 
  
   void traffic_init(ulen count);
  
   void traffic(ulen len);
   
   void traffic_exit();
    
   void show_traffic();
  
   void count(Event ev);
    
   void showStat();
   
   virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
     
   virtual void tick();
     
   void send();
    
  public: 
  
   explicit PacketEchoTest(StrLen ep_dev_name);
   
   ~PacketEchoTest();
    
   void getStat(StatInfo &ret); 
    
   void run(ulen forward,ulen cnt);
 };
 
/* class PTPEchoTest */  

class PTPEchoTest : public Funchor_nocopy
 {
  public:
  
   enum Event
    {
     Event_done,
     Event_nodata,
     Event_baddata,
     Event_failed,
     Event_datalen,
     Event_nopacket,
     Event_nomem,
     Event_timeout,
    
     EventLim
    };
    
   friend const char * GetTextDesc(Event ev);  
   
   typedef Counters<Event,EventLim> StatInfo;
    
  private:
  
   ulen burst_count;
 
   ObjHook hook;
   
   Net::PTP::ClientDevice *ptp;
   
   Atomic run_flag;
   
   Net::CheckedData cdata;
   
   Mutex mutex;
   
   StatInfo stat;
   
  private:
  
   void count(Event ev);
  
   void do_complete(Net::PTP::EchoTest::Ext *ext); 
  
   void complete(PacketHeader *packet_);
  
   PacketFunction function_complete() { return FunctionOf(this,&PTPEchoTest::complete); }
   
   // object run
  
   void prepareRun() { run_flag=1; }
   
   void objRun();
   
   void completeRun() {}
   
   void signalStop() { run_flag=0; }
   
   void completeStop() {}
    
  public:
  
   explicit PTPEchoTest(StrLen ptp_dev_name,ulen burst_count=10);
   
   ~PTPEchoTest();
    
   void getStat(StatInfo &ret); 
   
   friend class StartStopObject<PTPEchoTest>;
   
   typedef StartStopObject<PTPEchoTest> StartStop;
 };
 
/* class PacketRead */

class PacketRead : public Funchor_nocopy
 {
   Atomic ecount;
   FileError error;
  
   FilePosType file_len;
   
   struct Frame : MemBase_nocopy
    {
     DLink<Frame> link;
     
     // data
     
     FilePosType off;
     ulen len;
     
     PtrLen<const uint8> data;
     PacketBuf pbuf;
     
     ClockDiffTimer::ValueType time;
     
     // methods
     
     void copyTo(uint8 *base)
      {
       data.copyTo(base+(ulen)off);
      }
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"[#; ,+ #; ) : #;",off,len,time);
      }
    };
   
   class FrameList
    {
      Mutex mutex;
     
      DLink<Frame>::CircularAlgo<&Frame::link>::Top top;
      ClockDiffTimer timer;
      
     public:
      
      // constructors
     
      FrameList() {}
     
      ~FrameList();
      
      // methods
     
      Frame * alloc();
      
      void copyTo(uint8 *base);
      
      // print object
      
      template <class P>
      void print(P &out) const
       {
        for(auto cur=top.start(); +cur ;++cur) Printf(out,"#;\n",*cur);
       }
    };
   
   FrameList list;
   
  private:
   
   void set(FileError fe)
    {
     if( (ecount++)==0 ) error=fe;
    }
   
   void complete(PacketHeader *packet);
   
   PacketFunction function_complete() { return FunctionOf(this,&PacketRead::complete); }
   
  public:
   
   // constructors
   
   explicit PacketRead(StrLen file_name);
   
   ~PacketRead();
   
   // methods
   
   void guard();
   
   void map(DynArray<uint8> &ret);
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Putobj(out,list);
    }
 };

/* class PTPServerTest */

class PTPServerTest : NoCopy , public CmdInput::Target
 {
   Net::HFS::ClientDevice hfs;
   
   ObjMaster hfs_master;
   
   Net::HFS::FileSystemDevice host;
   
   ObjMaster host_master;
   
   Net::PTPCon::ClientDevice ptpcon;
   
   ObjMaster ptpcon_master;
   
   Net::PTPCon::Cfg ptpcon_cfg;
   
   PTPConOpenClose ptpcon_open_close;
   
   PrintPTPCon con;
   
   CmdInputCon<ReadPTPCon> cmd_input;
   bool run_flag;
   
   AsyncFileSystem fs;
   
   RunTasks run_task;
   
  private:
   
   class Report;
   class Split;
   
   static void PrintFile(unsigned ind);
   
   void cmd_empty(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_test1(StrLen arg);
   void cmd_test2(StrLen arg);
   void cmd_test3(StrLen arg);
   void cmd_test4(StrLen arg);
   
   void cmd_list(StrLen arg);
   void cmd_type(StrLen arg);
   void cmd_show(StrLen arg);
   
   void cmd_createFile(StrLen arg);
   void cmd_deleteFile(StrLen arg);
   void cmd_createDir(StrLen arg);
   void cmd_deleteDir(StrLen arg);
   void cmd_deleteDirRecursive(StrLen arg);
   
   void cmd_rename(StrLen arg);
   void cmd_renameOver(StrLen arg);
   void cmd_remove(StrLen arg);
   void cmd_exec(StrLen arg);
   void cmd_exec2(StrLen arg);
   
   virtual void buildCmdList(CmdInput &input);
   
  public:
   
   PTPServerTest();
   
   ~PTPServerTest();
   
   void run();
 };

} // namespace App
 
#endif
 

