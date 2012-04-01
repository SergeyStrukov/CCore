/* DirTreeRun.h */ 
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

#ifndef CCore_inc_DirTreeRun_h
#define CCore_inc_DirTreeRun_h

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* classes */

class DirTreeRun;

/* class DirTreeRun */ 

//
// class Proc
//  {
//   public:
//
//    typedef ??? DataType;
//
//    DataType * dir(StrLen root); // name=="." , parent_data==0
//
//    DataType * dir(StrLen path,StrLen name,DataType *parent_data);
//
//    void file(StrLen path,StrLen name,DataType *parent_data);
//
//    void enddir(StrLen path,StrLen name,DataType *data);
//  };
//

class DirTreeRun : NoCopyBase<PathBase>
 {
   class Path;
   class Node;
       
   FileSystem fs;
   StrLen root;
   Node *top;
   
  private:
  
   static bool IsSpecial(StrLen name) { return IsDot(name) || IsDotDot(name) ; }
   
   void push(StrLen base,StrLen dir,void *data);
    
   void pop();
    
  public:
  
   explicit DirTreeRun(StrLen root);
   
   ~DirTreeRun();
   
   StrLen pathOfRoot(char buf[MaxPathLen+1]) { return fs.pathOf(root,buf); }
   
   template <class Proc>
   void apply(Proc &proc);
 };

class DirTreeRun::Path : NoCopy
 {
   char buf[MaxPathLen];
   ulen off;
   ulen len;
   
  public: 
  
   Path(StrLen base,StrLen dir);
   
   StrLen getPath() const { return StrLen(buf,len); }
   
   StrLen getBase() const { return StrLen(buf,off-1); }
   
   StrLen getDir() const { return StrLen(buf+off,len-off); }
 };

class DirTreeRun::Node : public MemBase_nocopy
 {
   Node *next;
   Path path;
   FileSystem::DirCursor cur;
   void *data; 
   
  public:
  
   Node(Node *next,FileSystem &fs,StrLen base,StrLen dir,void *data);
   
   ~Node();
    
   Node * destroy();
    
   StrLen getPath() const { return path.getPath(); }
   
   StrLen getBase() const { return path.getBase(); }
    
   StrLen getDir() const { return path.getDir(); } 
   
   bool nextFile() { return cur.next(); }

   StrLen getFileName() const { return cur.getFileName(); }

   FileType getFileType() const { return cur.getFileType(); }

   template <class DataType>
   DataType * getData() const { return static_cast<DataType *>(data); }
 };   

template <class Proc>   
void DirTreeRun::apply(Proc &proc)
 {
  typedef typename Proc::DataType DataType;
  
  push(root,".",proc.dir(root));
  
  while( top )
    {
     while( top->nextFile() )
       {
        StrLen path=top->getPath();
        StrLen name=top->getFileName();
        DataType *parent_data=top->getData<DataType>();
        
        if( top->getFileType()==FileType_file )
          {
           proc.file(path,name,parent_data);
          }
        else
          {
           if( IsSpecial(name) ) continue;
           
           push(path,name, proc.dir(path,name,parent_data) );
          }
       }
     
     proc.enddir(top->getBase(),top->getDir(),top->getData<DataType>()); 
       
     pop(); 
    }
 }

} // namespace CCore
 
#endif
 

