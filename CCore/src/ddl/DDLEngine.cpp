/* DDLEngine.cpp */
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

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLMsgReport.h>

#include <CCore/inc/Crc.h>

namespace CCore {
namespace DDL {

/* struct EngineResult */

EngineResult::EngineResult(PrintBase &msg,Process<Eval> &proc,ParserResult result)
 : eval(0),
   body(0)
 {
  MsgReport report(msg);
  
  try
    {
     {
      if( !result ) return;
      
      Eval &eval_=proc(result.body,result.rev_list);
      
      if( !eval_ ) return;
      
      eval=&eval_;
      body=result.body;
     }
     
     report.guard();
    }
  catch(CatchType)
    {
     eval=0;
     body=0;
     
     report.print("\nFatal error\n");
    }
 }

/* class TextEngine */

auto TextEngine::openFile(StrLen) -> File 
 { 
  return File(&id,text); 
 }
     
ParserResult TextEngine::parse() 
 { 
  return parseFile(StrLen()); 
 }

TextEngine::TextEngine(PrintBase &msg,StrLen text_) 
 : ParserContext(msg),
   text(text_),
   proc(getPool(),getPool(),msg)
 {
 }

TextEngine::~TextEngine() 
 {
 }

EngineResult TextEngine::process()
 {
  proc.reset();
  
  return EngineResult(getMsg(),proc,parse());
 }

/* class FileName */

FileName::PathUp::PathUp(StrLen path,ulen up)
 : ok(false)
 {
  SplitPath split_dev(path);
  
  ulen len=split_dev.path.len;
  
  for(; len && up ;up--)
    {
     if( !--len ) return;
     
     for(; len && !IsSlash(split_dev.path[len-1]) ;len--);
    }

  set(path.prefix(split_dev.dev.len+len),up);
 }

void FileName::setAbs(StrLen file_name,SplitPath split_dev,SplitPathName split_file)
 {
  if( split_file.no_path )
    {
     buf.extend_copy(file_name.len,file_name.ptr);
     
     off=split_dev.dev.len;
    }
  else
    {
     DynArray<StrLen> list(DoReserve,10);
     ulen up=0;
     bool root=false;
     
     list.append_copy(split_file.name);
     
     StrLen path=split_file.path;
     
     for(;;)
       {
        SplitPathName split_path(path);
        
        switch( split_path.getNameType() )
          {
           case SplitPathName::Name :
            {
             if( up )
               up--;
             else
               list.append_copy(split_path.name);
            }
           break;
           
           case SplitPathName::EmptyName :
            {
             if( !split_path.no_path || up ) return;
             
             root=true;
            }
           break;
           
           case SplitPathName::DotName :
            {
             // skip
            }
           break;
           
           case SplitPathName::DotDotName :
            {
             up++;
            }
           break;
          }
        
        if( split_path.no_path ) break;
        
        path=split_path.path;
       }
     
     ulen len=split_dev.dev.len;
     
     if( root ) len++;
     
     len+=3*up;
     
     for(ulen i=list.getLen()-1; i ;i--) len+=list[i].len+1;
     
     off=len;
     
     len+=list[0].len;
     
     Out out(buf,len);
     
     out(split_dev.dev);
     
     if( root ) out('/');
     
     for(; up ;up--) out('.','.','/'); 
     
     for(ulen i=list.getLen()-1; i ;i--) out(list[i],'/');
     
     out(list[0]);
    }

  ok=true;
 }

void FileName::setRel(StrLen path,SplitPathName split_file)
 {
  if( split_file.no_path )
    {
     ulen len=path.len+split_file.name.len;
     
     Out out(buf,len);
     
     out(path,split_file.name);
     
     off=path.len;
    }
  else
    {
     DynArray<StrLen> list(DoReserve,10);
     ulen up=0;
     
     list.append_copy(split_file.name);
     
     StrLen p=split_file.path;
     
     for(;;)
       {
        SplitPathName split_path(p);
        
        switch( split_path.getNameType() )
          {
           case SplitPathName::Name :
            {
             if( up )
               up--;
             else
               list.append_copy(split_path.name);
            }
           break;
           
           case SplitPathName::EmptyName :
            {
             return;
            }
           break;
           
           case SplitPathName::DotName :
            {
             // skip
            }
           break;
           
           case SplitPathName::DotDotName :
            {
             up++;
            }
           break;
          }
        
        if( split_path.no_path ) break;
        
        p=split_path.path;
       }
     
     if( up )
       {
        PathUp path_up(path,up);
        
        if( !path_up ) return;
        
        path=path_up.path;
        up=path_up.up;
       }
     
     ulen len=path.len;
     
     len+=3*up;
     
     for(ulen i=list.getLen()-1; i ;i--) len+=list[i].len+1;
     
     off=len;
     
     len+=list[0].len;
     
     Out out(buf,len);
     
     out(path);
     
     for(; up ;up--) out('.','.','/'); 
     
     for(ulen i=list.getLen()-1; i ;i--) out(list[i],'/');
     
     out(list[0]);
    }

  ok=true;
 }

FileName::FileName(StrLen file_name)
 : off(0),
   ok(false)
 {
  SplitPath split_dev(file_name);

  SplitPathName split_file(split_dev.path);
  
  if( split_file.getNameType()!=SplitPathName::Name ) return;
  
  setAbs(file_name,split_dev,split_file);
 }

FileName::FileName(StrLen path,StrLen file_name)
 : off(0),
   ok(false)
 {
  SplitPath split_dev(file_name);

  SplitPathName split_file(split_dev.path);
  
  if( split_file.getNameType()!=SplitPathName::Name ) return;
  
  if( split_dev.no_dev && !IsRooted(file_name) )
    {
     setRel(path,split_file);
    }
  else
    {
     setAbs(file_name,split_dev,split_file);
    }
 }

void FileName::printPos(PrintBase &out,TextPos pos)
 {
  Putobj(out,getFile(),pos);
 }

/* struct FileKey */

FileKey::FileKey(StrLen str_)
 : str(str_)
 {
  Crc16 crc;
    
  crc.addRange(str_);
    
  hash=crc;
 }
  
CmpResult FileKey::objCmp(const FileKey &obj) const
 {
  if( CmpResult result=LessCmp(hash,obj.hash) ) return result;
    
  return StrCmp(str,obj.str);
 }
  
} // namespace DDL
} // namespace CCore


