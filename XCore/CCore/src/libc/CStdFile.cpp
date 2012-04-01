/* CStdFile.cpp */ 
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

#include <CCore/inc/libc/CStdFile.h>

#include <string.h>

namespace LibC_Internal {

/* struct IOFile */ 

template <class R,class ... TT>
R NoOpFileFunction(TT...)
 {
  return FileResult_NoSuchOp;
 }
 
void IOFile::initNoOp()
 {
  handle.ptr_handle=0;
  access_flags=0;
  
  do_close=NoOpFileFunction<FileResult,Handle>;
  do_size=NoOpFileFunction<RetFileOp<FilePos>,Handle>;
  do_tell=NoOpFileFunction<RetFileOp<FilePos>,Handle>;
  do_seek=NoOpFileFunction<FileResult,Handle,FilePos>;
  do_read=NoOpFileFunction<RetFileOp<Size>,Handle,void *,Size>;
  do_write=NoOpFileFunction<RetFileOp<Size>,Handle,const void *,Size>;
 }
 
/* class StdFile */ 

FileResult StdFile::end_get()
 {
  if( get_buf )
    {
     FilePos s=FilePos( get_lim-get_ptr );
        
     get_buf=0;
        
     if( s )
       {
        RetFileOp<FilePos> op=iofile.tell();
        
        if( !op ) return error(op.result);
          
        FilePos pos=op.ret-s;  
          
        if( FileResult ret=iofile.seek(pos) ) return error(ret);
       }
    }
    
  return FileResult_Ok;     
 }
 
FileResult StdFile::end_put()
 {
  if( put_buf )
    {
     FileResult ret=flush();
     
     put_buf=0;
     
     return ret;
    }
    
  return FileResult_Ok;     
 }
    
FileResult StdFile::begin_get()
 {
  if( FileResult ret=end_put() ) return ret;
    
  get_buf=buf;
  get_ptr=buf+FileBufSize;
  get_lim=buf+FileBufSize;
  
  return FileResult_Ok;     
 }
 
FileResult StdFile::begin_put()
 {
  if( FileResult ret=end_get() ) return ret;
  
  if( iofile.access_flags&Access_Append )
    {
     RetFileOp<FilePos> op=iofile.size();
        
     if( !op ) return error(op.result);
          
     if( FileResult ret=iofile.seek(op.ret) ) return error(ret);
    }
       
  put_buf=buf;
  put_ptr=buf;
  put_lim=buf+FileBufSize;
     
  return FileResult_Ok;     
 }
 
FileResult StdFile::begin_pos()
 {
  if( FileResult ret=end_put() ) return ret;
  
  if( FileResult ret=end_get() ) return ret;
  
  state_EOF=false;
  
  return FileResult_Ok;
 }
 
FileResult StdFile::fill(Size s,bool enable_eof)
 {
  RetFileOp<Size> op=iofile.read(get_buf+1,s);
  
  if( !op ) return error(op.result);
    
  if( !op.ret && enable_eof ) return eof(); 
    
  get_ptr=get_buf+1;
  get_lim=get_ptr+op.ret;  
  
  return FileResult_Ok;     
 }
 
Size StdFile::readbuf(void *buf,Size buf_size)
 {
  Size s=Min( Size( get_lim-get_ptr ) , buf_size );
     
  memcpy(buf,get_ptr,s);  
     
  get_ptr+=s;
  
  return s;
 }
  
RetFileOp<Size> StdFile::writebuf(const void *buf,Size buf_size)
 {
  RetFileOp<Size> op=iofile.write(buf,buf_size);
     
  if( !op ) return error(op.result);
     
  if( op.ret!=buf_size ) return error(FileResult_ShortWrite); 
  
  return buf_size;
 }
  
FileResult StdFile::doflush(Size s)
 {
  put_ptr=put_buf;
     
  RetFileOp<Size> op=iofile.write(put_buf,s);
     
  if( !op ) return error(op.result);
       
  if( op.ret!=s ) return error(FileResult_ShortWrite); 
  
  return FileResult_Ok;  
 }
  
void StdFile::prepare()
 {
  put_buf=0;
  put_ptr=0;
  put_lim=0;
  
  get_buf=0;
  get_ptr=0;
  get_lim=0;
  
  nobuf_mode=false;
  linebuf_mode=false;
  
  state_EOF=false;
  state_error=false;
 }

void StdFile::null()
 {
  iofile.initNoOp();
  
  tie=0;
  
  prepare();
 }

void StdFile::attach(const IOFile &iofile_,StdFile *tie_)
 {
  iofile=iofile_;
  tie=tie_;

  prepare();
 }
    
 // buf mode
  
FileResult StdFile::setFullBufMode()
 {
  if( state_error ) return FileResult_Fault;
  
  if( FileResult ret=flush() ) return ret;
  
  nobuf_mode=false;
  linebuf_mode=false;

  return FileResult_Ok;
 }
 
FileResult StdFile::setLineBufMode()
 {
  if( state_error ) return FileResult_Fault;
  
  if( FileResult ret=flush() ) return ret;
  
  nobuf_mode=false;
  linebuf_mode=true;

  return FileResult_Ok;
 }
 
FileResult StdFile::setNoBufMode()
 {
  if( state_error ) return FileResult_Fault;
  
  if( FileResult ret=flush() ) return ret;
  
  nobuf_mode=true;
  linebuf_mode=false;

  return FileResult_Ok;
 }
    
 // pos
   
FileResult StdFile::setPos(FilePos pos)
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  if( FileResult ret=begin_pos() ) return ret;
  
  if( FileResult ret=iofile.seek(pos) ) return error(ret);
  
  return FileResult_Ok;
 }
   
FileResult StdFile::plusPosCur(FilePos pos)
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  if( FileResult ret=begin_pos() ) return ret;
  
  RetFileOp<FilePos> op=iofile.tell();
        
  if( !op ) return error(op.result);
          
  pos=op.ret+pos;  
          
  if( FileResult ret=iofile.seek(pos) ) return error(ret);
        
  return FileResult_Ok;
 }
 
FileResult StdFile::minusPosCur(FilePos pos)
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  if( FileResult ret=begin_pos() ) return ret;
  
  RetFileOp<FilePos> op=iofile.tell();
        
  if( !op ) return error(op.result);
  
  if( pos>op.ret ) return error(FileResult_OpNotPermitted);
          
  pos=op.ret-pos;  
          
  if( FileResult ret=iofile.seek(pos) ) return error(ret);
        
  return FileResult_Ok;
 }
   
FileResult StdFile::plusPosEnd(FilePos pos)
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  if( FileResult ret=begin_pos() ) return ret;
  
  RetFileOp<FilePos> op=iofile.size();
        
  if( !op ) return error(op.result);
          
  pos=op.ret+pos;  
          
  if( FileResult ret=iofile.seek(pos) ) return error(ret);
        
  return FileResult_Ok;
 }
 
FileResult StdFile::minusPosEnd(FilePos pos)
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  if( FileResult ret=begin_pos() ) return ret;
  
  RetFileOp<FilePos> op=iofile.size();
        
  if( !op ) return error(op.result);
  
  if( pos>op.ret ) return error(FileResult_OpNotPermitted);
          
  pos=op.ret-pos;  
          
  if( FileResult ret=iofile.seek(pos) ) return error(ret);
        
  return FileResult_Ok;
 }
   
RetFileOp<FilePos> StdFile::getPos()
 {
  if( state_error ) return FileResult_Fault;

  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  RetFileOp<FilePos> op=iofile.tell();
     
  if( !op ) return error(op.result);
       
  if( put_buf )
    {
     op.ret+=FilePos( put_ptr-put_buf );
    }
  else if( get_buf )
    {
     op.ret-=FilePos( get_lim-get_ptr );
    }
    
  return op;
 }
    
RetFileOp<FilePos> StdFile::endPos()
 {
  if( state_error ) return FileResult_Fault;
  
  if( !(iofile.access_flags&Access_Pos) ) return FileResult_OpNotPermitted;
  
  return iofile.size();
 }
 
 // io
   
RetFileOp<Size> StdFile::read(void *buf,Size buf_size)
 {
  if( state_error ) return FileResult_Fault;
  
  if( state_EOF ) return FileResult_EOF;
 
  if( !(iofile.access_flags&Access_Read) ) return FileResult_OpNotPermitted;
  
  tie_flush();
  
  if( !get_buf )
    {
     if( FileResult ret=begin_get() ) return ret;
    }
    
  if( !buf_size ) return 0;
  
  Size ret_size=readbuf(buf,buf_size);
  
  if( ret_size>=buf_size ) return buf_size;
       
  buf=PtrAdd(buf,ret_size);
  buf_size-=ret_size;
   
  if( nobuf_mode || buf_size>=FileBufSize-1 )
    {
     RetFileOp<Size> op=iofile.read(buf,buf_size);
     
     if( !op ) return error(op.result);
         
     ret_size+=op.ret;
    }
  else
    {
     if( FileResult ret=fill(FileBufSize-1,false) ) return ret;
           
     Size s=readbuf(buf,buf_size);     
     
     ret_size+=s;
    }
    
  if( !ret_size ) return eof();

  return ret_size;
 }
 
RetFileOp<Size> StdFile::write(const void *buf,Size buf_size)
 {
  if( state_error ) return FileResult_Fault;
 
  if( !(iofile.access_flags&Access_Write) ) return FileResult_OpNotPermitted;
  
  tie_flush();
  
  if( !put_buf )  
    {
     if( FileResult ret=begin_put() ) return ret;
    }

  if( nobuf_mode ) return writebuf(buf,buf_size);

  Size s=Size( put_lim-put_ptr );
  
  if( buf_size<=s )
    {
     memcpy(put_ptr,buf,buf_size);
     
     put_ptr+=buf_size;
     
     return buf_size;
    }
    
  if( put_ptr==put_buf ) return writebuf(buf,buf_size); 
    
  memcpy(put_ptr,buf,s);  
  
  if( FileResult ret=doflush(FileBufSize) ) return ret;
  
  Size initial_size=buf_size;
  
  buf=PtrAdd(buf,s);
  buf_size-=s;
    
  if( buf_size<=FileBufSize )
    {
     memcpy(put_ptr,buf,buf_size);
     
     put_ptr+=buf_size;
     
     return initial_size;
    }
    
  RetFileOp<Size> op=writebuf(buf,buf_size);  
  
  if( !op ) return op.result;
    
  return initial_size;
 }
   
RetFileOp<char> StdFile::get()
 {
  if( state_error ) return FileResult_Fault;
  
  if( state_EOF ) return FileResult_EOF;
 
  if( !(iofile.access_flags&Access_Read) ) return FileResult_OpNotPermitted;
  
  tie_flush();
  
  if( !get_buf )
    {
     if( FileResult ret=begin_get() ) return ret;
    }
    
  if( get_ptr>=get_lim )  
    {
     Size s=nobuf_mode?1:(FileBufSize-1);
     
     if( FileResult ret=fill(s) ) return ret;
    }
    
  return *(get_ptr++);  
 }
 
FileResult StdFile::put(char c)
 {
  if( state_error ) return FileResult_Fault;
 
  if( !(iofile.access_flags&Access_Write) ) return FileResult_OpNotPermitted;
  
  tie_flush();
  
  if( !put_buf )  
    {
     if( FileResult ret=begin_put() ) return ret;
    }
    
  if( put_ptr>=put_lim )  
    {
     if( FileResult ret=flush() ) return ret;
    }
    
  *(put_ptr++)=c;
  
  if( nobuf_mode || ( linebuf_mode && c=='\n' ) )
    {
     if( FileResult ret=flush() ) return ret;
    }
  
  return FileResult_Ok;  
 }
 
FileResult StdFile::unget(char c)
 {
  if( state_error ) return FileResult_Fault;
  
  if( !(iofile.access_flags&Access_Read) ) return FileResult_OpNotPermitted;
  
  if( !get_buf )
    {
     if( FileResult ret=begin_get() ) return ret;
    }
    
  if( get_buf<get_ptr )  
    {
     *(--get_ptr)=c;
    
     state_EOF=false;
     
     return FileResult_Ok; 
    }
  else
    {
     return FileResult_EOF;  
    }
 }
    
 // flush
   
FileResult StdFile::flush()
 {
  if( state_error ) return FileResult_Fault;
 
  tie_flush();
  
  if( put_buf )
    {
     if( Size s=Size( put_ptr-put_buf ) ) return doflush(s);
    }
    
  return FileResult_Ok;  
 }
  
FileResult StdFile::close()
 {
  FileResult ret1=flush();
  FileResult ret2=iofile.close();
  
  null();
  
  if( ret2 ) return ret2;
  
  return ret1;
 }
 
} // namespace LibC_Internal
 

