/* SysCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysCon.h>

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

namespace CCore {
namespace Sys {

/* functions */ 

void ConWrite(StrLen str) noexcept
 {
  auto ret=write(STDOUT_FILENO,str.ptr,str.len);
  
  Used(ret);
 }
 
/* struct ConRead */ 

ErrorType ConRead::init() noexcept
 {
  if( tcgetattr(STDIN_FILENO,&con_attr)==-1 ) return NonNullError();
  
  struct termios new_attr=con_attr;
  
  BitClear(new_attr.c_lflag,ECHO|ICANON);
  
  new_attr.c_cc[VTIME]=0;
  new_attr.c_cc[VMIN]=1;
  
  if( tcsetattr(STDIN_FILENO,TCSANOW,&new_attr)==-1 ) return NonNullError();

  return NoError;
 }
  
ErrorType ConRead::exit() noexcept
 {
  if( tcsetattr(STDIN_FILENO,TCSANOW,&con_attr)==-1 ) return NonNullError();  

  return NoError;
 }
  
auto ConRead::read(char *buf,ulen len) noexcept -> IOResult
 {
  ssize_t result=::read(STDIN_FILENO,buf,len);
  
  if( result==-1 )
    {
     return IOResult{0,NonNullError()};
    }
  else
    {
     ulen ret_len=(ulen)result;
    
     for(char &ch : Range(buf,ret_len) )
       {
        if( ch==0x7F ) ch='\b';
       }
    
     return IOResult{ret_len,NoError};
    }
 }
  
auto ConRead::read(char *buf,ulen len,MSec timeout) noexcept -> IOResult
 {
  fd_set read_set;
  
  FD_ZERO(&read_set);
  FD_SET(STDIN_FILENO,&read_set);
  
  struct timeval to;
  
  to.tv_sec=(+timeout/1000u);
  to.tv_usec=(+timeout%1000u)*1000u;
  
  if( select(STDIN_FILENO+1,&read_set,0,0,&to)==-1 )
    {
     return IOResult{0,NonNullError()};
    }
  else
    {
     if( FD_ISSET(STDIN_FILENO,&read_set) ) return read(buf,len);    
    
     return IOResult{0,NoError};
    }
 }

} // namespace Sys
} // namespace CCore
 

