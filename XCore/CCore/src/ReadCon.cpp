/* ReadCon.cpp */ 
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
 
#include <CCore/inc/ReadCon.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class ReadCon */ 

Sys::ConInputResult ReadCon::input_any(char ch)
 {
  bool ok;
  
  {
   Dev::IntLock lock;
  
   if( ch==3 ) // ^C 
     {
      Abort("--- ^C abort ---");
     }
    
   ok=fifo.put(ch);
  }
  
  if( ok )
    {
     sem.give_any();
    
     return Sys::Con_NoEcho;
    } 
  
  return Sys::Con_Drop;
 }
 
ReadCon::ReadCon(MSec timeout_)
 : timeout(timeout_),
   sem("ReadCon"),
   own("ReadCon",function_input())
 {
 }
   
ReadCon::~ReadCon()
 {
 }
   
char ReadCon::get()
 {
  sem.take();
  
  Dev::IntLock lock;
  
  char ch=0;
  
  fifo.get(ch);
  
  return ch;
 }
   
bool ReadCon::get(MSec timeout,char &ret)
 {
  if( sem.take(timeout) )
    {
     Dev::IntLock lock;
  
     return fifo.get(ret);
    }
    
  return false;  
 }
   
bool ReadCon::get(TimeScope time_scope,char &ret)
 {
  if( sem.take(time_scope) )
    {
     Dev::IntLock lock;
  
     return fifo.get(ret);
    }
    
  return false;  
 }
 
void ReadCon::put(StrLen str)
 {
  while( +str )
    {
     NanoPacket<char> packet=Sys::AllocConPacket(timeout);
     
     if( !packet ) return;
     
     auto frame=str.takeup(packet.getMaxDataLen());
     
     packet.setDataLen(frame.len).copy(frame.ptr);
     
     Sys::ConWrite(packet);
    }
 }
 
} // namespace CCore
 

