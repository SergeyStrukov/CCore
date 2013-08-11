/* SysFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
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

/* AutoDelete() */ 

bool AutoDelete(Win64::handle_t handle,bool flag)
 {
  Win64::FileDispositionInfoData data;
     
  data.delete_file=flag;
    
  return Win64::SetFileInformationByHandle(handle,Win64::FileDispositionInfo,&data,sizeof data);
 }
 
/* Make...() */ 
 
Win64::flags_t MakeAccessFlags(FileOpenFlags oflags)
 {
  Win64::flags_t ret=0;
  
  if( oflags&Open_Read  ) ret|=Win64::AccessRead;
  
  if( oflags&Open_Write ) ret|=Win64::AccessWrite;
  
  if( oflags&Open_AutoDelete ) ret|=Win64::AccessDelete;
  
  return ret;
 }

Win64::flags_t MakeShareFlags(FileOpenFlags)
 {
  return Win64::ShareRead;
 }
 
Win64::options_t MakeCreationOptions(FileOpenFlags oflags)
 {
  Win64::options_t ret;
  
  if( oflags&Open_New )
    {
     ret=Win64::CreateNew;
    }
  else
    {
     if( oflags&Open_Create )
       {
        if( oflags&Open_Erase )
          ret=Win64::CreateAlways;
        else
          ret=Win64::OpenAlways;
       }
     else
       {
        if( oflags&Open_Erase )
          ret=Win64::TruncateExisting;
        else
          ret=Win64::OpenExisting;
       }
    }
    
  return ret;  
 }
 
Win64::flags_t MakeFileFlags(FileOpenFlags oflags)
 {
  Win64::flags_t ret=Win64::FileAttributeNormal;
  
  if( !(oflags&Open_Pos) ) ret|=Win64::FileSequentialScan;
  
  return ret;
 }

Win64::flags_t MakeAltFileFlags(FileOpenFlags)
 {
  Win64::flags_t ret=Win64::FileAttributeNormal|Win64::FileAsyncIO;
  
  return ret;
 }

/* struct OpenFile */ 
 
struct OpenFile : File::OpenType
 {
  bool set(Win64::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win64::InvalidFileHandle )
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
        
    Win64::CloseHandle(handle); // ignore unprobable error
        
    handle=Win64::InvalidFileHandle;
   }
   
  explicit OpenFile(FileError fe)
   {
    handle=Win64::InvalidFileHandle;
    error=fe;
   }
     
  OpenFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win64::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win64::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win64::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win64::flags_t file_flags = MakeFileFlags(oflags) ;
  
    // open
  
    if( !set( Win64::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( oflags&Open_PosEnd )
      {
       if( !Win64::SetFilePointerEx(handle,0,0,Win64::FromEnd) ) 
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
  bool set(Win64::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win64::InvalidFileHandle )
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
        
    Win64::CloseHandle(handle); // ignore unprobable error
        
    handle=Win64::InvalidFileHandle;
   }
   
  explicit OpenAltFile(FileError fe)
   {
    handle=Win64::InvalidFileHandle;
    h_event=0;
    file_len=0;
    error=fe;
   }
     
  OpenAltFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win64::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win64::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win64::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win64::flags_t file_flags = MakeAltFileFlags(oflags) ;
  
    // open
  
    if( !set( Win64::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( !Win64::GetFileSizeEx(handle,&file_len) ) 
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
    
    h_event=Win64::CreateEventA(0,false,false,0);
    
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
  bool set(Win64::handle_t h_file)
   {
    handle=h_file;
      
    if( h_file==Win64::InvalidFileHandle )
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
        
    Win64::CloseHandle(handle); // ignore unprobable error
        
    handle=Win64::InvalidFileHandle;
   }
   
  explicit OpenAltAsyncFile(FileError fe)
   {
    handle=Win64::InvalidFileHandle;
    file_len=0;
    error=fe;
   }
     
  OpenAltAsyncFile(const char *file_name,FileOpenFlags oflags)
   {
    // flags & options
  
    Win64::flags_t access_flags = MakeAccessFlags(oflags) ;
  
    Win64::flags_t share_flags = MakeShareFlags(oflags) ;
  
    Win64::options_t creation_options = MakeCreationOptions(oflags) ;
  
    Win64::flags_t file_flags = MakeAltFileFlags(oflags) ;
  
    // open
  
    if( !set( Win64::CreateFileA(file_name,access_flags,share_flags,0,creation_options,file_flags,0) ) ) return;
    
    // post-open  
    
    if( !Win64::GetFileSizeEx(handle,&file_len) ) 
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
     AddErrorIf(errout,FileError_CloseFault, !Win64::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win64::CloseHandle(handle) );
 }
  
auto File::Write(Type handle,FileOpenFlags oflags,const uint8 *buf,ulen len) noexcept -> IOResult
 {
  IOResult ret;
  
  if( oflags&Open_Write )
    {
     ret.error=MakeErrorIf(FileError_WriteFault, !Win64::ExtWriteFile(handle,buf,len,&ret.len) );
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
     ret.error=MakeErrorIf(FileError_ReadFault, !Win64::ExtReadFile(handle,buf,len,&ret.len) );
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
     ret.error=MakeErrorIf(FileError_PosFault, !Win64::GetFileSizeEx(handle,&ret.pos) );  
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
     ret.error=MakeErrorIf(FileError_PosFault, !Win64::SetFilePointerEx(handle,0,&ret.pos,Win64::FromCurrent) );
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
     return MakeErrorIf(FileError_PosFault, !Win64::SetFilePointerEx(handle,pos,0,Win64::FromBegin) );
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
     AddErrorIf(errout,FileError_CloseFault, !Win64::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win64::CloseHandle(handle) );
  
  AbortIf( !Win64::CloseHandle(h_event) ,"CCore::Sys::AltFile::Close()");
 }
  
FileError AltFile::Write(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,const uint8 *buf,ulen len) noexcept
 {
#if 0
  
  if( oflags&Open_Write )
    {
     Win64::Overlapped olap;
     Win64::ulen_t ret_len;
     
     olap.internal=0;
     olap.offset=off;
     olap.h_event=h_event;
     
     if( Win64::WriteFile(handle,buf,len,&ret_len,&olap) )
       {
        // all done
       }
     else
       {
        auto error=Win64::GetLastError();
       
        if( error==Win64::ErrorIOPending ) 
          {
           if( !Win64::GetOverlappedResult(handle,&olap,&ret_len,true) ) return MakeError(FileError_WriteFault);
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
   
#endif   
    {
     return FileError_NoMethod;
    }  
 }

FileError AltFile::Read(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,uint8 *buf,ulen len) noexcept
 {
#if 0
  
  if( oflags&Open_Read )
    {
     Win64::Overlapped olap;
     Win64::ulen_t ret_len;
     
     olap.internal=0;
     olap.offset=off;
     olap.h_event=h_event;
     
     if( Win64::ReadFile(handle,buf,len,&ret_len,&olap) )
       {
        // all done
       }
     else
       {
        auto error=Win64::GetLastError();
        
        if( error==Win64::ErrorIOPending )
          {
           if( !Win64::GetOverlappedResult(handle,&olap,&ret_len,true) ) return MakeError(FileError_ReadFault);
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
   
#endif   
    {
     return FileError_NoMethod;
    }  
 }
 
/* struct AltAsyncFile */

struct AltAsyncFile::AsyncState
 {
  Win64::Overlapped olap;
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
     AddErrorIf(errout,FileError_CloseFault, !Win64::FlushFileBuffers(handle) );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, !Win64::CloseHandle(handle) );
 }

auto AltAsyncFile::StartRead(Type handle,Async async,FilePosType off,uint8 *buf,ulen len) noexcept -> RWResult
 {
  RWResult ret;
  
  if( len>Win64::MaxUShortLen )
    {
     ret.error=FileError_BadLen;
     ret.pending=false;
    
     return ret;
    }
  
  Win64::ushortlen_t ret_len;
  Win64::Overlapped *olap=&async->olap;

  olap->internal=0;
  olap->internal_hi=0;
  olap->offset=off;
  
  if( Win64::ReadFile(handle,buf,(Win64::ushortlen_t)len,&ret_len,olap) )
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
     auto error=Win64::GetLastError();
     
     if( error==Win64::ErrorIOPending )
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
  Win64::ushortlen_t ret_len;

  if( !Win64::GetOverlappedResult(handle,&async->olap,&ret_len,false) ) return MakeError(FileError_ReadFault);
  
  if( ret_len!=len ) return FileError_ReadLenMismatch;
  
  return FileError_Ok;
 }

auto AltAsyncFile::StartWrite(Type handle,Async async,FilePosType off,const uint8 *buf,ulen len) noexcept -> RWResult
 {
  RWResult ret;
  
  if( len>Win64::MaxUShortLen )
    {
     ret.error=FileError_BadLen;
     ret.pending=false;
    
     return ret;
    }
  
  Win64::ushortlen_t ret_len;
  Win64::Overlapped *olap=&async->olap;
  
  olap->internal=0;
  olap->internal_hi=0;
  olap->offset=off;
  
  if( Win64::WriteFile(handle,buf,(Win64::ushortlen_t)len,&ret_len,olap) )
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
     auto error=Win64::GetLastError();
     
     if( error==Win64::ErrorIOPending )
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
  Win64::ushortlen_t ret_len;

  if( !Win64::GetOverlappedResult(handle,&async->olap,&ret_len,false) ) return MakeError(FileError_WriteFault);
  
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
 

