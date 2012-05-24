/* ARMCore.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ARMGo_inc_ARMCore_h
#define ARMGo_inc_ARMCore_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/PrintTime.h>

#include <inc/ARMCmd.h>

namespace ARMCore {

/* LoadImage() */

void LoadImage(PtrLen<Word> mem,StrLen file_name);

/* classes */ 

class NoLog;

template <class Target> class Memory;

template <class Memory,class Log> class Cpu;

/* class NoLog */ 
 
class NoLog : NoCopy
 {
  public:
  
   NoLog() {}
   
   ~NoLog() {}
   
   // switch mode
   
   void toPrefetchAbort(Word PC) { Used(PC); }
   
   void toIRQ(Word PC) { Used(PC); }
   
   void toFIQ(Word PC) { Used(PC); }
   
   void toSVC(Word PC) { Used(PC); }
   
   void cmdUndefined(Word PC,Word cmd) { Used(PC); Used(cmd); }
   
   void dataAbort(Word PC,Word address,MemTag tag) { Used(PC); Used(address); Used(tag); }
   
   // trace
   
   template <class ... TT>
   void trace(Word PC,const char *format,const TT & ...) { Used(PC); Used(format); }
   
   template <class ... TT>
   void trace(const char *format,const TT & ...) { Used(format); }
   
   template <class ... TT>
   void stat(const char *format,const TT & ...) { Used(format); }
   
   // execute

   void reset() {}
   
   void step() {}
 };
 
/* class Memory<Target> */ 
 
template <class Target> 
class Memory : NoCopy 
 {
   Target target;
   
   DynArray<Word> mem;
   
  public:
  
   explicit Memory(StrLen file_name);
   
   ~Memory() {}
   
   // data access
   
   MemUnit getX(Word address);
   
   MemUnit getD(Word address);
   
   MemUnit getH(Word address);
   
   MemUnit getB(Word address);
   
   NegMemTag putD(Word address,Word value);
   
   NegMemTag putH(Word address,Half value);
   
   NegMemTag putB(Word address,Byte value);
   
   // execute
   
   void reset() { target.reset(); }
   
   void step() { target.step(); }
   
   bool getRunFlag() { return target.getRunFlag(); }

   bool getIRQ() { return target.getIRQ(); }
   
   bool getFIQ() { return target.getFIQ(); }
 };
 
template <class Target> 
Memory<Target>::Memory(StrLen file_name)
 : mem(target.getMemLen()/4)
 {
  LoadImage(Range(mem),file_name);
 }

template <class Target> 
MemUnit Memory<Target>::getX(Word address) 
 {
  if( address&3 ) return MemTag_NotAligned;
  
  Word index=address/4;
  
  if( index<mem.getLen() ) return mem[index];
  
  return target.getX(address);
 }

template <class Target> 
MemUnit Memory<Target>::getD(Word address) 
 {
  if( address&3 ) return MemTag_NotAligned;
  
  Word index=address/4;
  
  if( index<mem.getLen() ) return mem[index];
  
  return target.getD(address);
 }

template <class Target> 
MemUnit Memory<Target>::getH(Word address) 
 { 
  if( address&1 ) return MemTag_NotAligned;
  
  Word index=address/4;
  
  if( index<mem.getLen() ) return GetHalf(mem[index],address&3);
  
  return target.getH(address);
 }

template <class Target> 
MemUnit Memory<Target>::getB(Word address) 
 { 
  Word index=address/4;
  
  if( index<mem.getLen() ) return GetByte(mem[index],address&3);
  
  return target.getB(address);
 }

template <class Target> 
NegMemTag Memory<Target>::putD(Word address,Word value) 
 { 
  if( address&3 ) return MemTag_NotAligned;
  
  Word index=address/4;
  
  if( index<mem.getLen() ) 
    {
     mem[index]=value;
     
     return MemTag_Ok;
    }
  
  return target.putD(address,value);
 }

template <class Target> 
NegMemTag Memory<Target>::putH(Word address,Half value) 
 { 
  if( address&1 ) return MemTag_NotAligned;
  
  Word index=address/4;
  
  if( index<mem.getLen() ) 
    {
     PutHalf(mem[index],address&3,value);
     
     return MemTag_Ok;
    }
  
  return target.putH(address,value);
 }

template <class Target> 
NegMemTag Memory<Target>::putB(Word address,Byte value) 
 { 
  Word index=address/4;
  
  if( index<mem.getLen() ) 
    {
     PutByte(mem[index],address&3,value);
     
     return MemTag_Ok;
    }
  
  return target.putB(address,value);
 }

/* class Cpu<Memory,Log> */ 

template <class Memory,class Log>
class Cpu : NoCopy
 {
   Memory mem;
   Log log;
   
   ARMv5TE_nonT::CPUCore<Memory,Log> core;
   
   uint64 cmd_count;
   SecTimer timer;

  public:
  
   explicit Cpu(StrLen file_name) : mem(file_name) { reset(); }
   
   Cpu(StrLen file_name,StrLen log_name) : mem(file_name),log(log_name) { reset(); }
 
   ~Cpu() {}
   
   // execute
   
   void reset();

   bool step();
   
   void run();
 };
 
template <class Memory,class Log>
void Cpu<Memory,Log>::reset()
 {
  core.reset();
  mem.reset();
  log.reset();
 }
 
template <class Memory,class Log>
bool Cpu<Memory,Log>::step()
 {
  cmd_count++;
  
  mem.step();
  log.step();
  
  if( !(core.CPSR&SR_F) && mem.getFIQ() )
    {
     core.stepFIQ(log);

     return true;
    }
  
  if( !(core.CPSR&SR_I) && mem.getIRQ() )
    {
     core.stepIRQ(log);

     return true;
    }
  
  core.step(mem,log);
  
  return mem.getRunFlag();
 }

template <class Memory,class Log>
void Cpu<Memory,Log>::run() 
 {
  cmd_count=0;
  
  timer.reset();
  
  while( step() );
  
  auto t=timer.get();
  
  log.stat("#8L;\nCommands = #;\nTime = #;\n",core.stat,cmd_count,PrintTime(t));
 }
 
} // namespace ARMCore
 
#endif

