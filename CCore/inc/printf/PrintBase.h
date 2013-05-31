/* PrintBase.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_printf_PrintBase_h
#define CCore_inc_printf_PrintBase_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* words */ 

enum NoPrintType { NoPrint };
 
/* classes */ 

template <class P> struct PrintOutAdapter;

class PrintBase;

class PrintBuf;

template <class P> class PrintCount;

/* struct PrintOutAdapter<P> */ 

template <class P> 
struct PrintOutAdapter 
 {
  typedef typename P::PrintOutType PrintOutType;
 };
 
template <> 
struct PrintOutAdapter<NoPrintType> 
 {
  typedef void PrintOutType;
 };
 
template <> 
struct PrintOutAdapter<const NoPrintType> 
 {
  typedef void PrintOutType;
 };
 
/* class PrintBase */ 

class PrintBase : NoCopy
 {
   char *ptr;
   char *cur;
   char *lim;
   
   bool overflow;
 
  private:
  
   void clear() { ptr=cur=lim=0; }
    
   bool provide(ulen hint_len); 
   
   bool flush_and_provide(ulen hint_len);
    
   virtual PtrLen<char> do_provide(ulen hint_len)=0;
   
   virtual void do_flush(char *ptr,ulen len)=0; 
   
   static void PrintBaseOverflow();

  protected:
  
   void clearOverflowFlag() { overflow=false; }
   
  public:
  
   typedef PrintBase & PrintOutType;
   
   PrintOutType printRef() { return *this; }
   
   // constructors
   
   PrintBase() { clear(); clearOverflowFlag(); }
   
   ~PrintBase() {} // flush() in derived class
   
   // methods
   
   bool getOverflowFlag() const { return overflow; }
   
   PrintBase & guardOverflow() { if( overflow ) PrintBaseOverflow(); return *this; }
   
   // put
   
   void put(char ch)
    {
     if( cur<lim || flush_and_provide(1) ) *(cur++)=ch;
    }
   
   void put(char ch,ulen len);
   
   void put(const char *str,ulen len);
   
   void flush();
 };
 
/* class PrintBuf */ 

class PrintBuf : public PrintBase
 {
   PtrLen<char> buf;
   ulen off;

  private:

   void initbuf(PtrLen<char> buf);
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public:
  
   explicit PrintBuf(PtrLen<char> buf=Nothing) { initbuf(buf); }
   
   ~PrintBuf();
   
   void init(PtrLen<char> buf);
   
   PrintBuf & guardOverflow() { PrintBase::guardOverflow(); return *this; }
   
   StrLen close();
   
   const char * closeZStr() { return close().ptr; }
 };
 
/* class PrintCount<P> */ 
 
template <class P> 
class PrintCount : NoCopy
 {
   P &out;
   ulen count;
   
  public:
  
   typedef PrintCount<P> & PrintOutType;
  
   PrintOutType printRef() { return *this; }
   
   // constructors
   
   explicit PrintCount(P &out_) : out(out_),count(0) {}
   
   ulen getCount() const { return count; }
   
   // put
   
   void put(char ch)
    {
     count++;
     out.put(ch);
    }
   
   void put(char ch,ulen len)
    {
     count+=len;
     out.put(ch,len);
    }
   
   void put(const char *str,ulen len)
    {
     count+=len;
     out.put(str,len);
    }
   
   void flush()
    {
     out.flush();
    }
 };

/* class PrintCount<void> */

template <> 
class PrintCount<void> : NoCopy
 {
   ulen count;
   
  public:
  
   typedef PrintCount<void> & PrintOutType;
  
   PrintOutType printRef() { return *this; }
   
   // constructors
   
   PrintCount() : count(0) {}
   
   // methods
   
   ulen getCount() const { return count; }
   
   // put
   
   void put(char)
    {
     count++;
    }
   
   void put(char,ulen len)
    {
     count+=len;
    }
   
   void put(const char *,ulen len)
    {
     count+=len;
    }
   
   void flush()
    {
    }
 };
 
} // namespace CCore
 
#endif
 

