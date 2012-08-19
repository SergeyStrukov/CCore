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
  public: 
   
   // constructors
  
   StreamFile();
   
   explicit StreamFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~StreamFile();
   
   // methods
   
   bool isOpened() const;
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void disableExceptions(); 
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile();
   
   // put
   
   void do_put(uint8 value);
   
   void do_put(const uint8 *ptr,ulen len);
   
   PtrLen<uint8> do_putRange(ulen len);
   
   void flush();
 };

} // namespace App

#endif

