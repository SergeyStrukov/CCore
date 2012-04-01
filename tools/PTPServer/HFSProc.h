/* HFSProc.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef PTPServer_HFSProc_h
#define PTPServer_HFSProc_h

#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/sys/SysFile.h>
#include <CCore/inc/sys/SysFileSystem.h>

#include <CCore/inc/net/HFSBase.h>

#include "ProcBase.h"

namespace App {

/* using */ 

using Net::HFS::FileId;
using Net::HFS::FileLenType;

/* classes */ 

class BuildPath;

class FileNode;

struct MemNodeExt;

class MemNode;

class PrintMemNode;

struct FileResult;

struct MemResult;

struct FileReadResult;

struct FileWriteResult;

template <class T> class NodeSet;

class FileSet;

class MemSet;

class FileSystem;

class HFSProc;

/* class BuildPath */ 

class BuildPath : NoCopy , PathBase
 {
   static const ulen BufLen = 2*MaxPathLen ;
   
   char buf[BufLen];
   
   PtrLen<char> out;
   ulen level;
   FileError fe;
   
  private: 
  
   void add(StrLen str); 
   
   static char Subst(char ch);
   
   static void Subst(StrLen str,char *out);
   
   void addHome(StrLen str);
    
   void back();
   
   void start();
   
   void next(StrLen name,StrLen point_name);
   
   void stop(StrLen name,StrLen point_name);
   
  public:
  
   BuildPath(StrLen file_name,StrLen point_name);
   
   FileError operator ! () const { return fe; }
   
   StrLen getStr() const { return Range_const(buf,BufLen-out.len); }
 };
 
/* class FileNode */ 

class FileNode : NoCopy
 {
   Sys::AltFile sys_file;
   FileLenType file_len;
   ErrorIdType error_state;
  
  private:
  
   static FileLenType MaxLen(FileLenType off) { return FileLenType(-1)-off; }
  
   ErrorIdType error(FileError fe) { return error_state=ToErrorId(fe); }
  
   ErrorIdType error(ErrorIdType error_id) { return error_state=error_id; }
  
  public:
   
   FileNode() : file_len(),error_state() {}
  
   ErrorIdType open(StrLen file_name,StrLen point_name,FlagType oflags);
  
   FileReadResult read(FileLenType off,PtrLen<uint8> buf);
  
   FileWriteResult write(FileLenType off,PtrLen<const uint8> data);
  
   ErrorIdType close(bool preserve_file=false);
   
   FileLenType getLen() const { return file_len; }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* struct MemNodeExt */ 

struct MemNodeExt : MemBase_nocopy
 {
  virtual ErrorIdType atClose(MemNode *node,bool preserve_file)=0;
 
  virtual ~MemNodeExt() {}
 };
 
/* class MemNode */ 

class MemNode : NoCopy
 {
   static const ulen MaxLen = 1_MByte ;
  
   DynArray<uint8> data;
   FlagType oflags;
   MemNodeExt *ext;
   
  private: 
  
   FileReadResult do_read(FileLenType off,PtrLen<uint8> buf);
  
   FileWriteResult do_write(FileLenType off,PtrLen<const uint8> data);
   
   friend class PrintMemNode;
  
  public:
   
   MemNode() : oflags(),ext() {}
  
   ErrorIdType open(FlagType oflags,MemNodeExt *ext=0);
  
   FileReadResult read(FileLenType off,PtrLen<uint8> buf);
  
   FileWriteResult write(FileLenType off,PtrLen<const uint8> data);
  
   ErrorIdType close(bool preserve_file=false);
  
   FileLenType getLen() const { return data.getLen(); }
   
   PtrLen<const uint8> getData() const { return Range_const(data); }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* class PrintMemNode */  

class PrintMemNode : public PrintBase
 {
   MemNode *node;
   FileLenType off;
   ErrorIdType error_id;
   char buf[4_KByte];
 
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
  
  public:
  
   explicit PrintMemNode(MemNode *node);
   
   ~PrintMemNode();
   
   ErrorIdType complete();
 };
 
/* struct FileResult */  
 
struct FileResult
 {
  FileId file_id;
  ErrorIdType error_id;
  FileNode *node;
  
  FileResult(ErrorIdType error_id_) : error_id(error_id_),node(0) {}
  
  FileResult(const FileId &file_id_,FileNode *node_) : file_id(file_id_),error_id(0),node(node_) {}
 };
 
/* struct MemResult */  
 
struct MemResult
 {
  FileId file_id;
  ErrorIdType error_id;
  MemNode *node;
  
  MemResult(ErrorIdType error_id_) : error_id(error_id_),node(0) {}
  
  MemResult(const FileId &file_id_,MemNode *node_) : file_id(file_id_),error_id(0),node(node_) {}
 };
 
/* struct FileReadResult */ 

struct FileReadResult 
 {
  ErrorIdType error_id;
  LenType len;
  
  FileReadResult(ErrorIdType error_id_,LenType len_=0) : error_id(error_id_),len(len_) {}
 };
  
/* struct FileWriteResult */ 

struct FileWriteResult 
 {
  ErrorIdType error_id;
  FileLenType file_len;
  
  FileWriteResult(ErrorIdType error_id_,FileLenType file_len_=0) : error_id(error_id_),file_len(file_len_) {}
 };
  
/* class NodeSet<T> */   
  
template <class T> 
class NodeSet : NoCopy
 {
   struct Node : NoCopyBase<T>
    {
     DLink<Node> link;
     TreeUpLink<Node,XPoint> tlink;
     
     FileId file_id;
     bool active;
     
     void init(ulen slot)
      {
       active=false;
       
       file_id.slot=(uint32)slot;
       file_id.number=0;
      }
      
     void activate() 
      {
       active=true;
       
       file_id.number++;
       file_id.clock=(uint64)ClockTimer::Get();
      }
      
     void deactivate()
      {
       active=false;
      }
      
     bool match(const FileId &file_id_) const
      {
       return active && file_id==file_id_ ;
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = ArrayAlgo<T>::Default_no_throw,
       Copy_no_throw = true
      };
    };
    
   typedef typename DLink<Node>::template CircularAlgo<&Node::link> Algo;
   typedef typename TreeUpLink<Node,XPoint>::template RadixAlgo<&Node::tlink> TreeAlgo;
 
   DynArray<Node> pool;
   
   typename Algo::Top avail_list;
   typename Algo::Top active_list;
   typename TreeAlgo::Root active_root;
   
  public:
  
   explicit NodeSet(ulen len);
   
   ~NodeSet();
   
   struct AllocResult
    {
     FileId file_id;
     T *node;
     
     AllocResult(NothingType) : node(0) {}
     
     AllocResult(const FileId &file_id_,Node *node_) : file_id(file_id_),node(node_) {}
    };
   
   AllocResult allocNode(XPoint point);
   
   void freeNode(T *node);
   
   T * find(const FileId &file_id);
   
   void purge(XPoint point);
 };
 
template <class T> 
NodeSet<T>::NodeSet(ulen len)
 : pool(len)
 {
  for(ulen slot=0; slot<len ;slot++)
    {
     Node *node=pool.getPtr()+slot;
     
     node->init(slot);
     
     avail_list.ins_last(node);
    }
 }
   
template <class T> 
NodeSet<T>::~NodeSet()
 {
  while( Node *node=active_list.del_first() )
    {
     node->close();
    }
 }
   
template <class T> 
auto NodeSet<T>::allocNode(XPoint point) -> AllocResult
 {
  if( Node *node=avail_list.del_first() )
    {
     node->activate();
    
     active_list.ins_last(node);
     active_root.ins(node,point);
    
     return AllocResult(node->file_id,node);
    }
 
  return Nothing;
 }
   
template <class T> 
void NodeSet<T>::freeNode(T *node_)
 {
  Node *node=static_cast<Node *>(node_);
  
  node->deactivate();
  
  active_list.del(node);
  active_root.del(node);
  
  avail_list.ins_last(node);
 }
   
template <class T> 
T * NodeSet<T>::find(const FileId &file_id)
 {
  ulen slot=file_id.slot;
  
  if( slot>=pool.getLen() ) return 0;
  
  Node *node=pool.getPtr()+slot;
  
  if( node->match(file_id) ) return node;
  
  return 0;
 }
   
template <class T> 
void NodeSet<T>::purge(XPoint point)
 {
  while( Node *node=active_root.del(point) )
    {
     node->close();
     
     node->deactivate();

     active_list.del(node);
     avail_list.ins_last(node);
    }
 }
   
/* class FileSet */ 

class FileSet : NoCopy
 {
   NodeSet<FileNode> set;
   
  public:
  
   static const ulen DefaultMaxFiles = 1000 ;
  
   explicit FileSet(ulen max_files=DefaultMaxFiles); // assume max_files <= 2^31
   
   ~FileSet();
   
   FileResult open(XPoint point,StrLen file_name,StrLen point_name,FlagType oflags);
   
   FileNode * find(const FileId &file_id) { return set.find(file_id); }
   
   ErrorIdType close(FileNode *node,bool preserve_file);
   
   void purge(XPoint point) { set.purge(point); }
 };
 
/* class MemSet */  
 
class MemSet : NoCopy
 {
   NodeSet<MemNode> set;
   
  public:
  
   static const ulen DefaultMaxMems = 1000 ;
  
   explicit MemSet(ulen max_mems=DefaultMaxMems); // assume max_mems <= 2^31
   
   ~MemSet();
   
   MemResult open(XPoint point,FlagType oflags,MemNodeExt *ext=0);
   
   MemNode * find(const FileId &file_id) { return set.find(file_id); }
   
   ErrorIdType close(MemNode *node,bool preserve_file=false);
   
   void purge(XPoint point) { set.purge(point); }
 };
 
/* class FileSystem */ 
 
class FileSystem : NoCopy
 {
   Sys::FileSystem fs;
   
  public:
  
   FileSystem();
   
   ~FileSystem();
   
   struct FileTypeResult
    {
     ErrorIdType error_id;
     FlagType type;
     
     explicit FileTypeResult(FileError fe) : error_id(ToErrorId(fe)),type(0) {}
     
     FileTypeResult(FileError fe,FlagType type_) : error_id(ToErrorId_Ok(fe)),type(type_) {}
    };
    
   FileTypeResult getFileType(StrLen path,StrLen point_name);
   
   ErrorIdType getFileList(StrLen dir_name,StrLen point_name,MemNode *node);
   
   ErrorIdType createFile(StrLen file_name,StrLen point_name);
   
   ErrorIdType deleteFile(StrLen file_name,StrLen point_name);
   
   ErrorIdType createDir(StrLen dir_name,StrLen point_name);
   
   ErrorIdType deleteDir(StrLen dir_name,StrLen point_name,bool recursive);
   
   ErrorIdType rename(StrLen old_path,StrLen new_path,StrLen point_name,bool allow_overwrite);
   
   ErrorIdType remove(StrLen path,StrLen point_name);
   
   ErrorIdType exec(StrLen dir,StrLen program,StrLen arg,StrLen point_name);
 };
 
/* class HFSProc */ 

class HFSProc : ProcBase
 {
   FileSystem filesys;
 
   FileSet file_set;
   MemSet mem_set;
   
  private:
  
   static const uint32 MemFlag = 0x80000000 ;
  
   static void SetMemFlag(FileId &file_id) { BitSet(file_id.slot,MemFlag); }
  
   static bool TakeMemFlag(FileId &file_id) 
    { 
     if( file_id.slot&MemFlag ) 
       {
        BitClear(file_id.slot,MemFlag);
        
        return true;
       }
       
     return false; 
    }
    
   class Exec2Ext : public MemNodeExt
    {
      FileSystem &filesys;
      
      String dir;
      String program;
      String point_name;
      
     private: 
      
      virtual ErrorIdType atClose(MemNode *node,bool preserve_file);

     public:
     
      Exec2Ext(FileSystem &filesys,StrLen dir,StrLen program,StrLen point_name);
      
      virtual ~Exec2Ext();
    };
  
  private:
  
   void function_Open(Inbound &inbound);
   
   void function_Read(Inbound &inbound);
   
   void function_Write(Inbound &inbound);
   
   void function_Close(Inbound &inbound);
   
   void function_GetFileType(Inbound &inbound);
  
   void function_GetFileList(Inbound &inbound);
  
   void function_CreateFile(Inbound &inbound);
  
   void function_DeleteFile(Inbound &inbound);
  
   void function_CreateDir(Inbound &inbound);
  
   void function_DeleteDir(Inbound &inbound);
  
   void function_Rename(Inbound &inbound);
  
   void function_Remove(Inbound &inbound);
  
   void function_Exec(Inbound &inbound);
  
   void function_Exec2(Inbound &inbound);
  
  public:
  
   explicit HFSProc(ServerProcBase *base,
                    ulen max_files=FileSet::DefaultMaxFiles,
                    ulen max_mems=MemSet::DefaultMaxMems);
   
   ~HFSProc();
   
   void inbound(Inbound &inbound);
   
   void tick();
   
   void session(XPoint point);
   
   bool exist(FunctionIdType function_id);
 };
 
} // namespace App
 
#endif


