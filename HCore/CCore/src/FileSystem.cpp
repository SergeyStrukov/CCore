/* FileSystem.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/FileSystem.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class FileSystem */ 

FileSystem::FileSystem()
 {
  if( auto fe=fs.init() )
    {
     Printf(Exception,"CCore::FileSystem::FileSystem() : #;",fe);
    }
 }
   
FileSystem::~FileSystem()
 {
  if( auto fe=fs.exit() )
    {
     Printf(NoException,"CCore::FileSystem::~FileSystem() : #;",fe);
    }
 }
   
FileType FileSystem::getFileType(StrLen path)
 {
  auto result=fs.getFileType(path);
  
  if( result.error )
    {
     Printf(Exception,"CCore::FileSystem::getFileType(#.q;) : #;",path,result.error);
    }
    
  return result.type;  
 }
  
void FileSystem::createFile(StrLen file_name)
 {
  if( FileError fe=fs.createFile(file_name) )
    {
     Printf(Exception,"CCore::FileSystem::createFile(#.q;) : #;",file_name,fe);
    }
 }
  
void FileSystem::deleteFile(StrLen file_name)
 {
  if( FileError fe=fs.deleteFile(file_name) )
    {
     Printf(Exception,"CCore::FileSystem::deleteFile(#.q;) : #;",file_name,fe);
    }
 }
  
void FileSystem::createDir(StrLen dir_name)
 {
  if( FileError fe=fs.createDir(dir_name) )
    {
     Printf(Exception,"CCore::FileSystem::createDir(#.q;) : #;",dir_name,fe);
    }
 }
  
void FileSystem::deleteDir(StrLen dir_name,bool recursive)
 {
  if( FileError fe=fs.deleteDir(dir_name,recursive) )
    {
     Printf(Exception,"CCore::FileSystem::deleteDir(#.q;#;) : #;",dir_name,(recursive?",recursive":""),fe);
    }
 }
  
void FileSystem::rename(StrLen old_path,StrLen new_path,bool allow_overwrite)
 {
  if( FileError fe=fs.rename(old_path,new_path,allow_overwrite) )
    {
     Printf(Exception,"CCore::FileSystem::rename(#.q;,#.q;#;) : #;",old_path,new_path,(allow_overwrite?",overwrite":""),fe);
    }
 }
  
void FileSystem::remove(StrLen path)
 {
  if( FileError fe=fs.remove(path) )
    {
     Printf(Exception,"CCore::FileSystem::remove(#.q;) : #;",path,fe);
    }
 }
  
void FileSystem::exec(StrLen dir,StrLen program,StrLen arg)
 {
  if( FileError fe=fs.exec(dir,program,arg) )
    {
     Printf(Exception,"CCore::FileSystem::exec(#.q;,#.q;,#.q;) : #;",dir,program,arg,fe);
    }
 }

StrLen FileSystem::pathOf(StrLen path,char buf[MaxPathLen+1])
 {
  auto result=fs.pathOf(path,buf);
  
  if( result.error )
    {
     Printf(Exception,"CCore::FileSystem::pathOf(#.q;,...) : #;",path,result.error);
    }
  
  return result.path;
 }
 
/* class FileSystem::DirCursor */ 

FileSystem::DirCursor::DirCursor(FileSystem &fs,StrLen dir_name)
 : ok(false)
 {
  cur.init(&fs.fs,dir_name);
  
  if( cur.error )
    {
     Printf(Exception,"Core::FileSystem::DirCursor::DirCursor(,#.q;) : #;",dir_name,cur.error);
    }
 }
   
FileSystem::DirCursor::~DirCursor()
 {
  cur.exit();
 }
   
bool FileSystem::DirCursor::next()
 {
  if( cur.next() ) return ok=true;
  
  ok=false;
  
  if( cur.error )
    {
     Printf(Exception,"Core::FileSystem::DirCursor::next() : #;",cur.error);
    }
    
  return false;
 }
   
StrLen FileSystem::DirCursor::getFileName() const
 {
  if( ok ) return StrLen(cur.file_name,cur.len);
  
  return StrLen();
 }
   
FileType FileSystem::DirCursor::getFileType() const
 {
  if( ok ) return cur.type;
  
  return FileType_none;
 }
   
} // namespace CCore
 

