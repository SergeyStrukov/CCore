/* PrintFile.cpp */ 
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
 
#include <CCore/inc/print/PrintFile.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class SafeBuf */ 
 
SafeBuf::SafeBuf(ulen len_)
 {
  if( len_>SafeLen )
    {
     if( void *mem=TryMemAlloc(len_) )
       {
        ptr=static_cast<char *>(mem);
        len=len_;
        
        return;
       }
    }
    
  ptr=safebuf;
  len=SafeLen;
 }
   
SafeBuf::~SafeBuf()
 {
  if( ptr!=safebuf )
    {
     MemFree(ptr);
    }
 }
 
/* class RawFileToPrint */

FileError RawFileToPrint::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( opened ) return FileError_NoMethod;
  
  if( FileError fe=file.open(file_name,oflags) ) return fe;
  
  opened=true;
  preserve_file=false;
  
  return FileError_Ok;
 }

void RawFileToPrint::close(FileMultiError &errout)
 {
  if( opened )
    {
     opened=false;
  
     file.close(errout,preserve_file);
    } 
  else
    {
     errout.add(FileError_NoMethod);
    }
 }

FileError RawFileToPrint::write(const uint8 *buf,ulen len)
 {
  if( !opened ) return FileError_NoMethod;
  
  auto result=file.write(buf,len);
  
  if( result.error ) return result.error;
  
  if( result.len!=len ) return FileError_WriteLenMismatch;
  
  return FileError_Ok;
 }

/* class PrintFile */ 

PtrLen<char> PrintFile::do_provide(ulen)
 {
  if( !isOpened() ) 
    {
     Printf(Exception,"CCore::PrintFile::do_provide(...) : file is not opened");
    }
 
  return Range(buf);
 }
   
void PrintFile::do_flush(char *ptr,ulen len)
 {
  if( FileError error=file.write(MutatePtr<const uint8>(ptr),len) )
    {
     if( no_flush_exception )
       {
        flush_error=error;
       }
     else
       {  
        Printf(Exception,"CCore::PrintFile::do_flush(...) : #;",error);
       }
    }
 }
   
PrintFile::PrintFile()
 : buf(BufLen),
   no_flush_exception(false)
 {
 }
   
PrintFile::PrintFile(StrLen file_name,FileOpenFlags oflags)
 : buf(BufLen),
   no_flush_exception(false)
 {
  open(file_name,oflags);
 }
   
PrintFile::~PrintFile()
 {
  if( isOpened() )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"CCore::PrintFile::~PrintFile() : #;",errout);
       }
    }
 }
 
void PrintFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( FileError error=file.open(file_name,oflags) )
    {
     Printf(Exception,"CCore::PrintFile::open(#.q;,#;) : #;",file_name,oflags,error);
    }
    
  no_flush_exception=false;  
 }
   
void PrintFile::soft_close(FileMultiError &errout)
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
   
void PrintFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"CCore::PrintFile::close() : #;",errout);
    }
 }
 
} // namespace CCore
 

