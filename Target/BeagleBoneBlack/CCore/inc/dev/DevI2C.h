/* DevI2C.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevI2C_h
#define CCore_inc_dev_DevI2C_h

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/InstanceLock.h>
 
namespace CCore {
namespace Dev {

/* enum I2CInstance */

enum I2CInstance
 {
  I2C_0,
  I2C_1,
  I2C_2,
  
  I2C_InstanceCount
 };

/* classes */

class I2C;

/* class I2C */

class I2C : InstanceLock<I2C,I2C_InstanceCount> , public Funchor
 {
   uint32 dev_instance;
   IntSource int_source;
   
  private:
   
   static const uint32 DevInstanceTable[I2C_InstanceCount];
   static const IntSource IntTable[I2C_InstanceCount];
   
  private:
   
   enum State
    {
     StartRX,
     StartTX,
     StartTXRX,
     DoRX,
     DoTX,
     DoTXRX,
     Complete,
     ErrorRXLen,
     ErrorTXLen,
     ErrorBusLost,
     ErrorNACK,
     ErrorTimeout
    };

   MSec timeout = DefaultTimeout ;
   uint32 threshold;
   State state;
   PtrLen<uint8> rx_buf;
   PtrLen<const uint8> tx_buf;
   
   Sem sem;
  
  private: 
   
   void cancel(State state);
   
   void pumpRX(ulen count);
   
   void pumpTX(ulen count);
   
   void handle_int();
   
   Function<void (void)> function_handle_int() { return FunctionOf(this,&I2C::handle_int); }
   
  public:
  
   explicit I2C(I2CInstance instance);
   
   ~I2C();
   
   // init
   
   void enable();
   
   void reset();
   
   void init(bool fast=false);
   
   void init_fast() { init(true); }
   
   // methods
   
   void setSlave7(uint8 address); // 7 bit
   
   void setSlave10(uint16 address); // 10 bit
   
   void setTimeout(MSec timeout_) { timeout=timeout_; }
   
   bool tryRead(PtrLen<uint8> buf);
   
   bool tryWrite(PtrLen<const uint8> buf);
   
   bool tryExchange(PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf);

   StrLen getStateDesc();
   
   // advanced
   
   void read(PtrLen<uint8> buf);
   
   void write(PtrLen<const uint8> buf);
   
   void exchange(PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf);
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

