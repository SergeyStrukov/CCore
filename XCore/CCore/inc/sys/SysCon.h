/* SysCon.h */ 
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

#ifndef CCore_inc_sys_SysCon_h
#define CCore_inc_sys_SysCon_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/NanoPacket.h>
#include <CCore/inc/Task.h>
 
namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_SysCon();

/* consts */ 

enum ConInputResult
 {
  Con_Drop = 0,
  Con_Echo,
  Con_NoEcho,
  Con_EOL
 };
 
/* types */  

typedef Function<ConInputResult (char)> ConInputFunction;

typedef Function<void (NanoPacket<char> packet)> ConOutputFunction;
 
/* functions */ 

NanoPacket<char> AllocConPacket(MSec timeout);

void ConWrite(NanoPacket<char> packet);

void EnablePacketCon();

void DisablePacketCon();

void ShowConStat();

/* classes */ 

class OwnConInput;

class HookConInput;

class RedirectCon;

class HookConOutput;

class ConBase;

/* class OwnConInput */

class OwnConInput : NoCopy
 {
   AntiSem asem;
   
  public:
   
   OwnConInput(TextLabel name,ConInputFunction input_any);
   
   ~OwnConInput();
 };

/* class HookConInput */

class HookConInput : NoCopy
 {
   ConInputFunction input_any;
   AntiSem *asem;
   
  public: 
   
   HookConInput();
   
   ~HookConInput();
   
   ConInputResult operator () (char ch) { return input_any(ch); }
 };

/* class RedirectCon */ 

class RedirectCon : NoCopy
 {
   AntiSem asem;
  
  public:
  
   RedirectCon(TextLabel name,ConOutputFunction output);
   
   ~RedirectCon();
 };

/* class HookConOutput */

class HookConOutput : NoCopy
 {
   ConOutputFunction output;
   AntiSem *asem;
   
  public: 
   
   HookConOutput();
   
   ~HookConOutput();
   
   void operator () (NanoPacket<char> packet) { output(packet); }
 };

/* class ConBase */

class ConBase : public Funchor_nocopy
 {
  private:
  
   class Pool : NanoPacketPool<char>
    {
      Sem sem;
    
     private:
  
      virtual void post_free();
      
     public:
     
      explicit Pool(TextLabel name,void *mem,ulen max_data_len,ulen count); 
      
      ~Pool();
      
      NanoPacket<char> get(MSec timeout);
    };
   
  private: 

   Pool pool;
   
   Mutex mutex;
   
   ConInputFunction input_any;
   AntiSem *input_asem;
   
   ConOutputFunction output;
   AntiSem *output_asem;
   
   unsigned nopacket_count;
   
  private: 
   
   // default input/output
   
   virtual void attachDefaultInput(ConInputFunction input_any)=0;
   
   virtual void detachDefaultInput()=0;
   
   virtual void defaultOutput(NanoPacket<char> packet)=0;
   
   ConOutputFunction function_defaultOutput() { return FunctionOf(this,&ConBase::defaultOutput); }
   
   // attach/detach/hook
   
   void attachInput(ConInputFunction input_any,AntiSem *input_asem);
   
   void detachInput(AntiSem *input_asem);
   
   AntiSem * hookInput(ConInputFunction &ret);
   
   void attachOutput(ConOutputFunction output,AntiSem *output_asem);
   
   void detachOutput(AntiSem *output_asem);
   
   AntiSem * hookOutput(ConOutputFunction &ret);
   
   friend class OwnConInput;
   friend class HookConInput;
   friend class RedirectCon;
   friend class HookConOutput;
   
  public:
   
   // constructors
   
   static constexpr ulen MemLen(ulen max_data_len,ulen count) { return NanoPacket<char>::AllocLen(max_data_len)*count; }
   
   ConBase(TextLabel name,void *mem,ulen max_data_len,ulen count);
   
   ~ConBase();
   
   // methods
   
   unsigned getNoPacketCount(); 
   
   NanoPacket<char> alloc(MSec timeout);
   
   virtual void enablePacket()=0;
   
   virtual void disablePacket()=0;
   
   virtual void showStat()=0;
   
   // global object
   
   static ConBase * GetObject(); 
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

