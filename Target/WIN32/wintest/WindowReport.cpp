/* WindowReport.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
//#include <CCore/inc/video/WindowReport.h>
#include "WindowReport.h"

//#include <CCore/inc/video/DrawArt.h>
#include "DrawArt.h"

#include <CCore/inc/MemBase.h>

namespace CCore {
namespace Video {

/* class WindowReport::Store */

auto WindowReport::Store::try_alloc() -> Header *
 {
  if( !head ) return PlaceAt(mem);
  
  if( (void *)head<(void *)tail )
    {
     void *ret=GetNext(tail);
    
     if( PtrDist(ret,lim)>=Delta+MaxMsgLen ) return PlaceAt(ret);
     
     ret=mem;
       
     if( PtrDist(ret,head)>=Delta+MaxMsgLen ) return PlaceAt(ret); 
        
     return 0;
    }
  else
    {
     void *ret=GetNext(tail);
     
     if( PtrDist(ret,head)>=Delta+MaxMsgLen ) return PlaceAt(ret);
     
     return 0;
    }
 }

auto WindowReport::Store::alloc() -> Header *
 {
  for(;;)
    {
     if( Header *ret=try_alloc() ) return ret;
    
     free();
    }
 }

void WindowReport::Store::free()
 {
  if( Header *ptr=head )
    {
     head=ptr->next;
     
     if( !head ) tail=0;
    }
 }

WindowReport::Store::Store()
 {
  ulen alloc_len=MaxMsgCount*(Delta+MaxMsgLen);
  
  mem=TryMemAlloc(alloc_len);
  
  if( !mem )
    {
     AbortMsgBox("Fatal error : no memory for exception reporter");
    
     throw CatchType();
    }
  
  lim=PtrAdd(mem,alloc_len);
  head=0;
  tail=0;
 }

WindowReport::Store::~Store()
 {
  MemFree(mem);
 }

PtrLen<char> WindowReport::Store::startMsg()
 {
  Header *ptr=alloc();
  
  ptr->next=0;
  ptr->len=MaxMsgLen;
  ptr->done=false;
  ptr->divide=false;
  
  if( tail )
    {
     tail->next=ptr;
     tail=ptr;
    }
  else
    {
     head=ptr;
     tail=ptr;
    }
  
  return GetBuf(ptr); 
 }

void WindowReport::Store::endMsg(PtrLen<char> rest)
 {
  tail->len-=rest.len;
  tail->done=true;
 }

void WindowReport::Store::divide()
 {
  if( tail ) tail->divide=true;
 }

/* class WindowReport */

void WindowReport::print(StrLen str)
 {
  if( !msg )
    {
     buf=store.startMsg();
     
     msg=true;
    }
  
  Replace_min(str.len,buf.len);
  
  str.copyTo(buf.ptr);
  
  buf+=str.len;
 }

void WindowReport::end()
 {
  if( msg )
    {
     store.endMsg(buf);
  
     msg=false;
     
     non_empty=true;
     
     setLines();
    }
 }

ulen WindowReport::Lines(StrLen text)
 {
  ulen ret=1;
  
  for(; +text ;++text) if( *text=='\n' ) ret++;
  
  return ret;
 }

void WindowReport::setLines()
 {
  ulen temp=0;
  
  store.apply( [&temp] (StrLen text,bool) { temp+=Lines(text)+1; } );
  
  lines=temp;
  
  if( off>=lines )
    {
     if( lines )
       off=lines-1;
     else
       off=0;
     
     redraw();
    }
 }

WindowReport::WindowReport(Config &cfg_)
 : cfg(cfg_),
   connector_updateConfig(this,&WindowReport::updateConfig)
 {
 }

WindowReport::~WindowReport()
 {
 }

void WindowReport::clear()
 {
  ReportException::clear();
  
  store.divide();
 }

bool WindowReport::show()
 {
  win->alert();
  
  return true;
 }

 // drawing

void WindowReport::layout(Point size)
 {
  FontMetrics metrics=cfg.text_font->getMetrics();
  
  text_by=metrics.by;
  text_dy=metrics.dy;
  
  visible_lines=size.y/metrics.dy;
 }

void WindowReport::draw(FrameBuf<DesktopColor> buf,bool) const
 {
  CommonDrawArt art(buf);
  
  art.erase(cfg.back);
  
  Coord y=text_by;
  ulen ind=0;
  
  store.apply( [&] (StrLen text,bool divide) 
                   {
                    if( ind>=off+visible_lines ) return;
    
                    for(;;)
                      {
                       StrLen cur=text;
                       
                       for(; +cur ;++cur) if( *cur=='\n' ) break;
                       
                       StrLen line=text.prefix(cur);
                       
                       if( ind>=off )
                         {
                          if( ind>=off+visible_lines ) return;
                         
                          cfg.text_font->text(buf,TextPlace(0,y),line,cfg.text);
                          
                          y+=text_dy;
                         }
                       
                       ind++;
                       
                       if( !cur ) break;
                       
                       text=cur;
                       
                       ++text;
                      }
    
                    if( ind>=off )
                      {
                       if( ind>=off+visible_lines ) return;
                       
                       if( divide )
                         {
                          Coord div_y=(y-text_by)+text_dy/2;
                       
                          art.path(cfg.divider,Point(0,div_y-1),Point(buf.dX()-1,div_y-1));
                          art.path(cfg.divider,Point(0,div_y+1),Point(buf.dX()-1,div_y+1));
                         }
                       else
                         {
                          Coord div_y=(y-text_by)+text_dy/2;
                        
                          art.path(cfg.divider,Point(0,div_y),Point(buf.dX()-1,div_y));
                         }
                       
                       y+=text_dy;
                      }
                    
                    ind++;
                    
                   } );
 }

 // base

void WindowReport::alive()
 {
  if( non_empty ) win->alert();
 }

 // keyboard

void WindowReport::key(VKey vkey,KeyMod kmod)
 {
  key(vkey,kmod,1);
 }

void WindowReport::key(VKey vkey,KeyMod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_PageUp : repeat*=visible_lines; // falldown;
     
     case VKey_Up :
      {
       if( off ) 
         {
          if( off>repeat ) off-=repeat; else off=0;
          
          redraw();
         }
      }
     break;
      
     case VKey_PageDown : repeat*=visible_lines; // falldown;
     
     case VKey_Down :
      {
       if( off+repeat<lines )
         {
          off+=repeat;
          
          redraw();
         }
       else if( off+1<lines )
         {
          off=lines-1;
         
          redraw();
         }
      }
     break; 
     
     case VKey_Home :
      {
       off=0;
       
       redraw();
      }
     break; 
      
     case VKey_End :
      {
       if( lines>=visible_lines )
         off=lines-visible_lines;
       else
         off=0;
       
       redraw();
      }
     break; 
    }
 }

} // namespace Video
} // namespace CCore
 

