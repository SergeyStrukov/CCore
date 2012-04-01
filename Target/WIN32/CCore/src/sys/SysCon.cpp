/* SysCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysCon.h>

#include <CCore/inc/TimeScope.h>

#include <CCore/inc/win32/Win32.h>
 
namespace CCore {
namespace Sys {

/* internal */ 

namespace Private_SysCon {

/* class ConOut */

class ConOut : NoCopy
 {
   Win32::handle_t handle;
   ErrorType error;
   
  public:
  
   ConOut()
    {
     handle=Win32::GetStdHandle(Win32::StdOutputHandle);
        
     if( handle==Win32::InvalidFileHandle )
       {
        error=NonNullError();
       }
     else if( handle==0 )
       {
        error=ErrorType(Win32::ErrorFileNotFound);
       }  
     else
       {
        error=ErrorIf( !Win32::SetConsoleOutputCP(Win32::GetACP()) );
       }  
    }
   
   void print(StrLen str)
    {
     if( error ) return;
     
     Win32::ulen_t ret_len;
 
     Win32::WriteFile(handle,str.ptr,str.len,&ret_len,0);
    }
 };
 
ConOut Object CCORE_INITPRI_0 ;
 
} // namespace Private_SysCon
 
using namespace Private_SysCon;
 
/* functions */ 

void ConWrite(StrLen str) noexcept
 {
  Object.print(str);
 }
 
/* struct ConRead */ 

auto ConRead::Init() noexcept -> InitType
 {
  InitType ret;
  
  ret.handle=Win32::GetStdHandle(Win32::StdInputHandle);
  
  if( ret.handle==Win32::InvalidFileHandle ) 
    {
     ret.modes=0;
     ret.error=NonNullError();
     
     return ret;
    }
  
  if( ret.handle==0 ) 
    {
     ret.modes=0;
     ret.error=ErrorType(Win32::ErrorFileNotFound);
     
     return ret;
    }
  
  if( !Win32::GetConsoleMode(ret.handle,&ret.modes) ) 
    {
     ret.modes=0;
     ret.error=NonNullError();
     
     return ret;
    }
  
  ModeType new_modes=ret.modes;
  
  BitClear(new_modes,Win32::ConEcho|Win32::ConLineInput);
  
  if( !Win32::SetConsoleMode(ret.handle,new_modes) ) 
    {
     ret.error=NonNullError();
     
     return ret;
    }
  
  ret.error=NoError;
  
  return ret;
 }
  
ErrorType ConRead::Exit(Type handle,ModeType modes) noexcept
 {
  return ErrorIf( !Win32::SetConsoleMode(handle,modes) );
 }
 
auto ConRead::Read(Type handle,char *buf,ulen len) noexcept -> IOResult 
 {
  IOResult ret;
  
  if( Win32::ReadFile(handle,buf,len,&ret.len,0) )
    {
     ret.error=NoError;
    }
  else
    {
     ret.len=0;
     ret.error=NonNullError();
    }
  
  return ret;
 }
 
auto ConRead::Read(Type handle,char *buf,ulen len,MSec timeout) noexcept -> IOResult
 {
  IOResult ret;
 
  if( len==0 )
    {
     ret.error=NoError;
     ret.len=0;

     return ret;
    }
    
  TimeScope time_scope(timeout);  
  
  for(unsigned to_msec; (to_msec=+time_scope.get())!=0 ;)
    {
     Win32::options_t opt=Win32::WaitForSingleObject(handle,to_msec);
     
     if( opt==Win32::WaitObject_0 )
       {
        Win32::ConInputRecord input;
        Win32::ulen_t ret_len;

        if( !Win32::ReadConsoleInputA(handle,&input,1,&ret_len) )
          {
           ret.error=NonNullError();
           ret.len=0;
  
           return ret;
          }
          
        if( !ret_len )  
          {
           ret.error=ErrorType(Win32::ErrorReadFault);
           ret.len=0;
  
           return ret;
          }
          
        if( input.event_type==Win32::ConKeyEvent )  
          {
           if( input.event.key.key_down && input.event.key.ch.ascii )
             {
              *buf=input.event.key.ch.ascii;
             
              ret.error=NoError;
              ret.len=1;
  
              return ret;
             }
          }
       }
     else if( opt!=Win32::WaitTimeout )
       {
        ret.error=NonNullError();
        ret.len=0;
  
        return ret;
       }
    }
    
  ret.error=NoError;
  ret.len=0;
  
  return ret;
 }
 
} // namespace Sys
} // namespace CCore
 

