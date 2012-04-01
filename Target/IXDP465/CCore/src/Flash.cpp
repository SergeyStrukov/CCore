/* Flash.cpp */ 
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
 
#include <CCore/inc/Flash.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/UIntSplit.h>
#include <CCore/inc/Print.h>
 
namespace CCore {
namespace Flash {

/* functions */ 

static void Wait(unsigned times)
 {
  volatile unsigned cnt=times;
  
  while( cnt ) cnt--;
 }
 
bool Erase(ulen block_index)
 {
  if( block_index>=BlockCount )
    {
     Printf(Exception,"CCore::Flash::Erase(#;) : out of range",block_index);
    }
    
  volatile uint16 *ptr=(volatile uint16 *)(Base+block_index*BlockSize);  
  
  *ptr=0x20;
  *ptr=0xD0;
  
  Wait(1024);
  
  for(;;)
    {
     uint16 ret=*ptr;
     
     if( ret&0x80 )
       {
        return (ret&0x20)==0;
       }
    }
 }
 
bool Write16(ulen off,uint16 data)
 {
  if( off>=Size )
    {
     Printf(Exception,"CCore::Flash::Write(#;,...) : out of range",off);
    }
 
  if( off&1 )
    {
     Printf(Exception,"CCore::Flash::Write(#;,...) : odd offset",off);
    }
 
  volatile uint16 *ptr=(volatile uint16 *)(Base+off);  
  
  *ptr=0x40;
  *ptr=data;
  
  Wait(40);
  
  for(;;)
    {
     uint16 ret=*ptr;
     
     if( ret&0x80 )
       {
        return (ret&0x10)==0;
       }
    }
 }
 
bool Write32(ulen off,uint32 data)
 {
  UIntSplit<uint32,uint16> split;
  
  split.set(data);
  
  uint16 d0=split[0]; // BE
  uint16 d1=split[1];
 
  return Write16(off,d0) && Write16(off+2,d1) ;
 }
 
bool Write(ulen off,PtrLen<const uint32> data)
 {
  for(; +data ;++data,off+=4) 
    {
     if( (data.len%10000)==0 )
       {
        Printf(Con,"Writing... #; words remain\n",data.len);
       }
     
     if( !Write32(off,*data) ) return false;
    }
  
  return true;
 }
 
void ReadMode()
 {
  volatile uint16 *ptr=(volatile uint16 *)(Base);  
  
  *ptr=0xFF;
  
  Wait(1024);
 }
 
} // namespace Flash
} // namespace CCore
 

