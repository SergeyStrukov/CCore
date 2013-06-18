/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: FileMap 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/DirTreeRun.h>

namespace App {

/* using */ 

using namespace CCore;

/* functions */
 
bool SoftExtLess(StrLen a,StrLen b)
 {
  SplitExt sa(a);
  SplitExt sb(b);
  
  if( auto cmp=StrCmp(sa.ext,sb.ext) ) return cmp<0;
     
  return false;
 }
 
bool ExtLess(StrLen a,StrLen b)
 {
  SplitExt sa(a);
  SplitExt sb(b);
  
  if( auto cmp=StrCmp(sa.ext,sb.ext) ) return cmp<0;
     
  return StrLess(sa.name,sb.name);
 }
 
bool DeepExtLess(StrLen a,StrLen b)
 {
  for(;;)
    {
     SplitExt sa(a);
     SplitExt sb(b);
     
     if( auto cmp=StrCmp(sa.ext,sb.ext) ) return cmp<0;
     
     if( !sa ) return StrLess(sa.name,sb.name);
     
     a=sa.name;
     b=sb.name;
    }
 }
 
/* classes */

class DirInfo;

class TreeInfo;

class PrintHTML;

class PrintText;

class Filter;

class Engine;

/* class DirInfo */

class DirInfo : public MemBase_nocopy
 {
   StrLen dir_name;
   
   DirInfo *parent;

   Collector<StrLen> files;
   Collector<DirInfo *> dirs;
   
   DynArray<StrLen> file_list;
   DynArray<DirInfo *> dir_list;
   
  private: 
   
   void add(DirInfo *dir) { dirs.append_copy(dir); }
   
   void clean()
    {
     for(auto r=getDirs(); +r ;++r) delete *r;
    }
    
  public:
  
   explicit DirInfo(StrLen dir_name_) 
    : dir_name(dir_name_),
      parent(0) 
    {   
    }
   
   DirInfo(StrLen dir_name_,DirInfo *parent_) 
    : dir_name(dir_name_),
      parent(parent_) 
    {   
     parent_->add(this);
    }
   
   ~DirInfo()
    {
     clean();
     dirs.extractTo(dir_list);
     clean();
    }
   
   void add(StrLen file_name) { files.append_copy(file_name); }
   
   StrLen getName() const { return dir_name; } 
    
   DirInfo * getParent() const { return parent; }
   
   PtrLen<const StrLen> getFiles() const { return Range_const(file_list); }
   
   PtrLen<DirInfo *const> getDirs() const { return Range_const(dir_list); }
   
   void sort()
    {
     files.extractTo(file_list);
     
     clean();
     
     dirs.extractTo(dir_list);
     
     IncrSort(Range(dir_list), [] (DirInfo *a,DirInfo *b) { return StrLess(a->getName(),b->getName()); } );
     
     IncrSort(Range(file_list), DeepExtLess );
    }
 };

/* class TreeInfo */

class TreeInfo : NoCopy
 {
   ElementPool pool;
   char buf[MaxPathLen+1];
   
   DirInfo *root;
   
  private:
   
   static void Sort(DirInfo *info);
   
   typedef DirInfo DataType;
   
   DirInfo * dir(StrLen root_path);
   
   DirInfo * dir(StrLen path,StrLen dir_name,DirInfo *data);
   
   void file(StrLen path,StrLen file_name,DirInfo *data);
   
   void enddir(StrLen path,StrLen dir_name,DirInfo *data);
   
   friend class CCore::DirTreeRun;
   
  public:
   
   TreeInfo();
   
   ~TreeInfo();
   
   DirInfo * getRoot() const { return root; } 
   
   StrLen build(StrLen root_path);
   
   void sort();
 };

void TreeInfo::Sort(DirInfo *info)
 {
  info->sort();
  
  for(auto r=info->getDirs(); +r ; ++r) Sort(*r);
 }

DirInfo * TreeInfo::dir(StrLen /*root_path*/)
 {
  delete Replace_null(root);
  
  root=new DirInfo(".");
  
  return root;
 }

DirInfo * TreeInfo::dir(StrLen /*path*/,StrLen dir_name,DirInfo *data)
 {
  return new DirInfo(pool.dup(dir_name),data);
 }
 
void TreeInfo::file(StrLen /*path*/,StrLen file_name,DirInfo *data)
 {
  data->add(pool.dup(file_name));
 }
   
void TreeInfo::enddir(StrLen /*path*/,StrLen /*dir_name*/,DirInfo * /*data*/) 
 {
 }
   
TreeInfo::TreeInfo()
 : root(0)
 {
 }

TreeInfo::~TreeInfo()
 {
  delete root;
 }

StrLen TreeInfo::build(StrLen root_path)
 {
  DirTreeRun run(root_path);
  
  run.apply(*this);
  
  return run.pathOfRoot(buf);
 }

void TreeInfo::sort()
 {
  if( root ) Sort(root);
 }  

/* class PrintHTML */

class PrintHTML : NoCopy
 {
   PrintFile out;
   
   StrLen root;
   
   ulen dir_id;
   ulen file_id;
   
   Path path;

   ElementPool pool;
   DynArray<StrLen> file_list;
   
  public:
   
   PrintHTML(StrLen file_name,StrLen root);
   
   ~PrintHTML();
   
   typedef ulen LevelType;
   
   LevelType startLevel() { return 0; }
   
   LevelType nextLevel(LevelType lvl,StrLen /*dir_name*/) { return lvl+1; }
   
   void beginDir(LevelType lvl,StrLen dir_name);
   
   void printFile(LevelType lvl,StrLen file_name);
   
   void printFileGroup(LevelType lvl,StrLen last_file_name,ulen count);
   
   void endDir(LevelType lvl,StrLen dir_name);
 };

PrintHTML::PrintHTML(StrLen file_name,StrLen root_)
 : out(file_name),
   root(root_),
   dir_id(0),
   file_id(0),
   path(Path::BeginEmpty)
 {
  Putobj(out,"<!DOCTYPE html>\n"
             "<html>\n\n"
    
             "<head>\n\n"
    
             " <title>File Map</title>\n\n"
    
             " <link href=\"FileMap.css\" rel=\"stylesheet\" type=\"text/css\">\n\n"
    
             " <script type=\"text/javascript\" src=\"FileMap.js\"></script>\n\n"
    
             "</head>\n\n"
    
             "<body>\n\n"
    
             "<section class=\"aspect\" id=\"aspect_section\">\n\n"
    
             "</section>\n\n"
    
             "<section class=\"save_load\">\n\n"
    
             "<button class=\"save_button\" type=\"button\" onclick=\"SaveAspect();\">Save</button>\n"
             "<button class=\"load_button\" type=\"button\" onclick=\"LoadAspect();\">Load</button>\n\n"
    
             "</section>\n\n"
    
             "<section class=\"new_delete\">\n\n"
    
             "<button class=\"new_button\" type=\"button\" onclick=\"NewAspect();\">New</button>\n"
             "<input class=\"aspect_name\" type=\"text\" id=\"new_aspect_name\" /> <br />\n\n"
             "<button class=\"delete_button\" type=\"button\" onclick=\"DeleteAspect();\">Delete</button>\n\n"
    
             "</section>\n\n"
    
             "<section class=\"hide_show\">\n\n"
    
             "<button class=\"hide_button\" type=\"button\" onclick=\"HideGreen();\">Hide Green</button>\n"
             "<button class=\"show_button\" type=\"button\" onclick=\"ShowAll();\">Show All</button>\n\n"
    
             "</section>\n\n"
    
             "<section class=\"stat\">\n\n"
    
             "<span id=\"stat_red\"></span> <span id=\"stat_yellow\"></span> <span id=\"stat_green\"></span>\n\n"
    
             "</section>\n\n"
    
             "<section class=\"content\">\n\n"
            );
 }

PrintHTML::~PrintHTML()
 {
  ulen len=file_list.getLen();
  
  Printf(out,"\n</section>\n\n"

             "</body>\n\n"
    
             "<script type=\"text/javascript\">\n\n"
    
             "function GetFileList()\n"
             "{\n"
             " var ret=new Array(#;);\n\n"
            ,len);
  
  
  for(ulen i=0; i<len ;i++)
    Printf(out," ret[#;]=\"#;\";\n",i,file_list[i]); 
    
  Putobj(out,"\n return ret;\n"
             "}\n\n"
    
             "</script>\n\n"
    
             "<script type=\"text/javascript\">Prepare();</script>\n\n"

             "</html>\n\n"
            );
 }

void PrintHTML::beginDir(LevelType lvl,StrLen dir_name)
 {
  ulen id=dir_id++;
  
  RepeatChar rep(lvl,' ');
  
  if( lvl ) Printf(out,"\n#;<li>\n\n",rep);
  
  if( !lvl ) dir_name=root;
  
  Printf(out,"#;<h3 class=\"dir_name\" id=\"dir#;\">"
             "<button class=\"dir_button\" type=\"button\">&minus;</button>"
             "<button class=\"dir_button_all\" type=\"button\">++</button>"
             "<button class=\"dir_button_none\" type=\"button\">&minus;&minus;</button>"
             "<input class=\"R_color\" type=\"radio\" name=\"dir#;_color\" />"
             "<input class=\"Y_color\" type=\"radio\" name=\"dir#;_color\" />"
             "<input class=\"G_color\" type=\"radio\" name=\"dir#;_color\" checked=\"checked\" />"
             "#;"
             "</h3>\n\n"
    
             "#;<ul class=\"dir_list\" id=\"dir#;_list\">\n\n"
    
            ,rep,id,id,id,id,dir_name,rep,id);
  
  path.addPath(dir_name);
 }

void PrintHTML::printFile(LevelType lvl,StrLen file_name)
 {
  ulen id=file_id++;
  
  RepeatChar rep(lvl,' ');
  
  Printf(out,"#; <li class=\"file_name\" id=\"file#;\">"
             "<input class=\"R_color\" type=\"radio\" name=\"file#;_color\" />"
             "<input class=\"Y_color\" type=\"radio\" name=\"file#;_color\" />"
             "<input class=\"G_color\" type=\"radio\" name=\"file#;_color\" checked=\"checked\" />"
             "#;</li>\n"
    
            ,rep,id,id,id,id,file_name);
  
  path.add(file_name);
  
  file_list.append_copy(pool.dup(path));
  
  path.back();
 }

void PrintHTML::printFileGroup(LevelType lvl,StrLen last_file_name,ulen count)
 {
  RepeatChar rep(lvl,' ');
  
  SplitExt split(last_file_name);
  
  Printf(out,"#; <li class=\"file_total\">#; *#; files</li>\n",rep,count,split.ext);
 }

void PrintHTML::endDir(LevelType lvl,StrLen /*dir_name*/)
 {
  RepeatChar rep(lvl,' ');
  
  Printf(out,"\n#;</ul>\n",rep);
  
  if( lvl ) Printf(out,"\n#;</li>\n\n",rep);
  
  path.back();
 }

/* class PrintText */

class PrintText : NoCopy
 {
   PrintFile out;
   
  public: 
   
   explicit PrintText(StrLen file_name);
   
   ~PrintText();
   
   typedef ulen LevelType;
   
   LevelType startLevel() { return 0; }
   
   LevelType nextLevel(LevelType lvl,StrLen dir_name) { return lvl+2+dir_name.len; }
   
   void beginDir(LevelType lvl,StrLen dir_name);
   
   void printFile(LevelType lvl,StrLen file_name);
   
   void printFileGroup(LevelType lvl,StrLen last_file_name,ulen count);
   
   void endDir(LevelType lvl,StrLen dir_name);
 };

PrintText::PrintText(StrLen file_name)
 : out(file_name)
 {
 }

PrintText::~PrintText()
 {
 }

void PrintText::beginDir(LevelType lvl,StrLen dir_name)
 {
  RepeatChar rep(lvl,' ');
  
  Printf(out,"#;#; {\n",rep,dir_name);
 }

void PrintText::printFile(LevelType lvl,StrLen file_name)
 {
  RepeatChar rep(lvl+2,' ');
  
  Printf(out,"#;#;\n",rep,file_name);
 }

void PrintText::printFileGroup(LevelType lvl,StrLen last_file_name,ulen count)
 {
  RepeatChar rep(lvl+2,' ');
  
  SplitExt split(last_file_name);
  
  Printf(out,"#;-----\n",rep);
  Printf(out,"#;#; *#; files\n",rep,count,split.ext);
  Printf(out,"#;----------\n",rep);
 }

void PrintText::endDir(LevelType lvl,StrLen dir_name)
 {
  RepeatChar rep(lvl,' ');
  
  Printf(out,"#;} // #;\n",rep,dir_name);
 }

/* class Filter */

class Filter : NoCopy
 {
   StrLen dir1;
   StrLen dir2;
   StrLen dir3;
   StrLen obj;
   
   StrLen ext1;
   StrLen ext2;
   StrLen ext3;
   StrLen ext4;
   StrLen files;
   
  public: 
  
   Filter()
    : dir1(".svn"),
      dir2("eclipse"),
      dir3(".git"),
      obj("obj"),
      
      ext1(".o"),
      ext2(".dep"),
      ext3(".txt"),
      ext4(".exe"),
      files("files")
    {
    }
  
   static bool HasSuffix(StrLen name,StrLen suffix)
    {
     return name.fit(suffix.len) && name.suffix(suffix.len).equal(suffix) ;
    }
   
   bool noDir(StrLen name) const
    {
     return name.equal(dir1) || 
            name.equal(dir2) ||
            name.equal(dir3) ||
            HasSuffix(name,obj) ;
    }
   
   bool noFileExt(StrLen ext) const
    {
     return ext.equal(ext1) || 
            ext.equal(ext2) || 
            ext.equal(ext3) || 
            ext.equal(ext4) || 
            HasSuffix(ext,files) ;
    }
   
   bool noFile(StrLen name) const
    {
     SplitExt split(name);

     return noFileExt(split.ext);
    }
 };

/* class Engine */ 

class Engine : NoCopy
 {
   TreeInfo info;
   StrLen root;
   Filter filter;
   
  private: 
   
   template <class Out>
   void printTo(Out &out,DirInfo *info,typename Out::LevelType lvl);
   
  public:
  
   explicit Engine(StrLen root_path);
   
   ~Engine();
   
   StrLen getRoot() const { return root; }
   
   template <class Out>
   void printTo(Out &out);
 };
 
template <class Out>
void Engine::printTo(Out &out,DirInfo *info,typename Out::LevelType lvl)
 {
  StrLen name=info->getName();
  
  if( filter.noDir(name) ) return;
  
  out.beginDir(lvl,name);
  
  typename Out::LevelType next_lvl=out.nextLevel(lvl,name);
  
  for(auto r=info->getDirs(); +r ; ++r) printTo(out,*r,next_lvl); 
  
  ulen count=0;
  StrLen last_file;
  
  for(auto r=info->getFiles(); +r ;++r) 
    {
     if( filter.noFile(*r) ) continue;
     
     if( count && SoftExtLess(last_file,*r) )
       {
        out.printFileGroup(lvl,last_file,count);
        
        count=0;
       }
     
     out.printFile(lvl,*r);
     
     last_file=*r;
     count++;
    }
  
  if( count ) out.printFileGroup(lvl,last_file,count);
  
  out.endDir(lvl,name);
 }

Engine::Engine(StrLen root_path)
 {
  root=info.build(root_path);
  
  info.sort();
 }

Engine::~Engine()
 {
 }

template <class Out>
void Engine::printTo(Out &out)
 {
  if( DirInfo *root=info.getRoot() ) printTo(out,root,out.startLevel()); 
 }

/* BuildHTML() */ 

int BuildHTML(StrLen root,StrLen file_name)
 {
  Engine engine(root);
  PrintHTML out(file_name,engine.getRoot());
  
  engine.printTo(out);
  
  return 0;
 }
 
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
      Putobj(Con,"--- FileMap 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=3 ) 
        {
         Putobj(Con,"Usage: FileMap <root> <output-file-name>\n");
        
         return 1;
        }
     
      ret=BuildHTML(argv[1],argv[2]);
     } 
     
     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
