/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
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

#include <inc/Target.h>
#include <inc/ArmCore.h>

namespace App {

/* using */

using namespace ARMCore;

/* classes */

class NanoLog;

class Log;

class Engine;

/* class NanoLog */ 
 
class NanoLog : NoCopy
 {
  public:
  
   NanoLog() {}
   
   ~NanoLog() {}
   
   // switch mode
   
   void toPrefetchAbort(Word PC) { Used(PC); }
   
   void toIRQ(Word PC) { Used(PC); }
   
   void toFIQ(Word PC) { Used(PC); }
   
   void toSVC(Word PC) { Used(PC); }
   
   void cmdUndefined(Word PC,Word cmd) { Used(PC); Used(cmd); }
   
   void dataAbort(Word PC,Word address,MemTag tag) { Used(PC); Used(address); Used(tag); }
   
   // trace
   
   template <class ... TT>
   void trace(Word PC,const char *format,const TT & ...) { Used(PC); Used(format); }
   
   template <class ... TT>
   void trace(const char *format,const TT & ...) { Used(format); }
   
   template <class ... TT>
   void stat(const char *format,const TT & ... tt) 
    {
     Printf(Con,"\n#;\n\n",Title("CPU stat"));
     
     Printf(Con,format,tt...);
     
     Printf(Con,"\n#;\n",TextDivider());
    }
   
   // execute

   void reset() {}
   
   void step() {}
 };
 
/* class Log */

class Log : NoCopy
 {
   PrintFile out;
   
  public:
  
   explicit Log(StrLen log_name) : out(log_name) {}
  
   ~Log() {}
  
   // switch mode
  
   void toPrefetchAbort(Word PC) 
    {
     Printf(out,"#8.16i;> Prefetch Abort\n",PC);
    }
   
   void toIRQ(Word PC) 
    {
     Printf(out,"#8.16i;> IRQ\n",PC);
    }
   
   void toFIQ(Word PC) 
    { 
     Printf(out,"#8.16i;> FIQ\n",PC);
    }
  
   void toSVC(Word PC) 
    { 
     Printf(out,"#8.16i;> SVC\n",PC);
    }
  
   void cmdUndefined(Word PC,Word cmd) 
    { 
     Printf(out,"#8.16i;> Undefined Command #8.16i;\n",PC,cmd);
    }
  
   void dataAbort(Word PC,Word address,MemTag tag) 
    { 
     Used(PC);
     
     Printf(out,"   Data Abort, address = #8.16i; #;\n",address,tag);
    }
  
   // trace
  
   template <class ... TT>
   void trace(Word PC,const char *format,const TT & ... tt)
    {
     Printf(out,"#8.16i;> ",PC);
     
     Printf(out,format,tt...);
     
     Putch(out,'\n');
    }
  
   template <class ... TT>
   void trace(const char *format,const TT & ... tt)
    {
     Putobj(out,"   ");
     
     Printf(out,format,tt...);
     
     Putch(out,'\n');
    }
  
   template <class ... TT>
   void stat(const char *format,const TT & ... tt)
    {
     Printf(out,"\n#;\n\n",Title("CPU stat"));
     
     Printf(out,format,tt...);
     
     Printf(out,"\n#;\n",TextDivider());
    }
  
   // execute

   void reset() 
    {
     Printf(out,"#;\n\n",Title("Reset"));
    }
  
   void step() 
    {
     // do nothing
    }
 };

/* class Engine */

class Engine : NoCopy
 {
   const char *file_name;
   const char *log_name;
 
  public:
  
   Engine(int argc,const char *argv[])
    : file_name(0),
      log_name(0)
    {
     Putobj(Con,"--- ARMGo 0.50 ---\n--- Copyright (c) 2012 Sergey Strukov. All rights reserved. ---\n\n");
     
     if( argc==2 )
       {
        file_name=argv[1];
       }
     else if( argc==3 )
       {
        file_name=argv[1];
        log_name=argv[2];
       }
     else  
       {
        Printf(Con,"Usage: ARMGo.exe <file-name> [<log-name>]\n\n");
       }
    }
   
   ~Engine()
    {
     Printf(Con,"#;\n\n",Title("the end"));
    }
    
   void run()
    {
     if( !file_name ) return;
     
     Printf(Con,"image = #.q;\n\n",file_name);
     
     if( log_name )
       {
        Printf(Con,"log = #.q;\n\n",log_name);
        
        Cpu<Memory<Target>,Log> cpu(file_name,log_name);

        cpu.run();
       }
     else
       {
        Printf(Con,"no log\n\n");
        
        Cpu<Memory<Target>,NanoLog> cpu(file_name);

        cpu.run();
       }   
    } 
 };
 
} // unnamed namespace
 
/* main() */ 

using namespace App;

int main(int argc,const char *argv[]) 
 { 
  ReportException report;

  try
    {
     {
      Engine engine(argc,argv);
  
      engine.run();
     }

     report.guard();

     return 0;
    }
  catch(CatchType)   
    {
     return 1;
    }
 }

