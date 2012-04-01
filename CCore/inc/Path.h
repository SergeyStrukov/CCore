/* Path.h */ 
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

#ifndef CCore_inc_Path_h
#define CCore_inc_Path_h

#include <CCore/inc/GenFile.h>
 
namespace CCore {

/* classes */

struct PathBase;

struct SplitDev;

struct SplitPath;

struct SplitDir;

struct SplitName;

struct SplitFullExt;

struct SplitExt;

struct SplitDevName;

struct SplitDirName;

struct SplitPathName;

class Path;

/* struct PathBase */ 

struct PathBase
 {
  static bool IsSlash(char ch) { return ch=='/' || ch=='\\' ; }
  
  static bool IsDot(char ch) { return ch=='.'; }
  
  static bool IsColon(char ch) { return ch==':'; }
  
  static bool IsDot(StrLen name) { return name.len==1 && name[0]=='.' ; }
  
  static bool IsDotDot(StrLen name) { return name.len==2 && name[0]=='.' && name[1]=='.' ; }
  
  static bool IsTilde(StrLen name) { return name.len==1 && name[0]=='~' ; }
  
  enum NameType
   {
    Name,
    EmptyName,
    DotName,
    DotDotName
   };
  
  static NameType GetNameType(StrLen name)
   {
    if( !name ) return EmptyName;
    
    if( IsDot(name) ) return DotName;
    
    if( IsDotDot(name) ) return DotDotName;
    
    return Name;
   }
  
  struct ToPrefix;
  
  struct ToPrefixDel;
  
  struct ToSuffix;
  
  template <bool Is(char ch),class To> struct ForwardScan;
  
  template <bool Is(char ch),class To> struct BackwardScan;
 };

struct PathBase::ToPrefix
 {
  StrLen prefix;
  StrLen suffix;
  bool no;
  
  void set(StrLen str,StrLen cur)
   {
    ++cur;
    
    prefix=str.prefix(cur);
    suffix=cur;
    no=false;
   }
  
  void set(StrLen str)
   {
    suffix=str;
    no=true;
   }
 };

struct PathBase::ToPrefixDel
 {
  StrLen prefix;
  StrLen suffix;
  bool no;
  
  void set(StrLen str,StrLen cur)
   {
    prefix=str.prefix(cur);
    
    ++cur;
    
    suffix=cur;
    no=false;
   }
  
  void set(StrLen str)
   {
    suffix=str;
    no=true;
   }
 };

struct PathBase::ToSuffix
 {
  StrLen prefix;
  StrLen suffix;
  bool no;
  
  void set(StrLen str,StrLen cur)
   {
    prefix=str.prefix(cur);
    suffix=cur;
    no=false;
   }
  
  void set(StrLen str)
   {
    prefix=str;
    no=true;
   }
 };

template <bool Is(char ch),class To>
struct PathBase::ForwardScan : To
 {
  using To::set;
  
  explicit ForwardScan(StrLen str)
   {
    for(StrLen cur=str; +cur ;++cur)
      if( Is(*cur) )
        {
         set(str,cur);
         
         return;
        }
    
    set(str);
   }
 };

template <bool Is(char ch),class To>
struct PathBase::BackwardScan : To
 {
  using To::set;
  
  explicit BackwardScan(StrLen str)
   {
    for(auto fin=str.getFin(); fin.next() ;)
      {
       if( Is(*fin) )
         {
          set(str,fin);
           
          return;
         }
      }
     
    set(str);
   }
 };

/* struct SplitDev */

struct SplitDev : PathBase
 {
  StrLen dev; // first  dev:
  StrLen dev_path;
  bool no_dev;
  
  explicit SplitDev(StrLen dev_path);
  
  bool operator ! () const { return no_dev; }
 };

/* struct SplitPath */

struct SplitPath : PathBase
 {
  StrLen dev; // all  dev1:dev2:...:
  StrLen path;
  bool no_dev;
  
  explicit SplitPath(StrLen dev_path);
  
  bool operator ! () const { return no_dev; }
 };

/* struct SplitDir */

struct SplitDir : PathBase
 {
  StrLen dir; // first  dir/
  StrLen path;
  bool no_path;
  
  explicit SplitDir(StrLen path);
  
  bool operator ! () const { return no_path; }
 };

/* struct SplitName */

struct SplitName : PathBase
 {
  StrLen path; // all  dir1/dir2/.../
  StrLen name;
  bool no_path;
  
  explicit SplitName(StrLen path);
  
  bool operator ! () const { return no_path; }
  
  NameType getNameType() const { return GetNameType(name); }
 };

/* struct SplitFullExt */

struct SplitFullExt : PathBase
 {
  StrLen name;
  StrLen ext;  // all  .ext1.ext2...
  bool no_ext;
  
  explicit SplitFullExt(StrLen name);
  
  bool operator ! () const { return no_ext; }
 };

/* struct SplitExt */

struct SplitExt : PathBase
 {
  StrLen name;
  StrLen ext;  // last  .ext
  bool no_ext;
  
  explicit SplitExt(StrLen name);
  
  bool operator ! () const { return no_ext; }
 };

/* struct SplitDevName */ 

struct SplitDevName : PathBase
 {                   
  StrLen dev_name; // first  dev_name: , : removed
  StrLen dev_path; 
  bool no_dev;
    
  explicit SplitDevName(StrLen dev_path);
  
  bool operator ! () const { return no_dev; }
 };

/* struct SplitDirName */

struct SplitDirName : PathBase
 {
  StrLen dir_name; // first  dir_name/ , / removed
  StrLen path;
  bool no_path;
  
  explicit SplitDirName(StrLen path);
  
  bool operator ! () const { return no_path; }
  
  NameType getNameType() const { return GetNameType(dir_name); }
 };
  
/* struct SplitPathName */

struct SplitPathName : PathBase
 {             
  StrLen path; // all  dir1/dir2/.../ , / removed
  StrLen name;
  bool no_path;
  
  explicit SplitPathName(StrLen path);
  
  bool operator ! () const { return no_path; }
  
  NameType getNameType() const { return GetNameType(name); }
 };

/* class Path */ 

class Path : NoCopyBase<PathBase>
 {
   static const ulen StackLen = 10 ;
 
   //
   // --- begin ---
   //
   //   <empty>
   //
   //   /
   //
   //   device:/
   //
   // --- path ---
   //
   //   <begin> 
   //
   //   <begin>.
   //
   //   <begin>dir1/dir2/.../dir_or_file , dir_or_file may == "."
   //
 
   char buf[MaxPathLen];
   ulen buf_len;
   
   ulen root_len;
   
   ulen stack[StackLen];
   ulen stack_len;
   
  private:
  
   void init()
    {
     stack[0]=root_len;
     stack_len=1;
    }
   
   void init(ulen root_len_)
    {
     root_len=root_len_;
     
     init();
    }
   
   ulen top() const { return stack[stack_len-1]; }
   
   void push(ulen len);
   
   void pop();
   
  public:
   
   enum BeginType
    {
     BeginEmpty,
     BeginRoot
    };
  
   explicit Path(BeginType=BeginRoot);
   
   explicit Path(StrLen dev_name);
   
   typedef StrLen PrintProxyType;
   
   operator StrLen() const { return StrLen(buf,buf_len); }
   
   bool isRoot() const { return buf_len==root_len ; }
   
   bool isRootDir() const { return buf_len==root_len+1 && buf[root_len]=='.' ; }
   
   void root();
   
   void rootDir();
   
   void add(StrLen name);
   
   void back();
   
   void addPath(StrLen path);
 };
 
} // namespace CCore
 
#endif
 

