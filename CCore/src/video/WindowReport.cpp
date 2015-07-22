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

Coord ExceptionWindow::VisibleDx(Font font,ulen index,StrLen text)
 {
  Coord ret;
  
  {
   StrLen cur=text;
   
   for(; +cur ;++cur) if( *cur=='\n' ) break;
   
   StrLen line=text.prefix(cur);
   
   char temp[TextBufLen];
   PrintBuf out(Range(temp));
   
   Printf(out,"#;) ",index);
   
   StrLen line1=out.close();
   
   TextSize ts=font->text(line1,line);
   
   ret=ts.full_dx;
   
   if( !cur ) return ret;
   
   text=cur;
   
   ++text;
  }
  
  for(;;)
    {
     StrLen cur=text;
     
     for(; +cur ;++cur) if( *cur=='\n' ) break;
     
     StrLen line=text.prefix(cur);
     
     TextSize ts=font->text(line);
     
     Replace_max(ret,ts.full_dx);
     
     if( !cur ) return ret;
     
     text=cur;
     
     ++text;
    }
 }

void ExceptionWindow::setLines()
 {
  ulen temp=0;
  Coord temp_dx=0;
  
  Font font=cfg.text_font.get();
  
  report.apply( [&] (ulen index,StrLen text,bool) 
                    { 
                     temp+=Lines(text)+1;
                     
                     Replace_max(temp_dx,VisibleDx(font,index,text));
                     
                    } );
  
  lines=temp;
  
  visible_dx=Min<Coord>(temp_dx,MaxCoord-ptext.dx-text_dx)+text_dx;
  
  setScrollPage();
 }

void ExceptionWindow::setScrollPage()
 {
  yscroll.setRange(lines+visible_lines-1,visible_lines);
  
  xscroll.setRange(visible_dx,ptext.dx);
 }

void ExceptionWindow::drawText(DrawBuf buf,Pane pane) const
 {
  CommonDrawArt art(buf);
  
  Font font=cfg.text_font.get();
  Coord y=text_by;
  ulen ind=0;
  ulen off=yscroll.getPos();
  
  report.apply( [&] (ulen index,StrLen text,bool divide) 
                    {
                     if( ind>=off+visible_lines ) return;
                     
                     for(bool first=true;;first=false)
                       {
                        StrLen cur=text;
                        
                        for(; +cur ;++cur) if( *cur=='\n' ) break;
                        
                        StrLen line=text.prefix(cur);
                        
                        if( ind>=off )
                          {
                           if( ind>=off+visible_lines ) return;
                           
                           if( first )
                             {
                              char temp[TextBufLen];
                              PrintBuf out(Range(temp));
                             
                              Printf(out,"#;) ",index);
                             
                              StrLen line1=out.close();
                             
                              font->text(buf,pane,TextPlace(AlignX_Left,y),line1,line,+cfg.text);
                             }
                           else
                             {
                              font->text(buf,pane,TextPlace(AlignX_Left,y),line,+cfg.text);
                             }
                          
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
   yscroll(list,cfg.scroll_ctor.get()),
   xscroll(list,cfg.scroll_ctor.get()),
   
   connector_updateReport(this,&ExceptionWindow::updateReport,report.update),
   connector_yposChanged(this,&ExceptionWindow::yposChanged,yscroll.changed),
   connector_xposChanged(this,&ExceptionWindow::xposChanged,xscroll.changed)
 {
  list.insTop(yscroll,xscroll);
 }

ExceptionWindow::~ExceptionWindow()
 {
 }

void ExceptionWindow::reposition()
 {
  ulen temp=0;
  ulen off=0;
  
  report.apply( [&] (ulen,StrLen text,bool divide) 
                    { 
                     temp+=Lines(text)+1;
                     
                     if( divide ) off=temp;
                     
                    } );
  
  yscroll.setPos(off);
 }

void ExceptionWindow::layout()
 {
  FontSize font_size=cfg.text_font.get()->getSize();
  
  text_by=font_size.by;
  text_dy=font_size.dy;
  text_dx=font_size.min_dx;
  
  Point size=getSize();
  Coord dxy=+cfg.scroll_dxy;
  
  if( size>Point::Diag(dxy) )
    {
     Pane yp=Pane(0,0,dxy,size.y-dxy);
     Pane xp=Pane(dxy,size.y-dxy,size.x-dxy,dxy);
     
     if( yscroll.isGoodSize(yp.getSize()) ) yscroll.setPlace(yp); else yscroll.setPlace(Empty);
     if( xscroll.isGoodSize(xp.getSize()) ) xscroll.setPlace(xp); else xscroll.setPlace(Empty);
     
     Coord offx=dxy+text_dx;
     
     ptext=Pane(offx,0,size.x-offx,size.y-dxy);
    }
  else
    {
     yscroll.setPlace(Empty);
     xscroll.setPlace(Empty);
     
     ptext=Pane(Null,size);
    }
  
  visible_lines=ptext.dy/text_dy;
  
  setLines();
 }

void ExceptionWindow::draw(DrawBuf buf,bool drag_active) const
 {
  try
    {
     buf.erase(+cfg.back);
     
     DrawBuf tbuf=buf.cutRebase(ptext);
     
     Coord xoff=Coord(xscroll.getPos());
     
     Pane pane(-xoff,0,ptext.dx+xoff,ptext.dy);
     
     drawText(tbuf,pane);
    
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
       if( ulen off=yscroll.getPos() ) 
         {
          yscroll.setPos(PosSub(off,repeat));
          
          redraw();
         }
      }
     break;
      
     case VKey_PageDown : repeat*=visible_lines; // falldown;
     
     case VKey_Down :
      {
       ulen off=yscroll.getPos();
       
       yscroll.setPos(off+repeat);
          
       redraw();
      }
     break; 
     
     case VKey_Left :
      {
       ulen off=xscroll.getPos();
       
       off=PosSub(off,text_dx);
       
       xscroll.setPos(off);
       
       redraw();
      }
     break;
     
     case VKey_Right :
      {
       ulen off=xscroll.getPos();
       
       off+=text_dx;
       
       xscroll.setPos(off);
       
       redraw();
      }
     break;
     
     case VKey_Home :
      {
       yscroll.setPos(0);
       
       redraw();
      }
     break; 
      
     case VKey_End :
      {
       yscroll.setPos(lines);
       
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

void ExceptionWindow::yposChanged(ulen)
 {
  redraw();
 }

void ExceptionWindow::xposChanged(ulen)
 {
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
  
  ErrorMsgBox(out.close(),Range(getTitle()));
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

void WindowReportBase::lastShow()
 {
  if( non_cleared )
    {
     show();
    }
 }

WindowReportBase::WindowReportBase(Desktop *desktop_,MSec tick_period_,const ExceptionWindow::Config &cfg_)
 : desktop(desktop_),
   tick_period(tick_period_),
   cfg(cfg_)
 {
 }

WindowReportBase::~WindowReportBase()
 {
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
 

