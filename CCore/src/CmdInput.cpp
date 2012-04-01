/* CmdInput.cpp */ 
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
 
#include <CCore/inc/CmdInput.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class CmdInput */ 

void CmdInput::add(StrLen cmd,TargetMethod method)
 {
  if( locked )
    {
     Printf(Exception,"CCore::CmdInput::add(...) : locked");
    }
    
  list.append_fill(cmd,method);  
 }
 
auto CmdInput::getCur() const -> Frame
 {
  if( off>0 ) return frame_list[off-1];
    
  return Frame(list.getLen());
 }
  
CmpResult CmdInput::cmp(ulen ind,char ch) const
 {
  if( list[ind].cmd.len<=off ) return CmpLess;
  
  return Cmp(list[ind].cmd[off],ch);
 } 
 
ulen CmdInput::findMin(Frame cur,char ch) const 
 {
  while( cur.getCount()>1 )
    {
     ulen med=cur.getMed();
     
     switch( cmp(med,ch) )
       {
        case CmpLess :
         {
          cur.ind=med+1;
         }
        break;
        
        default: // CmpEqual
         {
          cur.lim=med;
         }
       }
    }
    
  if( !cur ) return cur.ind; 
  
  if( cmp(cur.ind,ch)==CmpEqual ) return cur.ind;
  
  return cur.lim;
 }
  
ulen CmdInput::findMax(Frame cur,char ch) const 
 {
  while( cur.getCount()>1 )
    {
     ulen med=cur.getMed();
     
     switch( cmp(med,ch) )
       {
        case CmpGreater :
         {
          cur.lim=med;
         }
        break;
        
        default: // CmpEqual
         {
          cur.ind=med+1;
         }
       }
    }
    
  if( !cur ) return cur.ind; 
  
  if( cmp(cur.ind,ch)==CmpEqual ) return cur.lim;
  
  return cur.ind;
 }
  
auto CmdInput::find(Frame cur,char ch) const -> Frame
 {
  if( !cur ) return Nothing;

  while( cur.getCount()>1 )
    {
     ulen med=cur.getMed();
     
     switch( cmp(med,ch) )
       {
        case CmpLess :
         {
          cur.ind=med+1;
         }
        break;
        
        case CmpGreater :
         {
          cur.lim=med;
         }
        break;
        
        default: // CmpEqual
         {
          ulen ind=findMin(Frame(cur.ind,med),ch);
          
          ulen lim=findMax(Frame(med+1,cur.lim),ch);
          
          return Frame(ind,lim);
         }
       }
    }

  if( +cur && cmp(cur.ind,ch)==CmpEqual ) return cur;
  
  return Nothing;
 }
  
auto CmdInput::find(Frame cur) const -> Frame
 {
  if( !cur ) return Nothing;
  
  ulen ind=cur.ind;

  while( cur.getCount()>1 )
    {
     ulen med=cur.getMed();
     
     if( list[med].cmd.len>off )
       {
        cur.lim=med;
       }
     else
       {
        cur.ind=med+1;
       }  
    }
    
  if( !cur ) return Frame(ind,cur.ind); 
  
  if( list[cur.ind].cmd.len==off ) return Frame(ind,cur.lim);
  
  return Frame(ind,cur.ind);
 }
  
 // constructors

CmdInput::CmdInput(Target &target_)
 : target(target_),
   list(DoReserve,50)
 {
  locked=false;
  
  target_.buildCmdList(*this);
  
  locked=true;
  
  Sort(Range(list));
  
  ulen max_len=0;
  
  for(auto r=Range(list); +r ;++r) Replace_max(max_len,r->cmd.len);
  
  frame_list.extend_default(max_len);

  start();
 }
   
CmdInput::~CmdInput()
 {
 }
   
 // methods

bool CmdInput::put(char ch)
 {
  if( off>=frame_list.getLen() )
    {
     off++;
     
     return false;
    }
    
  Frame cur=getCur();
  Frame next=find(cur,ch);
    
  frame_list[off++]=next;
    
  return +next;
 }
 
auto CmdInput::complete() const -> CompleteResult
 {
  if( off>frame_list.getLen() ) return Nothing;
  
  Frame cur=getCur();
  
  if( !cur ) return Nothing;
  
  ulen count=cur.getCount();
  
  if( count>1 ) return count;
  
  return list[cur.ind].cmd.part(off);
 }
   
auto CmdInput::finish() -> FinishResult
 {
  if( off>frame_list.getLen() ) return Nothing;
  
  Frame cur=find(getCur());
  
  if( !cur ) return Nothing;
  
  return FinishResult(target,list[cur.ind].method);
 }
 
} // namespace CCore
 

