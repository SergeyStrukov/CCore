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

/* class PrintFile */

class PrintFile : public PrintAsyncFile
 {
  public:
   
   PrintFile();
   
   explicit PrintFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~PrintFile();
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
 };

} // namespace App

#endif

