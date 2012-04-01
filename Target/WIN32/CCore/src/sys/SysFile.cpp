/* SysFile.cpp */ 
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
 
#include <CCore/inc/sys/SysFile.h>
#include <CCore/inc/sys/SysFileInternal.h>
#include <CCore/inc/sys/SysWaitInternal.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysFile {

/* struct Functions */ 

struct Functions 
 {
  typedef Win32::bool_t WIN32_CALLTYPE (*SetFileInformationByHandle_type)(Win32::handle_t h_file,Win32::options_t file_info_options,Win32::void_ptr buf,Win32::ulen_t buf_len);
  
  SetFileInformationByHandle_type SetFileInformationByHandle;
 
  Functions();
  
  static const char * GetTag() { return "SysFile"; } 
 };
 
Functions::Functions()
 {
  Win32::handle_t h_module=Win32::GetModuleHandleA("kernel32.dll");
  
  SetFileInformationByHandle=(SetFileInformationByHandle_type)Win32::GetProcAddress(h_module,"SetFileInformationByHandle");
 }
 
PlanInitObject<Functions> Object CCORE_INITPRI_1 ;

/* AutoDelete() */ 

bool AutoDelete(Win32::handle_t handle,bool flag)
 {
#if 0 // supported from Vista 
 
  Win32::FileDispositionInfoData data;
     
  data.delete_file=flag;
    
  return Win32::SetFileInformationByHandle(handle,Win32::FileDispositionInfo,&data,sizeof data);
    
#else

  if( auto func=Object->SetFileInformationByHandle )
    {
     Win32::FileDispositionInfoData data;
     
     data.delete_file=flag;
        
     return func(handle,Win32::FileDispositionInfo,&data,sizeof data);
    }
    
  return true;
 
#endif    
 }
 
/* Make...() */ 
 
Win32::flags_t MakeAccessFlags(FileOpenFlags oflags)
 {
  Win32::flags_t ret=0;
  
  if( oflags&Open_Read  ) ret|=Win32::AccessRead;
  
  if( oflags&Open_Write ) ret|=Win32::AccessWrite;
  
  if( oflags&Open_AutoDelete ) ret|=Win32::AccessDelete;
  
  return ret;
 }

Win32::flags_t MakeShareFlags(FileOpenFlags)
 {
  return Win32::ShareRead;
 }
 
Win32::options_t MakeCreationOptions(FileOpenFlags oflags)
 {
  Win32::options_t ret;
  
  if( oflags&Open_New )
    {
     ret=Win32::CreateNew;
    }
  else
    {
     if( oflags&Open_Create )
       {
        if( oflags&Open_Erase )
          ret=Win32::CreateAlways;
        else
          ret=Win32::OpenAlways;
       }
     else
       {
        if( oflags&Open_Erase )
          ret=Win32::TruncateExisting;
        else
          ret=Win32::OpenExisting;
       }
    }
    
  return ret;  
 }
 
Win32::flags_t MakeFileFlags(FileOpenFlags oflags)
 {
  Win32::flags_t ret=Win32::FileAttributeNormal;
  
  if( !(oflags&Open_Pos) ) ret|=Win32::FileSequentialScan;
  
  return ret;
 }

Win32::flags_t MakeAltFileFlags(FileOpenFlags)
 {
  Win32::flags_t ret=Win32::FileAttributeNormal|Win32::FileAsyncIO;
  
  return ret;
 }

/* struct OpenFile */ 
 
struct OpenFile : File::OpenType
 {
  bool set(Win32::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win32::InvalidFileHandle )
      {
       error=MakeError(FileError_OpenFault);
          
       return false;
      }
    else
      {  
       error=FileError_Ok;
          
       return true;
      }
   }
     
  void close()
   {
    error=MakeError(FileError_OpenFault);
        
    Win32::CloseHandle(handle); // ignore unprobable error
        
    handle=Win32::InvalidFileHandle;
   }
   
  explicit OpenFile(FileError fe)
   {
    handle=Win32::InvalidFileHandle;
    error=fe;
   }
     
  OpenFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win32::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win32::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win32::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win32::flags_t file_flags = MakeFileFlags(oflags) ;
  
    // open
  
    if( !set( Win32::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( oflags&Open_PosEnd )
      {
       if( !Win32::SetFilePointerEx(handle,0,0,Win32::FromEnd) ) 
         {
          close();
          
          return;
         }
      }
  
    if( oflags&Open_AutoDelete ) 
      {
       if( !AutoDelete(handle,true) ) 
         {
          close();
          
          return;
         }
      }
   }
 };

/* struct OpenAltFile */ 
 
struct OpenAltFile : AltFile::OpenType
 {
  bool set(Win32::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win32::InvalidFileHandle )
      {
       h_event=0;
       file_len=0;
       error=MakeError(FileError_OpenFault);
          
       return false;
      }
    else
      {  
       error=FileError_Ok;
          
       return true;
      }
   }
     
  void close()
   {
    h_event=0;
    file_len=0;
    error=MakeError(FileError_OpenFault);
        
    Win32::CloseHandle(handle); // ignore unprobable error
        
    handle=Win32::InvalidFileHandle;
   }
   
  explicit OpenAltFile(FileError fe)
   {
    handle=Win32::InvalidFileHandle;
    h_event=0;
    file_len=0;
    error=fe;
   }
     
  OpenAltFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win32::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win32::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win32::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win32::flags_t file_flags = MakeAltFileFlags(oflags) ;
  
    // open
  
    if( !set( Win32::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( !Win32::GetFileSizeEx(handle,&file_len) ) 
      {
       close();
          
       return;
      }
  
    if( oflags&Open_AutoDelete ) 
      {
       if( !AutoDelete(handle,true) ) 
         {
          close();
          
          return;
         }
      }
    
    h_event=Win32::CreateEventA(0,false,false,0);
    
    if( h_event==0 ) 
      {
       close();
       
       return;
      }
   }
 };

/* struct OpenAltAsyncFile */ 
 
struct OpenAltAsyncFile : AltAsyncFile::OpenType
 {
  bool set(Win32::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win32::InvalidFileHandle )
      {
       file_len=0;
       error=MakeError(FileError_OpenFault);
          
       return false;
      }
    else
      {  
       error=FileError_Ok;
          
       return true;
      }
   }
     
  void close()
   {
    file_len=0;
    error=MakeError(FileError_OpenFault);
        
    Win32::CloseHandle(handle); // ignore unprobable error
        
    handle=Win32::InvalidFileHandle;
   }
   
  explicit OpenAltAsyncFile(FileError fe)
   {
    handle=Win32::InvalidFileHandle;
    file_len=0;
    error=fe;
   }
     
  OpenAltAsyncFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win32::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win32::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win32::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win32::flags_t file_flags = MakeAltFileFlags(oflags) ;
  
    // open
  
    if( !set( Win32::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( !Win32::GetFileSizeEx(handle,&file_len) ) 
      {
       close();
          
       return;
      }
  
    if( oflags&Open_AutoDelete ) 
      {
       if( !AutoDelete(handle,true) ) 
         {
          close();
          
          return;
         }
      }
   }
 };

} // namespace Private_SysFile
 
using namespace Private_SysFile;
 
PlanInitNode * GetPlanInitNode_SysFile() { return &Object; }
 
/* struct File */ 

auto File::Open(StrLen file_name_,FileOpenFlags oflags) noexcept -> OpenType
 {
  FileName file_name;
 
  if( !file_name.set(file_name_) ) return OpenFile(FileError_TooLongPath);
  
  return OpenFile(file_name,oflags);
 }
  
void File::Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,bool preserve_file) noexcept
 {
  if( preserve_file )
    {
     AddErrorIf(errout,FileError_CloseFault, !AutoDelete(handle,false) );
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, !Win32::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win32::CloseHandle(handle) );
 }
  
auto File::Write(Type handle,FileOpenFlags oflags,const uint8 *buf,ulen len) noexcept -> IOResult
 {
  IOResult ret;
  
  if( oflags&Open_Write )
    {
     ret.error=MakeErrorIf(FileError_WriteFault, !Win32::WriteFile(handle,buf,len,&ret.len,0) );
    }
  else
    {
     ret.len=0;
     ret.error=FileError_NoMethod;
    }  
  
  return ret;  
 }
  
auto File::Read(Type handle,FileOpenFlags oflags,uint8 *buf,ulen len) noexcept -> IOResult
 {
  IOResult ret;
  
  if( oflags&Open_Read )
    {
     ret.error=MakeErrorIf(FileError_ReadFault, !Win32::ReadFile(handle,buf,len,&ret.len,0) );
    }
  else
    {
     ret.len=0;
     ret.error=FileError_NoMethod;
    }  
  
  return ret;  
 }
  
auto File::GetLen(Type handle,FileOpenFlags oflags) noexcept -> PosResult
 {
  PosResult ret;

  if( oflags&Open_Pos )
    {
     ret.error=MakeErrorIf(FileError_PosFault, !Win32::GetFileSizeEx(handle,&ret.pos) );  
    }
  else
    {
     ret.pos=0;
     ret.error=FileError_NoMethod;
    }  
    
  return ret;    
 }
  
auto File::GetPos(Type handle,FileOpenFlags oflags) noexcept -> PosResult
 {
  PosResult ret;

  if( oflags&Open_Pos )
    {
     ret.error=MakeErrorIf(FileError_PosFault, !Win32::SetFilePointerEx(handle,0,&ret.pos,Win32::FromCurrent) );
    }
  else
    {
     ret.pos=0;
     ret.error=FileError_NoMethod;
    }  
  
  return ret;
 }
  
FileError File::SetPos(Type handle,FileOpenFlags oflags,FilePosType pos) noexcept
 {
  if( oflags&Open_Pos )
    {
     return MakeErrorIf(FileError_PosFault, !Win32::SetFilePointerEx(handle,pos,0,Win32::FromBegin) );
    }
  else
    {
     return FileError_NoMethod;
    }  
 }

/* struct AltFile */ 

auto AltFile::Open(StrLen file_name_,FileOpenFlags oflags) noexcept -> OpenType
 {
  FileName file_name;
 
  if( !file_name.set(file_name_) ) return OpenAltFile(FileError_TooLongPath);
  
  return OpenAltFile(file_name,oflags);
 }

void AltFile::Close(FileMultiError &errout,Type handle,EventType h_event,FileOpenFlags oflags,bool preserve_file) noexcept
 {
  if( preserve_file )
    {
     AddErrorIf(errout,FileError_CloseFault, !AutoDelete(handle,false) );
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, !Win32::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win32::CloseHandle(handle) );
  
  AbortIf( !Win32::CloseHandle(h_event) ,"CCore::Sys::AltFile::Close()");
 }
  
FileError AltFile::Write(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,const uint8 *buf,ulen len) noexcept
 {
  if( oflags&Open_Write )
    {
     Win32::Overlapped olap;
     Win32::ulen_t ret_len;
     
     olap.internal=0;
     olap.offset=off;
     olap.h_event=h_event;
     
     if( Win32::WriteFile(handle,buf,len,&ret_len,&olap) )
       {
        // all done
       }
     else
       {
        auto error=Win32::GetLastError();
       
        if( error==Win32::ErrorIOPending ) 
          {
           if( !Win32::GetOverlappedResult(handle,&olap,&ret_len,true) ) return MakeError(FileError_WriteFault);
          }
        else
          {
           return MakeError(FileError_WriteFault,error);
          }
       }
     
     if( ret_len!=len ) return FileError_WriteLenMismatch;
     
     return FileError_Ok;
    }
  else
    {
     return FileError_NoMethod;
    }  
 }

FileError AltFile::Read(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,uint8 *buf,ulen len) noexcept
 {
  if( oflags&Open_Read )
    {
     Win32::Overlapped olap;
     Win32::ulen_t ret_len;
     
     olap.internal=0;
     olap.offset=off;
     olap.h_event=h_event;
     
     if( Win32::ReadFile(handle,buf,len,&ret_len,&olap) )
       {
        // all done
       }
     else
       {
        auto error=Win32::GetLastError();
        
        if( error==Win32::ErrorIOPending )
          {
           if( !Win32::GetOverlappedResult(handle,&olap,&ret_len,true) ) return MakeError(FileError_ReadFault);
          }
        else
          {
           return MakeError(FileError_ReadFault,error);
          }
       }
     
     if( ret_len!=len ) return FileError_ReadLenMismatch;
     
     return FileError_Ok;
    }
  else
    {
     return FileError_NoMethod;
    }  
 }
 
/* struct AltAsyncFile */

struct AltAsyncFile::AsyncState
 {
  Win32::Overlapped olap;
 };

auto AltAsyncFile::Open(StrLen file_name_,FileOpenFlags oflags) noexcept -> OpenType
 {
  FileName file_name;
 
  if( !file_name.set(file_name_) ) return OpenAltAsyncFile(FileError_TooLongPath);
  
  return OpenAltAsyncFile(file_name,oflags);
 }

void AltAsyncFile::Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,bool preserve_file) noexcept
 {
  if( preserve_file )
    {
     AddErrorIf(errout,FileError_CloseFault, !AutoDelete(handle,false) );
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, !Win32::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win32::CloseHandle(handle) );
 }

auto AltAsyncFile::StartRead(Type handle,Async async,FilePosType off,uint8 *buf,ulen len) noexcept -> RWResult
 {
  RWResult ret;
  Win32::ulen_t ret_len;
  Win32::Overlapped *olap=&async->olap;

  olap->internal=0;
  olap->offset=off;
  
  if( Win32::ReadFile(handle,buf,len,&ret_len,olap) )
    {
     if( ret_len==len )
       {
        ret.error=FileError_Ok;
       }
     else
       {
        ret.error=FileError_ReadLenMismatch;
       }
     
     ret.pending=false;

     return ret;
    }
  else 
    {
     auto error=Win32::GetLastError();
     
     if( error==Win32::ErrorIOPending )
       {
        ret.error=FileError_Ok;
        ret.pending=true;
        
        return ret;
       }
     else
       {
        ret.error=MakeError(FileError_ReadFault,error);
        ret.pending=false;
        
        return ret;
       }
    }
 }

FileError AltAsyncFile::CompleteRead(Type handle,Async async,ulen len) noexcept
 {
  Win32::ulen_t ret_len;

  if( !Win32::GetOverlappedResult(handle,&async->olap,&ret_len,false) ) return MakeError(FileError_ReadFault);
  
  if( ret_len!=len ) return FileError_ReadLenMismatch;
  
  return FileError_Ok;
 }

auto AltAsyncFile::StartWrite(Type handle,Async async,FilePosType off,const uint8 *buf,ulen len) noexcept -> RWResult
 {
  RWResult ret;
  Win32::ulen_t ret_len;
  Win32::Overlapped *olap=&async->olap;
  
  olap->internal=0;
  olap->offset=off;
  
  if( Win32::WriteFile(handle,buf,len,&ret_len,olap) )
    {
     if( ret_len==len )
       {
        ret.error=FileError_Ok;
       }
     else
       {
        ret.error=FileError_WriteLenMismatch;
       }
     
     ret.pending=false;

     return ret;
    }
  else 
    {
     auto error=Win32::GetLastError();
     
     if( error==Win32::ErrorIOPending )
       {
        ret.error=FileError_Ok;
        ret.pending=true;
        
        return ret;
       }
     else
       {
        ret.error=MakeError(FileError_WriteFault,error);
        ret.pending=false;
        
        return ret;
       }
    }
 }

FileError AltAsyncFile::CompleteWrite(Type handle,Async async,ulen len) noexcept
 {
  Win32::ulen_t ret_len;

  if( !Win32::GetOverlappedResult(handle,&async->olap,&ret_len,false) ) return MakeError(FileError_WriteFault);
  
  if( ret_len!=len ) return FileError_WriteLenMismatch;
  
  return FileError_Ok;
 }

/* class AsyncFileWait::Engine */

class AsyncFileWait::Engine : public WaitBase<AltAsyncFile::AsyncState,WaitFile>
 {
  public:
   
   explicit Engine(ulen async_count) : WaitBase<AltAsyncFile::AsyncState,WaitFile>(async_count) {}
   
   ~Engine() {}
 };

/* struct AsyncFileWait */

FileError AsyncFileWait::init(ulen async_count) noexcept
 {
  if( async_count>MaxAsyncs ) return FileError_BadLen;
  
  SilentReportException report;
  
  try
    {
     obj=new Engine(async_count);
     
     asyncs=obj->getAsyncs();
     
     return FileError_Ok;
    }
  catch(CatchType)
    {
     return FileError_SysOverload;
    }
 }

void AsyncFileWait::exit() noexcept
 {
  delete Replace_null(obj);
  
  asyncs=0;
 }

bool AsyncFileWait::addWait(ulen index) noexcept
 {
  return obj->addWait(index);
 }

bool AsyncFileWait::delWait(ulen index) noexcept
 {
  return obj->delWait(index);
 }

auto AsyncFileWait::wait(MSec timeout) noexcept -> WaitResult
 {
  return obj->wait(timeout);
 }

void AsyncFileWait::interrupt() noexcept
 {
  obj->interrupt();
 }

} // namespace Sys
} // namespace CCore
 

