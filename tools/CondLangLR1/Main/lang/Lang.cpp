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
      
      ulen getCount() const { return count; }
     
      void add(T *obj) { list.ins_last(obj); count++; }
      
      T * del() 
       { 
        if( T *ret=list.del_first() ) 
          { 
           count--; 
           
           return ret; 
          } 
        
        return 0; 
       }
      
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
 
   struct BuildKind;
   struct BuildElement;
 
   struct BuildCondArg : NoCopy , PosStr
    {
     SLink<BuildCondArg> link;
     
     BuildElement *element;
     BuildKind *kind;
     BuildCondArg *peer;
     
     explicit BuildCondArg(PosStr postr_) : PosStr(postr_),element(0),kind(0),peer(0) {}
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,str);
      }
    };
   
   struct BuildCondAND;
   struct BuildCondOR;
   struct BuildCondNOT;
   struct BuildCondEQ;
   struct BuildCondNE;
   struct BuildCondGT;
   struct BuildCondGE;
   struct BuildCondLT;
   struct BuildCondLE;
   
  public: 
   
   using BuildCond = AnyPtr<BuildCondAND,
                            BuildCondOR,
                            BuildCondNOT,
                            BuildCondEQ,
                            BuildCondNE,
                            BuildCondGT,
                            BuildCondGE,
                            BuildCondLT,
                            BuildCondLE> ;
   
  private: 
   
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
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondEQ(PosStr a_,PosStr b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondNE : NoCopy
    {
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondNE(PosStr a_,PosStr b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondGT : NoCopy
    {
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondGT(PosStr a_,PosStr b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondGE : NoCopy
    {
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondGE(PosStr a_,PosStr b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondLT : NoCopy
    {
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondLT(PosStr a_,PosStr b_) : a(a_),b(b_) {}
    };
   
   struct BuildCondLE : NoCopy
    {
     BuildCondArg a;
     BuildCondArg b;
     
     BuildCondLE(PosStr a_,PosStr b_) : a(a_),b(b_) {}
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
   
   struct BuildAtom : NoCopy
    {
     SLink<BuildAtom> link;
     
     StrLen str;
     ulen index;
     
     explicit BuildAtom(StrLen str_) : str(str_),index(MaxULen) {}
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,str);
      }
    };
   
   struct BuildSynt;
   
   struct BuildKind : NoCopy , PosStr
    {
     SLink<BuildKind> link;
     
     ulen index;
     
     explicit BuildKind(PosStr postr) : PosStr(postr),index(MaxULen) {}
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,str);
      }
    };
   
   struct BuildElement : NoCopy , PosStr
    {
     SLink<BuildElement> link;
     
     BuildSynt *synt;
     StrLen arg;
     BuildAtom *atom;
     
     ulen index;
     
     explicit BuildElement(PosStr postr) : PosStr(postr),synt(0),atom(0),index(MaxULen) {}
     
     void cutArg(ulen len)
      {
       ulen name_len=str.len;

       if( name_len>len ) arg=str.part(len+1);
      }
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,str);
       
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
   
   struct BuildRule : NoCopy , PosStr 
    {
     SLink<BuildRule> link;
     
     BuildCond cond;
     PosStr result;
     ObjList<BuildElement> element_list;
     
     BuildKind *result_kind;
     
     ulen index;
     
     BuildRule() : result_kind(0),index(MaxULen) {}
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"rule #; ",str);
       
       if( +cond )
         {
          Putobj(out,"if( ");
         
          PrintCond<P>(out).print(cond);
          
          Putobj(out," ) ");
         }
       
       Putch(out,'(');
       
       element_list.apply( [&] (const BuildElement &element) { Printf(out," #;",element); } );
       
       Putobj(out," )");
       
       if( result_kind ) Printf(out," -> #;",*result_kind);
      }
    };
   
   struct BuildSynt : NoCopy , PosStr
    {
     SLink<BuildSynt> link;
     
     bool is_lang;
     ObjList<BuildKind> kind_list;
     ObjList<BuildRule> rule_list;
     ulen index;
     ulen rule_off;
     
     ObjList<BuildCondArg> arg_list;
     
     BuildSynt(PosStr postr,bool is_lang_) : PosStr(postr),is_lang(is_lang_),index(MaxULen),rule_off(MaxULen) {}
     
     void add(BuildCondArg *arg) { arg_list.add(arg); }
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"synt #;",str);
       
       if( is_lang ) Putobj(out," lang");
       
       if( +kind_list ) 
         {
          Putobj(out," { ");
          
          kind_list.apply( [&] (const BuildKind &kind) { Printf(out,"#; , ",kind); } ,
                           [&] (const BuildKind &kind) { Printf(out,"#;",kind); }
                         );
          
          Putobj(out," }");
         }
       
       Putobj(out,"\n\n");
       
       rule_list.apply( [&] (const BuildRule &rule) { Printf(out,"  #;\n",rule); } );
       
       Putch(out,'\n');
      }
    };
   
  public:
 
   BuildCond condOR(BuildCond a,BuildCond b);
   BuildCond condAND(BuildCond a,BuildCond b);
   BuildCond condNOT(BuildCond a);
   BuildCond condEQ(PosStr a,PosStr b);
   BuildCond condNE(PosStr a,PosStr b);
   BuildCond condGT(PosStr a,PosStr b);
   BuildCond condGE(PosStr a,PosStr b);
   BuildCond condLT(PosStr a,PosStr b);
   BuildCond condLE(PosStr a,PosStr b);
   
   void startSynt(PosStr postr,bool is_lang);
   
   void addKind(PosStr postr);
   void endKinds();
   
   void startRule();
   
   void addElement(PosStr postr);
   void endElements();
   
   void rule(BuildCond cond);
   void rule(PosStr postr);
   void result(PosStr postr);
   
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
   
   ObjList<BuildCondArg> arg_list;
   
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
     
     explicit BindElement(BuildSynt &synt) : BindName(synt.str),ptr(&synt) {}
     
     BindElement(StrLen name_,BuildElement &element) : BindName(name_),ptr(&element) {}
    };
   
   void bindElements(PtrLen<BindElement> range);
   
   void bindElements();
   
   struct BindAtom : BindName
    {
     BuildElement *element;
     
     explicit BindAtom(BuildElement &element_) : BindName(element_.str),element(&element_) {} 
    };
   
   static bool IsExpChar(char ch) { return ch=='\\' || ch=='"' ; }
   
   template <class R>
   static ulen ExpCharCount(R r) 
    { 
     ulen ret=0; 
     
     for(; +r ;++r) if( IsExpChar(*r) ) ret++;
     
     return ret;
    }
   
   class PutChar : NoCopy
    {
      PtrLen<char> out;
      
     public:
     
      explicit PutChar(PtrLen<char> out_) : out(out_) {}
      
      void put() {}
      
      void put(char ch) { *out=ch; ++out; }
      
      template <class ... CC>
      void put(char ch,CC ... cc)
       {
        put(ch);
        put(cc...);
       }
      
      void transform(char ch)
       {
        if( IsExpChar(ch) )
          put('\\',ch);
        else
          put(ch);
       }
    
      template <class R>
      void transform(R r)
       {
        for(; +r ;++r) transform(*r);
       }
    };
   
   StrLen buildAtomName(StrLen name);
   
   void bindAtom(PtrLen<BindAtom> range);
   
   void buildAtoms();
   
   struct CheckRuleName : BindName
    {
     BuildRule *rule;
     
     explicit CheckRuleName(BuildRule &rule_) : BindName(rule_.str),rule(&rule_) {}
    };
   
   void checkRuleNames();
   
   struct BindResult : BindName
    {
     AnyPtr<BuildRule,BuildKind> ptr;
     
     explicit BindResult(BuildRule &rule) : BindName(rule.result.str),ptr(&rule) {}
     
     explicit BindResult(BuildKind &kind) : BindName(kind.str),ptr(&kind) {}
    };
   
   void bindResults(PtrLen<BindResult> range);
   
   void bindResults();
   
   struct BindArgs : BindName
    {
     AnyPtr<BuildElement,BuildCondArg> ptr;
     
     explicit BindArgs(BuildElement &element) : BindName(element.arg),ptr(&element) {}
     
     explicit BindArgs(BuildCondArg &arg) : BindName(arg.str),ptr(&arg) {}
    };
   
   struct BindCondArgs
    {
     Collector<BindArgs> &collector;
     
     explicit BindCondArgs(Collector<BindArgs> &collector_) : collector(collector_) {}
     
     void operator () (BuildCondAND *cond)
      {
       cond->a.apply(*this);
       cond->b.apply(*this);
      }
     
     void operator () (BuildCondOR *cond)
      {
       cond->a.apply(*this);
       cond->b.apply(*this);
      }
     
     void operator () (BuildCondNOT *cond)
      {
       cond->a.apply(*this);
      }
     
     template <class T>
     void operator () (T *cond)
      {
       cond->a.peer=&cond->b;
       cond->b.peer=&cond->a;
         
       collector.append_fill(cond->a);
       collector.append_fill(cond->b);
      }
    };
   
   struct FindElement : NoCopy
    {
     BuildElement *element;
     ulen count;
     
     FindElement() : element(0),count(0) {}
     
     void operator () (BuildElement *element_) { element=element_; count++; }
     
     void operator () (BuildCondArg *) {}
    };
   
   struct SetArgElement
    {
     BuildElement *element;
     
     explicit SetArgElement(BuildElement *element_) : element(element_) {}
     
     void operator () (BuildElement *) {}
     
     void operator () (BuildCondArg *arg) { arg->element=element; }
    };
   
   struct RecordArg
    {
     Builder *builder;
     
     explicit RecordArg(Builder *builder_) : builder(builder_) {}
     
     void operator () (BuildElement *) {}
     
     void operator () (BuildCondArg *arg) { builder->arg_list.add(arg); }
    };
   
   void bindKindArgs();
   
   void bindArgs(PtrLen<BindArgs> range);
   
   void bindArgs(BuildRule &rule);
   
   void bindArgs(BuildSynt &synt);
   
   void bindArgs();
   
   struct BuildLangCond : NoCopy
    {
     Builder *builder;
     Cond result;
     
     CmpArg buildArg(BuildCondArg &arg)
      {
       if( arg.kind )
         {
          auto ptr=builder->lang.pool.create<CmpArgKind>();
         
          ptr->kind.index=arg.kind->index;
          ptr->kind.name=arg.kind->str;
         
          return {ptr};
         }
       else if( arg.element )
         {
          auto ptr=builder->lang.pool.create<CmpArgElement>();
          
          ptr->index=arg.element->index;
          
          return {ptr};
         }
       else
         {
          auto ptr=builder->lang.pool.create<CmpArgKind>();
        
          ptr->kind.index=MaxULen;
        
          return {ptr};
         }
      }
     
     explicit BuildLangCond(Builder *builder_) : builder(builder_) {}
     
     void operator () (BuildCondAND *cond)
      {
       auto a=builder->buildCond(cond->a);
       auto b=builder->buildCond(cond->b);
       
       auto result_=builder->lang.pool.create<CondAND>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondOR *cond)
      {
       auto a=builder->buildCond(cond->a);
       auto b=builder->buildCond(cond->b);
       
       auto result_=builder->lang.pool.create<CondOR>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondNOT *cond)
      {
       auto a=builder->buildCond(cond->a);
       
       auto result_=builder->lang.pool.create<CondNOT>();
       
       result_->a=a;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondEQ *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
       
       auto result_=builder->lang.pool.create<CondEQ>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondNE *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
       
       auto result_=builder->lang.pool.create<CondNE>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondGT *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
       
       auto result_=builder->lang.pool.create<CondGT>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
     
     void operator () (BuildCondGE *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
       
       auto result_=builder->lang.pool.create<CondGE>();
       
       result_->a=a;
       result_->b=b;
       
       result.ptr=result_;
      }
      
     void operator () (BuildCondLT *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
        
       auto result_=builder->lang.pool.create<CondLT>();
        
       result_->a=a;
       result_->b=b;
        
       result.ptr=result_;
      }
      
     void operator () (BuildCondLE *cond)
      {
       auto a=buildArg(cond->a);
       auto b=buildArg(cond->b);
        
       auto result_=builder->lang.pool.create<CondLE>();
        
       result_->a=a;
       result_->b=b;
        
       result.ptr=result_;
      }
    };
   
   Cond buildCond(BuildCond cond);
   
   void complete();
   
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

auto Lang::Builder::condEQ(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondEQ>(a,b);
 }

auto Lang::Builder::condNE(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondNE>(a,b);
 }

auto Lang::Builder::condGT(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondGT>(a,b);
 }

auto Lang::Builder::condGE(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondGE>(a,b);
 }

auto Lang::Builder::condLT(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondLT>(a,b);
 }

auto Lang::Builder::condLE(PosStr a,PosStr b) -> BuildCond
 {
  return pool.create<BuildCondLE>(a,b);
 }

void Lang::Builder::startSynt(PosStr postr,bool is_lang)
 {
  current_synt=pool.create<BuildSynt>(postr,is_lang);
 }

void Lang::Builder::addKind(PosStr postr)
 {
  current_synt->kind_list.add(pool.create<BuildKind>(postr));
 }

void Lang::Builder::endKinds()
 {
  // do nothing
 }

void Lang::Builder::startRule()
 {
  current_rule=pool.create<BuildRule>();
 }

void Lang::Builder::addElement(PosStr postr)
 {
  if( CorrectElement(postr.str) ) ++postr.str;
  
  current_rule->element_list.add(pool.create<BuildElement>(postr));
 }

void Lang::Builder::endElements()
 {
  // do nothing
 }

void Lang::Builder::rule(BuildCond cond)
 {
  current_rule->cond=cond;
 }

void Lang::Builder::rule(PosStr postr)
 {
  *(PosStr *)current_rule=postr;
 }

void Lang::Builder::result(PosStr postr)
 {
  current_rule->result=postr;
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
  bindArgs();        
  
  report.guard();
  
  Putobj(Con,*this);
  
  complete();
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
  BuildSynt *synt=0;
  ulen count=0;
  
  for(auto &bind : range ) bind.ptr.applyFor<BuildSynt>( [&] (BuildSynt *synt_) { synt=synt_; count++; } );
  
  switch( count )
    {
     case 0 :
      {
       // do nothing
      }
     break;
     
     case 1 :
      {
       ulen len=synt->str.len;
       
       for(auto &bind : range ) 
         bind.ptr.applyFor<BuildElement>( [=] (BuildElement *element) 
                                              {
                                               element->synt=synt;
                                               
                                               element->cutArg(len);
                                              } 
                                        );
      }
     break;
     
     default:
      {
       error("Builder #; : multiple declaration of syntax class #;",synt->pos,synt->str);
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
                                                                                 StrLen name=SyntElementName(element.str);
                                                     
                                                                                 if( +name ) collector.append_fill(name,element); 
                                                                                } 
                                                                          );
                                                  } 
                                            );
                       } 
                 );
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [this] (PtrLen<BindElement> range) { bindElements(range); } );
  
  if( !lang_count ) error("Builder : no lang syntax class");
 }

StrLen Lang::Builder::buildAtomName(StrLen name)
 {
  ulen len=LenAdd(5,name.len,ExpCharCount(name));
  
  auto ret=pool.createArray_raw<char>(len);

  PutChar out(ret);
  
  out.put('T','(','"');
  
  out.transform(name);
  
  out.put('"',')');
  
  return Range_const(ret);
 }

void Lang::Builder::bindAtom(PtrLen<BindAtom> range)
 {
  StrLen name=range->element->str;
  BuildAtom *atom=pool.create<BuildAtom>(buildAtomName(name));
  
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
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [this] (PtrLen<BindAtom> range) { bindAtom(range); } );
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
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [this] (PtrLen<CheckRuleName> range) 
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
  BuildKind *kind=0;
  ulen count=0;
  
  for(auto &bind : range ) bind.ptr.applyFor<BuildKind>( [&] (BuildKind *kind_) { kind=kind_; count++; } );
  
  switch( count )
    {
     case 0 :
      {
       BuildRule *rule=range->ptr.castPtr<BuildRule>();
       
       error("Builder #; : no declaration of kind #;",rule->result.pos,rule->result.str);
      }
     break;
     
     case 1 :
      {
       for(auto &bind : range ) bind.ptr.applyFor<BuildRule>( [=] (BuildRule *rule) { rule->result_kind=kind; } );
      }
     break;
     
     default:
      {
       error("Builder #; : multiple declaration of kind #;",kind->pos,kind->str);
      }
    }
 }

void Lang::Builder::bindResults()
 {
  synt_list.apply( [this] (BuildSynt &synt) 
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
                           
                              Algon::SortThenApplyUniqueRange(collector.flat(), [this] (PtrLen<BindResult> range)
                                                                                       {
                                                                                        bindResults(range);
                                                                                       }
                                                             );
                             }
                          } 
                 );
 }

void Lang::Builder::bindKindArgs()
 {
  while( BuildCondArg *arg=arg_list.del() )
    {
     if( BuildElement *element=arg->peer->element )
       {
        element->synt->add(arg);
       }
     else
       {
        error("Builder #; : comparision of constants",arg->pos);
       } 
    }
 }

void Lang::Builder::bindArgs(PtrLen<BindArgs> range)
 {
  FindElement find;
  
  for(auto &bind : range ) bind.ptr.apply( FunctorRef(find) );
  
  switch( find.count )
    {
     case 0 :
      {
       RecordArg record(this);
       
       for(auto &bind : range ) bind.ptr.apply(record);
      }
     break;
     
     case 1 :
      {
       SetArgElement set_element(find.element);
       
       for(auto &bind : range ) bind.ptr.apply(set_element);
      }
     break;
     
     default:
      {
       error("Builder #; : multiple declaration of element #; argument",find.element->pos,find.element->str);
      }
    }
 }

void Lang::Builder::bindArgs(BuildRule &rule)
 {
  Collector<BindArgs> collector;
  
  ulen index=0;
  
  rule.element_list.apply( [&] (BuildElement &element) 
                               {
                                if( +element.arg ) 
                                  {
                                   element.index=index;
                                 
                                   collector.append_fill(element);
                                  }
                               
                                index++;
                               } 
                         );
  
  rule.cond.apply( BindCondArgs(collector) );
  
  Algon::SortThenApplyUniqueRange(collector.flat(), [this] (PtrLen<BindArgs> range) { bindArgs(range); } );
 }

void Lang::Builder::bindArgs(BuildSynt &synt)
 {
 }

void Lang::Builder::bindArgs()
 {
  synt_list.apply( [this] (BuildSynt &synt) 
                          {
                           synt.rule_list.apply( [this] (BuildRule &rule) 
                                                        {
                                                         if( +rule.cond ) bindArgs(rule);
                                                        } 
                                               );
                          } 
                 );
  
  bindKindArgs();
  
  synt_list.apply( [this] (BuildSynt &synt) { bindArgs(synt); } );
 }

auto Lang::Builder::buildCond(BuildCond cond) -> Cond
 {
  BuildLangCond func(this);
  
  cond.apply( FunctorRef(func) );
  
  return func.result;
 }

void Lang::Builder::complete()
 {
  // atoms
  {
   ulen len=LenAdd(atom_list.getCount(),1);
   
   PtrLen<Atom> atoms=lang.pool.createArray<Atom>(len);
   
   lang.atoms=atoms;
   
   atoms[0].name="(End)";
   atoms[0].index=0;
   
   ulen index=1;
   
   atom_list.apply( [&] (BuildAtom &atom) 
                        {
                         atoms[index].name=lang.pool.dup(atom.str);
                         atoms[index].index=index;
                         
                         atom.index=index++;
                        } 
                  );
  }
  
  // synt
  {
   ulen len=synt_list.getCount();
   
   PtrLen<Synt> synts=lang.pool.createArray<Synt>(len);
   
   lang.synts=synts;
   
   ulen index=0;
   
   synt_list.apply( [&] (BuildSynt &synt) 
                        {
                         synts[index].name=lang.pool.dup(synt.str);
                         synts[index].index=index;
                         synts[index].is_lang=synt.is_lang;
                         
                         if( ulen klen=synt.kind_list.getCount() )
                           {
                            PtrLen<Kind> kinds=lang.pool.createArray<Kind>(klen);
                            
                            synts[index].kinds=Range_const(kinds);
                            
                            ulen kindex=0;
                            
                            synt.kind_list.apply( [&] (BuildKind &kind) 
                                                      {
                                                       kinds[kindex].name=lang.pool.dup(kind.str);
                                                       kinds[kindex].index=kindex;
                                                       
                                                       kind.index=kindex++;
                                                      }
                                                );
                           }
                         
                         synt.index=index++;
                        } 
                  );
  }
  
  // elements
  {
   ulen len=LenAdd(lang.atoms.len,lang.synts.len);
   
   PtrLen<Element> elements=pool.createArray<Element>(len);
   
   lang.elements=elements;
   
   ulen index=0;
   
   for(Atom &atom : lang.atoms )
     {
      elements[index].name=atom.name;
      elements[index].index=index;
      elements[index].ptr=&atom;
      
      index++;
     }
   
   for(Synt &synt : lang.synts )
     {
      elements[index].name=synt.name;
      elements[index].index=index;
      elements[index].ptr=&synt;
      
      index++;
     }
  }
  
  // rules
  {
   ulen len=1;
   
   synt_list.apply( [&] (BuildSynt &synt) 
                        { 
                         synt.rule_off=len;
     
                         len=LenAdd(len,synt.rule_list.getCount()); 
                        } 
                  );
   
   PtrLen<Rule> rules=lang.pool.createArray<Rule>(len);
   
   lang.rules=rules;
   
   rules[0].name="<-";
   rules[0].index=0;
   
   PtrLen<Synt> synts=lang.synts;
   
   synt_list.apply( [&] (BuildSynt &synt) 
                        { 
                         ulen index=synt.index;
                         
                         synts[index].rules=Range_const(rules.part(synt.rule_off,synt.rule_list.getCount()));
                         
                         ulen rindex=synt.rule_off;
                         
                         synt.rule_list.apply( [&] (BuildRule &rule)
                                                   {
                                                    rules[rindex].name=lang.pool.dup(rule.str);
                                                    rules[rindex].index=rindex;
                                                    rules[rindex].ret=synts[index];
                                                    
                                                    if( rule.result_kind )
                                                      rules[rindex].kind=synts[index].kinds[rule.result_kind->index];
                                                    
                                                    if( +rule.cond )
                                                      rules[rindex].cond=buildCond(rule.cond);
                                                    
                                                    ulen alen=rule.element_list.getCount();
                                                    
                                                    PtrLen<Element> args=pool.createArray<Element>(alen);
                                                    
                                                    rules[rindex].args=Range_const(args);
                                                    
                                                    PtrLen<Element> elements=lang.elements;
                                                    
                                                    ulen eindex=0;
                                                    ulen delta=lang.atoms.len;
                                                    
                                                    rule.element_list.apply( [&] (BuildElement &element)
                                                                                 {
                                                                                  ulen i;
                                                                                  
                                                                                  if( BuildSynt *synt=element.synt )
                                                                                    {
                                                                                     i=synt->index+delta;
                                                                                    }
                                                                                  else
                                                                                    {
                                                                                     i=element.atom->index;
                                                                                    }
                                                                                  
                                                                                  args[eindex]=elements[i];
                                                                                  
                                                                                  eindex++;
                                                                                 }
                                                                           );
                                                    
                                                    rule.index=rindex++;
                                                   }
                                             );
                        } 
                  );
  }
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

