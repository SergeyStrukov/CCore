/* test3014.Flash.cpp */ 
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

#include <CCore/inc/Flash.h>

namespace App {

namespace Private_3014 {

/* Dump() */

void Dump(StrLen file_name,const uint32 *base,ulen len)
 {
  PrintAsyncFile out(file_name);
  
  ulen off=0;

  for(; len>=8 ;base+=8,len-=8,off+=32)
    {
     Printf(out,"#7.16i;  #8.16i; #8.16i; #8.16i; #8.16i; #8.16i; #8.16i; #8.16i; #8.16i;\n",
                 off,base[0],base[1],base[2],base[3],base[4],base[5],base[6],base[7]);
    }
 }
 
} // namespace Private_3014
 
using namespace Private_3014; 
 
/* Testit<3014> */ 

template<>
const char *const Testit<3014>::Name="Test3014 Flash";

template<>
bool Testit<3014>::Main() 
 { 
  IPEngine ip_engine;
  
  HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));

  uint32 *base=static_cast<uint32 *>(Flash::GetBaseAddress());
  
  ulen len=0x200000; // 8 MByte/4
  
  Dump("host:FlashDump0.txt",base,len);
  //Dump("host:FlashDump1.txt",base+len,len);
  //Dump("host:FlashDump2.txt",base+2*len,len);
  //Dump("host:FlashDump3.txt",base+3*len,len);
  
#if 0
  
  ulen ind=Flash::BlockCount/2;

  if( !Flash::Erase(ind) )
    {
     Printf(Exception,"Flash erase failure");
    }
    
  uint16 data=0;  
    
  for(ulen off=Flash::Size/2,lim=off+Flash::BlockSize; off<lim ;data++,off+=2) 
    if( !Flash::Write16(off,data) )
      {
       Printf(Exception,"Flash write failure");
      }
  
  Flash::ReadMode();  
  
  Dump("host:flash.txt",base+Flash::Size/8,Flash::BlockSize/4);
  
#endif  
  
  return true;
 }
 
} // namespace App
 
