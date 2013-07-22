/* Lang.cpp */
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

#include "Lang.h"
#include "LangParser.h"

#include <CCore/inc/FunctorType.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/algon/SortUnique.h>

namespace App {

/* class Lang::Builder */

class Lang::Builder : NoCopy
 {
  public:
   
   struct BuildCondAND;
   struct BuildCondOR;
   struct BuildCondNOT;
   struct BuildCondEQ;
   struct BuildCondNE;
   struct BuildCondGT;
   struct BuildCondGE;
   struct BuildCondLT;
   struct BuildCondLE;
   
   using BuildCond = AnyPtr<BuildCondAND,
                            BuildCondOR,
                            BuildCondNOT,
                            BuildCondEQ,
                            BuildCondNE,
                            BuildCondGT,
                            BuildCondGE,
                            BuildCondLT,
                            BuildCondLE> ;
   
   struct BuildCondAND : NoCopy
    {
     BuildCond a;
     BuildCond b;
     
     BuildCondAND(BuildCond a_,BuildCond b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondOR : NoCopy
    {
     BuildCond a;
     BuildCond b;
     
     BuildCondOR(BuildCond a_,BuildCond b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondNOT : NoCopy
    {
     BuildCond a;
     
     explicit BuildCondNOT(BuildCond a_) : a(a_) {}
    };
   
   struct BuildCondEQ : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondEQ(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondNE : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondNE(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondGT : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondGT(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondGE : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondGE(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondLT : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondLT(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondLE : NoCopy
    {
     StrLen a;
     StrLen b;
     
     BuildCondLE(StrLen a_,StrLen b_) : a(a_),b(b_) {}
    };

   template <class P>
   struct PrintCond
    {
     P &out;
     
     explicit PrintCond(P &out_) : out(out_) {}
     
     void operator () (BuildCondAND *ptr)
      {
       Putobj(out,"( ");
       print(ptr->a);
       Putobj(out," & ");
       print(ptr->b);
       Putobj(out," )");
      }
     
     void operator () (BuildCondOR *ptr)
      {
       Putobj(out,"( ");
       print(ptr->a);
       Putobj(out," | ");
       print(ptr->b);
       Putobj(out," )");
      }
     
     void operator () (BuildCondNOT *ptr)
      {
       Putobj(out,"! ");
       print(ptr->a);
      }
     
     void operator () (BuildCondEQ *ptr)
      {
       Printf(out,"#; == #;",ptr->a,ptr->b);
      }
     
     void operator () (BuildCondNE *ptr)
      {
       Printf(out,"#; != #;",ptr->a,ptr->b);
      }
     
     void operator () (BuildCondGT *ptr)
      {
       Printf(out,"#; > #;",ptr->a,ptr->b);
      }
     
     void operator () (BuildCondGE *ptr)
      {
       Printf(out,"#; >= #;",ptr->a,ptr->b);
      }
     
     void operator () (BuildCondLT *ptr)
      {
       Printf(out,"#; < #;",ptr->a,ptr->b);
      }
     
     void operator () (BuildCondLE *ptr)
      {
       Printf(out,"#; <= #;",ptr->a,ptr->b);
      }
     
     void print(BuildCond cond)
      {
       cond.apply(*this);
      }
    };
   
   BuildCond condOR(BuildCond a,BuildCond b);
   BuildCond condAND(BuildCond a,BuildCond b);
   BuildCond condNOT(BuildCond a);
   BuildCond condEQ(StrLen a,StrLen b);
   BuildCond condNE(StrLen a,StrLen b);
   BuildCond condGT(StrLen a,StrLen b);
   BuildCond condGE(StrLen a,StrLen b);
   BuildCond condLT(StrLen a,StrLen b);
   BuildCond condLE(StrLen a,StrLen b);
   
   template <class T>
   class ObjList : NoCopy
    {
      using Algo = typename SLink<T>::template LinearAlgo<&T::link> ;
     
      typename Algo::FirstLast list;
      ulen count;
      
     public: 
     
      ObjList() : count(0) {}
     
      ulen operator + () const { return count; }
     
      bool operator ! () const { return !count; }
     
      void add(T *obj) { list.ins_last(obj); count++; }
      
      template <class FuncInit>
      void apply(FuncInit func_init) const
       {
        FunctorTypeOf<FuncInit> func(func_init);

        auto cur=list.start();
        
        for(ulen cnt=count; cnt ;cnt--) 
          {
           func(*cur);
           
           ++cur;
          }
       }
      
      template <class FuncInit,class EndFuncInit>
      void apply(FuncInit func_init,EndFuncInit end_func_init) const
       {
        FunctorTypeOf<FuncInit> func(func_init);
        FunctorTypeOf<EndFuncInit> end_func(end_func_init);

        if( !count ) return;
        
        auto cur=list.start();
        
        for(ulen cnt=count-1; cnt ;cnt--) 
          {
           func(*cur);
           
           ++cur;
          }
        
        end_func(*cur);
       }
    };
   
   struct BuildAtom : NoCopy
    {
     SLink<BuildAtom> link;
     
     StrLen name;
     
     explicit BuildAtom(StrLen name_) : name(name_) {}
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,name);
      }
    };
   
   struct BuildSynt;
   
   struct BuildKind : NoCopy
    {
     SLink<BuildKind> link;
     
     StrLen name;
     TextPos pos;
     
     BuildKind(StrLen name_,TextPos pos_) : name(name_),pos(pos_) {}
    };
   
   struct BuildElement : NoCopy
    {
     SLink<BuildElement> link;
     
     StrLen name;
     TextPos pos;
     BuildSynt *synt;
     StrLen arg;
     BuildAtom *atom;
     
     BuildElement(StrLen name_,TextPos pos_) : name(name_),pos(pos_),synt(0),atom(0) {}
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,name);
       
       if( synt )
         {
          Putch(out,'$');
          
          if( +arg ) Putch(out,'$');
         }
       
       if( atom )
         {
          Putch(out,'@');
         }
      }
    };
   
   struct BuildRule : NoCopy
    {
     SLink<BuildRule> link;
     
     StrLen name;
     TextPos pos;
     BuildCond cond;
     StrLen result;
     TextPos result_pos;
     ObjList<BuildElement> element_list;
     
     BuildKind *result_kind;
     
     BuildRule() : result_kind(0) {}
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"rule #; ",name);
       
       if( +cond )
         {
          Putobj(out,"if( ");
         
          PrintCond<P>(out).print(cond);
          
          Putobj(out," ) ");
         }
       
       Putch(out,'(');
       
       element_list.apply( [&] (const BuildElement &element) { Printf(out," #;",element); } );
       
       Putobj(out," )");
       
       if( result_kind ) Printf(out," -> #;",result_kind->name);
      }
    };
   
   struct BuildSynt : NoCopy
    {
     SLink<BuildSynt> link;
     
     StrLen name;
     TextPos pos;
     bool is_lang;
     ObjList<BuildKind> kind_list;
     ObjList<BuildRule> rule_list;
     
     BuildSynt(StrLen name_,TextPos pos_,bool is_lang_) : name(name_),pos(pos_),is_lang(is_lang_) {}
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"synt #;",name);
       
       if( is_lang ) Putobj(out," lang");
       
       if( +kind_list ) 
         {
          Putobj(out," { ");
          
          kind_list.apply( [&] (const BuildKind &kind) { Printf(out,"#; , ",kind.name); } ,
                           [&] (const BuildKind &kind) { Printf(out,"#;",kind.name); }
                         );
          
          Putobj(out," }");
         }
       
       Putobj(out,"\n\n");
       
       rule_list.apply( [&] (const BuildRule &rule) { Printf(out,"  #;\n",rule); } );
       
       Putch(out,'\n');
      }
    };
   
   void startSynt(StrLen name,TextPos pos,bool is_lang);
   
   void addKind(StrLen name,TextPos pos);
   void endKinds();
   
   void startRule();
   
   void addElement(StrLen name,TextPos pos);
   void endElements();
   
   void rule(BuildCond cond);
   void rule(StrLen name,TextPos pos);
   void result(StrLen name,TextPos pos);
   
   void endRule();
   
   void endSynt();
   
   void endLang();
   
   template <class ... TT>
   static void error(const char *format,const TT & ... tt)
    {
     Printf(NoException,format,tt...);
    }
   
   template <class ... TT>
   static void exception(const char *format,const TT & ... tt)
    {
     Printf(Exception,format,tt...);
    }

  private: 
   
   Lang &lang;
   ElementPool pool;
   
   ObjList<BuildSynt> synt_list;
   ObjList<BuildAtom> atom_list;
   
   BuildSynt *current_synt = 0 ;
   BuildRule *current_rule = 0 ;
   
  private: 
   
   static bool CorrectElement(StrLen name);
   
   static StrLen SyntElementName(StrLen name);
   
   struct BindName
    {
     StrLen name;
     
     explicit BindName(StrLen name_) : name(name_) {}
     
     bool operator < (BindName obj) const { return StrLess(name,obj.name); }
     
     bool operator != (BindName obj) const { return StrCmp(name,obj.name); }
    };
   
   struct BindElement : BindName
    {
     AnyPtr<BuildSynt,BuildElement> ptr;
     
     explicit BindElement(BuildSynt &synt) : BindName(synt.name),ptr(&synt) {}
     
     BindElement(StrLen name_,BuildElement &element) : BindName(name_),ptr(&element) {}
    };
   
   struct FindSynt : NoCopy
    {
     BuildSynt *synt;
     ulen count;
     
     FindSynt() : synt(0),count(0) {}
     
     void operator () (BuildSynt *synt_) { synt=synt_; count++; }
     
     void operator () (BuildElement *) {}
    };
   
   struct SetElement 
    {
     BuildSynt *synt;
     ulen len;
     
     explicit SetElement(BuildSynt *synt_) : synt(synt_),len(synt->name.len) {}
     
     void operator () (BuildSynt *) {}
     
     void operator () (BuildElement *element) 
      { 
       element->synt=synt;
       
       ulen name_len=element->name.len;
       
       if( name_len>len ) element->arg=element->name.part(len+1);
      }
    };
   
   void bindElements(PtrLen<BindElement> range);
   
   void bindElements();
   
   struct BindAtom : BindName
    {
     BuildElement *element;
     
     explicit BindAtom(BuildElement &element_) : BindName(element_.name),element(&element_) {} 
    };
   
   void bindAtom(PtrLen<BindAtom> range);
   
   void buildAtoms();
   
   struct CheckRuleName : BindName
    {
     BuildRule *rule;
     
     explicit CheckRuleName(BuildRule &rule_) : BindName(rule_.name),rule(&rule_) {}
    };
   
   void checkRuleNames();
   
   struct BindResult : BindName
    {
     AnyPtr<BuildRule,BuildKind> ptr;
     
     explicit BindResult(BuildRule &rule) : BindName(rule.result),ptr(&rule) {}
     
     explicit BindResult(BuildKind &kind) : BindName(kind.name),ptr(&kind) {}
    };
   
   struct FindKind : NoCopy
    {
     BuildKind *kind;
     ulen count;
     
     BuildRule *rule;
     
     FindKind() : kind(0),count(0),rule(0) {}
     
     void operator () (BuildRule *rule_) { rule=rule_; }
     
     void operator () (BuildKind *kind_) { kind=kind_; count++; }
    };
   
   struct SetResult
    {
     BuildKind *kind;
     
     explicit SetResult(BuildKind *kind_) : kind(kind_) {}
     
     void operator () (BuildRule *rule) { rule->result_kind=kind; }
     
     void operator () (BuildKind *) {}
    };
   
   void bindResults(PtrLen<BindResult> range);
   
   void bindResults();
   
  public:
 
   explicit Builder(Lang &lang);
   
   ~Builder();
   
   template <class P>
   void print(P &out) const
    {
     atom_list.apply( [&] (const BuildAtom &atom) { Printf(out,"#;\n",atom); } );
     
     Putch(out,'\n');
     
     synt_list.apply( [&] (const BuildSynt &synt) { Printf(out,"#;\n",synt); } );
    }
 };

auto Lang::Builder::condOR(BuildCond a,BuildCond b) -> BuildCond
 {
  return pool.create<BuildCondOR>(a,b);
 }

auto Lang::Builder::condAND(BuildCond a,BuildCond b) -> BuildCond
 {
  return pool.create<BuildCondAND>(a,b);
 }

auto Lang::Builder::condNOT(BuildCond a) -> BuildCond
 {
  return pool.create<BuildCondNOT>(a);
 }

auto Lang::Builder::condEQ(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondEQ>(a,b);
 }

auto Lang::Builder::condNE(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondNE>(a,b);
 }

auto Lang::Builder::condGT(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondGT>(a,b);
 }

auto Lang::Builder::condGE(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondGE>(a,b);
 }

auto Lang::Builder::condLT(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondLT>(a,b);
 }

auto Lang::Builder::condLE(StrLen a,StrLen b) -> BuildCond
 {
  return pool.create<BuildCondLE>(a,b);
 }

void Lang::Builder::startSynt(StrLen name,TextPos pos,bool is_lang)
 {
  current_synt=pool.create<BuildSynt>(name,pos,is_lang);
 }

void Lang::Builder::addKind(StrLen name,TextPos pos)
 {
  current_synt->kind_list.add(pool.create<BuildKind>(name,pos));
 }

void Lang::Builder::endKinds()
 {
  // do nothing
 }

void Lang::Builder::startRule()
 {
  current_rule=pool.create<BuildRule>();
 }

void Lang::Builder::addElement(StrLen name,TextPos pos)
 {
  if( CorrectElement(name) ) ++name;
  
  current_rule->element_list.add(pool.create<BuildElement>(name,pos));
 }

void Lang::Builder::endElements()
 {
  // do nothing
 }

void Lang::Builder::rule(BuildCond cond)
 {
  current_rule->cond=cond;
 }

void Lang::Builder::rule(StrLen name,TextPos pos)
 {
  current_rule->name=name;
  current_rule->pos=pos;
 }

void Lang::Builder::result(StrLen name,TextPos pos)
 {
  current_rule->result=name;
  current_rule->result_pos=pos;
 }

void Lang::Builder::endRule()
 {
  current_synt->rule_list.add(Replace_null(current_rule));
 }

void Lang::Builder::endSynt()
 {
  synt_list.add(Replace_null(current_synt));
 }

void Lang::Builder::endLang()
 {
  ReportException report;
  
  bindElements();
  buildAtoms();
  checkRuleNames();
  bindResults();
  // ...
  
  report.guard();
  
  Putobj(Con,*this);
 }

bool Lang::Builder::CorrectElement(StrLen name)
 {
  if( name.len>=2 && name[0]=='`' )
    {
     char ch=name.back(1);
     
     if( ch=='}' || ch==':' )
       {
        for(auto r=name.inner(1,1); +r ;++r)
          if( *r!='`' )
            return false;
        
        return true;
       }
    }
  
  return false;
 }

StrLen Lang::Builder::SyntElementName(StrLen name)
 {
  ulen len=LangParser::ScanName(name);
  
  if( !len ) return {};
  
  if( len==name.len ) return name;
  
  if( name[len]=='.' && LangParser::IsName(name.part(len+1)) ) return name.prefix(len);
   
  return {}; 
 }

void Lang::Builder::bindElements(PtrLen<BindElement> range)
 {
  FindSynt find;
  
  for(auto &bind : range ) bind.ptr.apply( FunctorRef(find) );
  
  switch( find.count )
    {
     case 0 :
      {
       // do nothing
      }
     break;
     
     case 1 :
      {
       SetElement set_element(find.synt);
       
       for(auto &bind : range ) bind.ptr.apply(set_element);
      }
     break;
     
     default:
      {
       error("Builder #; : multiple declaration of syntax class #;",find.synt->pos,find.synt->name);
      }
    }
 }

void Lang::Builder::bindElements()
 {
  ulen lang_count=0;
  Collector<BindElement> collector;
  
  synt_list.apply( [&] (BuildSynt &synt) 
                       {
                        lang_count+=synt.is_lang;  
    
                        collector.append_fill(synt);
                        
                        synt.rule_list.apply( [&] (BuildRule &rule) 
                                                  {
                                                   rule.element_list.apply( [&] (BuildElement &element) 
                                                                                {
                                                                                 StrLen name=SyntElementName(element.name);
                                                     
                                                                                 if( +name ) collector.append_fill(name,element); 
                                                                                } 
                                                                          );
                                                  } 
                                            );
                       } 
                 );
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [&] (PtrLen<BindElement> range) { bindElements(range); } );
  
  if( !lang_count ) error("Builder : no lang syntax class");
 }

void Lang::Builder::bindAtom(PtrLen<BindAtom> range)
 {
  StrLen name=range->element->name;
  BuildAtom *atom=pool.create<BuildAtom>(name);
  
  atom_list.add(atom);
  
  for(auto &bind: range ) bind.element->atom=atom;
 }

void Lang::Builder::buildAtoms()
 {
  Collector<BindAtom> collector;
  
  synt_list.apply( [&] (BuildSynt &synt) 
                       {
                        synt.rule_list.apply( [&] (BuildRule &rule) 
                                                  {
                                                   rule.element_list.apply( [&] (BuildElement &element) 
                                                                                {
                                                                                 if( !element.synt ) collector.append_fill(element);
                                                                                } 
                                                                          );
                                                  } 
                                            );
                       } 
                 );
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [&] (PtrLen<BindAtom> range) { bindAtom(range); } );
 }

void Lang::Builder::checkRuleNames()
 {
  Collector<CheckRuleName> collector; 
  
  synt_list.apply( [&] (BuildSynt &synt) 
                       {
                        synt.rule_list.apply( [&] (BuildRule &rule) 
                                                  {
                                                   collector.append_fill(rule);  
                                                  } 
                                            );
                       } 
                 );
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [&] (PtrLen<CheckRuleName> range) 
                                                        {
                                                         if( range.len>1 )
                                                           {
                                                            error("Builder #; : multiple declaration of rule #;",range->rule->pos,range->name);
                                                           }
                                                        } 
                                 );
 }

void Lang::Builder::bindResults(PtrLen<BindResult> range)
 {
  FindKind find;
  
  for(auto &bind : range ) bind.ptr.apply( FunctorRef(find) );
  
  switch( find.count )
    {
     case 0 :
      {
       error("Builder #; : no declaration of kind #;",find.rule->result_pos,find.rule->result);
      }
     break;
     
     case 1 :
      {
       SetResult set_result(find.kind);
       
       for(auto &bind : range ) bind.ptr.apply(set_result);
      }
     break;
     
     default:
      {
       error("Builder #; : multiple declaration of kind #;",find.kind->pos,find.kind->name);
      }
    }
 }

void Lang::Builder::bindResults()
 {
  synt_list.apply( [&] (BuildSynt &synt) 
                       {
                        if( +synt.kind_list )
                          {
                           Collector<BindResult> collector;  
      
                           synt.rule_list.apply( [&] (BuildRule &rule) 
                                                     {
                                                      collector.append_fill(rule);  
                                                     } 
                                               );
                          
                           synt.kind_list.apply( [&] (BuildKind &kind) 
                                                     {
                                                      collector.append_fill(kind);
                                                     } 
                                               );
                           
                           Algon::SortThenApplyUniqueRange(collector.flat(), [&] (PtrLen<BindResult> range)
                                                                                 {
                                                                                  bindResults(range);
                                                                                 }
                                                          );
                          }
                       } 
                 );
 }

Lang::Builder::Builder(Lang &lang_) 
 : lang(lang_)
 {
 }

Lang::Builder::~Builder()
 {
 }

/* class Lang */

Lang::Lang(StrLen file_name)
 {
  FileToMem file(file_name);
  
  LangParser::Parser<Builder> parser(*this);
  
  parser.run(Mutate<const char>(Range(file)));
 }

Lang::~Lang()
 {
 }

} // namespace App

