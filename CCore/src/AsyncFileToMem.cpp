/* AsyncFileToMem.cpp */ 
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
 
#include <CCore/inc/AsyncFileToMem.h>
 
#include <CCore/inc/Exception.h>
#include <CCore/inc/Path.h>

namespace CCore {

/* class AsyncFileToMem */ 

AsyncFileToMem::AsyncFileToMem(StrLen file_name,ulen max_len,MSec timeout,ulen max_packets)
 {
  AsyncFile file(timeout,max_packets);
  
  auto file_len=file.open(file_name,Open_Read);

  if( file_len>max_len )
    {
     Printf(Exception,"CCore::AsyncFileToMem::AsyncFileToMem(#.q;,max_len=#;) : file is too long #;",file_name,max_len,file_len);
    }

  ulen len=(ulen)file_len;

  file.read_all(0,alloc(len),len);
 }
 
AsyncFileToMem::~AsyncFileToMem()
 {
 }
 
/* class AsyncFileListToMem */  

void AsyncFileListToMem::build(AsyncFileSystem &fs,StrLen dev_path,ulen max_len,MSec timeout,ulen max_packets)
 {
  AsyncFile file(timeout,max_packets);
  
  auto file_len=fs.getFileList(dev_path,file);
  
  if( file_len>max_len )
    {
     Printf(Exception,"CCore::AsyncFileListToMem::build(,#.q;,max_len=#;,...) : file is too long #;",dev_path,max_len,file_len);
    }

  ulen len=(ulen)file_len;

  file.read_all(0,alloc(len),len);
  
  data=Range(*this);
  
  file_type=FileType_none;
 }
   
AsyncFileListToMem::AsyncFileListToMem(StrLen path,ulen max_len,MSec timeout,ulen max_packets)
 {
  SplitDevName split(path);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileListToMem::AsyncFileListToMem(#.q;,...) : bad name",path);
    }
 
  AsyncFileSystem fs(split.dev_name,timeout,max_packets);
 
  build(fs,split.dev_path,max_len,timeout,max_packets);
 }
 
AsyncFileListToMem::AsyncFileListToMem(AsyncFileSystem &fs,StrLen dev_path,ulen max_len,MSec timeout,ulen max_packets)
 {
  build(fs,dev_path,max_len,timeout,max_packets);
 }
   
AsyncFileListToMem::~AsyncFileListToMem()
 {
 }
 
bool AsyncFileListToMem::next()
 {
  if( !data ) return false;
  
  PtrLen<const uint8> rest=data;
  
  while( *rest!='\n' )
    {
     ++rest;
     
     if( !rest )
       {
        Printf(Exception,"CCore::AsyncFileListToMem::next() : no \\n");
       }
    }
  
  PtrLen<const uint8> prefix=data.prefix(rest);
  
  if( prefix.len<3 )
    {
     Printf(Exception,"CCore::AsyncFileListToMem::next() : short line");
    }
    
  if( prefix.back(2)!=' ' )  
    {
     Printf(Exception,"CCore::AsyncFileListToMem::next() : no space");
    }
    
  switch( prefix.back(1) )  
    {
     case 'f' :
      {
       file_type=FileType_file;
      }
     break;
    
     case 'd' :
      {
       file_type=FileType_dir;
      }
     break;
    
     default:
      {
       Printf(Exception,"CCore::AsyncFileListToMem::next() : bad type");
      }
    }
    
  file_name=prefix.inner(0,2);  
  
  ++rest;
  
  data=rest;
  
  return true;
 }
 
} // namespace CCore
 

