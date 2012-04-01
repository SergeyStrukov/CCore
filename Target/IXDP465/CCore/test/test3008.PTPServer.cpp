/* test3008.PTPServer.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/PTPSupport.h>

namespace App {

namespace Private_3008 {

/* using */ 

using Net::PTP::FlagType;
using Net::HFS::FileId; 
using Net::HFS::FileLenType;

using Net::HFS::OpenFlag_Read;
using Net::HFS::OpenFlag_Write;
using Net::HFS::OpenFlag_Create;
using Net::HFS::OpenFlag_Erase;
using Net::HFS::OpenFlag_New;
using Net::HFS::OpenFlag_AutoDelete;

/* class Test */ 

class Test : public Funchor_nocopy
 {
   Net::HFS::ClientDevice hfs;
   
   PacketSet<uint8> pset;
   MSec timeout;
   
   FileId file_id;
   FileLenType file_len;
   FileLenType write_off;
   FileLenType read_off;
   
   Net::PTP::TransStatus status;
   
   Mutex mutex;
   
  private: 
  
   template <class Ext>
   void guard(const char *name,TimeScope time_scope)
    {
     status.guard<Ext>(Exception,hfs.getPTPDevice(),pset,name,time_scope);
    }
  
   void complete_open(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::OpenExt> packet=packet_;
     
     Net::HFS::OpenExt *ext=packet.getExt();
     
     if( status.set(ext) )
       {
        file_id=ext->file_id;
        file_len=ext->file_len;
        write_off=0;
        read_off=0;
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_open() { return FunctionOf(this,&Test::complete_open); }
  
   void complete_close(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::CloseExt> packet=packet_;
     
     Net::HFS::CloseExt *ext=packet.getExt();
     
     status.set(ext);
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_close() { return FunctionOf(this,&Test::complete_close); }
   
   void complete_write(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::WriteExt> packet=packet_;
     
     Net::HFS::WriteExt *ext=packet.getExt();
     
     {
      Mutex::Lock lock(mutex);
     
      if( status.ok && status.set(ext) )
        {
         Replace_max(file_len,ext->file_len);
        }
     }  
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_write() { return FunctionOf(this,&Test::complete_write); }
   
   void complete_read(PacketHeader *packet_)
    {
     Packet<uint8,PtrLen<char>,Net::HFS::ReadExt> packet=packet_;
     
     Net::HFS::ReadExt *ext=packet.getExt();
     PtrLen<char> chunk=*packet.getDeepExt<1>();
     bool ok;
     
     {
      Mutex::Lock lock(mutex);
     
      if( status.ok && status.set(ext) )
        {
         if( chunk.len==ext->data.len )
           {
            ok=true;
           }
         else
           {
            status.setError(Net::PTP::Trans_Ok,Net::PTP::Error_Unknown);
           
            ok=false;
           }  
        }
      else
        {
         ok=false;
        }  
     }  
     
     if( ok )
       {
        ext->data.copyTo(chunk.ptr);
       }
     
     packet.popExt().popExt().complete();
    }
    
   PacketFunction function_complete_read() { return FunctionOf(this,&Test::complete_read); } 
   
  public:
  
   Test() : hfs("ptp"),pset("Test"),timeout(DefaultTimeout),mutex("Test") {}
   
   ~Test() {}
   
   void open(StrLen file_name,FlagType open_flags)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::OpenExt>("Test::open(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::OpenExt> packet2=packet.pushExt<Net::HFS::OpenExt>(); 
     
     packet2.pushCompleteFunction(function_complete_open());
     
     hfs.open(packet2,file_name,open_flags);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::OpenExt>("Test::open(...)",time_scope);
    }
    
   void close(bool preserve_file=false) 
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::CloseExt>("Test::close(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::CloseExt> packet2=packet.pushExt<Net::HFS::CloseExt>(); 
     
     packet2.pushCompleteFunction(function_complete_close());
     
     hfs.close(packet2,file_id,preserve_file);
        
     pset.wait(time_scope);
        
     guard<Net::HFS::CloseExt>("Test::close(...)",time_scope);
    }
 
   template <class Fill>
   void write(Fill &fill)
    {
     TimeScope time_scope(timeout);
     
     while( ulen len=fill.getLen() )
       {
        Packet<uint8> packet=pset.get(time_scope);
     
        if( !packet )
          {
           status.setNoPacket();
        
           guard<Net::HFS::WriteExt>("Test::write(...)",time_scope);
          }
       
        Packet<uint8,Net::HFS::WriteExt> packet2=packet.pushExt<Net::HFS::WriteExt>(); 
        
        ulen max_len=packet2.getMaxDataLen(hfs.getWriteFormat()).len;
        
        if( !max_len )
          {
           packet2.popExt().complete();
           
           Printf(Exception,"Test::write(...) : outbound is too short");
          }
          
        Replace_min(len,max_len);  
        
        fill.fill(packet2.setDataLen(hfs.getWriteFormat(),len));
     
        packet2.pushCompleteFunction(function_complete_write());
     
        hfs.write(packet2,file_id,write_off);
        
        write_off+=len;
       }
       
     pset.wait(time_scope);
        
     guard<Net::HFS::WriteExt>("Test::write(...)",time_scope);
    }
 
   void read(PtrLen<char> buf)
    {
     TimeScope time_scope(timeout);
     
     while( +buf )
       {
        Packet<uint8> packet=pset.get(time_scope);
        
        if( !packet )
          {
           status.setNoPacket();
        
           guard<Net::HFS::ReadExt>("Test::read(...)",time_scope);
          }
          
        PtrLen<char> chunk=buf.takeup(hfs.getMaxReadLen());
        
        Packet<uint8,PtrLen<char>,Net::HFS::ReadExt> packet2=packet.pushExt<PtrLen<char> >(chunk).pushExt<Net::HFS::ReadExt>(Net::PTP::MoveNothing);
        
        packet2.pushCompleteFunction(function_complete_read());
        
        hfs.read(packet2.forgetExt<1>(),file_id,read_off,chunk.len);
        
        read_off+=chunk.len;
       }
       
     pset.wait(time_scope);
        
     guard<Net::HFS::ReadExt>("Test::read(...)",time_scope);
    }
 };
 
/* class RangeFill */  

class RangeFill : NoCopy
 {
   PtrLen<const char> data;
   
  public: 
  
   RangeFill(const char *ptr,ulen len) : data(ptr,len) {}
   
   ulen getLen() const { return data.len; }
   
   void fill(PtrLen<uint8> buf)
    {
     buf.copyFrom(data.ptr);
    
     data+=buf.len;
    }
 };
 
/* class PrintTest */  

class PrintTest : public PrintBase
 {
   Test &test;
   
   SimpleArray<char> buf;
 
  private:
  
   virtual PtrLen<char> do_provide(ulen)
    {
     return Range(buf);
    }
   
   virtual void do_flush(char *ptr,ulen len)
    {
     RangeFill fill(ptr,len);
     
     test.write(fill);
    }
   
  public:
  
   explicit PrintTest(Test &test_) : test(test_),buf(16_KByte) {}
   
   ~PrintTest() 
    {
     try
       {
        flush(); 
       }
     catch(CatchType) {}
    }
 };
 
/* class Engine */  

class Engine : NoCopy
 {
   Net::NanoUDPEndpointDevice udp;
   
   ObjMaster udp_master;
 
   Net::PTP::ClientDevice ptp;
   
   ObjMaster ptp_master;
   
  public:
  
   explicit Engine(Net::UDPoint dst)
    : udp("IP",Net::PTPClientUDPort,false,dst),
      udp_master(udp,"udp"),
      ptp("udp"),
      ptp_master(ptp,"ptp")
    {
    }
    
   ~Engine()
    {
    } 
    
   void run()
    {
     ReportException report;
     
     ptp.support_guarded(10_sec);
     
     Printf(Con,"max in  = #;\nmax out = #;\n",ptp.getMaxInboundInfoLen(),ptp.getMaxOutboundInfoLen());
     
     Test test;
     
     test.open("temp.txt",OpenFlag_Write|OpenFlag_Create|OpenFlag_Erase);
     
     {
      PrintTest out(test);
      
      SecTimer timer;
      
      for(ulen ind=0; ind<1000000 ;ind++)
        {
         Printf(out,"--- #6; ---------------------------------------------------\n",ind);
        }
        
      Printf(Con,"time = #; sec\n",timer.get());  
     }
     
     test.close();
     
     test.open("temp.txt",OpenFlag_Read);
     
     {
      SimpleArray<char> buf(16_KByte);
      
      test.read(Range(buf));
      
      Printf(Con,"buf=\n#;\n",StrLen(Range_const(buf)));
     }
     
     test.close();

     try
       {
        test.open("nodir/temp.txt",OpenFlag_Read);
       }
     catch(CatchType) {}
       
     try
       {
        test.open("../temp.txt",OpenFlag_Read);
       }
     catch(CatchType) {}
       
     try
       {
        test.open("nofile.txt",OpenFlag_Read);
       }
     catch(CatchType) {}
     
     try
       {
        test.open("~/temp.txt",OpenFlag_Read);
       }
     catch(CatchType) {}
    }
 };
    
} // namespace Private_3008
 
using namespace Private_3008; 
 
/* Testit<3008> */ 

template<>
const char *const Testit<3008>::Name="Test3008 PTPServer";

template<>
bool Testit<3008>::Main() 
 { 
  IPEngine ip_engine;
  
  Engine engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  engine.run();
  
  return true;
 }
 
} // namespace App
 
