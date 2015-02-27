/* test2.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/Win32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/TickTimer.h>

#include <CCore/inc/task/TaskEvent.h>

#include "Malevich.h"

namespace App2 {

/* using */ 

using namespace App;

/* classes */

class FileReport;

class Application;

class StreamFile;

/* class FileReport */

class FileReport : public ReportException
 {
   PrintFile out;
   
  private: 
 
   virtual void print(StrLen str)
    {
     Putobj(out,str);
    }
   
   virtual void end()
    {
     Printf(out,"\n\n#;\n\n",TextDivider());
    }
   
  public:
  
   FileReport() : out("exception-log.txt") {}
   
   ~FileReport() {}
   
   bool show() { return true; }
 };

/* class Application */

class Application : NoCopy
 {
   FileReport report;
   
   Desktop *desktop;
 
   MalevichWindow main_win;
   MalevichWindow win1;
   MalevichWindow win2;
   MalevichWindow win3;
   
  private:
   
   bool pump()
    {
     try
       {
        report.clear();
           
        if( desktop->pump() )
          {
           report.guard();
             
           return true;
          }
        else
          {
           return false;
          } 
       }
     catch(CatchType) 
       {
        if( !report.show() )
          {
           main_win.destroy();
          }
           
        return true;
       } 
    }
   
   void tick()
    {
     try
       {
        report.clear();
        
        TickEntryEvent();
           
        main_win.tick();
        win1.tick();
        win2.tick();
        win3.tick();
        
        TickLeaveEvent();
           
        report.guard();
       }
     catch(CatchType) 
       {
        if( !report.show() )
          {
           main_win.destroy();
          }
       } 
    }
   
  public: 
   
   explicit Application(Desktop *desktop_=DefaultDesktop)
    : desktop(desktop_),
      main_win(desktop_),
      win1(desktop_),
      win2(desktop_),
      win3(desktop_)
    {
    }
   
   ~Application()
    {
    }
   
   int run(CmdDisplay cmd_display)
    {
     Point max_size=desktop->getScreenSize();
     
     main_win.createMain(cmd_display,max_size);
     
     win1.create(Pane(100,100,300,200),max_size);
     
     win2.create(win1.getControl(),Pane(150,150,300,200),max_size);
     win3.create(win1.getControl(),Pane(200,200,300,200),max_size);
     
     report.guard();
     
     TickTimer timer(500_msec);
     
     while( pump() )
       {
        if( timer.poll() ) tick();
        
        desktop->wait(timer.remains());
       }
     
     report.guard();
     
     return 0;
    }
 };

/* class StreamFile */

class StreamFile : NoCopy , public PutDevBase<StreamFile>
 {
   static const ulen BufLen = 64_KByte ;
 
   RawFileToPrint file;
   DynArray<uint8> buf;
   FileError flush_error;
   bool no_flush_exception;
   
   PtrLen<uint8> out;
   bool has_data;   
   
  private:
   
   void provide();
   
  public: 
   
   // constructors
  
   StreamFile();
   
   explicit StreamFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~StreamFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void disableExceptions() 
    { 
     if( !no_flush_exception )
       {
        no_flush_exception=true; 
        
        flush_error=FileError_Ok;
       }
    }
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { file.preserveFile(); }
   
   // put
   
   void do_put(uint8 value)
    {
     if( !out ) provide();
    
     *out=value;
    
     ++out;
    }
   
   void do_put(const uint8 *ptr,ulen len);
   
   PtrLen<uint8> do_putRange(ulen len);
   
   void flush();
 };

StreamFile::StreamFile()
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
 }

StreamFile::StreamFile(StrLen file_name,FileOpenFlags oflags)
 : buf(BufLen),
   no_flush_exception(false),
   has_data(false)
 {
  open(file_name,oflags);
 }

StreamFile::~StreamFile()
 {
  if( isOpened() )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"StreamFile::~StreamFile() : #;",errout);
       }
    }
 }

void StreamFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( FileError error=file.open(file_name,oflags) )
    {
     Printf(Exception,"StreamFile::open(#.q;,#;) : #;",file_name,oflags,error);
    }
    
  no_flush_exception=false;  
 }

void StreamFile::soft_close(FileMultiError &errout)
 {
  if( isOpened() ) 
    {
     disableExceptions();
 
     flush();
  
     errout.add(flush_error);
  
     file.close(errout);
    }
  else 
    {
     errout.add(FileError_NoMethod);
    }
 }

void StreamFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"StreamFile::close() : #;",errout);
    }
 }

void StreamFile::provide()
 {
  if( !isOpened() ) 
    {
     Printf(Exception,"StreamFile::provide(...) : file is not opened");
    }
  
  flush();
  
  out=Range(buf);
  has_data=true;
 }

void StreamFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len); 
  
  while( +src )
    {
     if( !out ) provide();
     
     ulen delta=Min(src.len,out.len);
     
     (out+=delta).copy( (src+=delta).ptr );
    }
 }

PtrLen<uint8> StreamFile::do_putRange(ulen)
 {
  Printf(Exception,"StreamFile::do_putRange(...) : not supported");
  
  return Nothing;
 }

void StreamFile::flush()
 {
  if( !has_data ) return;
  
  ulen len=buf.getLen()-out.len;
  
  out=Nothing;
  has_data=false;
  
  if( !len ) return;
  
  if( FileError error=file.write(buf.getPtr(),len) )
    {
     if( no_flush_exception )
       {
        flush_error=error;
       }
     else
       {  
        Printf(Exception,"StreamFile::flush(...) : #;",error);
       }
    }
 }

/* testmain() */

int testmain(CmdDisplay cmd_display)
 {
  int ret;
  
  TaskEventRecorder recorder(100_MByte);
  
  try
    {
     TickTask tick_task;
     TaskEventHostType::StartStop start_stop(TaskEventHost,&recorder);
     
     Application app;
    
     ret=app.run(cmd_display);
    }
  catch(CatchType)
    {
     return 1;
    }
  
  StreamFile dev("test2.bin");
  
  dev(recorder);
  
  return ret;
 }
 
} // namespace App2
 
 
 


