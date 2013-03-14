/* Data.h */
//----------------------------------------------------------------------------------------
//
//  Project: DDLTypeSet 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef DDLTypeSet_Data_h
#define DDLTypeSet_Data_h

#include <CCore/inc/Print.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/ddl/DDLEngine.h>

namespace App {

/* using */ 

using namespace CCore;

/* class Data */

class Data : NoCopy
 {
   PrintCon out;
   DDL::FileEngine<DDL::FileName,FileToMem> engine;
   DDL::EngineResult result;
   
  public: 
  
   explicit Data(StrLen file_name);
   
   ~Data() {}
   
   DDL::BodyNode * operator -> () const { return result.body; }
 };

} // namespace App

#endif

