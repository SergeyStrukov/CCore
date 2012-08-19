/* testPrint.h */
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

#ifndef CCore_test_testPrint_h
#define CCore_test_testPrint_h

#include <CCore/inc/Print.h>
#include <CCore/inc/SaveLoad.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

class StreamFile;

/* class StreamFile */

class StreamFile : NoCopy , public PutDevBase<StreamFile>
 {
   static const ulen BufLen = 64_KByte ;
 
   RawFileToPrint file;
   DynArray<uint8> buf;
   FileError flush_error;
   bool no_flush_exception;
   
   PtrLen<uint8> out;
   bool has_data;   
   
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

