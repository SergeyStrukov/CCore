/* stdio.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/PacketPool.h>

#include <CCore/inc/libc/stdioPlanInit.h>

#include <CCore/inc/libc/CSysFile.h>
#include <CCore/inc/libc/CPrintf.h>
#include <CCore/inc/libc/CScanf.h>
#include <CCore/inc/StdioReadCon.h>

/* Mutex */ 

using CCore::Mutex;

using CCore::GetAutoText;
using CCore::AutoTextNameType;

using CCore::PlaceAt;

using namespace LibC_Internal;

/* functions */ 

static int mapresult(FileSystemResult result)
 {
  switch( result )
    {
     case FileSystemResult_NoMemory :      return ENOMEM;
     case FileSystemResult_NoSuchFile :    return ENOFILE;
     case FileSystemResult_NoSuchPath :    return ENOPATH;
     case FileSystemResult_AccessDenied :  return ENOACCESS;
     
     default: return EFAULT;
    }
 }
 
static int seterrno(FileSystemResult result)
 {
  if( result )
    {
     errno=mapresult(result);
  
     return EOF;
    }
  else
    {
     return 0;
    }  
 }
 
static int mapresult(FileResult result)
 {
  switch( result )
    {
     case FileResult_NoSuchOp :        return ENOTSUPPORTED;
     case FileResult_OpNotPermitted :  return EFAULT;
     
     default: return EIOFAULT;
    }
 }
 
static inline int seterrno(FileResult result)
 {
  if( result>0 )
    {
     errno=mapresult(result);
  
     return EOF;
    }
  else
    {
     return result?EOF:0;
    }  
 }
 
static inline int seterrno_(int e)
 {
  errno=e;
  
  return EOF;
 }
 
/* struct __std_FILE */ 

struct __std_FILE : StdFile
 {
  public: 
   
   Mutex mutex;
   
   class StdoutFILE;
   class StdinFILE;
   class StderrFILE;
   
   class Alloc;
  
  private:
  
   static AutoTextNameType ObjName;
    
   enum StorageType
    {
     Storage_dynamic,
     Storage_reserved,
     Storage_std
     
    } stype;
  
   void setst(StorageType st)
    {
     stype=st; 
    }
   
   void setstd() { setst(Storage_std); }
   
  public: 
  
   __std_FILE() : mutex(GetAutoText<ObjName>()) {}
 };
 
AutoTextNameType __std_FILE::ObjName="!StdioFILEMutex";

/* class __std_FILE::StdoutFILE */ 
   
class __std_FILE::StdoutFILE : public __std_FILE
 {
  public:
  
   StdoutFILE()
    {
     IOFile iofile;
  
     FileSystem::Stdout(iofile);
 
     attach(iofile);
  
     setstd();
  
     setLineBufMode();
    }
    
   ~StdoutFILE() 
    {
     close();
    }
 };
 
/* class __std_FILE::StdinFILE */  
  
class __std_FILE::StdinFILE : public __std_FILE
 {
  public:
  
   explicit StdinFILE(StdFile *tie)
    {
     IOFile iofile;

     FileSystem::Stdin(iofile);
  
     attach(iofile,tie);
  
     setstd();
    }
    
   ~StdinFILE()
    {
     close();
    }
 };  
 
/* class __std_FILE::StderrFILE */  
   
class __std_FILE::StderrFILE : public __std_FILE
 {
  public:
  
   explicit StderrFILE(StdFile *tie)
    {
     IOFile iofile;
  
     FileSystem::Stderr(iofile);
  
     attach(iofile,tie);
  
     setstd();
  
     setNoBufMode();
    }
    
   ~StderrFILE()
    {
     close();
    }
 };
 
/* class __std_FILE::Alloc */ 
 
class __std_FILE::Alloc
 {
   Mutex mutex;
   
   class Obj : public __std_FILE , public Link {};
 
   class ObjPool
    {
      Obj reserved[FOPEN_MAX];
      Link list;
   
     public:
  
      ObjPool()
       { 
        list.empty(); 
     
        for(Obj *ptr=reserved,*lim=ptr+FOPEN_MAX; ptr<lim ;ptr++) put(ptr);
       }
   
      ~ObjPool() {}
 
      void put(Obj *obj) { list.insAfter(obj); }
   
      Obj * get() 
       {  
        if( list.isEmpty() ) return 0;
     
        Obj *ret=static_cast<Obj *>(list.next);
     
        ret->del();
     
        return ret;
       }
    };
    
   ObjPool pool; 
   Link list;
 
  public:
  
   Alloc()
    : mutex("!StdioAllocMutex")
    {
     list.empty();
    }
   
   ~Alloc()
    {
     while( !list.isEmpty() )
       {
        Obj *ptr=static_cast<Obj *>(list.next);
     
        ptr->close();
        
        free(ptr);
       }
    }
   
   FILE * alloc()
    {
     Mutex::Lock lock(mutex);
     
     if( Obj *obj=pool.get() )
       {
        obj->setst(Storage_reserved);
     
        list.insAfter(obj);
     
        return obj;
       }
  
     if( void *mem=malloc(sizeof (Obj)) )
       {
        Obj *obj=new(PlaceAt(mem)) Obj;
     
        obj->setst(Storage_dynamic);
        
        list.insAfter(obj);
     
        return obj;
       }
       
     return 0;  
    }
    
   void free(FILE *file) 
    {
     Mutex::Lock lock(mutex);
     
     switch( file->stype )
       {
        case Storage_dynamic :
         {
          Obj *ptr=static_cast<Obj *>(file);
  
          ptr->del();
       
          ptr->~Obj();
       
          free(ptr);
         }
        break;
     
        case Storage_reserved :
         {
          Obj *ptr=static_cast<Obj *>(file);
  
          ptr->del();
  
          pool.put(ptr);
         }
        break;
       }
    }
 };
  
namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_stdio {

class Host
 {
   class AttachDetach : NoCopy
    {
     public:
     
      AttachDetach() { FileSystem::AttachStdX(); }
      
      ~AttachDetach() { FileSystem::DetachStdX(); }
       
    } attach_detach;
 
   __std_FILE::StdoutFILE file_stdout;
   __std_FILE::StdinFILE file_stdin;
   __std_FILE::StderrFILE file_stderr;
   
   __std_FILE::Alloc file_alloc;
 
  public:
  
   Host()
    : file_stdin(&file_stdout),
      file_stderr(&file_stdout)
    {
    }
   
   ~Host()
    {
    }
   
   FILE * get_stdin() { return &file_stdin; }
   
   FILE * get_stdout() { return &file_stdout; }
   
   FILE * get_stderr() { return &file_stderr; }
   
   FILE * alloc() { return file_alloc.alloc(); }
   
   void free(FILE *file) { file_alloc.free(file);  }
   
   static const char * GetTag() { return "stdio"; }
 };
 
PlanInitObject<Host,PlanInitReq<GetPlanInitNode_PacketPool>
                   ,PlanInitReq<GetPlanInitNode_StdioReadCon>
                   > Object CCORE_INITPRI_1 ;

} // namespace Private_stdio
 
using namespace Private_stdio; 
 
PlanInitNode * GetPlanInitNode_stdio() { return &Object; }
 
} // namespace CCore
 
/* std streams */ 

FILE * __std_stdin(void)
 {
  return CCore::Object->get_stdin();
 }
 
FILE * __std_stdout(void)
 {
  return CCore::Object->get_stdout();
 }
 
FILE * __std_stderr(void)
 {
  return CCore::Object->get_stderr();
 }
 
/* file functions */ 

int remove(const char *file_name)
 {
  return seterrno(FileSystem::Remove(file_name));
 }
 
int rename(const char *old_name,const char *new_name)
 {
  return seterrno(FileSystem::Rename(old_name,new_name));
 }
 
char * tmpnam(char buf[L_tmpnam])
 {
  static char intbuf[L_tmpnam];
  static unsigned ind=0;
  
  if( !buf ) buf=intbuf;
  
  const char *format=FileSystem::TmpFileNamePattern();

  do
    {  
     ind++;
     
     if( ind>TMP_MAX ) return 0;
     
     sprintf(buf,format,ind);
    }
  while( FileSystem::Exist(buf) );  
  
  return buf;
 }
 
/* FILE functions */ 

FILE * tmpfile(void)
 {
  if( FILE *ret=CCore::Object->alloc() )
    {
     IOFile iofile;
     
     FileSystemResult result=FileSystem::OpenTemp(iofile);
     
     if( result )
       {
        seterrno(result);
        
        CCore::Object->free(ret);
        
        return 0;
       }
       
     ret->attach(iofile);  
    
     return ret;
    }
  
  return 0;
 }
 
static unsigned parsetail(const char *mode) 
 {
  /*
  
     <empty> b  ->  0
     + +b b+    ->  Access_Read|Access_Write
     
     ...        ->  Access_Unused
     
  */   
  
  switch( *mode )
    {
     case 0 : return 0;
     
     case 'b' :
      {
       switch( *(++mode) )
         {
          case 0 : return 0;
          
          case '+' : if( !mode[1] ) return Access_Read|Access_Write;
         }
      }
     break;
     
     case '+' :
      {
       switch( *(++mode) )
         {
          case 0 : return Access_Read|Access_Write;
          
          case 'b' : if( !mode[1] ) return Access_Read|Access_Write;
         } 
      }
     break;
    }
    
  return Access_Unused;
 }
 
static unsigned parsemode(const char *mode) 
 {
  /*
  
     r rb        ->  Access_Read|Access_Exist
     r+ r+b rb+  ->  Access_Read|Access_Exist|Access_Write
     
     w wb        ->  Access_Write|Access_Erase
     w+ w+b wb+  ->  Access_Write|Access_Erase|Access_Read
     
     a ab        ->  Access_Write|Access_Append
     a+ a+b ab+  ->  Access_Write|Access_Append|Access_Read
     
     ...         ->  Access_Unused
  
  */

  if( mode )
    switch( *mode )
      {
       case 'r' : return Access_Read|Access_Exist|parsetail(mode+1);
       
       case 'w' : return Access_Write|Access_Erase|parsetail(mode+1);
       
       case 'a' : return Access_Write|Access_Append|parsetail(mode+1);
      }

  return Access_Unused;
 }
  
FILE * fopen(const char *file_name,const char *mode)
 {
  unsigned access_flags=parsemode(mode);
  
  if( access_flags&Access_Unused )
    {
     seterrno_(EBADARG);
    
     return 0;
    }
  
  if( FILE *ret=CCore::Object->alloc() )
    {
     IOFile iofile;
     
     FileSystemResult result=FileSystem::Open(iofile,file_name,access_flags);
     
     if( result )
       {
        seterrno(result);
        
        CCore::Object->free(ret);
       
        return 0;
       }
       
     ret->attach(iofile);  
    
     return ret;
    }
  
  return 0;
 }
 
FILE * freopen(const char *file_name,const char *mode,FILE *file)
 {
  if( !file ) 
    {
     seterrno_(EBADARG);
     
     return 0;
    }
    
  if( !file_name )  
    {
     seterrno_(ENOTSUPPORTED);
    
     return 0;
    }
    
  unsigned access_flags=parsemode(mode);
  
  if( access_flags&Access_Unused )
    {
     seterrno_(EBADARG);
    
     return 0;
    }

  FileSystemResult result;

  {  
   Mutex::Lock lock(file->mutex);  
  
   file->close();
  
   IOFile iofile;
     
   result=FileSystem::Open(iofile,file_name,access_flags);
     
   if( !result )
     {
      file->attach(iofile);  
      
      return file;
     }
  } 
    
  seterrno(result);
  
  CCore::Object->free(file);
        
  return 0;
 }
 
int fflush(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  return seterrno(file->flush());
 }
 
int fclose(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);

  FileResult result;

  {
   Mutex::Lock lock(file->mutex);
   
   result=file->close();
  }
  
  CCore::Object->free(file);
  
  return seterrno(result);
 }
 
void setbuf(FILE *file,char buf[BUFSIZ])
 {
  if( buf )
    {
     setvbuf(file,buf,_IOFBF,BUFSIZ);
    }
  else
    {
     setvbuf(file,0,_IONBF,0);
    }
 }
 
int setvbuf(FILE *file,char *,int buf_mode,size_t)
 {
  if( !file ) return seterrno_(EBADARG);
 
  Mutex::Lock lock(file->mutex);
 
  switch( buf_mode )
    {
     case _IOFBF : return seterrno(file->setFullBufMode());
     
     case _IOLBF : return seterrno(file->setLineBufMode());
     
     case _IONBF : return seterrno(file->setNoBufMode());
     
     default: return seterrno_(EBADARG);
    }
 }
 
/* FILE error function */ 

int feof(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
 
  Mutex::Lock lock(file->mutex);
 
  return file->isEOF()?EOF:0;
 }
 
int ferror(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
 
  Mutex::Lock lock(file->mutex);
 
  return file->isError()?EOF:0;
 }
 
void clearerr(FILE *file)
 {
  if( !file ) return (void)seterrno_(EBADARG);
 
  Mutex::Lock lock(file->mutex);
 
  file->clear();
 }
 
/* FILE position functions */ 

int fgetpos(FILE *file,fpos_t *ret_)
 {
  if( !file || !ret_ ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  RetFileOp<FilePos> op=file->getPos();
  
  if( op ) 
    {
     (*ret_)=op.ret;
     
     return 0;
    }
  
  return seterrno(op.result);
 }
 
long ftell(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  RetFileOp<FilePos> op=file->getPos();
  
  if( !op ) return seterrno(op.result);
  
  return (long)op.ret;
 }
 
fpos_t ftell_ext(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  RetFileOp<FilePos> op=file->getPos();
  
  if( !op ) return seterrno(op.result);
  
  return op.ret;
 }
 
fpos_t fsize(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  RetFileOp<FilePos> op=file->endPos();
  
  if( !op ) return seterrno(op.result);
  
  return op.ret;
 }
 
int fsetpos(FILE *file,const fpos_t *pos)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  return seterrno(file->setPos(*pos));
 }
 
int fseek(FILE *file,long offset,int from_flag)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  switch( from_flag )
    {
     case SEEK_SET : 
      {
       if( offset<0 ) return seterrno_(ERANGE);
      
       FilePos pos=FilePos(offset);
      
       return seterrno(file->setPos(pos));
      }
     
     case SEEK_CUR : 
      {
       if( offset<0 )
         {
          FilePos pos=-FilePos(offset);
         
          return seterrno(file->minusPosCur(pos));
         }
       else
         {
          FilePos pos=FilePos(offset);
         
          return seterrno(file->plusPosCur(pos));
         }
      }
     
     case SEEK_END : 
      {
       if( offset<0 )
         {
          FilePos pos=-FilePos(offset);
         
          return seterrno(file->minusPosEnd(pos));
         }
       else
         {
          FilePos pos=FilePos(offset);
         
          return seterrno(file->plusPosEnd(pos));
         }
      }
     
     default: return seterrno_(EBADARG);
    }
 }
 
int fseek_ext(FILE *file,fpos_t offset,int from_flag)
 {
  const fpos_t msbit=fpos_t(-1)^(fpos_t(-1)>>1);
 
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
 
  switch( from_flag )
    {
     case SEEK_SET : 
      {
       if( offset&msbit ) return seterrno_(ERANGE);
      
       FilePos pos=FilePos(offset);
      
       return seterrno(file->setPos(pos));
      }
     
     case SEEK_CUR : 
      {
       if( offset&msbit )
         {
          FilePos pos=-FilePos(offset);
         
          return seterrno(file->minusPosCur(pos));
         }
       else
         {
          FilePos pos=FilePos(offset);
         
          return seterrno(file->plusPosCur(pos));
         }
      }
     
     case SEEK_END : 
      {
       if( offset&msbit )
         {
          FilePos pos=-FilePos(offset);
         
          return seterrno(file->minusPosEnd(pos));
         }
       else
         {
          FilePos pos=FilePos(offset);
         
          return seterrno(file->plusPosEnd(pos));
         }
      }
     
     default: return seterrno_(EBADARG);
    }
 }
 
void rewind(FILE *file)
 {
  if( !file ) return (void)seterrno_(EBADARG);
 
  Mutex::Lock lock(file->mutex);
  
  file->setPos(0);
  file->clear();
 }
 
/* FILE read/write functions */ 

size_t fread(void *buf,size_t elem_size,size_t elem_count,FILE *file)
 {
  size_t s=elem_size*elem_count;
  
  if( !s ) return 0;
  
  if( !file ) return seterrno_(EBADARG),0;
  
  Mutex::Lock lock(file->mutex);
  
  RetFileOp<Size> op=file->read(buf,s);
  
  if( op )
    {
     return op.ret/elem_size;
    }
  else
    {
     return seterrno(op.result),0;
    }  
 }
 
size_t fwrite(const void *buf,size_t elem_size,size_t elem_count,FILE *file)
 {
  size_t s=elem_size*elem_count;
  
  if( !s ) return 0;
  
  if( !file ) return seterrno_(EBADARG),0;
  
  Mutex::Lock lock(file->mutex);
  
  RetFileOp<Size> op=file->write(buf,s);
  
  if( op )
    {
     return op.ret/elem_size;
    }
  else
    {
     return seterrno(op.result),0;
    }  
 }
 
/* FILE io functions */ 

int fgetc(FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
  
  RetFileOp<char> op=file->get();
  
  if( op )
    {
     return (unsigned char)op.ret;
    }
  else
    {
     return seterrno(op.result);
    }  
 }
 
char * fgets(char *buf,size_t buf_size,FILE *file)
 {
  if( !file ) return seterrno_(EBADARG),(char *)0;
  
  if( !buf_size ) return buf;
 
  Mutex::Lock lock(file->mutex);
  
  char *out=buf;
  char *lim=buf+buf_size-1;
  
  while( out<lim )
    {
     RetFileOp<char> op=file->get();
     
     if( op )
       {
        *(out++)=op.ret;
        
        if( op.ret=='\n' ) break;
       }
     else
       {
        seterrno(op.result);
       
        if( file->isError() || out==buf ) return 0;
           
        break;
       }
    }
    
  *out=0;
  
  return buf;
 }
 
int fputc(int c,FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);

  Mutex::Lock lock(file->mutex);
  
  if( FileResult result=file->put(char(c)) ) return seterrno(result);
  
  return (unsigned char)c;
 }
 
int fputs(const char *str,FILE *file)
 {
  if( !file ) return seterrno_(EBADARG);

  Mutex::Lock lock(file->mutex);
  
  for(; char c=(*str) ;str++)
    if( FileResult result=file->put(c) ) 
      return seterrno(result);
  
  return 0;
 }
 
int ungetc(int c,FILE *file)
 {
  if( !file || c==EOF ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
  
  if( FileResult result=file->unget(char(c)) ) return seterrno(result);
  
  return (unsigned char)c;
 }
 
int getc(FILE *file)
 {
  return fgetc(file);
 }
 
int putc(int c,FILE *file)
 {
  return fputc(c,file);
 }
 
int getchar(void)
 {
  return fgetc(stdin);
 }
 
int putchar(int c)
 {
  return fputc(c,stdout);
 }
 
char * gets(char *buf)
 {
  FILE *file=stdin;
  char *out=buf;
  
  Mutex::Lock lock(file->mutex);
  
  for(;;)
    {
     RetFileOp<char> op=file->get();
     
     if( op )
       {  
        if( op.ret=='\n' ) break;
        
        *(out++)=op.ret;
       }
     else
       {
        seterrno(op.result);
       
        if( file->isError() || out==buf ) return 0;
           
        break;
       }
    }
    
  *out=0;
  
  return buf;
 }
 
int puts(const char *str)
 {
  FILE *file=stdout;
 
  if( fputs(str,file)==EOF ) return EOF;
  
  if( fputc('\n',file)==EOF ) return EOF;
  
  return 0;
 }
 
/* format functions */ 

int fprintf(FILE *file,const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vfprintf(file,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int fscanf(FILE *file,const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vfscanf(file,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int printf(const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vfprintf(stdout,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int scanf(const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vfscanf(stdin,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int sprintf(char *buf,const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vsprintf(buf,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int snprintf(char *buf,size_t buf_size,const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vsnprintf(buf,buf_size,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
int sscanf(const char *str,const char *format,...)
 {
  va_list arg;
  
  va_start(arg,format);
  
  int ret=vsscanf(str,format,arg);
  
  va_end(arg);
  
  return ret;
 }
 
namespace LibC_Internal {

/* struct InArg */

struct InArg
 {
  va_list arg;
  
  typedef va_list InitType;
  
  explicit InArg(InitType arg_) : arg(arg_) {}
 
  template <class T>
  T get();
 };
 
#define DEF(T)  template <> inline T InArg::get<T>() { return va_arg(arg,T); }

  DEF(int)
  DEF(long)
  DEF(long long)

  DEF(unsigned)
  DEF(unsigned long)
  DEF(unsigned long long)

  DEF(const void *)
  DEF(const char *)
  
  DEF(signed char *)
  DEF(short *)
  DEF(int *)
  DEF(long *)
  DEF(long long *)

#undef DEF

/* struct Out_FILE */
  
struct Out_FILE
 {
  FILE *file;
  bool error;
 
  typedef FILE * InitType;
  
  explicit Out_FILE(InitType file_) 
   : file(file_)
   {
    if( !file_ )
      {
       seterrno_(EBADARG);
       error=true;
      }
    else
      {
       error=false;
      }  
   }
  
  bool operator ! () const { return error; }
  
  void put(char c)
   {
    if( !error )
      if( FileResult result=file->put(c) ) 
        {
         seterrno(result);
         error=true;
        }
   }
   
  void put(const char *s,size_t cnt) 
   {
    if( !error )
      for(; cnt ;cnt--)
        if( FileResult result=file->put(*(s++)) ) 
          {
           seterrno(result);
           error=true;
           return;
          }
   }
    
  void pad(size_t cnt,char c) 
   {
    if( !error )
      for(; cnt ;cnt--)
        if( FileResult result=file->put(c) ) 
          {
           seterrno(result);
           error=true;
           return;
          }
   }
   
  void complete() {} 
 }; 
 
/* struct Out_str */  
  
struct Out_str
 {
  char *out;
 
  typedef char * InitType;
  
  explicit Out_str(InitType buf) : out(buf) {}
  
  bool operator ! () const { return false; }
  
  void put(char c) { *(out++)=c; }
  
  void put(const char *s,size_t cnt) 
   {
    memcpy(out,s,cnt);
    out+=cnt;
   }
    
  void pad(size_t cnt,char c) 
   {
    memset(out,c,cnt);
    out+=cnt;
   }
   
  void complete() { put(0); } 
 }; 
 
/* struct Out_strn */

struct Out_strn
 {
  char *out;
  char *lim;
  bool nonempty;
  
  struct InitType
   {
    char *buf;
    size_t buf_size;
    
    InitType(char *buf_,size_t buf_size_) : buf(buf_),buf_size(buf_size_) {}
    
    char * lim() const { return buf+buf_size; }
   };
 
  explicit Out_strn(InitType init) : out(init.buf),lim(init.lim()) 
   {
    if( out<lim )
      {
       nonempty=true;
       lim--;
      }
    else
      {
       nonempty=false;
      }
   }
  
  bool operator ! () const { return false; }
  
  void put(char c) { if( out<lim ) *(out++)=c; }
  
  void put(const char *s,size_t cnt) 
   {
    size_t avail=size_t(lim-out);
    
    if( cnt>avail ) cnt=avail;
    
    memcpy(out,s,cnt);
    out+=cnt;
   }
    
  void pad(size_t cnt,char c) 
   {
    size_t avail=size_t(lim-out);
    
    if( cnt>avail ) cnt=avail;
    
    memset(out,c,cnt);
    out+=cnt;
   }
   
  void complete() 
   {
    if( nonempty ) (*out)=0;
   } 
 }; 
 
/* struct OutArg */

struct OutArg
 {
  va_list arg;
  
  typedef va_list InitType;
  
  explicit OutArg(InitType arg_) : arg(arg_) {}
  
  template <class T>
  T * get();
 };
 
#define DEF(T)  template <> inline T * OutArg::get<T>() { return va_arg(arg,T *); }

  DEF(char)

  DEF(signed char)
  DEF(short)
  DEF(int)
  DEF(long)
  DEF(long long)

  DEF(unsigned char)
  DEF(unsigned short)
  DEF(unsigned)
  DEF(unsigned long)
  DEF(unsigned long long)

#undef DEF
  
/* struct In_FILE */  
  
struct In_FILE
 {
  FILE *file;
  
  Peek cur;
  bool stop;
  
  typedef FILE * InitType;
  
  explicit In_FILE(InitType file_) : file(file_),cur(),stop(false) {}
  
  bool operator ! () const { return stop; }
  
  Peek peek()
   {
    if( stop ) return Peek();
    
    if( !cur )
      {
       auto result=file->get();
       
       if( !result )
         {
          stop=true;
         }
       else
         {
          cur=result.ret;
         }
      }
     
    return cur;
   }
  
  void next()
   {
    cur=Peek();
   }
  
  void complete() 
   {
    if( +cur ) 
      {
       if( file->unget(cur.ch) ) stop=true;
      }
   }
 }; 
 
/* struct In_str */  
  
struct In_str
 {
  const char *str;
  
  typedef const char * InitType;
  
  explicit In_str(InitType str_) : str(str_) {}
  
  bool operator ! () const { return false; }
  
  Peek peek()
   {
    if( char ret=*str ) return ret;
    
    return Peek();
   }
  
  void next()
   {
    str++;
   }
  
  void complete() {}
 }; 
 
} // namespace LibC_Internal
 
int vfprintf(FILE *file,const char *format,va_list arg)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
  
  PrintfContext<Out_FILE,InArg> ctx(file,arg);
 
  return ctx.format(format);
 }
 
int vfscanf(FILE *file,const char *format,va_list arg)
 {
  if( !file ) return seterrno_(EBADARG);
  
  Mutex::Lock lock(file->mutex);
  
  ScanfContext<In_FILE,OutArg> ctx(file,arg);
  
  return ctx.scan(format);
 }
 
int vprintf(const char *format,va_list arg)
 {
  return vfprintf(stdout,format,arg);
 }
 
int vscanf(const char *format,va_list arg)
 {
  return vfscanf(stdin,format,arg);
 }
 
int vsprintf(char *buf,const char *format,va_list arg)
 {
  PrintfContext<Out_str,InArg> ctx(buf,arg);
 
  return ctx.format(format);
 }
 
int vsnprintf(char *buf,size_t buf_size,const char *format,va_list arg)
 {
  PrintfContext<Out_strn,InArg> ctx(Out_strn::InitType(buf,buf_size),arg);
 
  return ctx.format(format);
 }
 
int vsscanf(const char *str,const char *format,va_list arg)
 {
  ScanfContext<In_str,OutArg> ctx(str,arg);
  
  return ctx.scan(format);
 }
  
/* misc functions */ 

void perror(const char *str)
 {
  const char *errstr=strerror(errno);
 
  if( !str ) str="";
  
  fprintf(stderr,"%s: %s\n",str,errstr);
 }
 
