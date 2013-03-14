/* DDLEngine.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLEngine_h
#define CCore_inc_ddl_DDLEngine_h

#include <CCore/inc/ddl/DDLParser.h>
#include <CCore/inc/ddl/DDLEval.h>
 
#include <CCore/inc/Path.h>

namespace CCore {
namespace DDL {

/* classes */

struct EngineResult;

class TextEngine;

class TextEvalEngine;

class FileName;

struct FileKey;

template <class FileName,class FileText> class FileEngine;

/* struct EngineResult */

struct EngineResult
 {
  Eval *eval;
  BodyNode *body;
  
  EngineResult() : eval(0),body(0) {}
  
  EngineResult(PrintBase &msg,Process<Eval> &proc,ParserResult result);
  
  bool operator ! () const { return !eval; }
 };

/* class TextEngine */

class TextEngine : ParserContext
 {
   FileId id;
   StrLen pretext;
   StrLen text;
   
   Process<Eval> proc;
   
  private: 
     
   virtual File openFile(StrLen file_name);
   
   ParserResult parse();
   
  public: 
   
   TextEngine(PrintBase &msg,StrLen text,StrLen pretext={});
   
   ~TextEngine();
   
   EngineResult process();
 };

/* class FileName */

class FileName
 {
   DynArray<char> buf;
   ulen off;
   bool ok;
   
  private:
   
   static bool IsRooted(StrLen name)
    {
     return name.len && PathBase::IsSlash(name[0]) ;
    }
   
   struct PathUp : PathBase
    {
     StrLen path;
     ulen up;
     bool ok;
     
     PathUp(StrLen path,ulen up);
     
     bool operator ! () const { return !ok; }
     
     void set(StrLen path_,ulen up_)
      {
       path=path_;
       up=up_;
       ok=true;
      }
    };

   class Out : NoCopy
    {
      char *out;
      
     public: 
     
      Out(DynArray<char> &buf,ulen len)
       {
        out=buf.extend_raw(len).ptr;
       }
      
      void put(char ch)
       {
        *(out++)=ch;
       }
      
      void put(StrLen str)
       {
        str.copyTo(out);
       
        out+=str.len;
       }
      
      void operator () () {}
      
      template <class T,class ... TT>
      void operator () (T t,TT ... tt)
       {
        put(t);
        
        (*this)(tt...);
       }
    };
   
   void setAbs(StrLen file_name,SplitPath split_dev,SplitPathName split_file);
  
   void setRel(StrLen path,SplitPathName split_file);
   
  public: 
   
   // constructors
  
   FileName() : off(0),ok(false) {}
  
   explicit FileName(StrLen file_name);
  
   FileName(StrLen path,StrLen file_name);
   
   ~FileName() {}
   
   // methods
   
   bool operator ! () const { return !ok; }
  
   StrLen getStr() const { return Range(buf); }
  
   StrLen getPath() const { return getStr().prefix(off); }
   
   StrLen getFile() const { return getStr().part(off); }
   
   void printPos(PrintBase &out,TextPos pos);
  
   // swap objects
  
   void objSwap(FileName &obj)
    {
     Swap(buf,obj.buf);
     Swap(off,obj.off);
     Swap(ok,obj.ok);
    }
 };

/* struct FileKey */

struct FileKey
 {
  uint16 hash;
  StrLen str;
  
  FileKey() : hash(0) {}
  
  explicit FileKey(StrLen str);
  
  CmpResult objCmp(const FileKey &obj) const;
 };

/* class FileEngine<FileName,FileText> */

template <class FileName,class FileText> 
class FileEngine : ParserContext
 {
   struct FileRec : FileId , MemBase_nocopy
    {
     FileName file_name;
     FileText file_text;
     
     RBTreeLink<FileRec,FileKey> link;
     
     FileRec(FileName &file_name_,ulen max_file_len)
      : file_text(file_name_.getStr(),max_file_len)
      {
       Swap(file_name,file_name_);
      }
     
     StrLen getText() const { return Mutate<const char>(Range(file_text)); }
     
     virtual void printPos(PrintBase &out,TextPos pos) { file_name.printPos(out,pos); }
    };
   
   typedef typename RBTreeLink<FileRec,FileKey>::template Algo<&FileRec::link,FileKey> Algo;
  
   ulen max_files;
   ulen max_inc;
   ulen max_file_len;
     
   ulen file_count;
   ulen inc_count;
   
   typename Algo::Root root;

   Process<Eval> proc;
   
  private: 
     
   static void Destroy(FileRec *rec);
     
   static File Make(FileRec *rec);
     
   File open(FileName &file_name);
     
   virtual File openFile(StrLen file_name);
     
   virtual File openFile(FileId *file_id,const Token &name);
   
  public:
   
   static const ulen DefaultMaxFiles = 1000 ;
   static const ulen DefaultMaxIncludes = 100 ;
   static const ulen DefaultMaxFileLen = MaxULen ;
  
   explicit FileEngine(PrintBase &msg,ulen mem_cap=MaxULen,
                                      ulen max_files=DefaultMaxFiles,
                                      ulen max_inc=DefaultMaxIncludes,
                                      ulen max_file_len=DefaultMaxFileLen);
   
   ~FileEngine();
   
   EngineResult process(StrLen file_name,StrLen pretext={});
 };

template <class FileName,class FileText> 
void FileEngine<FileName,FileText>::Destroy(FileRec *rec)
 {
  if( rec )
    {
     Destroy( Algo::Link(rec).lo );
     Destroy( Algo::Link(rec).hi );
     
     delete rec;
    }
 }

template <class FileName,class FileText> 
ParserContext::File FileEngine<FileName,FileText>::Make(FileRec *rec)
 {
  return ParserContext::File(rec,rec->getText());
 }

template <class FileName,class FileText> 
ParserContext::File FileEngine<FileName,FileText>::open(FileName &file_name)
 {
  FileKey key(file_name.getStr());
  
  typename Algo::PrepareIns ins(root,key);
  
  if( ins.found ) return Make(ins.found); 
  
  if( file_count>=max_files )
    {
     printfError("Too many open files\n");
     
     return Nothing;
    }
  
  FileRec *rec=new FileRec(file_name,max_file_len);
  
  file_count++;
  
  ins.complete(rec);
  
  return Make(rec);
 }

template <class FileName,class FileText> 
ParserContext::File FileEngine<FileName,FileText>::openFile(StrLen file_name_)
 {
  inc_count=0;
  
  FileName file_name(file_name_);
  
  if( !file_name )
    {
     printfError("Bad file name #.q;\n",file_name_);
     
     return Nothing;
    }
  
  return open(file_name);
 }

template <class FileName,class FileText> 
ParserContext::File FileEngine<FileName,FileText>::openFile(FileId *file_id,const Token &name)
 {
  if( inc_count>=max_inc )
    {
     printfError("Too many included files\n");
     
     return Nothing;
    }
  
  inc_count++;
  
  FileRec *base=static_cast<FileRec *>(file_id);
  
  StrLen file_name_=name.str.inner(1,1);
  
  FileName file_name(base->file_name.getPath(),file_name_);

  if( !file_name )
    {
     printfError("Bad include file name #; #.q;\n",PrintPos(file_id,name.pos),name.str);
     
     return Nothing;
    }
  
  return open(file_name);
 }

template <class FileName,class FileText> 
FileEngine<FileName,FileText>::FileEngine(PrintBase &msg,ulen mem_cap,ulen max_files_,ulen max_inc_,ulen max_file_len_) 
 : ParserContext(msg,mem_cap),
   max_files(max_files_),
   max_inc(max_inc_),
   max_file_len(max_file_len_), 
   file_count(0),
   inc_count(0),
   proc(getPool(),getPool(),msg)
 {
 }

template <class FileName,class FileText> 
FileEngine<FileName,FileText>::~FileEngine() 
 {
  Destroy(root.root);
 }

template <class FileName,class FileText> 
EngineResult FileEngine<FileName,FileText>::process(StrLen file_name,StrLen pretext)
 {
  proc.reset();
  
  return EngineResult(getMsg(),proc,parseFile(file_name,pretext));
 }

} // namespace DDL
} // namespace CCore
 
#endif
 
