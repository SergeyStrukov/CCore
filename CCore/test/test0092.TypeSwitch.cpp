/* test0092.TypeSwitch.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/TypeSwitch.h>

namespace App {

namespace Private_0092 {

template <unsigned Ind> 
struct Node
 {
  template <class P>
  static void Print(P &out)
   {
    Printf(out,"Node<#;>\n",Ind);
   }
 };

template <class ... CC> struct PrintList;

template <class C,class ... CC> 
struct PrintList<C,CC...>
 {
  template <class P>
  static void Print(P &out)
   {
    C::Type::Print(out);
    
    PrintList<CC...>::Print(out);
   }
 };

template <> 
struct PrintList<>
 {
  template <class P>
  static void Print(P &)
   {
   }
 };

template <class CaseList> struct PrintCaseList;

template <class ... CC>
struct PrintCaseList<Meta::CaseList<CC...> >
 {
  template <class P>
  static void Print(P &out)
   {
    PrintList<CC...>::Print(out);
    
    Putch(out,'\n');
   }
 };

template <class CaseList,ulen Len>
struct PrintSplit
 {
  template <class P>
  static void Print(P &out)
   {
    PrintSplit<CaseList,Len-1>::Print(out);
    
    Printf(out,"-----\n\n");
    
    PrintCaseList<typename Meta::SplitCaseOf<Len,CaseList>::First>::Print(out);
    
    Putch(out,'\n');
    
    PrintCaseList<typename Meta::SplitCaseOf<Len,CaseList>::Last>::Print(out);
   }
 };

template <class CaseList>
struct PrintSplit<CaseList,0>
 {
  template <class P>
  static void Print(P &out)
   {
    PrintCaseList<typename Meta::SplitCaseOf<0,CaseList>::First>::Print(out);
    
    Putch(out,'\n');
    
    PrintCaseList<typename Meta::SplitCaseOf<0,CaseList>::Last>::Print(out);
   }
 };

template <unsigned Len>
struct MakeCaseList
 {
  using Ret = typename Meta::CaseListJoin<typename MakeCaseList<Len-1>::Ret,Meta::CaseList<Meta::Case<unsigned,Len,Node<Len> > > >::Ret ;
  
  static void test1()
   {
    PrintCon out(Con);
    
    PrintCaseList<Ret>::Print(out);
   }
  
  static void test2()
   {
    PrintCon out(Con);
    
    PrintSplit<Ret,Len>::Print(out);
   }

  struct Ctx
   {
    using RetType = void ;
    
    template <class T>
    static void call()
     {
      PrintCon out(Con);
      
      T::Print(out);
     }
    
    static void defcall(unsigned sw)
     {
      Printf(Con,"default #;\n",sw);
     }
   };
  
  static void test3()
   {
    PrintCon out(Con);
    
    for(unsigned sw=0; sw<=Len ;sw++)
      Meta::TypeSwitch<Ret>::Switch(sw,Ctx());
   }
 };

template <>
struct MakeCaseList<0>
 {
  using Ret = Meta::CaseList<> ;
 };

void test1()
 {
  MakeCaseList<100>::test1();  
 }

void test2()
 {
  MakeCaseList<10>::test2();  
 }

void test3()
 {
  MakeCaseList<100>::test3();
 }

} // namespace Private_0092
 
using namespace Private_0092; 
 
/* Testit<92> */ 

template<>
const char *const Testit<92>::Name="Test92 TypeSwitch";

template<>
bool Testit<92>::Main() 
 {
  //test1();
  //test2();
  test3();
  
  return true;
 }
 
} // namespace App
 
