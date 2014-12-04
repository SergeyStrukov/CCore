/* VideoDevice.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_VideoDevice_h
#define CCore_inc_video_VideoDevice_h

#include <CCore/inc/video/FrameBuf.h>

#include <CCore/inc/FunctorType.h>
 
namespace CCore {
namespace Video {

/* enum ColorMode */

enum ColorMode
 {
  ColorMode_none = 0,
  
  ColorMode16,
  ColorMode24,
  ColorMode32
 };

/* classes */

template <template <class Color> class T> class MultiMode;

struct VideoMode;

struct VideoDim;

struct VideoDevice;

/* class MultiMode<T> */

template <template <class Color> class T>
class MultiMode
 {
   ColorMode mode = ColorMode_none ;
   
   union Union
    {
     T<Color16> obj16;
     T<Color24> obj24;
     T<Color32> obj32;
     
     Union() {}
    };
   
   Union u;
   
  public: 
   
   MultiMode() {}
   
   ~MultiMode() {}

   ColorMode operator + () const { return mode; }
   
   bool operator ! () const { return !mode; }

   template <class FuncInit>
   void init(ColorMode mode_,FuncInit func_init)
    {
     mode=mode_;
     
     FunctorTypeOf<FuncInit> func(func_init);
     
     switch( mode_ )
       {
        case ColorMode16 : CreateAt(u.obj16); func(u.obj16); break;
        case ColorMode24 : CreateAt(u.obj24); func(u.obj24); break;
        case ColorMode32 : CreateAt(u.obj32); func(u.obj32); break;
       }
    }
   
   void clear()
    {
     mode=ColorMode_none;
    }
   
   template <class FuncInit>
   void apply(FuncInit func_init)
    {
     FunctorTypeOf<FuncInit> func(func_init);
     
     switch( mode )
       {
        case ColorMode16 : func(u.obj16); break;
        case ColorMode24 : func(u.obj24); break;
        case ColorMode32 : func(u.obj32); break;
       }
    }
 };

/* struct VideoMode */

struct VideoMode
 {
  ColorMode mode;
  unsigned dx;
  unsigned dy;
  unsigned freq; // Hz
  
  VideoMode() : mode(ColorMode_none),dx(0),dy(0),freq(0) {}
  
  ColorMode operator + () const { return mode; }
  
  bool operator ! () const { return !mode; }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct VideoDim */

struct VideoDim
 {
  unsigned hlen; // mm
  unsigned vlen; // mm
  
  VideoDim() : hlen(0),vlen(0) {}
 };

/* struct VideoDevice */

struct VideoDevice
 {
  // not synchronized
  
  virtual bool updateVideoModeList(MSec timeout=DefaultTimeout)=0;
  
  virtual PtrLen<const VideoMode> getVideoModeList() const =0;
  
  virtual bool setVideoMode(ulen index)=0;
  
  virtual void setTick(MSec period)=0;
  
  virtual VideoDim getVideoDim() const =0;
  
  virtual ColorMode getColorMode() const =0;
  
  virtual VideoMode getVideoMode() const =0;
  
  virtual FrameBuf<Color16> getBuf16() const =0;
  
  virtual FrameBuf<Color24> getBuf24() const =0;
  
  virtual FrameBuf<Color32> getBuf32() const =0;
  
  void getBuf(FrameBuf<Color16> &ret) const { ret=getBuf16(); }
  
  void getBuf(FrameBuf<Color24> &ret) const { ret=getBuf24(); }
  
  void getBuf(FrameBuf<Color32> &ret) const { ret=getBuf32(); }
  
  // synchronized
  
  struct Control
   {
    // serialized
    
    virtual void change(bool plug,bool power)=0;
    
    virtual void tick()=0;
   };
  
  virtual void attach(Control *ctrl)=0;
  
  virtual void detach()=0;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

