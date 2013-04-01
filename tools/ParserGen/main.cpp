/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.01
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
   
  private:
   
   struct ElementName
    {
     StrLen name;
     bool is_atom;
     
     explicit ElementName(const TypeDef::Element &element) 
      : name(element.name),
        is_atom(element.element<TypeDef::Element::AtomLim) 
      {
      }
     
     explicit ElementName(const TypeDef::Element *element) : ElementName(*element) {} 
     
     template <class P>
     void print(P &out) const
      {
       if( is_atom )
         Printf(out,"ElementAtom");
       else
         Printf(out,"Element_#;",name);
      }
    };
   
  public: 
   
   explicit Engine(StrLen file_name) 
    : data(file_name) 
    {
     if( !data.getRules() )
       {
        Printf(Exception,"Rule table is empty");
       }
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
  
  Putobj(out,"/* Elements */ \n\n");
  
  for(auto element : data.getElements() ) Printf(out,"#;\n",element);
  
  Putobj(out,"\n/* Rules */ \n\n");
  
  for(auto rule : data.getRules() ) Printf(out,"#;\n",rule);
  
  Putobj(out,"\n/* Finals */ \n\n");
  
  for(auto final : data.getFinals() ) Printf(out,"#;\n",final);
  
  Putobj(out,"\n/* States */ \n\n");
  
  for(auto state : data.getStates() ) Printf(out,"#;\n",state);
 }

void Engine::atom_h(StrLen file_name)
 {
  PrintFile out(file_name);
  
  auto atoms=data.getAtoms();
  
  Printf(out,"/* enum AtomClass */ \n\nenum AtomClass\n {\n  Atom_Nothing,\n\n");
  
  for(ulen i=1,n=atoms.len; i<n ;i++)
    {
     if( i+1<n )
       Printf(out,"  Atom_<nake>, /*  #;  */\n",StrLen(atoms[i].name.inner(3,2)));
     else
       Printf(out,"  Atom_<nake>  /*  #;  */\n",StrLen(atoms[i].name.inner(3,2)));
    }
  
  Printf(out," };\n\nconst char * GetTextDesc(AtomClass ac);\n\n");
 }

void Engine::atom_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  auto atoms=data.getAtoms();
  
  Printf(out,"/* enum AtomClass */ \n\nconst char * GetTextDesc(AtomClass ac)\n {\n");
  
  Printf(out,"  static const char *const Table[]=\n   {\n");
  
  Printf(out,"    \"no-atom\",\n\n");
  
  for(ulen i=1,n=atoms.len; i<n ;i++)
    {
     if( i+1<n )
       Printf(out,"    #;,\n",StrLen(atoms[i].name.inner(2,1)));
     else
       Printf(out,"    #;\n",StrLen(atoms[i].name.inner(2,1)));
    }
  
  Printf(out,"   };\n\n");
  
  Printf(out,"  return Table[ac];\n }\n\n");
 }

void Engine::elements1(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* elements */ \n\n");
  
  for(auto element : data.getNonAtoms() ) 
    {
     Printf(out,"struct Element_#;;\n",element.name);
    }
 }

void Engine::elements2(StrLen file_name)
 {
  PrintFile out(file_name);
  
  for(auto element : data.getNonAtoms() ) 
    {
     Printf(out,"/* struct Element_#; */ \n\n",element.name);
     
     Printf(out,"struct Element_#; : ElementBase\n {\n",element.name);
     
     Printf(out,"  static ulen NextState(ulen state);\n");
     
     for(auto *ptr: element.rules )
       {
        auto rule=*ptr;

        if( !rule.args )
          {
           Printf(out,"\n  void #;(ElementContext ctx);\n",rule.name);
          }
        else
          {
           Printf(out,"\n  void #;(ElementContext ctx",rule.name);
           
           for(auto *arg : rule.args ) Printf(out,",#; *",ElementName(*arg));
           
           Printf(out,");\n");
          }
       }
     
     Printf(out," };\n\n");
    }
 }

void Engine::elements3(StrLen file_name)
 {
  PrintFile out(file_name);
  
  for(auto element : data.getNonAtoms() ) 
    {
     Printf(out,"/* struct Element_#; */ \n\n",element.name);
     
     for(auto *ptr: element.rules )
       {
        auto rule=*ptr;

        if( !rule.args )
          {
           Printf(out,"void Element_#;::#;(ElementContext)\n",element.name,rule.name);
          }
        else
          {
           Printf(out,"void Element_#;::#;(ElementContext",element.name,rule.name);
           
           for(auto *arg : rule.args ) Printf(out,",#; *",ElementName(*arg));
           
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
  
  auto r=data.getRules();

  for(++r; +r ;++r)
    {
     if( r.len>1 )
       Printf(out,"    Do_#;,\n",r->name);
     else
       Printf(out,"    Do_#;\n",r->name);
    }
 }

void Engine::do_h(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* do_...() */ \n\n");

  auto r=data.getRules();
  
  for(++r; +r ;++r)
    {
     Printf(out,"   void do_#;();\n",r->name);
    }
 }

void Engine::do_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* do_...() */ \n\n");

  auto r=data.getRules();
  
  for(++r; +r ;++r)
    {
     auto rule=*r;
     
     Printf(out,"void Parser::do_#;()\n {\n",rule.name);
     
     for(ulen j=0,m=rule.args.len; j<m ;j++)
       {
        ulen k=m-1-j;
        
        Printf(out,"  #; *arg#;=pop();\n",ElementName(rule.args[k]),k+1);
       }
     
     auto result_name=rule.result->name;
     
     if( rule.args.len ) Putch(out,'\n');
     
     Printf(out,"  Element_#; *elem=elem_#;(",result_name,rule.name);
     
     for(ulen j=0,m=rule.args.len; j<m ;j++) 
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
  
  auto r=data.getRules();
  
  for(++r; +r ;++r)
    {
     auto rule=*r;
     
     auto result_name=rule.result->name;

     Printf(out,"   Element_#; * elem_#;(",result_name,rule.name);
     
     for(ulen j=0,m=rule.args.len; j<m ;j++) 
       {
        if( j )
          Printf(out,",#; *",ElementName(rule.args[j]));
        else
          Printf(out,"#; *",ElementName(rule.args[j]));
       }
     
     Printf(out,");\n");
    }   
 }

void Engine::elem_cpp(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* elem_...() */ \n\n");
  
  auto r=data.getRules();
   
  for(++r; +r ;++r)
    {
     auto rule=*r;
     
     auto result_name=rule.result->name;

     Printf(out,"Element_#; * Parser::elem_#;(",result_name,rule.name);
  
     for(ulen j=0,m=rule.args.len; j<m ;j++) 
       {
        if( j )
          Printf(out,",#; *arg#;",ElementName(rule.args[j]),j+1);
        else
          Printf(out,"#; *arg#;",ElementName(rule.args[j]),j+1);
       }
     
     Printf(out,")\n {\n");
     
     Printf(out,"  Element_#; *elem=ctx.create<Element_#;>();\n\n",result_name,result_name);
     
     Printf(out,"  elem->#;(ctx",rule.name);
     
     for(ulen j=0,m=rule.args.len; j<m ;j++) Printf(out,",arg#;",j+1);
      
     Printf(out,");\n\n");
     
     Printf(out,"  return elem;\n");
     
     Printf(out," }\n\n");
    }   
 }

void Engine::do_rule(StrLen file_name)
 {
  PrintFile out(file_name);
  
  Printf(out,"/* doRule */ \n\n");
  
  auto r=data.getRules();
   
  for(++r; +r ;++r)
    {
     auto name=r->name;
     
     Printf(out,"     case Action::Do_#; : do_#;(); break;\n",name,name);
    }  
 }

void Engine::rule_table(StrLen file_name)
 {
  PrintFile out(file_name);
  
  ulen n=data.getStates().len;
  ulen m=TypeDef::Element::AtomLim;
  
  DynArray<TypeDef::RuleIndex> buf(m);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(data.getRules().len);
  
  Printf(out,"/* RuleTable */ \n\n");
  
  Printf(out,"static const RuleTableType RuleTable[#;][#;]=\n",n,m);
  
  Printf(out," {\n");
  
  for(ulen i=0; i<n ;i++)
    {
     Printf(out,"  {");
     
     {
      Range(buf).set_null();

      auto actions=data.getStates()[i].final->actions;
      
      for(auto action : actions )
        {
         buf[action.atom->element]=action.rule->rule+1;
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
  
  ulen n=data.getStates().len;
  ulen m=TypeDef::Element::AtomLim;
  
  DynArray<TypeDef::StateIndex> buf(m);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(n);
  
  Printf(out,"/* AtomStateTable */ \n\n");
  
  Printf(out,"static const StateTableType AtomStateTable[#;][#;]=\n",n,m);
  
  Printf(out," {\n");
  
  for(ulen i=0; i<n ;i++)
    {
     Printf(out,"  {");
     
     {
      Range(buf).set_null();

      auto transitions=data.getStates()[i].transitions;
      
      for(auto transition : transitions )
        {
         auto ind=transition.element->element;
         
         if( ind<m )
           {
            buf[ind]=transition.state->state;
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
  
  ulen n=data.getNonAtoms().len;
  ulen m=data.getStates().len;
  
  DynArray<DynArray<TypeDef::StateIndex> > buf(DoFill(m),n);
  
  IntPrintOpt opt;
  
  opt.width=GetWidth(m);
  
  for(ulen j=0; j<m ;j++)
    {
     auto transitions=data.getStates()[j].transitions;
     
     for(auto transition : transitions )
       {
        auto ind=transition.element->element;
       
        if( ind>=TypeDef::Element::AtomLim )
          {
           buf[j][ind-TypeDef::Element::AtomLim]=transition.state->state;
          }
       }
    }
  
  Printf(out,"/* Element_...::NextState() */ \n\n");
  
  for(ulen i=0; i<n ;i++)
    {
     auto element=data.getNonAtoms()[i];
     
     Printf(out,"/* Element_#;::NextState() */ \n\n",element.name);
     
     Printf(out,"ulen Element_#;::NextState(ulen state)\n {\n  static const StateTableType Table[]=\n   {",element.name);
     
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
      Putobj(Con,"--- ParserGen 1.01 ---\n--- Copyright (c) 2012, 2013 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=3 ) 
        {
         Putobj(Con,"Usage: ParserGen <input-file-name> <output-files-name-prefix>\n");
         
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
      
      String test_atom_cpp=Stringf("#;.atom.gen.cpp",base_name);
      
      engine.atom_cpp(Range(test_atom_cpp));
      
      // elements1

      String elements1_name=Stringf("#;.elements1.gen.h",base_name);
      
      engine.elements1(Range(elements1_name));
      
      // elements2
      
      String elements2_name=Stringf("#;.elements2.gen.h",base_name);
      
      engine.elements2(Range(elements2_name));
      
      // elements3
      
      String elements3_name=Stringf("#;.elements3.gen.cpp",base_name);
      
      engine.elements3(Range(elements3_name));
      
      // actions
      
      String actions_name=Stringf("#;.actions.gen.h",base_name);
      
      engine.actions(Range(actions_name));
      
      // do_h
      
      String do_h_name=Stringf("#;.do.gen.h",base_name);
      
      engine.do_h(Range(do_h_name));
      
      // do_cpp
      
      String do_cpp_name=Stringf("#;.do.gen.cpp",base_name);
      
      engine.do_cpp(Range(do_cpp_name));
      
      // elem_h
      
      String elem_h_name=Stringf("#;.elem.gen.h",base_name);
      
      engine.elem_h(Range(elem_h_name));
      
      // elem_cpp
      
      String elem_cpp_name=Stringf("#;.elem.gen.cpp",base_name);
      
      engine.elem_cpp(Range(elem_cpp_name));
      
      // elem_cpp
      
      String do_rule_name=Stringf("#;.do_rule.gen.cpp",base_name);
      
      engine.do_rule(Range(do_rule_name));
      
      // rule_table
      
      String rule_table_name=Stringf("#;.rule_table.gen.cpp",base_name);
      
      engine.rule_table(Range(rule_table_name));
      
      // atom_state_table
      
      String atom_state_table_name=Stringf("#;.atom_state_table.gen.cpp",base_name);
      
      engine.atom_state_table(Range(atom_state_table_name));
      
      // next_state
      
      String next_state_name=Stringf("#;.next_state.gen.cpp",base_name);
      
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
 
