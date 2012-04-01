/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/String.h>

#include "DataMap.h"

namespace App {

/* functions */

template <class UInt>
ulen GetWidth(UInt maxval)
 {
  ulen ret=1;
  
  for(; maxval>=10 ;maxval/=10,ret++);
  
  return ret;
 }

/* classes */

class Engine;

/* class Engine */

class Engine : NoCopy
 {
   DataMap data;
   NTIndex tlim;
   
  private:
   
   struct ElementName
    {
     StrLen name;
     bool isNT;
     
     ElementName() : isNT(false) {}
     
     explicit ElementName(StrLen name_) : name(name_),isNT(true) {}
     
     template <class P>
     void print(P &out) const
      {
       if( isNT )
         Printf(out,"Element_#;",name);
       else
         Printf(out,"ElementAtom");
      }
    };
   
   ElementName getElementName(NTIndex ntt)
    {
     if( ntt<tlim )
       {
        return ElementName();
       }
     else
       {
        return ElementName(data.getNonTerminal(ntt-tlim).name);
       }
    }
   
  public: 
   
   explicit Engine(StrLen file_name) 
    : data(file_name) 
    {
     tlim=data.getTNames().len;
    }
   
   ~Engine() {}
   
   void test(StrLen file_name);
   
   void atom_h(StrLen file_name);
   
   void atom_cpp(StrLen file_name);
   
   void elements1(StrLen file_name);
   
   void elements2(StrLen file_name);
   
   void elements3(StrLen file_name);
   
   void actions(StrLen file_name);
   
   void do_h(StrLen file_name);
   
   void do_cpp(StrLen file_name);
   
   void elem_h(StrLen file_name);
   
   void elem_cpp(StrLen file_name);
   
   void do_rule(StrLen file_name);
   
   void rule_table(StrLen file_name);
   
   void atom_state_table(StrLen file_name);
   
   void next_state(StrLen file_name);
 };

void Engine::test(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* TNames */ \n\n");
  
  for(auto name : data.getTNames() ) Printf(out,"#;\n",name);
  
  Putobj(out,"\n/* Rules */ \n\n");
  
  for(ulen i=0,n=data.getRuleCount(); i<n ;i++) Printf(out,"#;\n",data.getRule(i));
  
  Putobj(out,"\n/* NonTerminals */ \n\n");
  
  for(ulen i=0,n=data.getNonTerminalCount(); i<n ;i++) data.getNonTerminal(i).print(out,data);
  
  Putobj(out,"\n/* States */ \n\n");
  
  for(ulen i=0,n=data.getStateCount(); i<n ;i++) data.getState(i).print(out,data);
 }

void Engine::atom_h(StrLen file_name)
 {
  PrintFile out(file_name);
  
  auto names=data.getTNames();
  
  Printf(out,"/* enum AtomClass */ \n\nenum AtomClass\n {\n  Atom_Nothing,\n\n");
  
  for(ulen i=1,n=names.len; i<n ;i++)
    {
     if( i+1<n )
       Printf(out,"  Atom_<nake>, /*  #;  */\n",StrLen(names[i].inner(3,2)));
     else
       Printf(out,"  Atom_<nake>  /*  #;  */\n",StrLen(names[i].inner(3,2)));
    }
  
  Printf(out," };\n\nconst char * GetTextDesc(AtomClass ac);\n\n");
 }

void Engine::atom_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  auto names=data.getTNames();
  
  Printf(out,"/* enum AtomClass */ \n\nconst char * GetTextDesc(AtomClass ac)\n {\n");
  
  Printf(out,"  static const char *const Table[]=\n   {\n");
  
  Printf(out,"    \"no-atom\",\n\n");
  
  for(ulen i=1,n=names.len; i<n ;i++)
    {
     if( i+1<n )
       Printf(out,"    #;,\n",StrLen(names[i].inner(2,1)));
     else
       Printf(out,"    #;\n",StrLen(names[i].inner(2,1)));
    }
  
  Printf(out,"   };\n\n");
  
  Printf(out,"  return Table[ac];\n }\n\n");
 }

void Engine::elements1(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* elements */ \n\n");
  
  for(ulen i=0,n=data.getNonTerminalCount(); i<n ;i++) 
    {
     Printf(out,"struct Element_#;;\n",data.getNonTerminal(i).name);
    }
 }

void Engine::elements2(StrLen file_name)
 {
  PrintFile out(file_name);
  
  for(ulen i=0,n=data.getNonTerminalCount(); i<n ;i++) 
    {
     auto nt=data.getNonTerminal(i);
     
     Printf(out,"/* struct Element_#; */ \n\n",nt.name);
     
     Printf(out,"struct Element_#; : ElementBase\n {\n",nt.name);
     
     Printf(out,"  static ulen NextState(ulen state);\n");
     
     for(DataPtr ptr: nt.rules )
       {
        auto rule=data.getRule(ptr);

        if( !rule.str )
          {
           Printf(out,"\n  void #;(ElementContext ctx);\n",rule.name);
          }
        else
          {
           Printf(out,"\n  void #;(ElementContext ctx",rule.name);
           
           for(auto ntt : rule.str ) Printf(out,",#; *",getElementName(ntt));
           
           Printf(out,");\n");
          }
       }
     
     Printf(out," };\n\n");
    }
 }

void Engine::elements3(StrLen file_name)
 {
  PrintFile out(file_name);
  
  for(ulen i=0,n=data.getNonTerminalCount(); i<n ;i++) 
    {
     auto nt=data.getNonTerminal(i);
     
     Printf(out,"/* struct Element_#; */ \n\n",nt.name);
     
     for(DataPtr ptr: nt.rules )
       {
        auto rule=data.getRule(ptr);

        if( !rule.str )
          {
           Printf(out,"void Element_#;::#;(ElementContext)\n",nt.name,rule.name);
          }
        else
          {
           Printf(out,"void Element_#;::#;(ElementContext",nt.name,rule.name);
           
           for(auto ntt : rule.str ) Printf(out,",#; *",getElementName(ntt));
           
           Printf(out,")\n");
          }
        
        Printf(out," {\n  // TODO\n }\n\n");
       }
    }
 }
  
void Engine::actions(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* Action::Rule */ \n\n");

  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     if( i+1<n )
       Printf(out,"    Do_#;,\n",data.getRule(i).name);
     else
       Printf(out,"    Do_#;\n",data.getRule(i).name);
    }
 }

void Engine::do_h(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* do_...() */ \n\n");

  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     Printf(out,"   void do_#;();\n",data.getRule(i).name);
    }
 }

void Engine::do_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* do_...() */ \n\n");

  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     auto rule=data.getRule(i);
     
     Printf(out,"void Parser::do_#;()\n {\n",rule.name);
     
     for(ulen j=0,m=rule.str.len; j<m ;j++)
       {
        ulen k=m-1-j;
        
        Printf(out,"  #; *arg#;=pop();\n",getElementName(rule.str[k]),k+1);
       }
     
     auto result_name=data.getNonTerminal(rule.result).name;
     
     if( rule.str.len ) Putch(out,'\n');
     
     Printf(out,"  Element_#; *elem=elem_#;(",result_name,rule.name);
     
     for(ulen j=0,m=rule.str.len; j<m ;j++) 
       {
        if( j )
          Printf(out,",arg#;",j+1);
        else
          Printf(out,"arg#;",j+1);
       }
     
     Printf(out,");\n\n");
     
     Printf(out,"  ulen new_state=Element_#;::NextState(stack->state);\n\n",result_name);
     
     Printf(out,"  push(elem,new_state);\n");
     
     Printf(out," }\n\n");
    }
 }

void Engine::elem_h(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* elem_...() */ \n\n");
  
  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     auto rule=data.getRule(i);
     
     auto result_name=data.getNonTerminal(rule.result).name;

     Printf(out,"   Element_#; * elem_#;(",result_name,rule.name);
     
     for(ulen j=0,m=rule.str.len; j<m ;j++) 
       {
        if( j )
          Printf(out,",#; *",getElementName(rule.str[j]));
        else
          Printf(out,"#; *",getElementName(rule.str[j]));
       }
     
     Printf(out,");\n");
    }   
 }

void Engine::elem_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* elem_...() */ \n\n");
  
  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     auto rule=data.getRule(i);
     
     auto result_name=data.getNonTerminal(rule.result).name;

     Printf(out,"Element_#; * Parser::elem_#;(",result_name,rule.name);
  
     for(ulen j=0,m=rule.str.len; j<m ;j++) 
       {
        if( j )
          Printf(out,",#; *arg#;",getElementName(rule.str[j]),j+1);
        else
          Printf(out,"#; *arg#;",getElementName(rule.str[j]),j+1);
       }
     
     Printf(out,")\n {\n");
     
     Printf(out,"  Element_#; *elem=ctx.create<Element_#;>();\n\n",result_name,result_name);
     
     Printf(out,"  elem->#;(ctx",rule.name);
     
     for(ulen j=0,m=rule.str.len; j<m ;j++) Printf(out,",arg#;",j+1);
      
     Printf(out,");\n\n");
     
     Printf(out,"  return elem;\n");
     
     Printf(out," }\n\n");
    }   
 }

void Engine::do_rule(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* doRule */ \n\n");
  
  for(ulen i=1,n=data.getRuleCount(); i<n ;i++)
    {
     auto name=data.getRule(i).name;
     
     Printf(out,"     case Action::Do_#; : do_#;(); break;\n",name,name);
    }  
 }

void Engine::rule_table(StrLen file_name)
 {
  PrintFile out(file_name);
  
  ulen n=data.getStateCount();
  ulen m=tlim;
  
  DynArray<RIndex> buf(m);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(data.getRuleCount());
  
  Printf(out,"/* RuleTable */ \n\n");
  
  Printf(out,"static const RuleTableType RuleTable[#;][#;]=\n",n,tlim);
  
  Printf(out," {\n");
  
  for(ulen i=0; i<n ;i++)
    {
     Printf(out,"  {");
     
     {
      auto finals=data.getState(i).finals;
      
      Range(buf).set_null();

      for(ulen j=0; j<finals.len ;j++)
        {
         auto final=data.getFinal(finals.ptr,j);
         
         buf[final.t]=data.getRule(final.rule).rule+1;
        }
     }
     
     for(ulen j=0; j<m ;j++)
       {
        Printf(out,"#;",BindOpt(opt,buf[j]));
        
        if( j+1<m ) Putch(out,',');
       } 
     
     if( i+1<n )
       Printf(out,"},\n");
     else
       Printf(out,"}\n");
    }
  
  Printf(out," };\n\n");
 }

void Engine::atom_state_table(StrLen file_name)
 {
  PrintFile out(file_name);
  
  ulen n=data.getStateCount();
  ulen m=tlim;
  
  DynArray<StateIndex> buf(m);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(data.getStateCount());
  
  Printf(out,"/* AtomStateTable */ \n\n");
  
  Printf(out,"static const StateTableType AtomStateTable[#;][#;]=\n",n,tlim);
  
  Printf(out," {\n");
  
  for(ulen i=0; i<n ;i++)
    {
     Printf(out,"  {");
     
     {
      auto transitions=data.getState(i).transitions;
      
      Range(buf).set_null();

      for(ulen j=0; j<transitions.len ;j++)
        {
         auto transition=data.getTransition(transitions.ptr,j);
         
         auto ntt=transition.ntt;
         
         if( ntt<tlim )
           {
            buf[ntt]=data.getState(transition.state).state;
           }
        }
     }
     
     for(ulen j=0; j<m ;j++)
       {
        Printf(out,"#;",BindOpt(opt,buf[j]));
        
        if( j+1<m ) Putch(out,',');
       } 
     
     if( i+1<n )
       Printf(out,"},\n");
     else
       Printf(out,"}\n");
    }
  
  Printf(out," };\n\n");
 }

void Engine::next_state(StrLen file_name)
 {
  PrintFile out(file_name);
  
  ulen n=data.getNonTerminalCount();
  ulen m=data.getStateCount();
  
  DynArray<DynArray<StateIndex> > buf(DoFill(m),n);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(data.getStateCount());
  
  for(ulen j=0; j<m ;j++)
    {
     auto transitions=data.getState(j).transitions;
     
     for(ulen k=0; k<transitions.len ;k++)
       {
        auto transition=data.getTransition(transitions.ptr,k);
        
        if( transition.ntt>=tlim )
          {
           buf[j][transition.ntt-tlim]=data.getState(transition.state).state;
          }
       }
    }
  
  Printf(out,"/* Element_...::NextState() */ \n\n");
  
  for(ulen i=0; i<n ;i++)
    {
     auto nt=data.getNonTerminal(i);
     
     Printf(out,"/* Element_#;::NextState() */ \n\n",nt.name);
     
     Printf(out,"ulen Element_#;::NextState(ulen state)\n {\n  static const StateTableType Table[]=\n   {",nt.name);
     
     for(ulen j=0; j<m ;j++)
       {
        if( j%10==0 ) Printf(out,"\n    ");
        
        Printf(out,"#;",BindOpt(opt,buf[j][i]));
        
        if( j+1<m ) Putch(out,',');
       }
     
     Printf(out,"\n   };\n\n  return Table[state];\n }\n\n");
    }
 }

} // namespace App

/* using */

using namespace App;

/* main() */ 

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;
    
     {
      Putobj(Con,"--- ParserGen 1.00 ---\n--- Copyright (c) 2012 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=3 ) 
        {
         Putobj(Con,"Usage: ParserGen <input-file-name> <output-file-name>\n");
         
         return 1;
        }
      
      Engine engine(argv[1]);
      StrLen base_name=argv[2];
      
      // test
      
      String test_name=Stringf("#;.test.gen.txt",base_name);
      
      engine.test(Range(test_name));
      
      // atom_h
      
      String test_atom_h=Stringf("#;.atom.gen.h",base_name);
      
      engine.atom_h(Range(test_atom_h));
      
      // atom_cpp
      
      String test_atom_cpp=Stringf("#;.atom.gen-cpp",base_name);
      
      engine.atom_cpp(Range(test_atom_cpp));
      
      // elements1

      String elements1_name=Stringf("#;.elements1.gen.h",base_name);
      
      engine.elements1(Range(elements1_name));
      
      // elements2
      
      String elements2_name=Stringf("#;.elements2.gen.h",base_name);
      
      engine.elements2(Range(elements2_name));
      
      // elements3
      
      String elements3_name=Stringf("#;.elements3.gen-cpp",base_name);
      
      engine.elements3(Range(elements3_name));
      
      // actions
      
      String actions_name=Stringf("#;.actions.gen.h",base_name);
      
      engine.actions(Range(actions_name));
      
      // do_h
      
      String do_h_name=Stringf("#;.do.gen.h",base_name);
      
      engine.do_h(Range(do_h_name));
      
      // do_cpp
      
      String do_cpp_name=Stringf("#;.do.gen-cpp",base_name);
      
      engine.do_cpp(Range(do_cpp_name));
      
      // elem_h
      
      String elem_h_name=Stringf("#;.elem.gen.h",base_name);
      
      engine.elem_h(Range(elem_h_name));
      
      // elem_cpp
      
      String elem_cpp_name=Stringf("#;.elem.gen-cpp",base_name);
      
      engine.elem_cpp(Range(elem_cpp_name));
      
      // elem_cpp
      
      String do_rule_name=Stringf("#;.do_rule.gen-cpp",base_name);
      
      engine.do_rule(Range(do_rule_name));
      
      // rule_table
      
      String rule_table_name=Stringf("#;.rule_table.gen-cpp",base_name);
      
      engine.rule_table(Range(rule_table_name));
      
      // atom_state_table
      
      String atom_state_table_name=Stringf("#;.atom_state_table.gen-cpp",base_name);
      
      engine.atom_state_table(Range(atom_state_table_name));
      
      // next_state
      
      String next_state_name=Stringf("#;.next_state.gen-cpp",base_name);
      
      engine.next_state(Range(next_state_name));
     } 
     
     report.guard();
    }
  catch(CatchType)   
    {
     return 1;
    }
  
  return 0;
 }
 
