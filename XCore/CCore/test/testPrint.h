/* testPrint.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_testPrint_h
#define CCore_test_testPrint_h

#include <CCore/inc/Print.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

class PrintFile;

class StreamFile;

/* class PrintFile */

class PrintFile : public PrintAsyncFile
 {
  public:
   
   PrintFile();
   
   explicit PrintFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~PrintFile();
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
 };

/* class StreamFile */

class StreamFile : NoCopy , public PutDevBase<StreamFile>
 {
   AsyncFile file;

   Packet<uint8> packet;
   FilePosType file_pos;
   
   PtrLen<uint8> out;
   ulen buf_len;
 
  private:
 
   void provide();
   
  public: 
   
   // constructors
  
   StreamFile();
   
   explicit StreamFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~StreamFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { file.preserveFile(); }
   
   void setLargeWriteLen(ulen large_write_len) { file.setLargeWriteLen(large_write_len); }
   
   void wait() { file.wait(); }
   
   void wait_final() { file.wait_final(); }
   
   void wait(MSec timeout) { file.wait(timeout); }
   
   void cancel_and_wait() { file.cancel_and_wait(); }
   
   // put
   
   void do_put(uint8 value)
    {
     if( !out ) provide();
   
     *out=value;
   
     ++out;
    }
   
   void do_put(const uint8 *ptr,ulen len);
   
   PtrLen<uint8> do_putRange(ulen len);
   
   void flush();
 };

} // namespace App

#endif

