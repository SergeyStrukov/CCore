/* SysFileSystem.cpp */ 
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
 
#include <CCore/inc/sys/SysFileSystem.h>
 
#include <CCore/inc/sys/SysInternal.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include <spawn.h>

#ifndef _DIRENT_HAVE_D_TYPE
#error "Bad dirent"
#endif

namespace CCore {
namespace Sys {

/* namespace Private_SysFileSystem */ 

namespace Private_SysFileSystem {

/* functions */

FileError EmptyDirRecursive(StrLen dir_name);

FileError DeleteDirRecursive(StrLen dir_name);

/* struct NameBuf */

struct NameBuf
 {
  char buf[MaxPathLen+1];
  ulen dir_len;
  ulen buf_len;
  
  bool init(StrLen dir_name)
   {
    if( dir_name.len>MaxPathLen-1 ) return false;
   
    dir_name.copyTo(buf);
    
    buf[dir_name.len]='/';
    
    dir_len=dir_name.len+1;
    
    return true;
   }
  
  bool set(StrLen file_name)
   {
    if( file_name.len>MaxPathLen-dir_len ) return false;
   
    file_name.copyTo(buf+dir_len);
    
    buf[dir_len+file_name.len]=0;
    
    buf_len=dir_len+file_name.len;
    
    return true;
   }
  
  operator const char * () const { return buf; }
  
  StrLen getStr() const { return StrLen(buf,buf_len); }
 };
 
/* IsSpecial() */

bool IsSpecial(StrLen name) 
 {
  return ( name.len==1 && name[0]=='.' ) || ( name.len==2 && name[0]=='.' && name[1]=='.' ) ;
 }
 
/* EmptyDirRecursive() */

FileError EmptyDirRecursive(StrLen dir_name)
 {
  NameBuf buf;
  
  if( !buf.init(dir_name) ) return FileError_TooLongPath;
  
  DIR *dir=opendir(dir_name.ptr);
  
  if( !dir ) return MakeError(FileError_OpFault);
  
  errno=0;
  
  while( dirent *result=readdir(dir) )
    {
     StrLen file_name(result->d_name);
     
     if( !IsSpecial(file_name) )
       {
        FileError fe=FileError_Ok;
        
        if( buf.set(file_name) )
          {
           if( result->d_type==DT_DIR )
             {
              fe=DeleteDirRecursive(buf.getStr());
             }
           else
             {
              if( unlink(buf)==-1 )
                {
                 fe=MakeError(FileError_OpFault);
                }
             }
          }
        else
          {
           fe=FileError_TooLongPath;
          }
       
        if( fe )
          {
           closedir(dir);
           
           return fe;
          }
       }
     
     errno=0;
    }
  
  int error=errno;
  
  closedir(dir);
  
  if( error ) return MakeError(FileError_OpFault);
  
  return FileError_Ok;
 }

/* DeleteDirRecursive() */
 
FileError DeleteDirRecursive(StrLen dir_name)
 {
  if( FileError fe=EmptyDirRecursive(dir_name) ) return fe;
  
  if( rmdir(dir_name.ptr)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }

/* class StrPool */

class StrPool : NoCopy
 {
   ElementPool pool;
 
  public:
 
   StrPool() : pool(4_KByte) {}
   
   ~StrPool() {}
   
   char * add(StrLen str)
    {
     auto buf=pool.createArray_raw<char>(LenAdd(str.len,1));
     
     str.copyTo(buf.ptr);
     
     buf.back(1)=0;
     
     return buf.ptr;
    }
   
   char * add(StrLen str1,StrLen str2)
    {
     auto buf=pool.createArray_raw<char>(LenAdd(str1.len,str2.len,1));
     
     str1.copyTo(buf.ptr);
     str2.copyTo(buf.ptr+str1.len);
     
     buf.back(1)=0;
     
     return buf.ptr;
    }
 };

/* class StrList */

class StrList : NoCopy
 {
   StrPool &pool;
   DynArray<char *> list;
   
  public:
  
   explicit StrList(StrPool &pool_) : pool(pool_),list(DoReserve,100) {}
   
   ~StrList() {}
   
   void add(StrLen str)
    {
     list.append_copy(pool.add(str));
    }
   
   void add(StrLen str1,StrLen str2)
    {
     list.append_copy(pool.add(str1,str2));
    }
   
   char ** complete()
    {
     list.append_copy(0);
     
     return list.getPtr();
    }
   
   void prepareArg(StrLen program,StrLen arg);
   
   void prepareEnv(StrLen dir);
 };

void StrList::prepareArg(StrLen program,StrLen arg)
 {
  add(program);
  
  while( +arg )
    {
     for(; +arg && CharIsSpace(*arg) ;++arg);
     
     if( !arg ) return;
     
     if( *arg=='\'' )
       {
        ++arg;
        
        StrLen cur=arg;
        
        for(; +cur && *cur!='\'' ;++cur);
        
        add(arg.prefix(cur));
        
        arg=cur;
        
        if( +arg ) ++arg;
       }
     else if( *arg=='"' )
       {
        ++arg;
       
        StrLen cur=arg;
       
        for(; +cur && *cur!='"' ;++cur);
       
        add(arg.prefix(cur));
       
        arg=cur;
       
        if( +arg ) ++arg;
       }
     else
       {
        StrLen cur=arg;
       
        for(; +cur && !CharIsSpace(*cur) ;++cur);
        
        add(arg.prefix(cur));
        
        arg=cur;
       }
    }
 }

void StrList::prepareEnv(StrLen dir)
 {
  StrLen prefix("PWD=");
  
  add(prefix,dir);
  
  for(char **env=environ; char *str_=*env ;env++)
    {
     StrLen str(str_);
    
     if( !str.hasPrefix(prefix) ) add(str);
    }
 }

} // namespace Private_SysFileSystem
 
using namespace Private_SysFileSystem;
 
/* struct FileSystem::DirCursor */

void FileSystem::DirCursor::init(FileSystem *,StrLen dir_name) noexcept
 {
  FileName path;
  
  if( path.set(dir_name) )
    {
     dir=opendir(path);
     
     if( dir )
       error=FileError_Ok;
     else
       error=MakeError(FileError_OpFault);
    }
  else
    {
     dir=0;
     error=FileError_TooLongPath;
    }  
 }
  
void FileSystem::DirCursor::exit() noexcept
 {
  if( dir )
    {
     closedir(static_cast<DIR *>(dir));
    }
 }
    
bool FileSystem::DirCursor::next() noexcept
 {
  if( !dir ) return false;
  
  errno=0;
  
  if( dirent *result=readdir(static_cast<DIR *>(dir)) )
    {
     StrLen name(result->d_name);
     
     if( name.len>MaxPathLen )
       {
        error=FileError_TooLongPath;
        
        closedir(static_cast<DIR *>(dir));
        
        dir=0;
        
        return false;
       }
    
     name.copyTo(file_name);
     len=name.len;
     type=(result->d_type==DT_DIR)?FileType_dir:FileType_file;
     error=FileError_Ok;
    
     return true;
    }
  else
    {
     int error_=errno;
     
     if( error_ )
       {
        error=MakeError(FileError_OpFault,error_);
       }
     else
       {
        error=FileError_Ok;
       }
     
     closedir(static_cast<DIR *>(dir));
     
     dir=0;
     
     return false;
    }
 }
 
/* struct FileSystem */ 

FileError FileSystem::init() noexcept
 {
  return FileError_Ok;
 }
  
FileError FileSystem::exit() noexcept
 {
  return FileError_Ok;
 }
  
auto FileSystem::getFileType(StrLen path) noexcept -> TypeResult
 {
  FileName file_name;
  
  if( !file_name.set(path) ) return {FileType_none,FileError_TooLongPath};

  struct stat result;
  
  if( stat(file_name,&result)==-1 ) 
    {
     int error=errno;
     
     if( error==ENOENT || error==ENOTDIR ) return {FileType_none,FileError_Ok};
    
     return {FileType_none,MakeError(FileError_OpFault,error)};
    }

  return {(S_ISDIR(result.st_mode))?FileType_dir:FileType_file,FileError_Ok};
 }
  
FileError FileSystem::createFile(StrLen file_name_) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(file_name_) ) return FileError_TooLongPath;
  
  int flags=O_RDWR|O_CREAT|O_EXCL;
  int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
  
  int handle=open(file_name,flags,mode);
  
  if( handle==-1 ) return MakeError(FileError_OpenFault);
  
  close(handle);

  return FileError_Ok;
 }
  
FileError FileSystem::deleteFile(StrLen file_name_) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(file_name_) ) return FileError_TooLongPath;
  
  if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::createDir(StrLen dir_name) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(dir_name) ) return FileError_TooLongPath;
  
  int mode=S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP;
  
  if( mkdir(file_name,mode)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::deleteDir(StrLen dir_name,bool recursive) noexcept
 {
  FileName path;
  
  if( !path.set(dir_name) ) return FileError_TooLongPath;
  
  if( recursive ) return DeleteDirRecursive(StrLen(path,dir_name.len));

  if( rmdir(path)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::rename(StrLen old_path_,StrLen new_path_,bool allow_overwrite) noexcept
 {
  FileName old_path;
  
  if( !old_path.set(old_path_) ) return FileError_TooLongPath;
 
  FileName new_path;
  
  if( !new_path.set(new_path_) ) return FileError_TooLongPath;
  
  if( allow_overwrite )
    {
     struct stat result;
    
     if( stat(new_path,&result)==-1 ) 
       {
        int error=errno;
       
        if( error!=ENOENT && error!=ENOTDIR ) return MakeError(FileError_OpFault);
       }
     else
       {
        if( S_ISDIR(result.st_mode) ) return FileError_FileExist;
       }
   
     if( ::rename(old_path,new_path)==-1 ) return MakeError(FileError_OpFault);
    }
  else
    {
     struct stat result;
     
     if( stat(new_path,&result)==-1 ) 
       {
        int error=errno;
        
        if( error!=ENOENT && error!=ENOTDIR ) return MakeError(FileError_OpFault);
       }
     else
       {
        return FileError_FileExist;
       }
    
     if( ::rename(old_path,new_path)==-1 ) return MakeError(FileError_OpFault);
    }

  return FileError_Ok;
 }
  
FileError FileSystem::remove(StrLen path) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(path) ) return FileError_TooLongPath;

  struct stat result;
  
  if( stat(file_name,&result)==-1 ) 
    {
     int error=errno;
     
     if( error==ENOENT || error==ENOTDIR ) return FileError_NoPath;
    
     return MakeError(FileError_OpFault,error);
    }

  if( S_ISDIR(result.st_mode) )
    {
     if( rmdir(file_name)==-1 ) return MakeError(FileError_OpFault);
     
     return FileError_Ok;
    }
  else
    {
     if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);
     
     return FileError_Ok;
    }
 }
 
FileError FileSystem::exec(StrLen dir,StrLen program,StrLen arg) noexcept
 {
  try
    {
     SilentReportException report;
     
     StrPool pool;
     StrList argc(pool);
     StrList envp(pool);
     
     const char *path=pool.add(program);
     
     argc.prepareArg(program,arg);
     
     char temp[MaxPathLen+1];
     
     auto result=pathOf(dir,temp);
     
     if( result.error ) return result.error;
     
     envp.prepareEnv(result.path);
     
     if( posix_spawn(0,path,0,0,argc.complete(),envp.complete())!=0 ) return FileError_OpFault;
     
     return FileError_Ok;
    }
  catch(CatchType)
    {
     return FileError_SysOverload;
    }
 }
 
auto FileSystem::pathOf(StrLen path_,char buf[MaxPathLen+1]) noexcept -> PathOfResult
 {
  FileName path;
  
  if( !path.set(path_) ) return PathOfResult{StrLen(),FileError_TooLongPath};
  
  char temp[PATH_MAX+1];
  
  if( char *result=realpath(path,temp) )
    {
     StrLen src(result);
     
     if( src.len>MaxPathLen )
       {
        return PathOfResult{StrLen(),FileError_TooLongPath};
       }
     else
       {
        src.copyTo(buf);
        
        return PathOfResult{StrLen(buf,src.len),FileError_Ok};
       }
    }
  else
    {
     return PathOfResult{StrLen(),MakeError(FileError_OpFault)};
    }
 }

} // namespace Sys
} // namespace CCore
 

