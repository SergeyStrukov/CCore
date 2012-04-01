/* StrPrint.h */ 
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

#ifndef CCore_inc_printf_StrPrint_h
#define CCore_inc_printf_StrPrint_h

#include <CCore/inc/StrParse.h>
 
namespace CCore {

/* classes */ 

class RepeatChar;

//enum StrAlign;

struct StrPrintOpt;

class StrPrint;

struct TitlePrintOpt;

class Title;

struct TextDividerPrintOpt;

class TextDivider;

/* class RepeatChar */ 

class RepeatChar
 {
   ulen count;
   char ch;
   
  public: 
  
   RepeatChar(ulen count_,char ch_) : count(count_),ch(ch_) {}
  
   template <class P>
   void print(P &out) const
    {
     out.put(ch,count);
    }
 };

/* enum StrAlign */

enum StrAlign
 {
  StrAlignLeft,
  StrAlignRight,
  StrAlignCenter,
  
  StrAlignDefault = StrAlignRight
 };
 
template <class Dev>
void Parse_empty(Dev &dev,StrAlign &ret)
 {
  typename Dev::Peek peek(dev);
  
  if( !peek )
    {
     ret=StrAlignDefault;
    }
  else
    {
     switch( *peek )
       {
        case 'l' : case 'L' : ret=StrAlignLeft;   ++dev; break;
        case 'r' : case 'R' : ret=StrAlignRight;  ++dev; break;
        case 'c' : case 'C' : ret=StrAlignCenter; ++dev; break;
        
        default: ret=StrAlignDefault;
       }
    }
 }
 
/* struct StrPrintOpt */ 

struct StrPrintOpt
 {
  ulen width;
  StrAlign align;
  bool quoted;
  
  void setDefault()
   {
    width=0;
    align=StrAlignDefault;
    quoted=false;
   }
  
  StrPrintOpt() { setDefault(); }
  
  StrPrintOpt(const char *ptr,const char *lim);
  
  //
  // [width=0][.q|.Q][l|L|r|R|c|C=R]
  //
 };
 
/* class StrPrint */ 

class StrPrint
 {
   StrLen str;
   
  private:
  
   ulen getExtra(ulen width,bool quoted) const
    {
     return quoted?PosSub(width,str.len,2):PosSub(width,str.len);
    }
  
   template <class P>
   void printStr(P &out,bool quoted) const
    {
     if( quoted ) out.put('"');
     
     out.put(str.ptr,str.len);
     
     if( quoted ) out.put('"');
    }
   
  public:
  
   explicit StrPrint(StrLen str_) : str(str_) {}
   
   typedef StrPrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     if( ulen extra=getExtra(opt.width,opt.quoted) )
       {
        switch( opt.align )
          {
           case StrAlignLeft :
            {
             printStr(out,opt.quoted);
             out.put(' ',extra);
            } 
           break;
           
           case StrAlignRight :
            {
             out.put(' ',extra);
             printStr(out,opt.quoted);
            } 
           break;
           
           case StrAlignCenter :
            {
             ulen off=extra/2;
            
             out.put(' ',off);
             printStr(out,opt.quoted);
             out.put(' ',extra-off);
            } 
           break;
          }
       }
     else
       {
        printStr(out,opt.quoted);
       }
    }
 };
 
/* struct TitlePrintOpt */ 

struct TitlePrintOpt
 {
  static const ulen Default_width  = 80  ;
  static const ulen Default_off    =  3  ;
  static const char Default_border = '-' ;
    
  ulen width;
  ulen off;
  char border;
     
  void setDefault()
   {
    width=Default_width;
    off=Default_off;
    border=Default_border;
   }
     
  TitlePrintOpt() { setDefault(); }
     
  TitlePrintOpt(const char *ptr,const char *lim);
     
  //
  // [width=80][.off=3][border=-]
  //
 };
 
/* class Title */ 

class Title
 {
   StrLen str;
   
  public:
  
   explicit Title(StrLen str_) : str(str_) {}
 
   typedef TitlePrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     out.put(opt.border,opt.off);
     out.put(' ');
     out.put(str.ptr,str.len);
     out.put(' ');
     out.put(opt.border,PosSub(opt.width,opt.off,str.len,2));
    }
 };
 
/* struct TextDividerPrintOpt */ 

struct TextDividerPrintOpt
 {
  static const ulen Default_width  = TitlePrintOpt::Default_width  ;
  static const char Default_border = TitlePrintOpt::Default_border ;
    
  ulen width;
  char border;
     
  void setDefault()
   {
    width=Default_width;
    border=Default_border;
   }
     
  TextDividerPrintOpt() { setDefault(); }
     
  TextDividerPrintOpt(const char *ptr,const char *lim);
     
  //
  // [width=80][border=-]
  //
 };
 
/* class TextDivider */ 

class TextDivider
 {
  public:
  
   TextDivider() {}
   
   typedef TextDividerPrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     out.put(opt.border,opt.width);
    }
 };
 
} // namespace CCore
 
#endif
 

