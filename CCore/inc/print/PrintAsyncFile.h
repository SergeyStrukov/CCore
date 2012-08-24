/* PrintAsyncFile.h */ 
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

#ifndef CCore_inc_print_PrintAsyncFile_h
#define CCore_inc_print_PrintAsyncFile_h
 
#include <CCore/inc/Printf.h>

#include <CCore/inc/AsyncFile.h>

namespace CCore {

/* classes */ 

class PrintAsyncFile;

/* class PrintAsyncFile */ 

class PrintAsyncFile : public PrintBase
 {
   AsyncFile file;
 
   Packet<uint8> packet;
   FilePosType file_pos;
   
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public:
   
   // constructors
  
   explicit PrintAsyncFile(MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   explicit PrintAsyncFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   ~PrintAsyncFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void exec2(StrLen dir,StrLen program,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   void exec2(AsyncFileSystem &fs,StrLen dev_dir,StrLen dev_program);
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { file.preserveFile(); }
   
   void setLargeWriteLen(ulen large_write_len) { file.setLargeWriteLen(large_write_len); }
   
   void wait() { file.wait(); }
   
   void wait_final() { file.wait_final(); }
   
   void wait(MSec timeout) { file.wait(timeout); }
   
   void cancel_and_wait() { file.cancel_and_wait(); }
 };
 
} // namespace CCore
 
#endif
 

