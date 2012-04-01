/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: MakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/CharProp.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/FileToMem.h>

namespace App {

/* using */

using namespace CCore;

/* functions */ 

StrLen GetFileName(StrLen path) 
 { 
  SplitPath split1(path);
  SplitName split2(split1.path);
  SplitExt split3(split2.name);
  
  return split3.name; 
 }

/* classes */

class Cursor;

struct FileName;

class FileList;

struct ObjList;

struct AsmList;

struct DepList;

struct AsmObjList;

struct ObjRule;

struct AsmRule;

struct DepRule;

struct AsmObjRule;

class Engine;

/* class Cursor */ 

class Cursor
 {
   StrLen text;

  public:

   explicit Cursor(PtrLen<const char> text_) : text(text_) {}
 
   StrLen next()
    {
     for(; +text && CharIsSpace(*text) ;++text);

     if( !text ) return text;

     StrLen start=text;

     for(; +text && !CharIsSpace(*text) ;++text);

     return start.prefix(text);
    }
 };
 
/* struct FileName */  

struct FileName
 {
  StrLen path;
  StrLen name;
  
  explicit FileName(StrLen path_) : path(path_),name(GetFileName(path_)) {}
  
  // operators
  
  bool operator < (FileName file) const { return StrLess(name,file.name); }
  
  bool operator == (FileName file) const { return name.equal(file.name); }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* class FileList */ 

class FileList
 {
   DynArray<FileName> buf;
   
  private:
  
   static void Guard(FileName a,FileName b)
    {
     if( a==b )
       {
        Printf(Exception,"File name duplication: #; #;",a.path,b.path);
       }
    }
  
   static void Process(PtrLen<FileName> r)
    {
     Sort(r);
     
     for(; r.len>=2 ;++r) Guard(r[0],r[1]);
    }
 
  public:
  
   explicit FileList(PtrLen<const char> text)
    {
     Cursor cur(text);
     Collector<FileName> temp;
     
     for(;;)
       {
        StrLen path=cur.next();

        if( !path ) break;

        temp.append_fill(path);
       }
     
     temp.extractTo(buf);
    }
    
   void process()
    {
     Process(Range(buf));
    }
    
   template <class Func> 
   void apply(Func &func) const
    {
     for(auto r=Range(buf); +r ;++r) func(*r);
    }
 };
 
/* struct ObjList */  

struct ObjList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  ObjList(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
    Printf(out,"OBJ_LIST = \\\n");
   }
  
  ~ObjList()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.o \\\n",obj_path,file.name);
   }
 };
 
/* struct AsmList */ 
 
struct AsmList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmList(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
    Printf(out,"ASM_LIST = \\\n");
   }
 
  ~AsmList()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s \\\n",obj_path,file.name);
   }
 };
 
/* struct DepList */ 
 
struct DepList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  DepList(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
    Printf(out,"DEP_LIST = \\\n");
   }
 
  ~DepList()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.dep \\\n",obj_path,file.name);
   }
 }; 
 
/* struct AsmObjList */ 
  
struct AsmObjList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  explicit AsmObjList(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
    Printf(out,"ASM_OBJ_LIST = \\\n");
   }
 
  ~AsmObjList()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s.o \\\n",obj_path,file.name);
   }
 };
 
/* struct ObjRule */ 

struct ObjRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  ObjRule(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
   }
 
  ~ObjRule()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.o : #;\n\t$(CC) $(CCOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };
 
/* struct AsmRule */ 
 
struct AsmRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmRule(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
   }
 
  ~AsmRule()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s : #;\n\t$(CC) -S $(CCOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };
 
/* struct DepRule */ 
 
struct DepRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  DepRule(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
   }
 
  ~DepRule()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.dep : #;\n\t$(CC) $(CCOPT) -MM -MT $(OBJ_PATH)/#;.o $< -MF $@\n\n",obj_path,file.name,file.path,file.name);
   }
 };
 
/* struct AsmObjRule */ 
 
struct AsmObjRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmObjRule(PrintFile &out_,StrLen obj_path_) 
   : out(out_), 
     obj_path(obj_path_)
   {
   }
 
  ~AsmObjRule()
   {
    Printf(out,"\n\n");
   }
 
  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s.o : #;\n\t$(AS) $(ASOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };
 
/* class Engine */ 

class Engine : NoCopy
 {
   FileToMem cpp_files;
   FileToMem s_files;
   
   StrLen obj_path;
   
   FileList cpp_list;
   FileList s_list;
   
   PrintFile out;
   
  private:
   
   template <class T>
   void apply_to(FileList &list)
    {
     T func(out,obj_path);
     
     list.apply(func);
    }

   template <class T>
   void apply_to_cpp() { apply_to<T>(cpp_list); }

   template <class T>
   void apply_to_s() { apply_to<T>(s_list); }

  public:

   Engine(StrLen obj_path_,StrLen cpp_list_file_name,StrLen s_list_file_name)
    : cpp_files(cpp_list_file_name),
      s_files(s_list_file_name),
      obj_path(obj_path_),
      cpp_list( Mutate<const char>(Range(cpp_files)) ),
      s_list( Mutate<const char>(Range(s_files)) ),
      out("Makefile.files")
    {
     cpp_list.process();
     s_list.process();
    }
 
   ~Engine() {}
 
   int run()
    {
     apply_to_cpp<ObjList>();
     apply_to_cpp<AsmList>();
     apply_to_cpp<DepList>();
     apply_to_s<AsmObjList>();
     
     Printf(out,"include $(RULES_FILE)\n\n\n");

     apply_to_cpp<ObjRule>();
     apply_to_cpp<AsmRule>();
     apply_to_cpp<DepRule>();
     apply_to_s<AsmObjRule>();
     
     Printf(out,"ifneq ($(MAKECMDGOALS),clean)\n\n"
       
                "include $(DEP_FILE)\n\n"
       
                "endif\n\n" 
           );

     return 0;
    }
 };
 
} // namespace App 
  
/* main() */ 

using namespace App;

int main(int argc,const char *argv[])
 {
  ReportException report;

  try
    {
     int ret;

     {
      Putobj(Con,"--- MakeList 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=4 ) 
        {
         Putobj(Con,"Usage: MakeList <obj-path> <cpp-list-file-name> <s-list-file-name>\n");
         
         return 1;
        }
      
      Engine engine(argv[1],argv[2],argv[3]);

      ret=engine.run();
     } 
     
     report.guard();
     
     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
