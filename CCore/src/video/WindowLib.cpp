/* WindowLib.cpp */ 
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
 
#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Video {

/* class RadioItem */

void RadioItem::setCheck()
 {
  if( group )
    {
     RadioItem *prev=group->cur;
     
     if( prev!=this )
       {
        int prev_id;
       
        if( prev ) 
          prev_id=prev->radio_id;
        else
          prev_id=-1;
       
        group->cur=this;
        
        group->changed.assert(radio_id,prev_id);
        
        if( prev ) prev->uncheck(); 
       }
    }
 }
  
RadioItem::RadioItem(int radio_id_)
 : radio_id(radio_id_)
 {
 }
   
RadioItem::~RadioItem()
 {
  if( group ) group->del(this);
 }

/* class RadioGroup */

RadioGroup::RadioGroup()
 {
 }
   
RadioGroup::~RadioGroup()
 {
  for(auto cur=list.start(); +cur ;++cur) cur->group=0;
 }
   
void RadioGroup::add(RadioItem *item)
 {
  if( item->group )
    {
     Printf(Exception,"CCore::Video::RadioGroup::add(...) : item is already included in a group");
    }
   
  bool flag=!list;
  
  list.ins_last(item);
  
  item->group=this;
  
  item->check(flag);
  
  if( flag ) cur=item;
 }
   
void RadioGroup::del(RadioItem *item)
 {
  if( item->group!=this )
    {
     Printf(Exception,"CCore::Video::RadioGroup::del(...) : item is not included in this group");
    }
  
  if( item==cur ) cur=0;
  
  list.del(item);
  
  item->group=0;
 }
   
} // namespace Video
} // namespace CCore
 

