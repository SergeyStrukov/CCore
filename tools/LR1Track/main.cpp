/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Track 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>

#include "Tools.h"

namespace App {

/* Main() */

void Main(StrLen input_file_name)
 {
  DataMap data(input_file_name);
  TrackBuilder builder(&data);
  
  PrintFile out("Track.txt");
  
  Putobj(out,builder);
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  ReportException report;
  
  try
    {
     {
      Putobj(Con,"--- LR1Track 1.00 ---\n--- Copyright (c) 2013 Sergey Strukov. All rights reserved. ---\n\n");
      
      Main("ShiftState.ddl");
     } 
     
     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }
  
  return 0;
 }



