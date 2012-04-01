/* CStdFile.h */ 
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

#ifndef CCore_inc_libc_CStdFile_h
#define CCore_inc_libc_CStdFile_h

#include <CCore/inc/libc/CDef.h>

namespace LibC_Internal {

/* classes */ 

//enum AccessFlag;

//enum FileResult;

template <class T> struct RetFileOp;

struct IOFile;

class StdFile;

/* enum AccessFlag */ 

enum AccessFlag
 {
  Access_Read   = 0x01, // used by StdFile     passed to FileSystem::Open    copy to IOFile
  Access_Write  = 0x02, // used by StdFile     passed to FileSystem::Open    copy to IOFile
  Access_Pos    = 0x04, // used by StdFile                                   set  to IOFile
  
  Access_Erase  = 0x08, //                     passed to FileSystem::Open
  Access_Exist  = 0x10, //                     passed to FileSystem::Open
  
  Access_Append = 0x20, // used by StdFile     passed to FileSystem::Open    copy to IOFile   require Access_Pos
  
  Access_Unused = 0x40
 };
  
/* enum FileResult */ 

enum FileResult
 {
  FileResult_EOF = -1,
  FileResult_Ok  =  0,
  
  FileResult_CloseFault,
  FileResult_SizeFault,
  FileResult_TellFault,
  FileResult_SeekFault,
  FileResult_ReadFault, 
  FileResult_WriteFault,
  
  FileResult_NoSuchOp,
  
  FileResult_OpNotPermitted,
  FileResult_Fault,
  FileResult_ShortWrite
 };
 
/* struct RetFileOp<T> */ 

template <class T> 
struct RetFileOp
 {
  FileResult result;
  T ret;
  
  RetFileOp(FileResult result_) : result(result_),ret(0) {}
  
  RetFileOp(T ret_) : result(FileResult_Ok),ret(ret_) {}
  
  operator bool() const { return !result; }
  
  bool operator ! () const { return result!=0; }
 }; 
 
/* struct IOFile */ 

struct IOFile
 {
  union Handle
   {
    int    int_handle;
    void * ptr_handle;
   };
  
  // data
   
  Handle handle;
  unsigned access_flags;
  
  // virtual methods table
  
  FileResult         (*do_close)(Handle hfile);
  
  RetFileOp<FilePos> (*do_size)(Handle hfile);
  RetFileOp<FilePos> (*do_tell)(Handle hfile);
  FileResult         (*do_seek)(Handle hfile,FilePos pos);
  
  RetFileOp<Size>    (*do_read)(Handle hfile,void *buf,Size buf_size);
  RetFileOp<Size>    (*do_write)(Handle hfile,const void *buf,Size buf_size);
  
  // methods
  
  void initNoOp();
  
  FileResult         close() { return do_close(handle); }
  
  RetFileOp<FilePos> size() { return do_size(handle); }
  RetFileOp<FilePos> tell() { return do_tell(handle); }
  FileResult         seek(FilePos pos) { return do_seek(handle,pos); }
  
  RetFileOp<Size>    read(void *buf,Size buf_size) { return do_read(handle,buf,buf_size); }
  RetFileOp<Size>    write(const void *buf,Size buf_size) { return do_write(handle,buf,buf_size); }
 };
  
/* class StdFile */ 

class StdFile
 {
   IOFile iofile;
   StdFile *tie;
 
   char buf[FileBufSize];
   
   char *put_buf;
   char *put_ptr;
   char *put_lim;
   
   char *get_buf;
   char *get_ptr;
   char *get_lim;
   
   bool nobuf_mode;
   bool linebuf_mode;
   
   bool state_EOF;
   bool state_error;
   
  private:
  
   FileResult error(FileResult result)
    {
     state_error=true;
     
     return result;
    }
  
   FileResult eof()
    {
     state_EOF=true;
     
     return FileResult_EOF;
    }
  
   void tie_flush() { if( tie ) tie->flush(); }
   
   FileResult end_get();
   FileResult end_put();
   
   FileResult begin_get();
   FileResult begin_put();
   
   FileResult begin_pos();
   
   FileResult fill(Size s,bool enable_eof=true);
   
   Size readbuf(void *buf,Size buf_size);
   
   RetFileOp<Size> writebuf(const void *buf,Size buf_size);
   
   FileResult doflush(Size s);
   
   void prepare();
   
   void null();
   
  private:
   
   StdFile(const StdFile &) = delete ;
   
   void operator = (const StdFile &) = delete ;
 
  public:
  
   StdFile() { null(); }
  
   void attach(const IOFile &iofile,StdFile *tie=0);
   
   // buf mode
  
   FileResult setFullBufMode();
   FileResult setLineBufMode();
   FileResult setNoBufMode();
   
   // state

   bool isEOF() const { return state_EOF; }
   bool isError() const { return state_error; }
   
   void clear()
    {
     state_EOF=false;
     state_error=false;
    } 
   
   // pos
   
   FileResult setPos(FilePos pos);
   
   FileResult plusPosCur(FilePos pos);
   FileResult minusPosCur(FilePos pos);
   
   FileResult plusPosEnd(FilePos pos);
   FileResult minusPosEnd(FilePos pos);
   
   RetFileOp<FilePos> getPos();
   RetFileOp<FilePos> endPos();
   
   // io
   
   RetFileOp<Size> read(void *buf,Size buf_size);
   RetFileOp<Size> write(const void *buf,Size buf_size);
   
   RetFileOp<char> get();
   FileResult put(char c);
   FileResult unget(char c);
   
   // flush
   
   FileResult flush();
   FileResult close();
 };
 
} // namespace LibC_Internal
 
#endif




