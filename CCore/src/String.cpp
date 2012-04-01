/* String.cpp */ 
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
 
#include <CCore/inc/String.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class PrintString */  

PtrLen<char> PrintString::do_provide(ulen hint_len)
 {
  if( !buf ) 
    {
     ulen len=data.getLen();
     
     if( len>max_len ) return Nothing;
     
     buf=data.extend_raw(Min<ulen>(Max(frame_len,hint_len)-1,max_len-len)+1);
    }
  
  return buf; 
 }
   
void PrintString::do_flush(char *,ulen len)
 {
  buf+=len;
 }
   
PrintString::PrintString(ulen max_len_,ulen frame_len_)
 : max_len(max_len_),
   frame_len(Max(frame_len_,DefaultFrameLen)),
   data(frame_len)
 {
 }
   
String PrintString::close()
 {
  flush();
  
  data.shrink(buf.len);
  
  buf=Empty;
  
  if( data.getLen()>max_len )
    {
     Printf(Exception,"CCore::PrintString::close() : overflow");
    }
  
  String ret;
  
  data.copyTo(ret);
  
  return ret;
 }
 
void PrintString::cleanup()
 {
  flush();
  
  data.erase();
  
  buf=Empty;
 }
 
} // namespace CCore
 

