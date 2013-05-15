/* PrintFile.h */ 
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

#ifndef CCore_inc_print_PrintFile_h
#define CCore_inc_print_PrintFile_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/SafeBuf.h>

#include <CCore/inc/sys/SysFile.h>
 
namespace CCore {

/* classes */ 

class RawFileToPrint;

class PrintFile;

/* class RawFileToPrint */  
 
class RawFileToPrint : NoCopy
 {
   Sys::File file;
   bool opened;
   bool preserve_file;
   
  public:
   
   // constructors
  
   RawFileToPrint() : opened(false) {}
   
    // No destructor ! 
   
   // methods
   
   bool isOpened() const { return opened; }
   
   FileError open(StrLen file_name,FileOpenFlags oflags);
   
   void close(FileMultiError &errout);
   
   void preserveFile() { preserve_file=true; }
   
   FileError write(const uint8 *buf,ulen len);
 }; 
 
/* class PrintFile */ 

class PrintFile : public PrintBase
 {
   static const ulen BufLen = 64_KByte ;
   
   RawFileToPrint file;
   SafeBuf buf;
   FileError flush_error;
   bool no_flush_exception;
   
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public:
   
   // constructors
  
   PrintFile();
   
   explicit PrintFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~PrintFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void disableExceptions() 
    { 
     if( !no_flush_exception )
       {
        no_flush_exception=true; 
        
        flush_error=FileError_Ok;
       }
    }
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { file.preserveFile(); }
 };
 
} // namespace CCore
 
#endif
 

