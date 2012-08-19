/* testPrint.cpp */
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

#include <CCore/test/testPrint.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class StreamFile */

StreamFile::StreamFile()
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
 }

StreamFile::StreamFile(StrLen file_name,FileOpenFlags oflags)
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
  open(file_name,oflags);
 }

StreamFile::~StreamFile()
 {
  if( isOpened() )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"StreamFile::~StreamFile() : #;",errout);
       }
    }
 }

void StreamFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( FileError error=file.open(file_name,oflags) )
    {
     Printf(Exception,"StreamFile::open(#.q;,#;) : #;",file_name,oflags,error);
    }
    
  no_flush_exception=false;  
 }

void StreamFile::soft_close(FileMultiError &errout)
 {
  if( isOpened() ) 
    {
     disableExceptions();
 
     flush();
  
     errout.add(flush_error);
  
     file.close(errout);
    }
  else 
    {
     errout.add(FileError_NoMethod);
    }
 }

void StreamFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"StreamFile::close() : #;",errout);
    }
 }

void StreamFile::provide()
 {
  if( !isOpened() ) 
    {
     Printf(Exception,"StreamFile::provide(...) : file is not opened");
    }
  
  flush();
  
  out=Range(buf);
  has_data=true;
 }

void StreamFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len); 
  
  while( +src )
    {
     if( !out ) provide();
     
     ulen delta=Min(src.len,out.len);
     
     (out+=delta).copy( (src+=delta).ptr );
    }
 }

PtrLen<uint8> StreamFile::do_putRange(ulen)
 {
  Printf(Exception,"StreamFile::do_putRange(...) : not supported");
  
  return Nothing;
 }

void StreamFile::flush()
 {
  if( !has_data ) return;
  
  ulen len=buf.getLen()-out.len;
  
  if( !len ) return;
  
  out=Nothing;
  has_data=false;
  
  if( FileError error=file.write(buf.getPtr(),len) )
    {
     if( no_flush_exception )
       {
        flush_error=error;
       }
     else
       {  
        Printf(Exception,"StreamFile::flush(...) : #;",error);
       }
    }
 }

} // namespace App

