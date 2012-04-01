/* DirTreeRun.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/DirTreeRun.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class DirTreeRun::Path */

DirTreeRun::Path::Path(StrLen base,StrLen dir)
 {
  if( base.len>=MaxPathLen || dir.len>=MaxPathLen-base.len )
    {
     Printf(Exception,"CCore::DirTreeRun::Path::Path(...) : too long path");
    }
    
  off=base.len+1;
  len=base.len+1+dir.len;
  
  base.copyTo(buf);  
  
  buf[base.len]='/';
  
  dir.copyTo(buf+base.len+1);
 }

/* class DirTreeRun::Node */

DirTreeRun::Node::Node(Node *next_,FileSystem &fs,StrLen base,StrLen dir,void *data_)
 : next(next_),
   path(base,dir),
   cur(fs,path.getPath()),
   data(data_)
 {
 }

DirTreeRun::Node::~Node()
 {
 }

DirTreeRun::Node * DirTreeRun::Node::destroy()
 {
  Node *ret=next;
  
  delete this;
  
  return ret;
 }

/* class DirTreeRun */

void DirTreeRun::push(StrLen base,StrLen dir,void *data)
 {
  top=new Node(top,fs,base,dir,data);
 }
 
void DirTreeRun::pop()
 {
  top=top->destroy();
 }

DirTreeRun::DirTreeRun(StrLen root_)
 : root(root_),
   top(0)
 {
 }
   
DirTreeRun::~DirTreeRun()
 {
  Node *node=Replace_null(top);
  
  while( node ) node=node->destroy();
 }

} // namespace CCore
 

