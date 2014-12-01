/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: BeagleBoot 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Elf.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PTPBoot.h>

namespace App {

using namespace CCore;

/* enum BootFlags */ 

enum BootFlags
 {
  BootRun,
  BootFlash,
  BootFlashBoot
 };
 
/* struct PrintFlags */ 
 
struct PrintFlags
 {
  uint32 flags;
  
  explicit PrintFlags(uint32 flags_) : flags(flags_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( flags&Elf::SectFlag_code )
      Putobj(out,"C  ");
    else
      Putobj(out,"D  ");
    
    if( flags&Elf::SectFlag_write )
      Putobj(out,"RW");
    else
      Putobj(out,"RO");
   }
 };
 
/* class Load */ 

class Load : NoCopy
 {
   struct Rec : NoThrowFlagsBase
    {
     StrLen name;
     Elf::SectHeader sect;
     PtrLen<const uint8> data;
     
     Rec(StrLen name_,const Elf::SectHeader &sect_,PtrLen<const uint8> data_) : name(name_),sect(sect_),data(data_) {}
     
     bool operator < (const Rec &b) const { return sect.address<b.sect.address ; }
    };
    
   DynArray<Rec> table;
   
   uint32 entry_point;
   
  private:
  
   static const uint32 MinAddress   = 0x80100000 ;
   static const uint32 LimAddress   = 0x90000000 ;
   static const uint32 AlignAddress =          4 ;
  
   static uint32 Guard(uint32 address,uint32 size);
   
   static void Guard(uint32 entry_point);
   
  public:
  
   Load() {}
   
   ~Load() {}
  
   void operator () (const Elf::Header &header)
    {
     if( !header.check_id(Elf::BitType_32,Elf::EndianType_LE) )
       {
        Printf(Exception,"Bad file");
       }
       
     if( !header.check_cpu(Elf::CPUType_ARM) )
       {
        Printf(Exception,"Bad file");
       }
     
     Guard(header.entry_point);
       
     entry_point=header.entry_point;
    }
    
   void operator () (ulen,StrLen,const Elf::SectHeader &)
    {
    }
    
   void operator () (ulen,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data)
    {
     table.append_fill(name,sect,data);
    }
    
   void operator () (); 
    
   void boot(BootFlags flags); 
 };
 
uint32 Load::Guard(uint32 address,uint32 size)
 {
  uint32 lim=address+size;
        
  if( address<MinAddress )
    {
     Printf(Exception,"Section is below limit");
    }
        
  if( size>LimAddress || address>LimAddress-size )
    {
     Printf(Exception,"Section is above limit");
    }
    
  if( address%AlignAddress )  
    {
     Printf(Exception,"Section is not aligned");
    }

  return lim;     
 }
 
void Load::Guard(uint32 entry_point)
 {
  if( entry_point<MinAddress )
    {
     Printf(Exception,"Entry point is below limit");
    }
  
  if( entry_point>=LimAddress )
    {
     Printf(Exception,"Entry point is above limit");
    }
  
  if( entry_point%AlignAddress )
    {
     Printf(Exception,"Entry point is not aligned");
    }
 }

void Load::operator () ()
 {
  Sort(Range(table));
     
  ulen max_name_len=8;
     
  for(auto r=Range(table); +r ;++r) Replace_max(max_name_len,r->name.len);
     
  StrPrintOpt name_opt;
     
  name_opt.width=max_name_len;
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
   
  Printf(Con,"#;   address      size  flags\n",BindOpt(name_opt,"name"));
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
     
  for(auto r=Range(table); +r ;++r)
    {
     Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",BindOpt(name_opt,r->name),r->sect.address,r->sect.size,PrintFlags(r->sect.flags));
     
     uint32 lim=Guard(r->sect.address,r->sect.size);
     
     if( r.len>=2 )
       {
        auto r1=&(r[1]);
        
        if( r1->sect.address<lim )
          {
           Printf(Exception,"Section overlapp");
          }
             
        if( r1->sect.address>lim )  
          {
           Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",RepeatChar(max_name_len,' '),lim,(r1->sect.address-lim),"hole");
          }
       }
     else
       {
        Printf(Con,"#;  #8.16i;\n",RepeatChar(max_name_len,' '),lim);
       }
    } 
       
  Printf(Con,"#;  --------  --------  -----\n\n",RepeatChar(max_name_len,'-'));  
     
  Printf(Con,"entry_point = #8.16i;\n\n",entry_point);
 } 
    
void Load::boot(BootFlags flags) 
 {
  Net::PTPBoot::BootClient client("ptp");
  
  for(auto r=Range(table); +r ;++r)
    {
     auto index=client.alloc(r->sect.address,r->sect.size);
     
     client.write(index,0,r->data);
    }
    
  client.boot(entry_point,flags);  
 }
 
/* Main() */ 

bool MakeFlags(BootFlags &flags,StrLen type)
 {
  if( type.len!=1 ) return false;
  
  switch( type[0] )
    {
     case 'r' : case 'R' : flags=BootRun;       return true;
     case 'f' : case 'F' : flags=BootFlash;     return true;
     case 'b' : case 'B' : flags=BootFlashBoot; return true;
    }
    
  return false;  
 }
 
int Main(StrLen type,StrLen ip,StrLen file_name)
 {      
  BootFlags flags=BootRun;
  
  if( !MakeFlags(flags,type) )
    {
     Printf(Exception,"Bad type: #.q;",type);
    }
  
  //Printf(Con,"ip = #.q;\nfile_name = #.q;\n",ip,file_name);
  
  Net::IPAddress dst_ip;
  
  StrParse dev(ip);
  
  Net::ParseIPAddress(dev,dst_ip);
  
  if( !dev.finish() )
    {
     Printf(Exception,"Bad IP address string: #.q;",ip);
    }
    
  //Printf(Con,"ip = #;\n",dst_ip);  
  
  FileToMem file(file_name);
  
  Load load;
  
  Elf::Parse<LeOrder>(load,Range(file));

  Net::AsyncUDPEndpointDevice udp(Net::PTPClientUDPort,Net::UDPoint(dst_ip,Net::PTPServerUDPort));
   
  ObjMaster udp_master(udp,"udp");
  
  Net::PTP::ClientDevice ptp("udp");
  
  ObjMaster ptp_master(ptp,"ptp");
  
  Net::AsyncUDPEndpointDevice::StartStop start_stop(udp);
  
  ptp.support_guarded();

  load.boot(flags);
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main(int argc,const char *argv[])
 {
  if( argc!=4 ) 
    {
     Printf(Con,"Usage: BeagleBoot.exe (r|f|b) <IP address> <file_name>\n");
    
     return 1;
    }

  int ret=0;

  try
    {
     ReportException report;
     
     {
      ret=App::Main(argv[1],argv[2],argv[3]);
     }

     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }

  return ret;
 }
 
