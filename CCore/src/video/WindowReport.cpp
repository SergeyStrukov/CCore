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
 
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/CommonDrawArt.h>

#include <CCore/inc/MemBase.h>

namespace CCore {
namespace Video {

/* class ExceptionStore */

auto ExceptionStore::try_alloc() -> Header *
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

auto ExceptionStore::alloc() -> Header *
 {
  for(;;)
    {
     if( Header *ret=try_alloc() ) return ret;
    
     free();
    }
 }

void ExceptionStore::free()
 {
  if( Header *ptr=head )
    {
     head=ptr->next;
     
     if( !head ) tail=0;
    }
 }

ExceptionStore::ExceptionStore()
 {
  ulen alloc_len=MaxMsgCount*(Delta+MaxMsgLen);
  
  mem=TryMemAlloc(alloc_len);
  
  if( !mem )
    {
     ErrorMsgBox("No memory for the exception store","Fatal error");
    
     throw CatchType();
    }
  
  lim=PtrAdd(mem,alloc_len);
  head=0;
  tail=0;
 }

ExceptionStore::~ExceptionStore()
 {
  MemFree(mem);
 }

PtrLen<char> ExceptionStore::startMsg()
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

void ExceptionStore::endMsg(PtrLen<char> rest)
 {
  tail->index=index++;
  tail->len-=rest.len;
  tail->done=true;
 }

void ExceptionStore::divide()
 {
  if( tail ) tail->divide=true;
 }

/* class ExceptionWindow */

ulen ExceptionWindow::Lines(StrLen text)
 {
  ulen ret=1;
  
  for(; +text ;++text) if( *text=='\n' ) ret++;
  
  return ret;
 }

void ExceptionWindow::setLines()
 {
  ulen temp=0;
  
  report.apply( [&temp] (ulen,StrLen text,bool) { temp+=Lines(text)+1; } );
  
  lines=temp;
  
  if( off>=lines )
    {
     if( lines )
       off=lines-1;
     else
       off=0;
    }
  
  setScrollPage();
 }

void ExceptionWindow::setScrollPage()
 {
  yscroll.setRange(lines+visible_lines-1,visible_lines,off);
 }

void ExceptionWindow::setScrollPos()
 {
  yscroll.setPos(off);
 }

void ExceptionWindow::drawText(DrawBuf buf) const
 {
  CommonDrawArt art(buf);
  
  Coord y=text_by;
  ulen ind=0;
  
  report.apply( [&] (ulen index,StrLen text,bool divide) 
                    {
                     if( ind>=off+visible_lines ) return;
                     
                     TextPlace place(AlignX_Left,y);
                     
                     if( ind>=off )
                       {
                        char temp[TextBufLen];
                        PrintBuf out(Range(temp));
                        
                        Printf(out,"#;) ",index);
                        
                        StrLen line=out.close();
                        
                        cfg.text_font.get()->text_update(buf,buf.getPane(),place,line,+cfg.text);
                       }
     
                     for(;;)
                       {
                        StrLen cur=text;
                        
                        for(; +cur ;++cur) if( *cur=='\n' ) break;
                        
                        StrLen line=text.prefix(cur);
                        
                        if( ind>=off )
                          {
                           if( ind>=off+visible_lines ) return;
                          
                           cfg.text_font.get()->text(buf,buf.getPane(),place,line,+cfg.text);
                           
                           y+=text_dy;
                          }
                        
                        ind++;
                        
                        if( !cur ) break;
                        
                        text=cur;
                        
                        ++text;
                        
                        place=TextPlace(AlignX_Left,y);
                       }
     
                     if( ind>=off )
                       {
                        if( ind>=off+visible_lines ) return;
                        
                        if( divide )
                          {
                           Coord div_y=(y-text_by)+text_dy/2;
                        
                           art.path(+cfg.divider,Point(0,div_y-1),Point(buf.dX()-1,div_y-1));
                           art.path(+cfg.divider,Point(0,div_y+1),Point(buf.dX()-1,div_y+1));
                          }
                        else
                          {
                           Coord div_y=(y-text_by)+text_dy/2;
                         
                           art.path(+cfg.divider,Point(0,div_y),Point(buf.dX()-1,div_y));
                          }
                        
                        y+=text_dy;
                       }
                     
                     ind++;
                     
                    } );
 }

ExceptionWindow::ExceptionWindow(SubWindowHost &host,const Config &cfg_,WindowReportBase &report_)
 : SubWindow(host),
   cfg(cfg_),
   report(report_),
   
   list(*this),
   yscroll(list,cfg.scroll_cfg.get()),
   xscroll(list,cfg.scroll_cfg.get()),
   
   connector_updateReport(this,&ExceptionWindow::updateReport,report.update),
   connector_yposChanged(this,&ExceptionWindow::yposChanged,yscroll.changed)
 {
  list.insTop(yscroll,xscroll);
  
  setLines();
 }

ExceptionWindow::~ExceptionWindow()
 {
 }

void ExceptionWindow::reposition()
 {
  ulen temp=0;
  
  report.apply( [&] (ulen,StrLen text,bool divide) 
                    { 
                     temp+=Lines(text)+1;
                     
                     if( divide ) off=temp;
                     
                    } );
 }

void ExceptionWindow::layout()
 {
  Point size=getSize();
  Coord dxy=+cfg.scroll_dxy;
  
  if( size>Point::Diag(dxy) )
    {
     Pane yp=Pane(0,0,dxy,size.y-dxy);
     Pane xp=Pane(dxy,size.y-dxy,size.x-dxy,dxy);
     
     if( yscroll.isGoodSize(yp.getSize()) ) yscroll.setPlace(yp); else yscroll.setPlace(Empty);
     if( xscroll.isGoodSize(xp.getSize()) ) xscroll.setPlace(xp); else xscroll.setPlace(Empty);
     
     ptext=Pane(dxy,0,size.x-dxy,size.y-dxy);
    }
  else
    {
     yscroll.setPlace(Empty);
     xscroll.setPlace(Empty);
     
     ptext=Extent(Null,size);
    }
  
  FontSize font_size=cfg.text_font.get()->getSize();
  
  text_by=font_size.by;
  text_dy=font_size.dy;
  
  visible_lines=ptext.dy/font_size.dy;
  
  setScrollPage();
 }

void ExceptionWindow::draw(DrawBuf buf,bool drag_active) const
 {
  try
    {
     buf.erase(+cfg.back);
     
     drawText(buf.cutRebase(ptext));
    
     list.draw(buf,drag_active);
    }
  catch(CatchType)
    {
    }
 }

void ExceptionWindow::open()
 {
  opened=true;
  
  setLines();
 }

void ExceptionWindow::close()
 {
  opened=false;
 }

void ExceptionWindow::react(UserAction action)
 {
  action.dispatch(*this, [this] (UserAction action) { list.react(action); } );
 }
   
void ExceptionWindow::react_Key(VKey vkey,KeyMod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_PageUp : repeat*=visible_lines; // falldown;
     
     case VKey_Up :
      {
       if( off ) 
         {
          if( off>repeat ) off-=repeat; else off=0;
          
          setScrollPos();
          
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
          
          setScrollPos();
          
          redraw();
         }
       else if( off+1<lines )
         {
          off=lines-1;
          
          setScrollPos();
         
          redraw();
         }
      }
     break; 
     
     case VKey_Home :
      {
       off=0;
       
       setScrollPos();
       
       redraw();
      }
     break; 
      
     case VKey_End :
      {
       if( lines>=visible_lines )
         off=lines-visible_lines;
       else
         off=0;
       
       setScrollPos();
       
       redraw();
      }
     break;
    }
 }

void ExceptionWindow::updateReport()
 {
  if( opened ) 
    {
     setLines();
     
     redraw();
    }
 }

void ExceptionWindow::yposChanged(ulen pos)
 {
  off=pos;
  
  redraw();
 }

/* class WindowReportBase */

void WindowReportBase::print(StrLen str)
 {
  if( !enable ) return;
  
  if( !msg )
    {
     buf=startMsg();
     
     msg=true;
    }
  
  Replace_min(str.len,buf.len);
  
  str.copyTo(buf.ptr);
  
  buf+=str.len;
 }

void WindowReportBase::end()
 {
  if( !enable ) return;
  
  if( msg )
    {
     endMsg(buf);
  
     msg=false;
     
     non_cleared=true;
     
     update.assert();
    }
 }

void WindowReportBase::boxShow()
 {
  char buf[TextBufLen];
  
  PrintBuf out(Range(buf));

  ulen off=0;
  
  {
   ulen temp=0;
   
   apply( [&] (ulen,StrLen,bool divide) 
              { 
               temp++;
               
               if( divide ) off=temp;
               
              } );
  }
  
  {
   ulen temp=0;
   
   apply( [&] (ulen index,StrLen text,bool divide) 
              { 
               if( temp>=off ) 
                 {
                  Printf(out,"#;) #;\n",index,text);
                  
                  if( divide )
                    Printf(out,"#16=;\n",TextDivider());
                  else
                    Printf(out,"#16;\n",TextDivider());
                 }
                
               temp++;
               
              } );
  }
  
  ErrorMsgBox(out.close(),"Fatal error");
 }

class WindowReportBase::TempQueue : DeferCallQueue
 {
   Desktop *desktop;
 
  private:
 
   virtual void forward(TimeScope time_scope)
    {
     try
       {
        desktop->wait(time_scope);
        
        if( !desktop->pump() ) stop();
       }
     catch(CatchType) 
       {
        // ignore
       }
    }
   
  public:
 
   explicit TempQueue(Desktop *desktop_,MSec tick_period)
    : DeferCallQueue(tick_period),
      desktop(desktop_)
    {
     activate();
    }
   
   ~TempQueue()
    {
     deactivate();
    }
 };

WindowReportBase::WindowReportBase(Desktop *desktop_,MSec tick_period_,const ExceptionWindow::Config &cfg_)
 : desktop(desktop_),
   tick_period(tick_period_),
   cfg(cfg_)
 {
 }

WindowReportBase::~WindowReportBase()
 {
  if( non_cleared )
    {
     show();
    }
 }

void WindowReportBase::show()
 {
  enable=false;
 
  ReportException::clear();
  
  try
    {
     if( DeferCallQueue::IsActive() )
       {
        modalLoop();
       }
     else
       {
        TempQueue queue(desktop,tick_period);
       
        modalLoop();
       }
    }
  catch(CatchType)
    {
     boxShow();
    }

  enable=true;
 }

/* class ExceptionClient */

ExceptionClient::~ExceptionClient()
 {
 }

void ExceptionClient::clear()
 {
  report.clear();
 }

void ExceptionClient::guard()
 { 
  report.guard(); 
 }

void ExceptionClient::show()
 {
  if( in_loop )
    {
     window.reposition();
    
     alert.assert();
    }
  else
    {
     report.show();
    }
 }

void ExceptionClient::beforeLoop()
 {
  in_loop=true;
 }

void ExceptionClient::afterLoop()
 {
  in_loop=false;
 }

void ExceptionClient::alive()
 {
  if( report.nonEmpty() && in_loop ) alert.assert();
 }

} // namespace Video
} // namespace CCore
 

