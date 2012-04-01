/* SysCon_general.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysCon.h>

namespace CCore {
namespace Sys {

/* functions */ 

NanoPacket<char> AllocConPacket(MSec timeout)
 {
  return ConBase::GetObject()->alloc(timeout);
 }

void ConWrite(NanoPacket<char> packet)
 {
  HookConOutput hook;
  
  hook(packet);
 }
 
void EnablePacketCon()
 {
  ConBase::GetObject()->enablePacket();
 }
 
void DisablePacketCon()
 {
  ConBase::GetObject()->disablePacket();
 }
 
void ShowConStat()
 {
  ConBase::GetObject()->showStat();
 }

/* class OwnConInput */

OwnConInput::OwnConInput(TextLabel name,ConInputFunction input_any)
 : asem(name)
 {
  ConBase::GetObject()->attachInput(input_any,&asem);
 }
   
OwnConInput::~OwnConInput()
 {
  ConBase::GetObject()->detachInput(&asem);
  
  asem.wait();
 }

/* class HookConInput */

HookConInput::HookConInput()
 {
  asem=ConBase::GetObject()->hookInput(input_any);
 }
   
HookConInput::~HookConInput()
 {
  if( asem ) asem->dec();
 }

/* class RedirectCon */ 

RedirectCon::RedirectCon(TextLabel name,ConOutputFunction output)
 : asem(name)
 {
  ConBase::GetObject()->attachOutput(output,&asem);
 }
   
RedirectCon::~RedirectCon()
 {
  ConBase::GetObject()->detachOutput(&asem);
  
  asem.wait();
 }

/* class HookConOutput */

HookConOutput::HookConOutput()
 {
  asem=ConBase::GetObject()->hookOutput(output);
 }
   
HookConOutput::~HookConOutput()
 {
  if( asem ) asem->dec();
 }
   
/* class ConBase::Pool */

void ConBase::Pool::post_free() { sem.give_any(); }
   
ConBase::Pool::Pool(TextLabel name,void *mem,ulen max_data_len,ulen count) 
 : NanoPacketPool<char>(mem,max_data_len,count),
   sem(name,count)
 {
 }
   
ConBase::Pool::~Pool() {}
   
NanoPacket<char> ConBase::Pool::get(MSec timeout)
 {
  if( sem.take(timeout) ) return try_get();
     
  return Nothing;
 }

/* class ConBase */

void ConBase::attachInput(ConInputFunction input_any_,AntiSem *input_asem_)
 {
  Mutex::Lock lock(mutex);
  
  input_any=input_any_;
  input_asem=input_asem_;
  
  attachDefaultInput(input_any_);
 }

void ConBase::detachInput(AntiSem *input_asem_)
 {
  Mutex::Lock lock(mutex);
  
  if( input_asem==input_asem_ )
    {
     input_any=Nothing;
     input_asem=0;
     
     detachDefaultInput();
    }
 }

AntiSem * ConBase::hookInput(ConInputFunction &ret)
 {
  Mutex::Lock lock(mutex);
  
  if( AntiSem *asem=input_asem )
    {
     asem->inc();
     
     ret=input_any;
     
     return asem;
    }
  
  return 0;
 }

void ConBase::attachOutput(ConOutputFunction output_,AntiSem *output_asem_)
 {
  Mutex::Lock lock(mutex);
  
  output=output_;
  output_asem=output_asem_;
 }

void ConBase::detachOutput(AntiSem *output_asem_)
 {
  Mutex::Lock lock(mutex);
  
  if( output_asem==output_asem_ )
    {
     output=Nothing;
     output_asem=0;
    }
 }

AntiSem * ConBase::hookOutput(ConOutputFunction &ret)
 {
  Mutex::Lock lock(mutex);
  
  if( AntiSem *asem=output_asem )
    {
     asem->inc();
     
     ret=output;
     
     return asem;
    }
  
  ret=function_defaultOutput();
  
  return 0;
 }

ConBase::ConBase(TextLabel name,void *mem,ulen max_data_len,ulen count)
 : pool(name,mem,max_data_len,count),
   mutex(name),
   input_asem(0),
   output_asem(0),
   nopacket_count(0)
 {
 }

ConBase::~ConBase()
 {
 }

unsigned ConBase::getNoPacketCount()
 {
  Mutex::Lock lock(mutex);
  
  return nopacket_count;
 }

NanoPacket<char> ConBase::alloc(MSec timeout) 
 { 
  NanoPacket<char> ret=pool.get(timeout);
  
  if( !ret )
    {
     Mutex::Lock lock(mutex);
     
     nopacket_count++;
    }
  
  return ret; 
 }

} // namespace Sys
} // namespace CCore


