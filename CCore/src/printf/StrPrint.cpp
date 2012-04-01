/* StrPrint.cpp */ 
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
 
#include <CCore/inc/printf/StrPrint.h>
 
namespace CCore {

/* struct StrPrintOpt */ 

StrPrintOpt::StrPrintOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);
  
  ParseUInt_empty(dev,width,0);
  
  if( ParseChar_try(dev,'.') )
    {
     StrParse::Peek peek(dev);
     
     if( !peek )
       {
        dev.fail();
       }
     else
       {
        switch( *peek )
          {
           case 'q' : case 'Q' : quoted=true; ++dev; break;
           
           default: dev.fail();
          }
       }
    }
  else
    {
     quoted=false;
    }
    
  Parse_empty(dev,align);
  
  if( !dev.finish() ) setDefault();
 }
 
/* struct TitlePrintOpt */ 

TitlePrintOpt::TitlePrintOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  ParseUInt_empty(dev,width,Default_width);
  
  if( ParseChar_try(dev,'.') )
    {
     ParseUInt(dev,off);
    }
  else
    {
     off=Default_off;
    }  
    
  ParseChar_empty(dev,border,Default_border);
 
  if( !dev.finish() ) setDefault();
 }
 
/* struct TextDividerPrintOpt */ 

TextDividerPrintOpt::TextDividerPrintOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  ParseUInt_empty(dev,width,Default_width);
  
  ParseChar_empty(dev,border,Default_border);
 
  if( !dev.finish() ) setDefault();
 }
 
} // namespace CCore
 

