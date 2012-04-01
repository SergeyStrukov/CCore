/* test3009.PTPServer.cpp */ 
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
#include <CCore/inc/net/PTPConDevice.h>
#include <CCore/inc/RedirectPTPCon.h>
#include <CCore/inc/String.h>

namespace App {

namespace Private_3009 {

/* using */ 

using Net::PTP::FlagType;

/* class Test */ 

class Test : public Funchor_nocopy
 {
   Net::HFS::ClientDevice hfs;
   
   PacketSet<uint8> pset;
   MSec timeout;
   
   FlagType type;
   
   Net::PTP::TransStatus status;
   
   // file
   
   Net::HFS::FileId file_id;
   Net::HFS::FileLenType file_len;
   Net::HFS::FileLenType file_off;
   
   PacketBuf pbuf;
   PtrLen<const uint8> data;
   
  private: 
  
   template <class Ext>
   void guard(const char *name,TimeScope time_scope)
    {
     status.guard<Ext>(Exception,hfs.getPTPDevice(),pset,name,time_scope);
    }
    
   void complete_getFileType(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::GetFileTypeExt> packet=packet_;
     
     Net::HFS::GetFileTypeExt *ext=packet.getExt();
     
     if( status.set(ext) )
       {
        type=ext->type;
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_getFileType() { return FunctionOf(this,&Test::complete_getFileType); }
   
   void complete_getFileList(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::GetFileListExt> packet=packet_;
     
     Net::HFS::GetFileListExt *ext=packet.getExt();
     
     if( status.set(ext) )
       {
        file_id=ext->file_id;
        file_len=ext->file_len;
        file_off=0;
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_getFileList() { return FunctionOf(this,&Test::complete_getFileList); }
   
   void complete_exec2(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::Exec2Ext> packet=packet_;
     
     Net::HFS::Exec2Ext *ext=packet.getExt();
     
     if( status.set(ext) )
       {
        file_id=ext->file_id;
        file_len=0;
        file_off=0;
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_exec2() { return FunctionOf(this,&Test::complete_exec2); }
   
   void complete_read(PacketHeader *packet_)
    {
     Packet<uint8,Net::HFS::ReadExt> packet=packet_;
     
     Net::HFS::ReadExt *ext=packet.getExt();
     
     if( status.set(ext) )
       {
        packet.detach(pbuf);
        
        data=ext->data;
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete_read() { return FunctionOf(this,&Test::complete_read); }
 
   template <class Ext>
   void complete_empty(PacketHeader *packet_)
    {
     Packet<uint8,Ext> packet=packet_;
     
     Ext *ext=packet.getExt();
     
     status.set(ext);
     
     packet.popExt().complete();
    }
    
   template <class Ext>
   PacketFunction function_complete_empty() { return FunctionOf(this,&Test::complete_empty<Ext>); }
   
  public:
  
   Test() : hfs("ptp"),pset("Test"),timeout(DefaultTimeout) {}
   
   ~Test() {}
   
   void getFileType(StrLen path)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::GetFileTypeExt>("Test::getFileType(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::GetFileTypeExt> packet2=packet.pushExt<Net::HFS::GetFileTypeExt>(); 
     
     packet2.pushCompleteFunction(function_complete_getFileType());
     
     hfs.getFileType(packet2,path);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::GetFileTypeExt>("Test::getFileType(...)",time_scope);
     
     Printf(Con,"getFileType(\"#;\") = #;\n",path,type);
    }
    
   void getFileList(StrLen path) 
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::GetFileListExt>("Test::getFileList(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::GetFileListExt> packet2=packet.pushExt<Net::HFS::GetFileListExt>(); 
     
     packet2.pushCompleteFunction(function_complete_getFileList());
     
     hfs.getFileList(packet2,path);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::GetFileListExt>("Test::getFileList(...)",time_scope);
    }
 
   void readFile()
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::ReadExt>("Test::readFile(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::ReadExt> packet2=packet.pushExt<Net::HFS::ReadExt>(Net::PTP::MovePacketBuf); 
     
     packet2.pushCompleteFunction(function_complete_read());
     
     hfs.read(packet2,file_id,file_off,hfs.getMaxReadLen());
     
     pset.wait(time_scope);
     
     guard<Net::HFS::ReadExt>("Test::readFile(...)",time_scope);
     
     file_off+=data.len;
    }
 
   void showFile()
    {
     while( file_off<file_len )
       {
        readFile();
        
        if( !data.len ) break;
        
        Putobj(Con,StrLen(Mutate<const char>(data)));
       }
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
     
        packet2.pushCompleteFunction(function_complete_empty<Net::HFS::WriteExt>());
     
        hfs.write(packet2,file_id,file_off);
        
        file_off+=len;
       }
       
     pset.wait(time_scope);
        
     guard<Net::HFS::WriteExt>("Test::write(...)",time_scope);
    }
    
   void closeFile(bool preserve_file=false)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::CloseExt>("Test::closeFile(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::CloseExt> packet2=packet.pushExt<Net::HFS::CloseExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::CloseExt>());
     
     hfs.close(packet2,file_id,preserve_file);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::CloseExt>("Test::closeFile(...)",time_scope);
    }
 
   void createFile(StrLen file_name)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::CreateFileExt>("Test::createFile(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::CreateFileExt> packet2=packet.pushExt<Net::HFS::CreateFileExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::CreateFileExt>());
     
     hfs.createFile(packet2,file_name);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::CreateFileExt>("Test::createFile(...)",time_scope);
    }
    
   void deleteFile(StrLen file_name)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::DeleteFileExt>("Test::deleteFile(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::DeleteFileExt> packet2=packet.pushExt<Net::HFS::DeleteFileExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::DeleteFileExt>());
     
     hfs.deleteFile(packet2,file_name);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::DeleteFileExt>("Test::deleteFile(...)",time_scope);
    }
 
   void createDir(StrLen dir_name)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::CreateDirExt>("Test::createDir(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::CreateDirExt> packet2=packet.pushExt<Net::HFS::CreateDirExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::CreateDirExt>());
     
     hfs.createDir(packet2,dir_name);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::CreateDirExt>("Test::createDir(...)",time_scope);
    }
 
   void deleteDir(StrLen dir_name,bool recursive)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::DeleteDirExt>("Test::deleteDir(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::DeleteDirExt> packet2=packet.pushExt<Net::HFS::DeleteDirExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::DeleteDirExt>());
     
     hfs.deleteDir(packet2,dir_name,recursive);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::DeleteDirExt>("Test::deleteDir(...)",time_scope);
    }
 
   void rename(StrLen old_path,StrLen new_path,bool allow_owerwrite)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::RenameExt>("Test::rename(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::RenameExt> packet2=packet.pushExt<Net::HFS::RenameExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::RenameExt>());
     
     hfs.rename(packet2,old_path,new_path,allow_owerwrite);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::RenameExt>("Test::rename(...)",time_scope);
    }
    
   void remove(StrLen path)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::RemoveExt>("Test::remove(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::RemoveExt> packet2=packet.pushExt<Net::HFS::RemoveExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::RemoveExt>());
     
     hfs.remove(packet2,path);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::RemoveExt>("Test::remove(...)",time_scope);
    }
    
   void exec(StrLen dir,StrLen program,StrLen arg)
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::ExecExt>("Test::exec(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::ExecExt> packet2=packet.pushExt<Net::HFS::ExecExt>(); 
     
     packet2.pushCompleteFunction(function_complete_empty<Net::HFS::ExecExt>());
     
     hfs.exec(packet2,dir,program,arg);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::ExecExt>("Test::exec(...)",time_scope);
    }
   
   void exec2(StrLen dir,StrLen program) 
    {
     TimeScope time_scope(timeout);
     
     Packet<uint8> packet=pset.get(time_scope);
     
     if( !packet )
       {
        status.setNoPacket();
        
        guard<Net::HFS::Exec2Ext>("Test::exec2(...)",time_scope);
       }
       
     Packet<uint8,Net::HFS::Exec2Ext> packet2=packet.pushExt<Net::HFS::Exec2Ext>(); 
     
     packet2.pushCompleteFunction(function_complete_exec2());
     
     hfs.exec2(packet2,dir,program);
     
     pset.wait(time_scope);
        
     guard<Net::HFS::Exec2Ext>("Test::exec2(...)",time_scope);
    }
 };
 
/* class Fill */  

class Fill : NoCopy
 {
   ulen len;
 
  public:
  
   explicit Fill(ulen len_) : len(len_) {}
   
   ulen getLen() const { return len; }
   
   void fill(PtrLen<uint8> buf)
    {
     buf.set('x');
     
     len-=buf.len;
    }
 };
   
/* class Engine */  

class Engine : NoCopy
 {
   Net::NanoUDPEndpointDevice udp;
   
   ObjMaster udp_master;
 
   Net::PTP::ClientDevice ptp;
   
   struct Support
    {
     explicit Support(Net::PTP::ClientDevice &ptp)
      {
       ptp.support_guarded(10_sec);
      }
      
    } support;
    
   ObjMaster ptp_master;
   
   Net::PTPCon::ClientDevice ptpcon;
   
   ObjMaster ptpcon_master;
   
   RedirectPTPCon redirect;
   
  public:
  
   explicit Engine(Net::UDPoint dst)
    : udp("IP",Net::PTPClientUDPort,false,dst),
      udp_master(udp,"udp"),
      ptp("udp"),
      support(ptp),
      ptp_master(ptp,"ptp"),
      ptpcon("ptp"),
      ptpcon_master(ptpcon,"ptpcon"),
      redirect("ptpcon","test3009")
    {
    }
    
   ~Engine()
    {
    } 
    
   void run()
    {
     Printf(Con,"max in  = #;\nmax out = #;\n",ptp.getMaxInboundInfoLen(),ptp.getMaxOutboundInfoLen());
     
     Test test;
     
     // getFileType
     
     test.getFileType(".");
     
     test.getFileType("nofile.txt");
     
     test.getFileType("PTPServerLog.txt");
     
     // createFile
     
     for(ulen i=1; i<1000 ;i++)
       {
        String file_name=Stringf("new_file#;.txt",i);
       
        test.createFile(Range(file_name));
       }
     
     // getFileList
     
     test.getFileList(".");
     
     test.showFile();
     
     test.closeFile();
     
     // deleteFile
     
     for(ulen i=1; i<1000 ;i++)
       {
        String file_name=Stringf("new_file#;.txt",i);
       
        test.deleteFile(Range(file_name));
       }
       
     // createDir
     
     test.createDir("new_dir");  
     test.createFile("new_dir/new_file.txt");  
     
     // deleteDir
     
     test.deleteDir("new_dir",true);
     
     // rename
     
     test.createFile("new_file.txt");
     test.createFile("new_file3.txt");
     
     test.rename("new_file.txt","new_file2.txt",false);
     test.rename("new_file2.txt","new_file3.txt",true);
     
     test.deleteFile("new_file3.txt");
     
     // remove
     
     test.createDir("new_dir");  
     test.createFile("new_dir/new_file.txt");  
     
     test.remove("new_dir/new_file.txt");
     test.remove("new_dir");
     
     // exec
     
     test.exec("test-dir","exectest.exe","1 2 3 4 5");
     
     // exec2
     
     test.exec2("test-dir1","exectest.exe");
     
     Fill fill(6_KByte);
     
     test.write(fill);
     
     test.closeFile(true);
     
     test.exec2("new_dir","test.exe");
     
     test.closeFile();
    }
 };
    
} // namespace Private_3009
 
using namespace Private_3009; 
 
/* Testit<3009> */ 

template<>
const char *const Testit<3009>::Name="Test3009 PTPServer";

template<>
bool Testit<3009>::Main() 
 { 
  IPEngine ip_engine;
  
  Engine engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  engine.run();
  
  return true;
 }
 
} // namespace App
 
