/* PrintBase.cpp */ 
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
 
#include <CCore/inc/printf/PrintBase.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class PrintBase */ 

bool PrintBase::provide(ulen hint_len)
 {
  PtrLen<char> buf=do_provide(hint_len);
  
  if( !buf ) 
    {
     overflow=true;
     
     return false;
    }
  
  ptr=cur=buf.ptr;
  lim=buf.ptr+buf.len;
  
  return true;
 }
 
bool PrintBase::flush_and_provide(ulen hint_len)
 {
  flush();
  
  return provide(hint_len);
 }
 
void PrintBase::PrintBaseOverflow()
 {
  Printf(Exception,"CCore::PrintBase::guardOverflow() : overflow");
 }
 
void PrintBase::put(char ch,ulen len)
 {
  if( !len ) return;
  
  if( cur>=lim && !flush_and_provide(len) ) return;
  
  ulen avail;
  
  while( len>(avail=Dist(cur,lim)) )
    {
     Range(cur,avail).set(ch);
     
     len-=avail;
     
     cur=lim;
     
     if( !flush_and_provide(len) ) return; 
    }
    
  Range(cur,len).set(ch);
  
  cur+=len;  
 }
   
void PrintBase::put(const char *str,ulen len)
 {
  if( !len ) return;
  
  if( cur>=lim && !flush_and_provide(len) ) return;
  
  ulen avail;
  
  while( len>(avail=Dist(cur,lim)) )
    {
     Range(cur,avail).copy(str);
     
     str+=avail;
     len-=avail;
     
     cur=lim;
     
     if( !flush_and_provide(len) ) return; 
    }
    
  Range(cur,len).copy(str);
  
  cur+=len;  
 }
 
void PrintBase::flush()
 {
  if( char *beg=ptr )
    {
     ulen len=Dist(beg,cur);
  
     clear();
 
     do_flush(beg,len);
    }
 }
 
/* class PrintBuf */ 
 
void PrintBuf::initbuf(PtrLen<char> buf_)
 {
  buf=buf_;
  off=0;
 }
 
PtrLen<char> PrintBuf::do_provide(ulen)
 {
  if( buf.fit(off,1) ) return buf.inner(off,1);
  
  return Nothing;
 }
   
void PrintBuf::do_flush(char *,ulen len)
 {
  off+=len;
 }
   
PrintBuf::~PrintBuf()
 {
  close();
 }
   
void PrintBuf::init(PtrLen<char> buf)
 {
  close();
  
  clearOverflowFlag();
  
  initbuf(buf);
 }
 
StrLen PrintBuf::close()
 {
  flush();
  
  if( off>=buf.len ) return "";
  
  buf[off]=0;
  
  return buf.prefix(off);
 }
 
} // namespace CCore
 

