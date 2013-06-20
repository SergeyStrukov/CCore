/* SysFile.cpp */ 
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
 
#include <CCore/inc/sys/SysFile.h>
#include <CCore/inc/sys/SysInternal.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Fifo.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Print.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include <libaio.h>
#include <sys/eventfd.h>
#include <poll.h>

namespace CCore {
namespace Sys {

namespace Private_SysFile {

/* functions */

inline void AddErrorIf(FileMultiError &errout,FileError fe,bool nok)
 {
  if( nok ) errout.add(MakeError(fe));
 }

inline int MakeOpenFlags(FileOpenFlags oflags)
 {
  int ret;
  
  if( oflags&Open_Read )
    {
     if( oflags&(Open_Write|Open_Erase) )
       {
        ret=O_RDWR;
       }
     else
       {
        ret=O_RDONLY;
       }
    }
  else
    {
     if( oflags&(Open_Write|Open_Erase) )
       {
        ret=O_WRONLY;
       }
     else
       {
        ret=O_RDONLY; // stub choice
       }
    }
  
  if( oflags&Open_New )
    {
     ret|=O_CREAT|O_EXCL; 
    }
  else
    {
     if( oflags&Open_Create )
       {
        ret|=O_CREAT;
       }
     
     if( oflags&Open_Erase )
       {
        ret|=O_TRUNC;
       }
    }
   
  return ret; 
 }

/* classes */

struct OpenFile;

struct OpenAltFile;

struct OpenAltAsyncFile;

/* struct OpenFile */ 
 
struct OpenFile : File::OpenType
 {
  bool set(int fd)
   {
    handle=fd;
      
    if( fd==-1 )
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
        
    ::close(handle); // ignore unprobable error
        
    handle=-1;
   }
   
  explicit OpenFile(FileError fe)
   {
    handle=-1;
    to_unlink=0;
    error=fe;
   }
     
  OpenFile(const char *file_name,FileOpenFlags oflags)
   {
    to_unlink=0;
    
    // flags & mode
    
    int flags=MakeOpenFlags(oflags);
    int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
    
    // open
  
    if( !set( open(file_name,flags,mode) ) ) return;
    
    // post-open  
    
    if( oflags&Open_PosEnd )
      {
       if( lseek(handle,0,SEEK_END)==(off_t)-1 ) 
         {
          close();
          
          return;
         }
      }
  
    if( oflags&Open_AutoDelete )
      {
       to_unlink=realpath(file_name,nullptr);
       
       if( !to_unlink )
         {
          close();
         }
      }
   }
 };

/* struct OpenAltFile */ 
 
struct OpenAltFile : AltFile::OpenType
 {
  bool set(int fd)
   {
    handle=fd;
      
    if( fd==-1 )
      {
       error=MakeError(FileError_OpenFault);
       file_len=0;
          
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
        
    ::close(handle); // ignore unprobable error
        
    handle=-1;
   }
   
  explicit OpenAltFile(FileError fe)
   {
    handle=-1;
    file_len=0;
    to_unlink=0;
    error=fe;
   }
     
  OpenAltFile(const char *file_name,FileOpenFlags oflags)
   {
    to_unlink=0;
    
    // flags & mode
    
    int flags=MakeOpenFlags(oflags);
    int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
    
    // open
  
    if( !set( open(file_name,flags,mode) ) ) return;
    
    // post-open  
    
    {
     struct stat result;
      
     if( fstat(handle,&result)==-1 )
       {
        close();
        
        return;
       }
     else
       {
        file_len=(FilePosType)result.st_size;
       }
    }
  
    if( oflags&Open_AutoDelete )
      {
       to_unlink=realpath(file_name,nullptr);
       
       if( !to_unlink )
         {
          close();
         }
      }
   }
 };

/* struct OpenAltAsyncFile */ 
 
struct OpenAltAsyncFile : AltAsyncFile::OpenType
 {
  bool set(int fd)
   {
    handle=fd;
      
    if( fd==-1 )
      {
       error=MakeError(FileError_OpenFault);
       file_len=0;
          
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
        
    ::close(handle); // ignore unprobable error
        
    handle=-1;
   }
   
  explicit OpenAltAsyncFile(FileError fe)
   {
    handle=-1;
    file_len=0;
    to_unlink=0;
    error=fe;
   }
     
  OpenAltAsyncFile(const char *file_name,FileOpenFlags oflags)
   {
    to_unlink=0;
    
    // flags & mode
    
    int flags=MakeOpenFlags(oflags);
    int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
    
    // open
  
    if( !set( open(file_name,flags,mode) ) ) return;
    
    // post-open  
    
    {
     struct stat result;
      
     if( fstat(handle,&result)==-1 )
       {
        close();
        
        return;
       }
     else
       {
        file_len=(FilePosType)result.st_size;
       }
    }
  
    if( oflags&Open_AutoDelete )
      {
       to_unlink=realpath(file_name,nullptr);
       
       if( !to_unlink )
         {
          close();
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

void File::Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept
 {
  if( to_unlink )
    {
     if( !preserve_file )
       {
        AddErrorIf(errout,FileError_CloseFault, unlink(to_unlink)==-1 );
       }
    
     free(to_unlink);
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, fsync(handle)==-1 );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, ::close(handle)==-1 );
 }

auto File::Write(Type handle,FileOpenFlags oflags,const uint8 *buf,ulen len) noexcept -> IOResult
 {
  IOResult ret;
  
  if( oflags&Open_Write )
    {
     ssize_t result=::write(handle,buf,len);
     
     if( result==-1 )
       {
        ret.len=0;
        ret.error=MakeError(FileError_WriteFault);
       }
     else
       {
        ret.len=(ulen)result;
        ret.error=FileError_Ok;
       }
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
     ssize_t result=::read(handle,buf,len);
    
     if( result==-1 )
       {
        ret.len=0;
        ret.error=MakeError(FileError_ReadFault);
       }
     else
       {
        ret.len=(ulen)result;
        ret.error=FileError_Ok;
       }
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
     struct stat result;
     
     if( fstat(handle,&result)==-1 )
       {
        ret.pos=0;
        ret.error=MakeError(FileError_PosFault);
       }
     else
       {
        ret.pos=(FilePosType)result.st_size;
        ret.error=FileError_Ok;
       }
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
     off_t result=lseek(handle,0,SEEK_CUR);
    
     if( result==(off_t)-1 )
       {
        ret.pos=0;
        ret.error=MakeError(FileError_PosFault);
       }
     else
       {
        ret.pos=(FilePosType)result;
        ret.error=FileError_Ok;
       }
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
     off_t result=lseek(handle,pos,SEEK_SET);
     
     if( result==(off_t)-1 )
       return MakeError(FileError_PosFault);
     else
       return FileError_Ok;
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

void AltFile::Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept
 {
  if( to_unlink )
    {
     if( !preserve_file )
       {
        AddErrorIf(errout,FileError_CloseFault, unlink(to_unlink)==-1 );
       }
    
     free(to_unlink);
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, fsync(handle)==-1 );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, ::close(handle)==-1 );
 }

FileError AltFile::Write(Type handle,FileOpenFlags oflags,FilePosType off,const uint8 *buf,ulen len) noexcept
 {
  if( oflags&Open_Write )
    {
     // pos
     {
      off_t result=lseek(handle,off,SEEK_SET);
      
      if( result==(off_t)-1 ) return MakeError(FileError_WriteFault);
     }
     
     // write
     {
      ssize_t result=::write(handle,buf,len);
    
      if( result==-1 )
        {
         return MakeError(FileError_WriteFault);
        }
      else
        {
         if( (ulen)result!=len ) return FileError_WriteLenMismatch;
         
         return FileError_Ok;
        }
     }
    }
  else
    {
     return FileError_NoMethod;
    }
 }

FileError AltFile::Read(Type handle,FileOpenFlags oflags,FilePosType off,uint8 *buf,ulen len) noexcept
 {
  if( oflags&Open_Read )
    {
     // pos
     {
      off_t result=lseek(handle,off,SEEK_SET);
      
      if( result==(off_t)-1 ) return MakeError(FileError_ReadFault);
     }
     
     // read
     {
      ssize_t result=::read(handle,buf,len);
    
      if( result==-1 )
        {
         return MakeError(FileError_ReadFault);
        }
      else
        {
         if( (ulen)result!=len ) return FileError_ReadLenMismatch;
         
         return FileError_Ok;
        }
     }
    }
  else
    {
     return FileError_NoMethod;
    }
 }  

/* struct AltAsyncFile */

struct AltAsyncFile::AsyncState
 {
  struct iocb control_block;
  
  ulen index;
  
  ssize_t retlen;
  int error;
  
  void prepareRead(Type handle,uint8 *buf,ulen len,FilePosType off)
   {
    io_prep_pread(&control_block,handle,buf,len,off);
    
    control_block.data=this;
   }
  
  void prepareWrite(Type handle,const uint8 *buf,ulen len,FilePosType off)
   {
    io_prep_pwrite(&control_block,handle,const_cast<uint8 *>(buf),len,off);
    
    control_block.data=this;
   }
  
  void setEventFd(int fd)
   {
    io_set_eventfd(&control_block,fd);
   }
  
  FileError completeRead(ulen len)
   {
    if( retlen==-1 )
      {
       return MakeError(FileError_ReadFault,error);
      }
    else
      {
       if( len!=(ulen)retlen ) return FileError_ReadLenMismatch;
       
       return FileError_Ok;
      }
   }
  
  FileError completeWrite(ulen len)
   {
    if( retlen==-1 )
      {
       return MakeError(FileError_WriteFault,error);
      }
    else
      {
       if( len!=(ulen)retlen ) return FileError_WriteLenMismatch;
       
       return FileError_Ok;
      }
   }
  
  bool submit(io_context_t ctx)
   {
    struct iocb * temp[1]={&control_block};
    
    int result=io_submit(ctx,1,temp);
    
    if( result==1 ) return true;
    
    retlen=-1;
    error=-result;
    
    return false;
   }
  
  void complete(io_event *ev)
   {
    ssize_t result=ev->res;
    
    if( result<0 )
      {
       retlen=-1;
       error=int(-result);
      }
    else
      {
       retlen=result;
       error=0;
      }
   }
 };

auto AltAsyncFile::Open(StrLen file_name_,FileOpenFlags oflags) noexcept -> OpenType
 {
  FileName file_name;
 
  if( !file_name.set(file_name_) ) return OpenAltAsyncFile(FileError_TooLongPath); 
  
  return OpenAltAsyncFile(file_name,oflags); 
 }

void AltAsyncFile::Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept
 {
  if( to_unlink )
    {
     if( !preserve_file )
       {
        AddErrorIf(errout,FileError_CloseFault, unlink(to_unlink)==-1 );
       }
    
     free(to_unlink);
    }
    
  if( oflags&Open_Write )  
    {
     AddErrorIf(errout,FileError_CloseFault, fsync(handle)==-1 );  
    }
  
  AddErrorIf(errout,FileError_CloseFault, ::close(handle)==-1 );
 }

auto AltAsyncFile::StartRead(Type handle,Async async,FilePosType off,uint8 *buf,ulen len) noexcept -> RWResult
 {
  async->prepareRead(handle,buf,len,off);
  
  return {true,FileError_Ok};
 }

FileError AltAsyncFile::CompleteRead(Type,Async async,ulen len) noexcept
 {
  return async->completeRead(len);
 }

auto AltAsyncFile::StartWrite(Type handle,Async async,FilePosType off,const uint8 *buf,ulen len) noexcept -> RWResult
 {
  async->prepareWrite(handle,buf,len,off);
  
  return {true,FileError_Ok};
 }

FileError AltAsyncFile::CompleteWrite(Type,Async async,ulen len) noexcept
 {
  return async->completeWrite(len);
 }

/* class AsyncFileWait::Engine */

class AsyncFileWait::Engine : public MemBase_nocopy
 {
   class Context : NoCopy
    {
      io_context_t ctx;
      
     public: 
      
      explicit Context(ulen async_count)
       {
        int result=io_queue_init((int)async_count,&ctx);
        
        if( result )
          {
           Printf(Exception,"io_queue_init() : #;",-result);
          }
       }
      
      ~Context()
       {
        int result=io_queue_release(ctx);
        
        AbortIfError( -result ,"CCore::Sys::AsyncFileWait::Engine::Context::~Context()");
       }
    
      operator io_context_t() { return ctx; }
    };
  
   typedef AltAsyncFile::AsyncState AsyncState;
   
   enum Status
    {
     StatusReady,
     StatusFailed,
     StatusPending
    };
 
   class State : NoCopy , public NoThrowFlagsBase
    {
      AsyncState state;
      
     public: 
      
      Status status;
      
      State() : status(StatusReady) {}
      
      AsyncState * getAsync() { return &state; }
    };
   
   class FdSem : NoCopy
    {
      int fd;
     
     public: 
      
      FdSem()
       {
        fd=eventfd(0,EFD_SEMAPHORE);
        
        if( fd==-1 )
          {
           int error=errno;
          
           Printf(Exception,"eventfd() : #;",error);
          }
       }
      
      ~FdSem()
       {
        AbortIf( close(fd)==-1 ,"CCore::Sys::AsyncFileWait::Engine::FdSem::~FdSem()");
       }
      
      operator int() { return fd; }
      
      void give()
       {
        AbortIf( eventfd_write(fd,1)==-1 ,"CCore::Sys::AsyncFileWait::Engine::FdSem::give()");
       }
      
      void take()
       {
        eventfd_t value;
        
        AbortIf( eventfd_read(fd,&value)==-1 ,"CCore::Sys::AsyncFileWait::Engine::FdSem::take()");
       }
    };
   
   Context ctx;
   
   SimpleArray<State> state_buf;
   SimpleArray<AsyncState *> async_buf;
   
   SimpleArray<ulen> failed_buf;
   Fifo<ulen> failed_list;
   
   FdSem async_sem;
   FdSem interrupt_sem;
   bool async_first = false ;
   
  private:
   
   WaitResult waitAsync();
   
   WaitResult waitInterrupt();
   
  public:
   
   explicit Engine(ulen async_count);
   
   ~Engine();
   
   AsyncState ** getAsyncs() { return async_buf.getPtr(); }
   
   bool addWait(ulen index);
   
   bool delWait(ulen index);
   
   WaitResult wait(MSec timeout);
   
   void interrupt();
 };

WaitResult AsyncFileWait::Engine::waitAsync()
 {
  async_sem.take();
  
  struct io_event temp[1];
  
  int result=io_getevents(ctx,0,1,temp,NULL);
  
  if( result<=0 ) return Wait_error;
  
  AsyncState *async=static_cast<AsyncState *>(temp[0].data);
  
  async->complete(temp);
  
  return WaitResult(async->index);
 }

WaitResult AsyncFileWait::Engine::waitInterrupt()
 {
  interrupt_sem.take();
  
  return Wait_interrupt;
 }

AsyncFileWait::Engine::Engine(ulen async_count)
 : ctx(async_count),
   state_buf(async_count),
   async_buf(async_count),
   failed_buf(async_count),
   failed_list(failed_buf.getPtr(),failed_buf.getLen())
 {
  for(ulen i=0; i<async_count ;i++) 
    {
     AsyncState *async=state_buf[i].getAsync();
     
     async->index=i;
     
     async_buf[i]=async;
    }
 }

AsyncFileWait::Engine::~Engine()
 {
 }

bool AsyncFileWait::Engine::addWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].status!=StatusReady ) return false;
  
  AsyncState *async=state_buf[index].getAsync();
  
  async->setEventFd(async_sem);
  
  if( async->submit(ctx) )
    {
     state_buf[index].status=StatusPending;
    }
  else
    {
     state_buf[index].status=StatusFailed;
    
     failed_list.put(index);
    }
  
  return true;
 }

bool AsyncFileWait::Engine::delWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].status==StatusReady ) return false;
  
  state_buf[index].status=StatusReady;
  
  return true;
 }

WaitResult AsyncFileWait::Engine::wait(MSec timeout)
 {
  ulen index;
  
  if( failed_list.get(index) ) return WaitResult(index);

  struct pollfd towait[2];
    
  towait[0].fd=async_sem;
  towait[0].events=POLLIN;
    
  towait[1].fd=interrupt_sem;
  towait[1].events=POLLIN;
    
  int result=poll(towait,2,+timeout);
   
  if( result==-1 ) return Wait_error;
   
  if( result==0 ) return Wait_timeout;
   
  if( async_first )
    {
     if( towait[0].revents&POLLIN )
       {
        async_first=false;
         
        return waitAsync();
       }
     
     if( towait[1].revents&POLLIN )
       {
        return waitInterrupt();
       }
    }
  else
    {
     if( towait[1].revents&POLLIN )
       {
        async_first=true;
        
        return waitInterrupt();
       }
    
     if( towait[0].revents&POLLIN )
       {
        return waitAsync();
       }
    }
  
  return Wait_error;
 }

void AsyncFileWait::Engine::interrupt()
 {
  interrupt_sem.give();
 }

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
 

