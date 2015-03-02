/* AsyncBinaryFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_AsyncBinaryFile_h
#define CCore_inc_AsyncBinaryFile_h

#include <CCore/inc/SaveLoad.h>

#include <CCore/inc/AsyncFile.h>
 
namespace CCore {

/* classes */

class AsyncBinaryFile;

/* class AsyncBinaryFile */

class AsyncBinaryFile : NoCopy , public PutDevBase<AsyncBinaryFile>
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
  
   AsyncBinaryFile();
   
   explicit AsyncBinaryFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~AsyncBinaryFile();
   
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

} // namespace CCore
 
#endif
 

