/* LangTestMain.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>

#include "Parser.gen.h"
#include "Generator.gen.h"

namespace App {

/* using */ 

using namespace CCore;

using namespace DEF_LANG;

/* functions */

void InternalGuard(const char *msg)
 {
  Printf(Exception,"Internal fault : #;",msg);
 }

/* class Stack<T> */  

template <class T>
class Stack : NoCopy
 {
   DynArray<T> array;
  
   T *ptr,*lim,*end;
   
  public:
  
   Stack() { ptr=lim=end=0; }
   
   ~Stack() {}
   
   ulen getLen() const { return Dist(ptr,lim); }
   
   void clean() { lim=ptr; }
   
   void push(T x);
   
   T top() const
    {
     if( ptr==lim ) InternalGuard("Underflow");
     
     return lim[-1];
    }
   
   void pop(ulen count)
    {
     if( count>getLen() ) InternalGuard("Underflow");
     
     lim-=count;
    }
    
   T operator [] (ulen i) const { return ptr[i]; }
 };
 
template <class T>
void Stack<T>::push(T x)
 {
  if( lim>=end )
    {
     ulen len=getLen();
     
     array.extend_default(Max<ulen>(len,1000));
     
     ptr=array.getPtr();
     lim=ptr+len;
     end=ptr+array.getLen();
    }
  
  *(lim++)=x;
 }

/* class Generator */ 

class Generator : GeneratorProp
 {
   Random random;
   Stack<const NRTIndex *> stack;
   const NRTIndex *cur;
   ulen stack_lim;
   ulen gen_lim;
   ulen gen_count;
   
  private: 
   
   const NRTIndex * chooseStart();
   
   const NRTIndex * choose(NRTIndex);
   
  public:
  
   Generator(ulen stack_lim_,ulen gen_lim_) 
    : stack_lim(stack_lim_),
      gen_lim(gen_lim_),
      gen_count(0)
    { 
     start(); 
    }
   
   ~Generator() {}
   
   void start();
   
   RTIndex next();
 };
 
const NRTIndex * Generator::chooseStart()
 {
  return choose(StartTable[random.select(DimOf(StartTable))]); 
 }

const NRTIndex * Generator::choose(NRTIndex i)
 {
  NTRec rec=NTable[i-NRTIndexNonTerminal];
  
  if( stack.getLen()>stack_lim || !gen_count ) return rec.list[0];
  
  return rec.list[random.select(rec.list_len)];
 }
   
void Generator::start()
 {
  gen_count=gen_lim;
  
  stack.clean();
  
  cur=chooseStart();
 }
  
RTIndex Generator::next()
 {
  if( gen_count ) gen_count--;
  
  for(;;)
    {
     if( NRTIndex i=*cur )
       {
        if( isNonTerminal(i) )
          {
           stack.push(cur+1);
           
           cur=choose(i);
          }
        else
          {
           cur++;
           
           return toRTIndex(i);
          }
       }
     else
       {
        if( stack.getLen() )
          {
           cur=stack.top();
           
           stack.pop(1);
          }
        else
          {
           return RTIndexEnd;
          }
       }
    } 
 }

/* class Parser */  

class Parser
 {
   Stack<const State *> stack;
   
  public:
  
   Parser() { start(); }
   
   ~Parser() {}
   
   void start()
    {
     stack.clean();
     
     stack.push(State::GetBegin());
    }
    
   RIndex next(TIndex);
 };

RIndex Parser::next(TIndex t)
 {
  const RuleProp *prop=stack.top()->final(t);
  
  if( !prop ) InternalGuard("Parser::next");
  
  stack.pop(prop->length);
     
  if( const State *s=stack.top()->transition(prop->result) ) stack.push(s);
     
  return prop->rule;
 }
 
/* class Run */ 

#if 0

typedef PrintFile OutType;

static const char *const OutInit = "Test.txt" ;

#else

typedef NoPrintType OutType;

const NoPrintType OutInit = NoPrint ;

#endif

class Run
 {
   OutType out;
   
   Generator gen;
   Parser parser;
   
   Stack<RIndex> buf;
   
  private: 
 
   bool step();
 
  public:
  
   Run();
   
   ~Run();
   
   int run(ulen cnt);
 };

bool Run::step()
 {
  gen.start();
  parser.start();
  
  RTIndex i;
  
  for(;;)
    {
     i=gen.next();
    
     if( isRule(i) )
       {
        RIndex r=toRIndex(i);
       
        buf.push(r);
       }
     else
       {
        TIndex t=toTIndex(i);
        ulen buf_ind=0;
        
        while( RIndex r=parser.next(t) )
          if( buf_ind>=buf.getLen() ) 
            {
             Printf(out,"#; mismatch #;\n",r,t);
             
             return true;
            }
          else if( buf[buf_ind]!=r )
            {
             Printf(out,"#; mismatch #;\n",r,buf[buf_ind]);
             
             return true;
            }
          else  
            {
             Printf(out,"#;\n",r);
             
             buf_ind++;
            }
            
       if( buf_ind<buf.getLen() ) 
         {
          Printf(out,"#; mismatch #;\n",t,buf[buf_ind]);
             
          return true;
         }
         
        buf.clean(); 
          
        Printf(out,"#;\n",t);
       }
       
     if( !i ) break; 
    }

  Putobj(out,"------------------\n");
    
  return false;
 }
 
Run::Run() 
 : out(OutInit),
   gen(1000,100000)
 {
 }

Run::~Run()
 {
 }
   
int Run::run(ulen cnt)
 {
  Printf(Con,"Start testing ...\n\n");
  
  for(; cnt ;cnt--)
    {
     if( (cnt%100)==0 )
       Printf(Con," step #;\n",cnt);
     
     if( step() )
       {
        Printf(Con,"\nfailure\n");
  
        return 1;
       }
    }

  Printf(Con,"\nsuccess\n");
  
  return 0;
 }
   
} // namespace App 
   
/* main() */ 

using namespace CCore;

int main()
 {
  try
    {
     ReportException report;
    
     {
      App::Run run;
      
      return run.run(10000);
     } 
     
     report.guard();
    }
  catch(CatchType)   
    {
     return 1;
    }
  
  return 0;
 }

