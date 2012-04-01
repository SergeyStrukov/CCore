/* Boot.cpp */ 
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
 
#include <CCore/inc/Boot.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>

#include <string.h>

extern "C" {

extern void __std_boot(unsigned *ptr,unsigned *lim);

extern const unsigned __std_boot_beg;
extern const unsigned __std_boot_end;

extern const unsigned __std_bootflash_beg;
extern const unsigned __std_bootflash_end;

} // extern "C"
 
namespace CCore {

/* class Boot::Wait */

Boot::Wait::Wait()
 : msem("Boot::Wait")
 {
 }

Boot::Wait::~Wait()
 {
 }

void Boot::Wait::complete()
 {
  msem.give(SignalDone);
 }

Sys::ConInputResult Boot::Wait::key_any(char)
 {
  msem.give_any(SignalKey);
  
  return Sys::Con_NoEcho;
 }

void Boot::Wait::wait()
 {
  ulen cnt=0;
  bool aloud=true;
  
  for(;;)
    switch( msem.take(3_sec) )
      {
       case SignalTimeout :
        {
         if( aloud )
           {
            if( !cnt ) cnt=10;
            
            Printf(Con,"waiting#;\n",RepeatChar(cnt--,'.'));
           }
        }
       break;
       
       case SignalDone :
        {
         Printf(Con,"\ndone\n");
         
         return;
        }
       break;
       
       case SignalKey :
        {
         if( aloud )
           {
            Printf(Con,"silent\n");
            
            aloud=false;
           }
         else
           {
            Printf(Con,"aloud\n");
            
            aloud=true;
           }
        }
       break;
      }
 }

/* class Boot */ 

void Boot::boot_run() const
 {
  DynArray<unsigned> boot;
  
  buildBoot(boot,Range(&__std_boot_beg,&__std_boot_end));

  __std_boot(boot.getPtr(),boot.getPtr()+boot.getLen());
 }
 
void Boot::boot_flash(ulen off) const
 {
  DynArray<unsigned> boot;
  
  buildBoot(boot);

  const unsigned WS = sizeof (unsigned) ; // 4, unsigned == uint32

  if( boot.getLen()>(MaxFlashLen-BootDataOff)/WS )
    {
     Printf(Exception,"CCore::Boot::boot_flash() : too large boot");
    }
    
  ulen len=boot.getLen()*WS+BootDataOff;  
  
  ulen block_count=(len+Flash::BlockSize-1)/Flash::BlockSize;
  
  ulen block_index=off/Flash::BlockSize;
  
  for(ulen ind=block_index,lim=ind+block_count; ind<lim ;ind++) 
    if( !Flash::Erase(ind) )
      {
       Flash::ReadMode();
      
       Printf(Exception,"CCore::Boot::boot_flash() : flash erase failure");
      }
    else
      {
       Printf(Con,"Block #; erased\n",ind);
      }  
      
  if( !Flash::Write(off+BootDataOff,Range_const(boot)) )   
    {
     Flash::ReadMode();
    
     Printf(Exception,"CCore::Boot::boot_flash() : flash write failure");
    }
    
  PtrLen<const uint32> boot_code=Range(&__std_bootflash_beg,&__std_bootflash_end);  
    
  if( !Flash::Write(off,boot_code) )   
    {
     Flash::ReadMode();
    
     Printf(Exception,"CCore::Boot::boot_flash() : flash write failure");
    }
 }
 
void Boot::signal_complete()
 {
  wait.complete();
 }

void Boot::wait_complete()
 {
  wait.wait();
 }

Boot::Boot(bool half_flash)
 : own("Boot",wait.function_key())
 { 
  delta = half_flash?DeltaFlash:0 ; 
 }
   
Boot::~Boot() {}
   
void Boot::buildBoot(DynArray<unsigned> &ret,PtrLen<const unsigned> tail) const
 {
  const unsigned MinAddress   =  2_MByte ;
  const unsigned LimAddress   = 32_MByte ;
  const unsigned TopAddress   = 64_MByte ;
  
  const unsigned WS = sizeof (unsigned) ; // 4, unsigned == uint32
 
  ulen len=tail.len+2;
  
  for(auto r=Range(table); +r ;++r)
    {
     unsigned address=r->getAddress();
     unsigned size=r->getLen();
     
     if( address<MinAddress || size>LimAddress || address>LimAddress-size )
       {
        Printf(Exception,"CCore::Boot::buildBoot() : bad section placement #8.16i; #8.16i;",address,size);
       }
     
     unsigned size_w=(size+WS-1)/WS;
     
     if( !size_w ) continue;
     
     len+=(2+size_w);
     
     if( len>(TopAddress-LimAddress)/WS )  
       {
        Printf(Exception,"CCore::Boot::buildBoot() : too large boot #;",len);
       }
    }
    
  DynArray<unsigned> temp(len);
    
  unsigned *out=temp.getPtr();
  
  for(auto r=Range(table); +r ;++r)
    {
     unsigned address=r->getAddress();
     unsigned size=r->getLen();
     
     unsigned size_w=(size+WS-1)/WS;
     
     if( !size_w ) continue;
     
     *(out++)=address;
     *(out++)=size_w;
     
     const uint8 *data=r->getData().ptr;
     
     memcpy(out,data,size);
     
     out+=size_w;
    }
  
  *(out++)=entry_point;
  *(out++)=0;
  
  tail.copyTo(out);
  
  Swap(ret,temp);
 }
 
void Boot::show() const
 {
  for(auto r=Range(table); +r ;++r)
    Printf(Con,"#8.16i; #8.16i;\n",r->getAddress(),r->getLen());
       
  Printf(Con,"entry_point = #8.16i;\n",entry_point);  
 }
 
void Boot::boot() const
 {
  switch( flags )
    {
     case BootRun       : boot_run();                     break;
     case BootFlash     : boot_flash(AppFlashOff-delta);  break;
     case BootFlashBoot : boot_flash(BootFlashOff-delta); break;
     
     default:
      {
       Printf(Exception,"CCore::Boot::boot() : bad boot flag");
      }
    }
 }
 
} // namespace CCore
 

