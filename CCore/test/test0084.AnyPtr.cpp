/* test0084.AnyPtr.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/AnyPtr.h>

namespace App {

namespace Private_0084 {

/* struct PrintVal */

struct PrintVal
 {
  template <class T>
  void operator () (T *ptr)
   {
    Printf(Con,"val = #;\n",*ptr);
   }
  
  template <class T>
  void operator () (T *ptr,int &a)
   {
    Printf(Con,"val = #; a = #;\n",*ptr,a);
   }
  
  template <class T>
  void operator () (T *ptr,short &&b)
   {
    Printf(Con,"val = #; b = #;\n",*ptr,b);
   }
 };

} // namespace Private_0084
 
using namespace Private_0084; 
 
/* Testit<84> */ 

template<>
const char *const Testit<84>::Name="Test84 AnyPtr";

template<>
bool Testit<84>::Main() 
 {
  {
   AnyPtr<int,short> ptr;
    
   int a=1;
   short b=2;
    
   ptr=&a;
    
   ptr.apply( PrintVal() );
   ptr.apply( PrintVal() ,a);
   ptr.apply( PrintVal() ,static_cast<short &&>(b));
   //ptr.apply( PrintVal() ,b);
    
   ptr.applyFor<int>( [] (int *ptr) { Printf(Con,"int val = #;\n",*ptr); } );
   ptr.applyFor<short>( [] (short *ptr) { Printf(Con,"short val = #;\n",*ptr); } );
   
   ptr=&b;
    
   ptr.apply( PrintVal() );
   
   ptr.applyFor<int>( [] (int *ptr) { Printf(Con,"int val = #;\n",*ptr); } );
   ptr.applyFor<short>( [] (short *ptr) { Printf(Con,"short val = #;\n",*ptr); } );
   
   ptr=Nothing;
   ptr=nullptr;
  }
  
  {
   AnyPtr_const<int,short> ptr;
    
   const int a=1;
   const short b=2;
    
   ptr=&a;
   
   int a1=1;
   short b1=2;
    
   ptr.apply( PrintVal() );
   ptr.apply( PrintVal() ,a1);
   ptr.apply( PrintVal() ,static_cast<short &&>(b1));
   //ptr.apply( PrintVal() ,b1);
    
   ptr.applyFor<int>( [] (const int *ptr) { Printf(Con,"int val = #;\n",*ptr); } );
   ptr.applyFor<short>( [] (const short *ptr) { Printf(Con,"short val = #;\n",*ptr); } );
   
   ptr=&b;
    
   ptr.apply( PrintVal() );
   
   ptr.applyFor<int>( [] (const int *ptr) { Printf(Con,"int val = #;\n",*ptr); } );
   ptr.applyFor<short>( [] (const short *ptr) { Printf(Con,"short val = #;\n",*ptr); } );
   
   ptr=Nothing;
   ptr=nullptr;
  }
  
  {
   AnyPtr<int,short> a,b;
   
   struct Ret
    {
     Ret() {}
     
     Ret(unsigned,unsigned) {}
    };
   
   struct Func
    {
     Ret operator () (int *,int *) { return Ret(); }
     
     Ret operator () (short *,short *) { return Ret(); }
    };
   
   AnyPtr<int,short>::Binary<Ret>(a,b,Func());
  }
  
  {
   AnyPtr_const<int,short> a,b;
   
   struct Ret
    {
     Ret() {}
     
     Ret(unsigned,unsigned) {}
    };
   
   struct Func
    {
     Ret operator () (const int *,const int *) { return Ret(); }
     
     Ret operator () (const short *,const short *) { return Ret(); }
    };
   
   AnyPtr_const<int,short>::Binary<Ret>(a,b,Func());
  }
  
  {
   int a=1;
   short b=2;
   
   AnyPtr<int,short> ptr_a(&a);
   const AnyPtr<int,short> ptr_b(&b);
   
   struct Func
    {
     void operator () (int *a,short *b)
      {
       Printf(Con,"int a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (int *a,int *b)
      {
       Printf(Con,"int a = #; int b = #;\n",*a,*b);
      }
     
     void operator () (short *a,short *b)
      {
       Printf(Con,"short a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (short *a,int *b)
      {
       Printf(Con,"short a = #; int b = #;\n",*a,*b);
      }
    };

   Func func;
   
   ElaborateAnyPtr(func,AnyPtr<int,short>(&a),static_cast<const AnyPtr<int,short> &&>(ptr_b));
  }
  
  {
   int a=1;
   short b=2;
   
   AnyPtr<int,short> ptr_a(&a);
   AnyPtr<int,short> ptr_b(&b);
   
   struct Func
    {
     void operator () (int *a,short *b,int &&)
      {
       Printf(Con,"int a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (int *a,int *b,int)
      {
       Printf(Con,"int a = #; int b = #;\n",*a,*b);
      }
     
     void operator () (short *a,short *b,int)
      {
       Printf(Con,"short a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (short *a,int *b,int)
      {
       Printf(Con,"short a = #; int b = #;\n",*a,*b);
      }
    };

   Func func;
   
   ElaborateAnyPtr(func,AnyPtr<int,short>(&a),ptr_b,0);
  }
  
  {
   const int a=1;
   const short b=2;
   
   AnyPtr_const<int,short> ptr_a(&a);
   const AnyPtr_const<int,short> ptr_b(&b);
   
   struct Func
    {
     void operator () (const int *a,const short *b)
      {
       Printf(Con,"int a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (const int *a,const int *b)
      {
       Printf(Con,"int a = #; int b = #;\n",*a,*b);
      }
     
     void operator () (const short *a,const short *b)
      {
       Printf(Con,"short a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (const short *a,const int *b)
      {
       Printf(Con,"short a = #; int b = #;\n",*a,*b);
      }
    };

   Func func;
   
   ElaborateAnyPtr(func,AnyPtr_const<int,short>(&a),ptr_b);
  }
  
  {
   const int a=1;
   const short b=2;
   
   AnyPtr_const<int,short> ptr_a(&a);
   const AnyPtr_const<int,short> ptr_b(&b);
   
   struct Func
    {
     void operator () (const int *a,const short *b,int)
      {
       Printf(Con,"int a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (const int *a,const int *b,int)
      {
       Printf(Con,"int a = #; int b = #;\n",*a,*b);
      }
     
     void operator () (const short *a,const short *b,int)
      {
       Printf(Con,"short a = #; short b = #;\n",*a,*b);
      }
     
     void operator () (const short *a,const int *b,int)
      {
       Printf(Con,"short a = #; int b = #;\n",*a,*b);
      }
    };

   Func func;
   
   ElaborateAnyPtr(func,ptr_a,static_cast<const AnyPtr_const<int,short> &&>(ptr_b),0);
  }
  
  return true;
 }
 
} // namespace App
 
