/* RawinMsgProc.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/rawin/RawinMsgProc.h>
 
namespace CCore {
namespace Rawin {

/* struct TraceMsg */  

struct TraceMsg::BeginTrace
 {
  TraceMsg *trace;
  PrintResultFunc func;
  
  explicit BeginTrace(TraceMsg *trace_) : trace(trace_) {}
  
  template <class M>
  void handle(ProcMsgBase *,M msg)
   {
    func=trace->trace(msg);
   }
 };
 
auto TraceMsg::begin_trace(const ProcMsgBase &proc_) -> PrintResultFunc
 {
  BeginTrace obj(this);
  
  ProcMsg<BeginTrace> proc(proc_,&obj);
  
  proc.handle();
  
  return obj.func;
 }
   
void TraceMsg::end_trace(const ProcMsgBase &proc,PrintResultFunc func)
 {
  level--;
    
  indent();
     
  func(out,proc);
  
  endLine();
 }
 
TraceMsg::Op::Op(TraceMsg &trace_,const ProcMsgBase &proc_,bool enable) 
 : trace(trace_),
   proc(proc_) 
 {
  if( enable )
    func=trace.begin_trace(proc);
  else  
    func=0;
 }
     
TraceMsg::Op::~Op()
 {
  try
    {
     if( func )
       trace.end_trace(proc,func);
    }
  catch(CatchType) 
    {
    } 
 }
 
} // namespace Rawin
} // namespace CCore
 

