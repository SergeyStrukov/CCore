/* StringScan.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_StringScan_h
#define CCore_inc_StringScan_h

#include <CCore/inc/String.h>
#include <CCore/inc/scanf/ScanTools.h>
 
namespace CCore {

/* classes */

//enum StringScanType;

struct StringScanOpt;

class StringScan;

/* enum StringScanType */

enum StringScanType
 {
  StringScanQuote,
  StringScanToSpace,
  StringScanToPunct
 };

template <class Dev>
bool Parse_try(Dev &dev,StringScanType &ret)
 {
  typename Dev::Peek peek(dev);
  
  if( !peek )
    {
     return false;
    }
  else
    {
     switch( *peek )
       {
        case 'q' : case 'Q' : ret=StringScanQuote;   ++dev; return true;
        case 's' : case 'S' : ret=StringScanToSpace; ++dev; return true;
        case 'p' : case 'P' : ret=StringScanToPunct; ++dev; return true;
       }
     
     return false;
    }
 }

/* struct StringScanOpt */

struct StringScanOpt
 {
  StringScanType type;
  
  void setDefault() 
   {
    type=StringScanToPunct;
   }
  
  StringScanOpt() { setDefault(); }
  
  StringScanOpt(const char *ptr,const char *lim);
  
  //
  // [.q|.Q|.s|.S|.p|.P]
  //
 };

/* class StringScan */

class StringScan
 {
   String &ret;
   
  private: 
   
   template <class S>
   void scanQuote(S &inp)
    {
     PassChars(inp,'"');
    
     PrintString out;

     for(; +inp ;++inp)
       {
        char ch=*inp;
        
        if( ch=='"' )
          {
           ++inp;
           
           ret=out.close();
           
           return;
          }
        else
          {
           out.put(ch);
          }
       }
     
     inp.fail();
    }
   
   template <class S>
   void scanToSpace(S &inp)
    {
     PrintString out;
     
     for(char ch; +inp && !CharIsSpace(ch=*inp) ;++inp) out.put(ch);
     
     ret=out.close();
    }
   
   template <class S>
   void scanToPunct(S &inp)
    {
     PrintString out;
     
     for(char ch; +inp && !CharIsSpaceOrPunct(ch=*inp) ;++inp) out.put(ch);
     
     ret=out.close();
    }
   
  public:
  
   explicit StringScan(String &ret_) : ret(ret_) {}
   
   template <class S>
   void scan(S &inp,StringScanOpt opt)
    {
     ret={};
     
     switch( opt.type )
       {
        case StringScanQuote : scanQuote(inp); break;
        case StringScanToSpace : scanToSpace(inp); break;
        case StringScanToPunct : scanToPunct(inp); break;
       }
    }
 };

} // namespace CCore
 
#endif
 

