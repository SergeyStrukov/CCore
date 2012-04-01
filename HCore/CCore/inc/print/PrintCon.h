/* PrintCon.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
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
 
namespace CCore {

/* words */ 

enum ConType { Con };
 
/* classes */ 

class PrintCon;

/* class PrintCon */ 

class PrintCon : public PrintBase
 {
   char buf[TextBufLen];
 
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public:
  
   explicit PrintCon(ConType) {}
   
   ~PrintCon() { flush(); }
   
   static void Print(const char *ptr,ulen len) { Print(Range(ptr,len)); }
   
   static void Print(StrLen str); // ignore errors
 };
 
template <> 
struct PrintOutAdapter<ConType> 
 {
  typedef PrintCon PrintOutType;
 };
 
} // namespace CCore
 
#endif
 

