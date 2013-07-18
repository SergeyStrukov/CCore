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

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Exception.h>

namespace App {

/* class Lang::Builder */

class Lang::Builder : NoCopy
 {
   Lang &lang;
   
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
   
   struct BuildCondAND
    {
     BuildCond a;
     BuildCond b;
    };
   
   struct BuildCondOR
    {
     BuildCond a;
     BuildCond b;
    };
   
   struct CondNOT
    {
     BuildCond a;
    };
   
   struct CondEQ
    {
     StrLen a;
     StrLen b;
    };
   
   struct CondNE
    {
     StrLen a;
     StrLen b;
    };
   
   struct CondGT
    {
     StrLen a;
     StrLen b;
    };
   
   struct CondGE
    {
     StrLen a;
     StrLen b;
    };
   
   struct CondLT
    {
     StrLen a;
     StrLen b;
    };
   
   struct CondLE
    {
     StrLen a;
     StrLen b;
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
   
   void startSynt(StrLen name,bool is_lang);
   
   void addKind(StrLen name);
   void endKinds();
   
   void addElement(StrLen elem);
   void endElements();
   
   void rule(BuildCond cond);
   void rule(StrLen name);
   void result(StrLen name);
   
   void endSynt();
   
   void endLang();
   
   template <class ... TT>
   static void error(const char *format,const TT & ... tt)
    {
     Printf(Exception,format,tt...);
    }
   
  public:
 
   explicit Builder(Lang &lang);
   
   ~Builder();
 };

auto Lang::Builder::condOR(BuildCond a,BuildCond b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condAND(BuildCond a,BuildCond b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condNOT(BuildCond a) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condEQ(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condNE(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condGT(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condGE(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condLT(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

auto Lang::Builder::condLE(StrLen a,StrLen b) -> BuildCond
 {
  return Null;
 }

void Lang::Builder::startSynt(StrLen name,bool is_lang)
 {
  Printf(Con,"startSynt(#.q;,#;)\n",name,is_lang);
 }

void Lang::Builder::addKind(StrLen name)
 {
  Printf(Con,"addKind(#.q;)\n",name);
 }

void Lang::Builder::endKinds()
 {
  Printf(Con,"endKinds()\n");
 }

void Lang::Builder::addElement(StrLen elem)
 {
  Printf(Con,"addElement( #; )\n",elem);
 }

void Lang::Builder::endElements()
 {
  Printf(Con,"endElements()\n");
 }

void Lang::Builder::rule(BuildCond cond)
 {
  Printf(Con,"rule( cond )\n");
 }

void Lang::Builder::rule(StrLen name)
 {
  Printf(Con,"rule(#.q;)\n",name);
 }

void Lang::Builder::result(StrLen name)
 {
  Printf(Con,"result(#.q;)\n",name);
 }

void Lang::Builder::endSynt()
 {
  Printf(Con,"endSynt()\n");
 }

void Lang::Builder::endLang()
 {
  Printf(Con,"endLang()\n");
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

