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

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

namespace CCore {
namespace Sys {

namespace Private_SysFile {

/* functions */

inline FileError MakeError(FileError fe,int error)
 {
  switch( error )
    {
     case ENOENT       : return FileError_NoFile;
     case EMFILE       : return FileError_SysOverload;
     case ENFILE       : return FileError_SysOverload;
     case EACCES       : return FileError_NoAccess;
     case ENOMEM       : return FileError_SysOverload;
     case ENODEV       : return FileError_NoDevice;
     case ENOSPC       : return FileError_DiskFull;
     case EBADF        : return FileError_BadId;
     case EEXIST       : return FileError_FileExist;
     case ENOTEMPTY    : return FileError_DirIsNotEmpty;
     case EFBIG        : return FileError_SysOverload;
     case ENAMETOOLONG : return FileError_TooLongPath;
    
     default: 
      {
       //Printf(Con,"error = #;\n",error); 
       
       return fe;
      }
    }
 }
 
inline FileError MakeError(FileError fe)
 {
  return MakeError(fe,errno);
 }

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

struct FileName;

struct OpenFile;

struct OpenAltFile;

/* struct FileName */ 

struct FileName
 {
  char buf[MaxPathLen+1];
    
  operator const char * () const { return buf; }
    
  template <class T>  
  bool set(T str)
   {
    if( str.len>MaxPathLen ) return false;
      
    str.copyTo(buf);
  
    buf[str.len]=0;
      
    return true;
   }
   
  template <class T1,class T2>  
  bool set(T1 str1,T2 str2)
   {
    if( str1.len>MaxPathLen || str2.len>MaxPathLen-str1.len ) return false;
      
    str1.copyTo(buf);
    str2.copyTo(buf+str1.len);
  
    buf[str1.len+str2.len]=0;
      
    return true;
   }
 };

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

auto AltAsyncFile::open(StrLen /*file_name*/,FileOpenFlags /*oflags*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
  
void AltAsyncFile::close(FileMultiError & /*errout*/,bool /*preserve_file*/) noexcept
 {
  // TODO
 }
  
void AltAsyncFile::close() noexcept
 {
  FileMultiError errout;

  close(errout);
 }
  
FileError AltAsyncFile::testRead(FilePosType /*off*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
auto AltAsyncFile::setWrite(FilePosType /*off*/,ulen /*len*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
  
auto AltAsyncFile::startRead(Async /*async*/,FilePosType /*off*/,uint8 * /*buf*/,ulen /*len*/) noexcept -> RWResult
 {
  // TODO

  return RWResult{};
 }
  
FileError AltAsyncFile::completeRead(Async /*async*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
auto AltAsyncFile::startWrite(Async /*async*/,FilePosType /*off*/,const uint8 * /*buf*/,ulen /*len*/) noexcept -> RWResult
 {
  // TODO

  return RWResult{};
 }
  
FileError AltAsyncFile::completeWrite(Async /*async*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }

/* struct AsyncFileWait */

FileError AsyncFileWait::init(ulen /*async_count*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
void AsyncFileWait::exit() noexcept
 {
  // TODO
 }
  
AltAsyncFile::Async AsyncFileWait::getAsync(ulen /*index*/) noexcept
 {
  // TODO

  return 0;
 }
  
bool AsyncFileWait::addWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
bool AsyncFileWait::delWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
WaitResult AsyncFileWait::wait(MSec /*timeout*/) noexcept
 {
  // TODO

  return Wait_error; 
 }
  
WaitResult AsyncFileWait::wait(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return Wait_error; 
 }
  
void AsyncFileWait::interrupt() noexcept
 {
  // TODO
 }

} // namespace Sys
} // namespace CCore
 

