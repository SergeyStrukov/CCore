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

#include <CCore/inc/sys/SysAtomic.h>
 
namespace CCore {
namespace Dev {

/* enum I2CInstance */

enum I2CInstance
 {
  I2C_0,
  I2C_1,
  I2C_2
 };

/* classes */

class I2C;

/* class I2C */

class I2C : public Funchor_nocopy
 {
   I2CInstance instance;
   uint32 base_address;
   IntSource int_source;
   
  private:
   
   static const uint32 AddressTable[];
   static const IntSource IntTable[];
   
   static Sys::Atomic LockTable[];
   
  private:
   
   enum State
    {
     StartRX,
     StartTX,
     DoRX,
     DoTX,
     CompleteOk,
     CompleteError
    };
   
   State state;
   PtrLen<uint8> rx_buf;
   PtrLen<const uint8> tx_buf;
  
  private: 
   
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
   
   void setSlave(uint8 address);
   
   bool read(uint8 *ptr,ulen len);
   
   bool write(const uint8 *ptr,ulen len);
 };

} // namespace Dev
} // namespace CCore
 
#endif
 

