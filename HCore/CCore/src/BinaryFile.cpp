/* BinaryFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/BinaryFile.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class BinaryFile */

void BinaryFile::provide()
 {
  if( !isOpened() ) 
    {
     Printf(Exception,"BinaryFile::provide(...) : file is not opened");
    }
  
  flush();
  
  out=Range(buf);
  has_data=true;
 }

BinaryFile::BinaryFile()
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
 }

BinaryFile::BinaryFile(StrLen file_name,FileOpenFlags oflags)
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
  open(file_name,oflags);
 }

BinaryFile::~BinaryFile()
 {
  if( isOpened() )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"BinaryFile::~BinaryFile() : #;",errout);
       }
    }
 }

void BinaryFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( FileError error=file.open(file_name,oflags) )
    {
     Printf(Exception,"BinaryFile::open(#.q;,#;) : #;",file_name,oflags,error);
    }
    
  no_flush_exception=false;  
 }

void BinaryFile::soft_close(FileMultiError &errout)
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

void BinaryFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"BinaryFile::close() : #;",errout);
    }
 }

void BinaryFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len); 
  
  while( +src )
    {
     if( !out ) provide();
     
     ulen delta=Min(src.len,out.len);
     
     (out+=delta).copy( (src+=delta).ptr );
    }
 }

PtrLen<uint8> BinaryFile::do_putRange(ulen)
 {
  Printf(Exception,"BinaryFile::do_putRange(...) : not supported");
  
  return Nothing;
 }

void BinaryFile::flush()
 {
  if( !has_data ) return;
  
  ulen len=buf.getLen()-out.len;
  
  out=Nothing;
  has_data=false;
  
  if( !len ) return;
  
  if( FileError error=file.write(buf.getPtr(),len) )
    {
     if( no_flush_exception )
       {
        flush_error=error;
       }
     else
       {  
        Printf(Exception,"BinaryFile::flush(...) : #;",error);
       }
    }
 }

} // namespace CCore
 

