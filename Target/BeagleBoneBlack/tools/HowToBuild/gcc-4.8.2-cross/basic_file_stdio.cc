/* basic_file.cpp */ 
/*
/
/   NeatCLib
/
/   Copyright © 2007 Sergey Strukov. All rights reserved.
/
*/

#include <fstream>

static const char * toc_mode(std::ios_base::openmode mode)
 {
  enum 
   {
    in     = std::ios_base::in,
    out    = std::ios_base::out,
    trunc  = std::ios_base::trunc,
    app    = std::ios_base::app,
    binary = std::ios_base::binary
   };
    
  switch( mode&(in|out|trunc|app|binary) )
   {
    case (   out                 ): return "w";  
    case (   out      |app       ): return "a";  
    case (   out|trunc           ): return "w";  
    case (in                     ): return "r";  
    case (in|out                 ): return "r+"; 
    case (in|out|trunc           ): return "w+"; 
	
    case (   out          |binary): return "wb"; 
    case (   out      |app|binary): return "ab"; 
    case (   out|trunc    |binary): return "wb"; 
    case (in              |binary): return "rb"; 
    case (in|out          |binary): return "r+b";
    case (in|out|trunc    |binary): return "w+b";
	
    default: return 0;
   }
 }

namespace std {

__basic_file<char>::__basic_file(__c_lock *)
 : _M_cfile(0),
   _M_cfile_created(false)
 {
 }

__basic_file<char> * __basic_file<char>::open(const char *name,ios_base::openmode mode,int)
 {
  if( _M_cfile ) return 0;

  if( const char *c_mode=toc_mode(mode) )
    {
     if( FILE *file=fopen(name,c_mode) )
       {
        _M_cfile=file;
        _M_cfile_created=true;

        return this;
       }
    }

  return 0;
 }

__basic_file<char> * __basic_file<char>::sys_open(FILE *file,ios_base::openmode)
 {
  if( _M_cfile || !file ) return 0;

  if( sync() ) return 0;

  _M_cfile=file;
  _M_cfile_created=false;

  return this;
 }

__basic_file<char> * __basic_file<char>::sys_open(int,ios_base::openmode)
 {
  // NOT SUPPORTED

  return 0;
 }

__basic_file<char> * __basic_file<char>::close()
 {
  if( FILE *toclose=_M_cfile )
    {
     _M_cfile=0;

     if( _M_cfile_created )
       {
        if( fclose(toclose) ) return 0;
       }

     return this;
    }

  return 0;
 }

bool __basic_file<char>::is_open() const 
 {
  return _M_cfile!=0;
 }

int __basic_file<char>::fd() 
 {
  // NOT SUPPORTED

  return -1;
 }

FILE * __basic_file<char>::file() 
 {
  return _M_cfile;
 }

__basic_file<char>::~__basic_file() 
 {
  close();
 }

streamsize __basic_file<char>::xsputn(const char *s,streamsize n)
 {
  return fwrite(s,1,n,_M_cfile);
 }

streamsize __basic_file<char>::xsputn_2(const char *s1,streamsize n1,const char *s2,streamsize n2)
 {
  streamsize ret=fwrite(s1,1,n1,_M_cfile);

  if( ret!=n1 ) return ret;

  return n1+fwrite(s2,1,n2,_M_cfile);
 }

streamsize __basic_file<char>::xsgetn(char *s,streamsize n)
 {
  return fread(s,1,n,_M_cfile);
 }

int __basic_file<char>::sync()
 {
  return fflush(_M_cfile);
 }

streamoff __basic_file<char>::seekoff(streamoff off,ios_base::seekdir way)
 {
  if( off<LONG_MIN || off>LONG_MAX ) return streamoff(-1);

  int flag;

  switch( way )
    {
     case ios_base::beg : flag=SEEK_SET; break;
     case ios_base::cur : flag=SEEK_CUR; break;
     case ios_base::end : flag=SEEK_END; break;
     default: return streamoff(-1);
    }

  if( fseek(_M_cfile,long(off),flag) ) return streamoff(-1);

  return streamoff( ftell(_M_cfile) );
 }

streamsize __basic_file<char>::showmanyc()
 {
  long cur=ftell(_M_cfile);

  if( cur==-1 ) return 0;

  long end=fsize(_M_cfile);

  if( end==-1 ) return 0;

  return streamsize(end-cur);
 }

} // namespace std

