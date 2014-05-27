/* testNet.cpp */ 
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
 
#include <CCore/test/testNet.h>

#include <CCore/inc/Exception.h>
 
namespace App {

/* class PacketSource */

const char * GetTextDesc(PacketSource::Event ev)
 {
  static const char *const Table[]=
   {
    "nofill",
    "broken",
 
    ""
   };

  return Table[ev];
 }

void PacketSource::count(Event ev)
 {
  Mutex::Lock lock(mutex);
  
  stat.count(ev);
 }
 
PacketSource::PacketSource(ulen max_packets,ulen max_len_)
 : max_len(max_len_),
   pset(max_packets)
 {
  run_flag=1;
 }

PacketSource::~PacketSource()
 {
 }
 
void PacketSource::getStat(StatInfo &ret) 
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }

Packet<uint8> PacketSource::get() 
 { 
  return pset.get(100_msec);
 }

ulen PacketSource::getDataLen() 
 { 
  Mutex::Lock lock(mutex);
 
  return cdata.getLen(max_len); 
 }

void PacketSource::fill(PtrLen<uint8> data)
 {
  Mutex::Lock lock(mutex);
  
  if( !cdata.fill(data) )
    {
     stat.count(Event_nofill);
    }
 }
 
void PacketSource::check(PtrLen<const uint8> data)
 {
  if( !cdata.check(data) ) count(Event_broken);
 }

/* class PacketTask */

const char * GetTextDesc(PacketTask::Event ev)
 {
  static const char *const Table[]=
   {
    "nopacket",
    "outbound",
    "badformat",
    "inbound",
    "tick",
 
    ""
   };

  return Table[ev];
 }

void PacketTask::count(Event ev)
 {
  Mutex::Lock lock(mutex);
  
  stat.count(ev);
 }

void PacketTask::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  count(Event_inbound);
  
  src.check(data);
 
  packet.complete();
 }
  
void PacketTask::tick()
 {
  count(Event_tick);
 }
 
void PacketTask::run()
 {
  PacketFormat format=ep->getOutboundFormat();
    
  while( src.getRunFlag() )
    {
     Packet<uint8> packet=src.get();
     
     if( !packet ) 
       {
        count(Event_nopacket);
        
        continue;
       }
        
     ulen len=src.getDataLen();
        
     if( packet.checkDataLen(format,len) )
       {
        src.fill(packet.setDataLen(format,len));

        ep->outbound(packet);
        
        count(Event_outbound);
       }
     else
       {
        packet.complete();
        
        count(Event_badformat);
       }  
    }
 }
 
PacketTask::PacketTask(PacketSource &src_,StrLen ep_dev_name) 
 : src(src_),
   hook(ep_dev_name),
   ep(hook) 
 {
  ep->attach(this);  
 }
 
PacketTask::~PacketTask()
 {
  ep->detach();
 }

void PacketTask::getStat(StatInfo &ret) 
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }

/* class PacketEchoTest */ 

const char * GetTextDesc(PacketEchoTest::Event ev)
 {
  static const char *const Table[]=
   {
    "Rx",
    "Tx",
    
    "Broken packet",
    "No semaphore",
    
    ""
   };
 
  return Table[ev];
 }
 
void PacketEchoTest::traffic_init(ulen count)
 {
  Mutex::Lock lock(mutex);
     
  timer.reset();
     
  packet_count=count;
  total_data=0;
 }
  
void PacketEchoTest::traffic(ulen len)
 {
  Mutex::Lock lock(mutex);
     
  if( packet_count )
    {
     packet_count--;
        
     total_data+=len;
        
     if( !packet_count )
       {
        run_time=timer.get();
       }
    }
 }
  
void PacketEchoTest::traffic_exit()
 {
  Mutex::Lock lock(mutex);
     
  if( packet_count )
    {
     packet_count=0;
     
     run_time=timer.get();
    } 
 }

void PacketEchoTest::show_traffic()
 {
  uint64 total_data;
  MSecTimer::ValueType run_time;

  {
   Mutex::Lock lock(mutex);
   
   total_data=this->total_data;
   run_time=this->run_time;
  }
     
  uint64 speed=0;
     
  if( run_time ) speed=(total_data*1000)/run_time;
     
  Printf(Con,"Total data = #;\nRun time = #; msec\nSpeed = #; byte/sec\n\n",total_data,run_time,speed);
 }
  
void PacketEchoTest::count(Event ev)
 {
  Mutex::Lock lock(mutex);
     
  stat.count(ev);
 }
    
void PacketEchoTest::showStat()
 {
  ShowStat(*this,"PacketEchoTest");
  
  show_traffic();
 } 
   
void PacketEchoTest::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  traffic(data.len);
    
  if( cdata.check(data) )
    {
     count(Event_inbound);
    }
  else
    {
     count(Event_broken);
    }
       
  packet.complete();  
     
  sem.give();
 }
     
void PacketEchoTest::tick()
 {
  // do nothing
 }
     
void PacketEchoTest::send()
 {
  if( !sem.take(100_msec) ) count(Event_nosem);
    
  ulen len=cdata.getLen(format.max_data);
     
  Packet<uint8> packet=AllocPacket<uint8>();
  
  if( !packet ) return;
  
  if( packet.checkDataLen(format,len) )
    {
     cdata.fill(packet.setDataLen(format,len));
        
     packet.setDataLen(format,len);
        
     ep->outbound(packet);
        
     count(Event_outbound);
    }
  else
    {
     packet.complete();
    }
 } 
    
PacketEchoTest::PacketEchoTest(StrLen ep_dev_name)
 : hook(ep_dev_name),
   ep(hook),
   packet_count(0)
 {
  ep->attach(this);
     
  format=ep->getOutboundFormat();
 }
   
PacketEchoTest::~PacketEchoTest()
 {
  ep->detach();
 }
    
void PacketEchoTest::getStat(StatInfo &ret) 
 {
  Mutex::Lock lock(mutex);
     
  ret=stat;
 }
    
void PacketEchoTest::run(ulen forward,ulen cnt)
 {
  sem.give_many(forward);
     
  traffic_init(cnt);
     
  for(; cnt ;cnt--) send();
       
  Task::Sleep(1_sec);
  
  traffic_exit();
     
  showStat();
 } 
 
/* class PTPEchoTest */  

const char * GetTextDesc(PTPEchoTest::Event ev) 
 {
  static const char *const Table[]=
   {
    "done",
    "nodata",
    "baddata",
    "failed",
    "datalen",
    "no packet",
    "no memory",
    "timeout",
    
    ""
   };
 
  return Table[ev];
 }
 
void PTPEchoTest::count(Event ev)
 {
  Mutex::Lock lock(mutex);
     
  stat.count(ev);
 }
  
void PTPEchoTest::do_complete(Net::PTP::EchoTest::Ext *ext) 
 {
  if( ext->isOk() )
    {
     if( cdata.check(ext->info) )
       count(Event_done);
     else
       count(Event_baddata);
    }
  else
    {
     count(Event_failed);
    }  
 }
  
void PTPEchoTest::complete(PacketHeader *packet_)
 {
  Packet<uint8,Net::PTP::EchoTest::Ext> packet=packet_;
     
  do_complete(packet.getExt());
     
  packet.popExt().complete();
 }
  
void PTPEchoTest::objRun()
 {
  PacketFormat format=ptp->getFormat_guarded<Net::PTP::EchoTest::Ext>("App::PTPEchoTest::objRun()");
        
  ulen max_len=Min<ulen>(format.max_data,PosSub(ptp->getMaxInboundInfoLen(),Net::PTP::EchoTest::DeltaLen));
  
  PacketSet<uint8> pset(burst_count);
     
  while( run_flag )
    {   
     TimeScope time_scope(10_sec);
      
     for(ulen cnt=burst_count; cnt ;cnt--)
       {
        Packet<uint8> packet=pset.get(time_scope);
        
        if( !packet ) 
          { 
           count(Event_nopacket); 
           
           break; 
          }
        
        Packet<uint8,Net::PTP::EchoTest::Ext> packet2=packet.pushExt<Net::PTP::EchoTest::Ext>();
        
        packet2.pushCompleteFunction(function_complete());
           
        ulen len=cdata.getLen(max_len);
           
        if( packet2.checkDataLen(format,len) )
          {
           if( !cdata.fill(packet2.setDataLen(format,len)) ) count(Event_nodata);
        
           Net::PTP::EchoTest::Ext::InputType input(len);
        
           ptp->start_format(packet2,input);
          }
        else
          {
           count(Event_datalen);
             
           packet2.complete();
          }  
       }
        
     if( !pset.wait(time_scope) ) 
       {
        count(Event_timeout);
       }
    }
 }
    
PTPEchoTest::PTPEchoTest(StrLen ptp_dev_name,ulen burst_count_)
 : burst_count(burst_count_),
   hook(ptp_dev_name),
   ptp(hook)
 {
 }
   
PTPEchoTest::~PTPEchoTest()
 {
 }
    
void PTPEchoTest::getStat(StatInfo &ret) 
 {
  Mutex::Lock lock(mutex);
     
  ret=stat;
 }
 
/* class PacketRead */

PacketRead::FrameList::~FrameList()
 {
  while( Frame *frame=top.del_first() ) delete frame;
 }

auto PacketRead::FrameList::alloc() -> Frame *
 {
  Frame *frame=new(JustTry) Frame;
  
  if( frame )
    {
     Mutex::Lock lock(mutex);

     top.ins_last(frame);
     
     frame->time=timer.get();
    }
  
  return frame;
 }

void PacketRead::FrameList::copyTo(uint8 *base)
 {
  for(auto cur=top.start(); +cur ;++cur) cur->copyTo(base);
 }

void PacketRead::complete(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::ReadBufExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  if( ext->error )
    {
     set(ext->error);
    }
  else
    {
     if( Frame *frame=list.alloc() )
       {
        frame->off=ext->off;
        frame->len=ext->len;
        frame->data=ext->getData();
        
        packet.detach(frame->pbuf);
       }
     else
       {
        set(FileError_SysOverload);
       }
    }
  
  packet.popExt().complete();
 }

PacketRead::PacketRead(StrLen file_name)
 {
  AsyncFile file;
  
  file_len=file.open(file_name,Open_ToRead);
  
  ulen max_len=file.getMaxReadLen();
  
  if( !max_len )
    {
     Printf(Exception,"App::PacketRead::PacketRead(...) : getMaxReadLen() == 0");
    }
  
  ecount=0;
  error=FileError_Ok;
  
  for(FilePosType off=0; off<file_len ;)
    {
     ulen len=max_len;
     
     FilePosType avail=file_len-off;
     
     if( len>avail ) len=(ulen)avail;
     
     file.read(off,len,function_complete());
     
     off+=len;
    }
  
  file.wait_final();
 }

PacketRead::~PacketRead()
 {
 }

void PacketRead::guard()
 {
  if( error ) 
    {
     Printf(Exception,"App::PacketRead::guard() : #;",error);
    }
 }
 
void PacketRead::map(DynArray<uint8> &ret)
 {
  guard();
  
  ret.erase();
  
  uint8 *base=ret.extend_default((ulen)file_len).ptr;
  
  list.copyTo(base);
 }

/* class PTPServerTest::Report */

class PTPServerTest::Report : public ReportException
 {
   PrintPTPCon &con;
  
  private:
   
   virtual void print(StrLen str)
    {
     SilentReportException report; 
     
     try
       {
        Putobj(con,str);
       }
     catch(CatchType)
       {
       }
    }
  
  public:
   
   explicit Report(PrintPTPCon &con_) : con(con_) {}
   
   ~Report() {}
 };

/* class PTPServerTest::Split */ 

class PTPServerTest::Split
 {
   StrLen text;
   
  private:
  
   void skipSpace()
    {
     for(; +text && CharIsSpace(*text) ;++text);
    }
   
   StrLen nextSpace()
    {
     StrLen ret=text;
     
     for(; +ret && !CharIsSpace(*ret) ;++ret);
     
     return ret;
    }
   
  public:
   
   explicit Split(StrLen text_) : text(text_) {}
   
   StrLen take()
    {
     skipSpace();
     
     StrLen next=nextSpace();
     
     StrLen ret=text.prefix(next);
     
     text=next;
     
     if( !ret )
       {
        Printf(Exception,"App::PTPServerTest::Split::take() : not enough args");
       }
     
     return ret;
    }
   
   void finish()
    {
     skipSpace();
     
     if( +text )
       {
        Printf(Exception,"App::PTPServerTest::Split::finish() : too many args");
       }
    }
 };

/* class PTPServerTest */

void PTPServerTest::PrintFile(unsigned ind)
 {
  PrintPTPCon ptpcon("ptpcon");
  
  Report report(ptpcon);
  
  for(unsigned i=0; i<100 ;i++)
    {
     String file_name=Stringf("host:/test-dir/test-#;-#;.txt",ind,i);
     
     PrintAsyncFile out(Range(file_name));
     
     for(unsigned line=0; line<10000 ;line++)
       Printf(out,"--- #4; ------------------------------\n",line);
    }
  
  Printf(ptpcon,"PrintFile(#;) finished\n",ind);
  
  ptpcon.flush_and_wait();
 }

void PTPServerTest::cmd_empty(StrLen)
 {
 }

void PTPServerTest::cmd_exit(StrLen)
 {
  run_flag=false;
 }

void PTPServerTest::cmd_test1(StrLen)
 {
  for(unsigned line=0; line<1000 ;line++) 
    Printf(con,"--- #4; ------------------------\n",line);
 }

void PTPServerTest::cmd_test2(StrLen)
 {
  for(unsigned ind=0; ind<10 ;ind++) run_task( [=] () -> void { PrintFile(ind); } );
 }

void PTPServerTest::cmd_test3(StrLen)
 {
  Net::CheckedData data;
  
  for(unsigned cnt=100; cnt ;cnt--)
    {
     String file_name=Stringf("host:/test-dir/tmp#;",cnt);
     
     {
      PrintAsyncFile out(Range(file_name));
     
      ulen len=data.getLen(1_MByte);
     
      SimpleArray<uint8> buf(len);
     
      data.fill(Range(buf));
     
      out.put(MutatePtr<const char>(buf.getPtr()),buf.getLen());
     }
     {
      AsyncFileToMem map(Range(file_name));
      
      if( !data.check(Range(map)) )
        {
         Printf(Exception,"Data check failed");
        }
     }
    }
 }

void PTPServerTest::cmd_test4(StrLen)
 {
  Net::CheckedData data;
  
  for(unsigned cnt=100; cnt ;cnt--)
    {
     String file_name=Stringf("host:/test-dir/tmp#;",cnt);
     
     {
      PrintAsyncFile out(Range(file_name));
     
      ulen len=data.getLen(1_MByte);
     
      SimpleArray<uint8> buf(len);
     
      data.fill(Range(buf));
     
      out.put(MutatePtr<const char>(buf.getPtr()),buf.getLen());
     }
     {
      PacketRead read(Range(file_name));
      
      if( cnt==1 ) Putobj(con,read);
      
      DynArray<uint8> buf;
      
      read.map(buf);
      
      if( !data.check(Range_const(buf)) )
        {
         Printf(Exception,"Data check failed");
        }
     }
    }
 }

void PTPServerTest::cmd_list(StrLen arg)
 {
  AsyncFileListToMem cur(fs,arg);
     
  Printf(con,"#;\n",Title(arg));
     
  while( cur.next() )
    Printf(con,"#20l; #;\n",cur.getFileName(),cur.getFileType());
     
  Printf(con,"#;\n",TextDivider());
 }

void PTPServerTest::cmd_type(StrLen arg)
 {
  Printf(con,"#.q; #;\n",arg,fs.getFileType(arg));
 }

void PTPServerTest::cmd_show(StrLen arg)
 {
  String file_name=Stringf("host:/#;",arg);
     
  AsyncFileToMem file(Range(file_name));
     
  Printf(con,"#;\n",Title(arg));
     
  Putobj(con,StrLen(Mutate<const char>(Range(file))));
     
  Printf(con,"\n#;\n",TextDivider());
 }

void PTPServerTest::cmd_createFile(StrLen arg)
 {
  fs.createFile(arg);
 }

void PTPServerTest::cmd_deleteFile(StrLen arg)
 {
  fs.deleteFile(arg);
 }
  
void PTPServerTest::cmd_createDir(StrLen arg)
 {
  fs.createDir(arg);
 }

void PTPServerTest::cmd_deleteDir(StrLen arg)
 {
  fs.deleteDir(arg,false);
 }

void PTPServerTest::cmd_deleteDirRecursive(StrLen arg)
 {
  fs.deleteDir(arg,true);
 }

void PTPServerTest::cmd_rename(StrLen arg)
 {
  Split split(arg);
     
  StrLen name1=split.take();
  StrLen name2=split.take();
     
  split.finish();
  
  fs.rename(name1,name2,false);
 }

void PTPServerTest::cmd_renameOver(StrLen arg)
 {
  Split split(arg);
     
  StrLen name1=split.take();
  StrLen name2=split.take();
     
  split.finish();
  
  fs.rename(name1,name2,true);
 }

void PTPServerTest::cmd_remove(StrLen arg)
 {
  fs.remove(arg);
 }

void PTPServerTest::cmd_exec(StrLen arg)
 {
  Split split(arg);
     
  StrLen dir=split.take();
  StrLen program=split.take();
  StrLen execarg=split.take();
  
  split.finish();
     
  fs.exec(dir,program,execarg);
 }

void PTPServerTest::cmd_exec2(StrLen arg)
 {
  Split split(arg);
     
  StrLen dir=split.take();
  StrLen program=split.take();
     
  split.finish();
  
  PrintAsyncFile out;
     
  out.exec2(fs,dir,program);
     
  for(unsigned i=0; i<1000 ;i++)
    Printf(out,"---#;---\n",i);
     
  out.preserveFile();
 } 

void PTPServerTest::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&PTPServerTest::cmd_empty);
  addCommand(input,"exit",&PTPServerTest::cmd_exit);
  addCommand(input,"test1",&PTPServerTest::cmd_test1);
  addCommand(input,"test2",&PTPServerTest::cmd_test2);
  addCommand(input,"test3",&PTPServerTest::cmd_test3);
  addCommand(input,"test4",&PTPServerTest::cmd_test4);
  
  addCommand(input,"list",&PTPServerTest::cmd_list);
  addCommand(input,"type",&PTPServerTest::cmd_type);
  addCommand(input,"show",&PTPServerTest::cmd_show);
  
  addCommand(input,"mkfile",&PTPServerTest::cmd_createFile);
  addCommand(input,"rmfile",&PTPServerTest::cmd_deleteFile);
  addCommand(input,"mkdir",&PTPServerTest::cmd_createDir);
  addCommand(input,"rmdir",&PTPServerTest::cmd_deleteDir);
  addCommand(input,"rmdirall",&PTPServerTest::cmd_deleteDirRecursive);
  
  addCommand(input,"rename",&PTPServerTest::cmd_rename);
  addCommand(input,"renameover",&PTPServerTest::cmd_renameOver);
  addCommand(input,"remove",&PTPServerTest::cmd_remove);
  addCommand(input,"exec",&PTPServerTest::cmd_exec);
  addCommand(input,"exec2",&PTPServerTest::cmd_exec2);
  
  //addCommand(input,"",&PTPServerTest::cmd_);
 }

PTPServerTest::PTPServerTest()
 : hfs("ptp"),
   hfs_master(hfs,"hfs"),
   host("hfs"),
   host_master(host,"host"),
   ptpcon("ptp"),
   ptpcon_master(ptpcon,"ptpcon"),
   ptpcon_cfg(Net::PTPCon::TriggerAll),
   ptpcon_open_close("ptpcon","PTPServerTest",ptpcon_cfg),
   con("ptpcon"),
   cmd_input(*this,"test> ",ptpcon_open_close),
   fs("host")
 {
 }

PTPServerTest::~PTPServerTest()
 {
 }

void PTPServerTest::run()
 {
  Report report(con);
  
  run_flag=true;
  
  while( run_flag )
    try
      {
       con.flush_and_wait();
       
       cmd_input.command(report);
     
       report.guard();
      }
    catch(CatchType)
      {
       run_flag=false;
      }
    
  con.flush_and_wait();
 }

} // namespace App
 

