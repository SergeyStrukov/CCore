/* Data.cpp */
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

#include "Data.h"

#include <CCore/inc/Exception.h>

namespace App {

/* class Data */

Data::Data(StrLen file_name)
 : out(Con),
   engine(out)
 {
  result=engine.process(file_name);
  
  out.flush();
  
  if( !result ) Printf(Exception,"Input file processing error");
 }

} // namespace App

