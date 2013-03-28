/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Shift 1.00
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

void Main(StrLen input_file_name,StrLen output_file_name)
 {
  DataMap data(input_file_name);
  
  StateCompressor compr(data.getFinals(),data.getStates());
   
  compr.run();
   
  compr.check();
   
  auto result=compr.getResult(data.getRules());
  
  PrintFile out(output_file_name);
  
  Putobj(out,"/* ShiftState.ddl */\n\n");
  
  Putobj(out,"include <State.ddl>\n\n");
  
  ulen Lim=result.state_groups.getLen();
  
  Printf(out,"StateIndex ShiftStateIndexLim = #; ;\n\n",Lim);
  
  Printf(out,"ShiftState[#;] ShiftStateTable=\n",Lim);
  Putobj(out," {\n");
  
  for(ulen i=0; i<Lim ;i++)
    {
     auto &sg=result.state_groups[i];
     
     Printf(out,"  { #; ,\n",sg.group);
     
     Putobj(out,"   {\n");
     
     for(ulen i=0,len=sg.transitions.getLen(); i<len ;i++)
       {
        auto &t=sg.transitions[i];
        
        Printf(out,"    { ElementTable+#; , ShiftStateTable+#; }",t.element->element,t.group);
       
        if( i+1<len )
          Putch(out,',','\n');
        else
          Putch(out,'\n');
       }
     
     Putobj(out,"   },\n");
     
     Putobj(out,"   {\n");
     
     for(ulen i=0,len=sg.states.getLen(); i<len ;i++)
       {
        Printf(out,"    StateTable+#;",sg.states[i]->state);
        
        if( i+1<len )
          Putch(out,',','\n');
        else
          Putch(out,'\n');
       }
     
     Putobj(out,"   },\n");
     
     Putobj(out,"   {\n");
     
     for(ulen i=0,len=sg.finals.getLen(); i<len ;i++)
       {
        Printf(out,"    FinalTable+#;",sg.finals[i]->final);
        
        if( i+1<len )
          Putch(out,',','\n');
        else
          Putch(out,'\n');
       }
     
     Putobj(out,"   },\n");
     
     Putobj(out,"   {\n");
     
     for(ulen i=0,len=sg.shift.aset.atoms.getLen(); i<len ;i++)
       {
        Printf(out,"    ElementTable+#;",sg.shift.aset.atoms[i].atom->element);
        
        if( i+1<len )
          Putch(out,',','\n');
        else
          Putch(out,'\n');
       }
     
     Putobj(out,"   }\n");
     
     if( i+1<Lim )
       Putobj(out,"  },\n");
     else
       Putobj(out,"  }\n");
    }
  
  Putobj(out," };\n\n");
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;
     
     Main("State.ddl","ShiftState.ddl");
     
     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }
  
  return 0;
 }



