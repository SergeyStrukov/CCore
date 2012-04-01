/* test0048.Tuple.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Tuple.h>

#include <typeinfo>

namespace App {

namespace Private_0048 {

/* struct Acc */

struct Acc : NoCopy
 {
  int sum;
  
  Acc() : sum(0) {}
  
  void operator () ()
   {
   }
  
  template <class T,class ... TT>
  void operator () (T t,TT ... tt)
   {
    sum+=t;
    
    operator () (tt...);
   }
 };

/* struct Int */

struct Int : NoCopy
 {
  int val;
  
  explicit Int(int val_) : val(val_) {}
 };

/* Show() */

template <class ... SS> struct Show;

template <>
struct Show<>
 {
  static void show()
   {
    Printf(Con,"\n");
   }
 };

template <class S,class ... SS>
struct Show<S,SS...>
 {
  static void show()
   {
    Printf(Con,"#; ,",typeid(S).name());
    
    Show<SS...>::show();
   }
 };

template <class S,class ... SS>
struct Show<S &,SS...>
 {
  static void show()
   {
    Printf(Con,"#; & ,",typeid(S).name());
    
    Show<SS...>::show();
   }
 };

template <class S,class ... SS>
struct Show<S &&,SS...>
 {
  static void show()
   {
    Printf(Con,"#; && ,",typeid(S).name());
    
    Show<SS...>::show();
   }
 };

/* Take() */

template <class ... SS>
void Take1(SS && ...)
 {
  Show<SS...>::show();
 }

template <class ... SS>
void Take(SS && ... ss)
 {
  Show<SS...>::show();
  
  Take1(ss...);
  
  // Tuple<SS && ...> t(ss...); // error
 }

template <class ... SS>
void TakeL1(SS & ...)
 {
  Show<SS...>::show();
 } 
  
template <class ... SS>
void TakeL(SS & ... ss)
 {
  Show<SS...>::show();
  
  TakeL1(ss...);
 }

template <class ... SS>
void TakeCL1(const SS & ...)
 {
  Show<SS...>::show();
 } 
  
template <class ... SS>
void TakeCL(const SS & ... ss)
 {
  Show<SS...>::show();
  
  TakeCL1(ss...);
 }

} // namespace Private_0048
 
using namespace Private_0048; 
 
/* Testit<48> */ 

template<>
const char *const Testit<48>::Name="Test48 Tuple";

template<>
bool Testit<48>::Main() 
 {
  auto t=MakeTuple(1,2,3,4,5);
  
  Acc acc;
  
  t.call(FunctorRef(acc));
  
  Printf(Con,"sum = #;\n",acc.sum);

  int v1=10;
  Int v2(2);
  
  Take(1,v1,Int(1),v2);
  TakeL(v1,v2);
  TakeCL(1,v1,Int(1),v2);
  
  return true;
 }
 
} // namespace App
 
