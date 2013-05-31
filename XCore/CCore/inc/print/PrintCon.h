/* PrintCon.h */ 
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

#ifndef CCore_inc_print_PrintCon_h
#define CCore_inc_print_PrintCon_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/NanoPacket.h>
 
namespace CCore {

/* words */ 

enum ConType { Con };
 
/* classes */ 

class PrintCon;

/* class PrintCon */ 

class PrintCon : public PrintBase
 {
   MSec timeout;
   NanoPacket<char> packet;
 
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public:
  
   explicit PrintCon(ConType,MSec timeout_=DefaultTimeout) : timeout(timeout_) {}
   
   ~PrintCon() { flush(); }
   
   static void Print(const char *ptr,ulen len); // ignore errors
   
   static void Print(StrLen str) { Print(str.ptr,str.len); } 
 };
 
template <> 
struct PrintOutAdapter<ConType> 
 {
  typedef PrintCon PrintOutType;
 };
 
template <> 
struct PrintOutAdapter<const ConType> 
 {
  typedef PrintCon PrintOutType;
 };
 
} // namespace CCore
 
#endif
 

