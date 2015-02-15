/* RawinDraw.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/rawin/RawinDraw.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Rawin {

/* class Pen */ 

Pen::Pen(Color color,int width_px,unsigned style)
 {
  hPen=Win32::CreatePen(style,width_px,color);
  
  SysCheck("CCore::Rawin::Pen::Pen(...) : #;",hPen!=0);
 }
   
Pen::~Pen()
 {
  Win32::DeleteObject(Win32::ToGDObject(hPen));
 }
 
/* class Brush */ 

Brush::Brush(Color color)
 {
  hBrush=Win32::CreateSolidBrush(color);
  
  SysCheck("CCore::Rawin::Brush::Brush(...) : #;",hBrush!=0);
 }
   
Brush::~Brush()
 {
  Win32::DeleteObject(Win32::ToGDObject(hBrush));
 }
 
/* class Font */  

Font::Font(const char *typeface,int size_px,unsigned flags)
 {
  hFont=Win32::CreateFontA(size_px,0,0,0,
    
                           (flags&Bold)?Win32::FontWeight_Bold:Win32::FontWeight_Normal,
      
                           bool(flags&Italic),
                           bool(flags&Underline),
                           bool(flags&Strikeout),
                   
                           Win32::FontCharset_Default,
                           Win32::FontOutPrecision_Default,
                           Win32::FontClipPrecision_Default,
                           Win32::FontQuality_Cleartype,
                           Win32::FontPitch_Default|Win32::FontFamily_DontCare,
                           
                           typeface);
  
  SysCheck("CCore::Rawin::Font::Font(...) : #;",hFont!=0);
 }
   
Font::~Font()
 {
  Win32::DeleteObject(Win32::ToGDObject(hFont));
 }
 
/* class EnumFontsBase */ 
 
EnumFontsBase::EnumFontsBase() {}
   
EnumFontsBase::~EnumFontsBase() {}
 
static int WIN32_CALLTYPE EnumFontProc(const Win32::EnumLogFontEx *ex_logfont,const Win32::TextMetrics *,unsigned,Win32::MsgLParam lParam)
 {
  EnumFontsBase *obj=static_cast<EnumFontsBase *>((void *)lParam);
  
  FontInfo info;
  
  info.typeface=ex_logfont->logfont.typeface;
  
  info.full_name=(const char *)ex_logfont->full_name;
  info.style=(const char *)ex_logfont->style;
  info.script=(const char *)ex_logfont->script;
  
  obj->font(info);
 
  return true;
 }
   
void EnumFontsBase::run(Win32::HGDevice hGD)
 {
  Win32::LogFont logfont;
  
  logfont.charset=Win32::FontCharset_Default;
  logfont.typeface[0]=0;
  logfont.pitch_and_family=0;
 
  Win32::EnumFontFamiliesExA(hGD,&logfont,EnumFontProc,(Win32::MsgLParam)(void *)this,0);
 }
 
/* class DrawContext */ 

DrawContext::DrawContext(Win32::HGDevice hGD_)
 : hGD(hGD_)
 {
  old_pen_flag=false;
  old_brush_flag=false;
  old_font_flag=false;
  
  Win32::SetBkMode(hGD_,Win32::BkMode_Transparent);
  Win32::SetTextAlign(hGD_,Win32::TextAlign_Left|Win32::TextAlign_Top);
  Win32::SetTextColor(hGD_,0);
  
  Win32::MoveToEx(hGD_,0,0,0);
 }
   
DrawContext::~DrawContext()
 {
  if( old_pen_flag ) Win32::SelectObject(hGD,old_pen);
  if( old_brush_flag ) Win32::SelectObject(hGD,old_brush);
  if( old_font_flag ) Win32::SelectObject(hGD,old_font);
 }
   
 // select
 
void DrawContext::select(Win32::HPen hPen)
 {
  if( old_pen_flag )
    {
     Win32::SelectObject(hGD,Win32::ToGDObject(hPen));
    }
  else
    {
     old_pen=Win32::SelectObject(hGD,Win32::ToGDObject(hPen));
     old_pen_flag=true;
    }   
 }
 
void DrawContext::select(Win32::HBrush hBrush)
 {
  if( old_brush_flag )
    {
     Win32::SelectObject(hGD,Win32::ToGDObject(hBrush));
    }
  else
    {
     old_brush=Win32::SelectObject(hGD,Win32::ToGDObject(hBrush));
     old_brush_flag=true;
    }  
 }
 
void DrawContext::select(Win32::HFont hFont)
 {
  if( old_font_flag )
    {
     Win32::SelectObject(hGD,Win32::ToGDObject(hFont));
    }
  else
    {
     old_font=Win32::SelectObject(hGD,Win32::ToGDObject(hFont));
     old_font_flag=true;
    }
 }
 
 // line
   
Point DrawContext::move(Point point)
 {
  Win32::Point ret;
 
  SysCheck("CCore::Rawin::DrawContext::move(...) : #;", Win32::MoveToEx(hGD,point.x,point.y,&ret) );
  
  return MsgBody::ToPoint(ret);
 }
   
void DrawContext::line(Point point)
 {
  SysCheck("CCore::Rawin::DrawContext::line(...) : #;", Win32::LineTo(hGD,point.x,point.y) );
 }
 
 // fill
   
void DrawContext::fill(Pane pane)
 {
  SysCheck("CCore::Rawin::DrawContext::fill(...) : #;", Win32::PatBlt(hGD,pane.x,pane.y,pane.dx,pane.dy,Win32::PatOp_Copy) );
 }
 
 // path
   
void DrawContext::beginPath()
 {
  SysCheck("CCore::Rawin::DrawContext::beginPath() : #;", Win32::BeginPath(hGD) );
 }
   
void DrawContext::endPath()
 {
  SysCheck("CCore::Rawin::DrawContext::endPath() : #;", Win32::EndPath(hGD) );
 }
 
void DrawContext::closeFigure()
 {
  SysCheck("CCore::Rawin::DrawContext::closeFigure() : #;", Win32::CloseFigure(hGD) );
 }
 
void DrawContext::strokePath()
 {
  SysCheck("CCore::Rawin::DrawContext::strokePath() : #;", Win32::StrokePath(hGD) );
 }
 
void DrawContext::fillPath()
 {
  SysCheck("CCore::Rawin::DrawContext::fillPath() : #;", Win32::FillPath(hGD) );
 }
 
void DrawContext::drawPath()
 {
  SysCheck("CCore::Rawin::DrawContext::drawPath() : #;", Win32::StrokeAndFillPath(hGD) );
 }
 
 // text
   
void DrawContext::setTextColor(Color color)
 {
  SysCheck("CCore::Rawin::DrawContext::setTextColor(...) : #;", Win32::SetTextColor(hGD,color)!=Win32::InvalidColor );
 }
   
void DrawContext::setTextRef(unsigned flags)
 {
  SysCheck("CCore::Rawin::DrawContext::setTextRef(...) : #;", Win32::SetTextAlign(hGD,flags)!=Win32::GDIError );
 }
 
void DrawContext::text(Point ref_point,StrLen str)
 {
  SysCheck("CCore::Rawin::DrawContext::text(...) : #;", Win32::TextOutA(hGD,ref_point.x,ref_point.y,str.ptr,str.len) );
 }
 
Point DrawContext::textSize(StrLen str)
 {
  Win32::Size ret;
 
  SysCheck("CCore::Rawin::DrawContext::textSize(...) : #;", Win32::GetTextExtentPoint32A(hGD,str.ptr,str.len,&ret) );
  
  return Point(ret.dx,ret.dy);
 }

Point DrawContext::text(Point ref_point,StrLen str,int caret_pos[])
 {
  if( str.len>Win32::MaxExtTextOutLen ) 
    {
     Printf(Exception,"CCore::Rawin::DrawContext::text(...) : too long string");
    }
  
  TempArray<int,512> buf(str.len);
  
  int *dcell=buf.getPtr();
  
  Win32::CharPlacement res;
  
  res.cb=sizeof res;
  res.str=0;
  res.order=0;
  res.dcell=dcell;
  res.caret_pos=caret_pos;
  res.class_name=0;
  res.glyphs=0;
  res.glyphs_count=str.len;
  res.max_fit=0;
  
  auto ret=Win32::GetCharacterPlacementA(hGD,str.ptr,str.len,0,&res,0);
  
  SysCheck("CCore::Rawin::DrawContext::text(...) : placement #;",ret);
  
  SysCheck("CCore::Rawin::DrawContext::text(...) : #;", Win32::ExtTextOutA(hGD,ref_point.x,ref_point.y,0,0,str.ptr,str.len,dcell) );
  
  return Point(Win32::LoWord(ret),Win32::HiWord(ret));
 }
 
/* class MemSurface */ 

MemSurface::MemSurface(MemPaint &mem_paint)
 {
  Point s=mem_paint.getSize();
 
  dx=s.x;
  dy=s.y;
  dline=s.x;
  
  surface=mem_paint.getMem();
  
  Win32::GdiFlush();
 }
 
} // namespace Rawin
} // namespace CCore
 

