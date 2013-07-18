/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
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
#include <CCore/inc/Array.h>

#include "DataMap.h"

namespace App {

/* Main() */

void Main(StrLen input_file_name,StrLen output_file_name)
 {
  DataMap data(input_file_name);
  PrintFile out(output_file_name);
  
  ulen atomCount=data.getAtoms().len;
  ulen syntCount=data.getNonAtoms().len;
  ulen ruleCount=data.getRules().len;
  ulen stateCount=data.getStates().len;
  
  Printf(Con,"atomCount = #;\nsyntCount = #;\nruleCount = #;\nstateCount = #;\n",atomCount,syntCount,ruleCount,stateCount);
  
  DynArray<ulen> actions(atomCount);
  DynArray<ulen> atom_transitions(atomCount);
  DynArray<ulen> synt_transitions(syntCount);
  
  for(const auto &state : data.getStates() )
    {
     // erase
    
     Range(actions).set(ruleCount);
     Range(atom_transitions).set(stateCount);
     Range(synt_transitions).set(stateCount);
     
     // fill
     
     for(auto action : state.final->actions )
       {
        ulen atom=action.atom->element;
        ulen rule=action.rule->rule;
        
        actions[atom]=rule;
       }
     
     for(auto trans : state.transitions )
       {
        ulen element=trans.element->element;
        ulen ind=trans.state->state;
        
        if( element<atomCount )
          atom_transitions[element]=ind;
        else
          synt_transitions[element-atomCount]=ind;
       }
     
     // print
     
     Printf(out,"  {\n");
     
     Printf(out,"   {\n");
     
     for(ulen rule : Range(actions) ) Printf(out,"    Rule(#;),\n",rule);
     
     Printf(out,"   },\n");
     
     Printf(out,"   {\n");
     
     for(ulen ind : Range(atom_transitions) ) 
       {
        if( ind<stateCount )
          Printf(out,"    StateTable+#;,\n",ind);
        else
          Printf(out,"    0,\n");
       }
     
     Printf(out,"   },\n");
     
     Printf(out,"   {\n");
     
     for(ulen ind : Range(synt_transitions) ) 
       {
        if( ind<stateCount )
          Printf(out,"    StateTable+#;,\n",ind);
        else
          Printf(out,"    0,\n");
       }
     
     Printf(out,"   },\n");
     
     Printf(out,"  },\n");
    }
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  ReportException report;
  
  try
    {
     Main("../State.ddl","../StateTable.gen.cpp");
     
     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }
  
  return 0;
 }



