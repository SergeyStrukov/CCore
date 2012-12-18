/* List.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_List_h
#define CCore_inc_List_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */ 

template <class T> struct SLink;

template <class T> struct DLink;

/* struct SLink<T> */ 

template <class T> 
struct SLink
 {
  T *next;
  
  template <SLink<T> T::* LinkMember>
  struct LinearAlgo
   {
    static SLink<T> & Link(T *obj) { return obj->*LinkMember; }
    
    // obj -> null
 
    static void Init(T *obj) // obj!=0 unlinked
     {
      Link(obj).next=0;
     }
     
    // place -> obj -> next -> ... -> null
 
    static void InsNext(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Link(obj).next=Replace(Link(place).next,obj);
     } 
     
    static T * DelNext(T *place) // place!=0 linked, return obj
     {
      T *obj=Link(place).next;
      
      if( obj ) Link(place).next=Link(obj).next;
      
      return obj;
     }
   
    // ptr -> next -> ... -> null
    
    struct Cur
     {
      T *ptr;
      
      // constructors
      
      explicit Cur(T *ptr_) : ptr(ptr_) {}
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ () { ptr=Link(ptr).next; }
     };
     
    // top -> next -> ... -> null
    
    struct Top
     {
      T *top;
      
      // constructors
      
      Top() { init(); }
      
      // methods
      
      void init() { top=0; }
      
      T * operator + () const { return top; }
      
      bool operator ! () const { return !top; }
      
      Cur start() const { return Cur(top); }
      
      // insert object
      
      void ins(T *obj) // obj!=0 unlinked
       { 
        Link(obj).next=top;
        
        top=obj;
       }
      
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        InsNext(pos,obj);
       }
       
      void ins_after(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_after(cur.ptr,obj);
       }
      
      // delete object
       
      T * del()
       { 
        T *ret=top;
        
        if( ret ) top=Link(ret).next;
        
        return ret;
       }
     };
     
    // first -> next -> ... -> last -> null
    
    struct FirstLast
     {
      T *first;
      T *last;
      
      // constructors
      
      FirstLast() { init(); }
      
      // methods
      
      void init()
       {
        first=0;
        last=0;
       }
       
      T * operator + () const { return first; }
      
      bool operator ! () const { return !first; }
      
      Cur start() const { return Cur(first); }
      
      // insert object
      
      void ins_first(T *obj) // obj!=0 unlinked
       {
        if( !(Link(obj).next=first) )
          {
           last=obj;
          }
          
        first=obj;
       }
       
      void ins_last(T *obj) // obj!=0 unlinked
       {
        Link(obj).next=0;
        
        if( T *ptr=last )
          {
           Link(ptr).next=obj;
          }
        else
          {
           first=obj;
          }
          
        last=obj;
       }
       
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==last )
          {
           InsNext(pos,obj);
           
           last=obj;
          }
        else
          {
           InsNext(pos,obj);
          }
       }
       
      void ins_after(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_after(cur.ptr,obj);
       }
       
      // delete object
      
      T * del_first()
       {
        T *ret=first;
        
        if( ret )
          {
           if( !(first=Link(ret).next) ) last=0;
          }
        
        return ret; 
       }
     };
   };
  
  template <SLink<T> T::* LinkMember>
  struct CircularAlgo
   {
    static SLink<T> & Link(T *obj) { return obj->*LinkMember; }
    
    // obj -> obj
 
    static void Init(T *obj) // obj!=0 unlinked
     {
      Link(obj).next=obj;
     }
     
    // place -> obj -> next -> ... -> place
     
    static void InsNext(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Link(obj).next=Replace(Link(place).next,obj);
     } 
     
    static T * DelNext(T *place) // place!=0 linked
     {
      T *obj=Link(place).next;
      
      if( obj==place ) return 0;
      
      Link(place).next=Link(obj).next;
      
      return obj;
     }
     
    // ptr -> next -> ... -> bottom
    
    struct Cur
     {
      T *ptr;
      T *bottom;
      
      // constructors
      
      explicit Cur(T *bottom_)
       : bottom(bottom_) 
       {
        if( bottom_ )
          ptr=Link(bottom_).next;
        else
          ptr=0;
       }
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ ()
       {
        if( ptr!=bottom )
          ptr=Link(ptr).next;
        else
          ptr=0;
       }
     };
     
    // bottom -> top -> next -> ... -> bottom
    
    struct Top
     {
      T *bottom;
      
      // constructors
      
      Top() { init(); }
      
      // methods
      
      void init() { bottom=0; }
      
      T * operator + () const { return bottom; }
      
      bool operator ! () const { return !bottom; }
      
      Cur start() const { return Cur(bottom); }
      
      // insert object
      
      void ins(T *obj) // obj!=0 unlinked
       {
        if( bottom )
          {
           InsNext(bottom,obj);
          }
        else
          {
           Init(obj);  
        
           bottom=obj;  
          }
       }
       
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==bottom )
          {
           InsNext(pos,obj);
           
           bottom=obj;
          }
        else
          {
           InsNext(pos,obj);
          }  
       }
       
      void ins_after(Cur &cur,T *obj) // +cur, obj!=0 unlinked
       {
        T *pos=cur.ptr;
        
        if( pos==bottom )
          {
           InsNext(pos,obj);
           
           cur.bottom=obj;
           bottom=obj;
          }
        else
          {
           InsNext(pos,obj);
          }  
       }
      
      // delete object
       
      T * del()
       {
        if( bottom )
          {
           if( T *ret=DelNext(bottom) ) return ret;
           
           return Replace_null(bottom);
          }
        else
          {
           return 0;
          }  
       }
      
      // rotate
       
      T * rotate() // return top element moved to bottom
       {
        T *ptr=bottom;
        
        if( ptr )
          {
           ptr=Link(ptr).next;
           
           bottom=ptr;
           
           return ptr;
          }
        
        return 0;
       }
     };
   };
 };
 
/* struct DLink<T> */ 
 
template <class T> 
struct DLink
 {
  T *next;
  T *prev;
  
  template <DLink<T> T::* LinkMember>
  struct LinearAlgo
   {
    static DLink<T> & Link(T *obj) { return obj->*LinkMember; }
    
    // Connect...()
    
    static void Connect(T *a,T *b)
     {
      Link(a).next=b;
      Link(b).prev=a;
     }
  
    static void Connect_null(T *a,T *b)
     {
      if( a ) Link(a).next=b;
      if( b ) Link(b).prev=a;
     }
  
    static void Connect_nulla(T *a,T *b)
     {
      if( a ) Link(a).next=b;
              Link(b).prev=a;
     }
  
    static void Connect_nullb(T *a,T *b)
     {
              Link(a).next=b;
      if( b ) Link(b).prev=a;
     }
     
    static void Connect_nulla(T *a,T *b,T *c)
     {
      Connect_nulla(a,b);
      Connect(b,c);
     }
  
    static void Connect_nullc(T *a,T *b,T *c)
     {
      Connect(a,b);
      Connect_nullb(b,c);
     }
     
    // null <- obj -> null
  
    static void Init(T *obj) // obj!=0 unlinked
     {
      Link(obj).prev=0;
      Link(obj).next=0;
     }
     
    // place -> obj -> next -> ... -> null
  
    static void InsNext(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Connect_nullc(place,obj,Link(place).next);
     }
     
    // null <- ... <- prev <- obj <- place
     
    static void InsPrev(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Connect_nulla(Link(place).prev,obj,place);
     }
     
    // null <- ... <- prev <- obj -> next -> ... -> null
     
    static void Del(T *obj) // obj!=0 linked
     {
      Connect_null(Link(obj).prev,Link(obj).next);
     }
     
    // place -> obj -> next -> ... -> null
 
    static T * DelNext(T *place) // place!=0 linked
     {
      T *obj=Link(place).next;
      
      if( obj ) Connect_nullb(place,Link(obj).next);
      
      return obj;
     }
     
    // null <- ... <- prev <- obj <- place
 
    static T * DelPrev(T *place) // place!=0 linked
     {
      T *obj=Link(place).prev;
      
      if( obj ) Connect_nulla(Link(obj).prev,place);
      
      return obj;
     }
 
    // null <- top -> next -> ... -> null
 
    static T * /* top */ InsTop(T *top,T *obj) // obj!=0 unlinked
     {
      Link(obj).prev=0;
      Connect_nullb(obj,top);
     
      return obj;
     }
     
    // null <- top -> ... -> obj -> ... -> null
     
    static T * /* top */ DelTop(T *top,T *obj) // obj!=0 linked
     {
      if( top==obj ) 
        {
         top=Link(obj).next;
         
         if( top ) Link(top).prev=0;
        }
      else
        {
         Connect_nullb(Link(obj).prev,Link(obj).next);
        }
        
      return top;
     }
     
    // ptr -> next -> ... -> null
    
    struct Cur
     {
      T *ptr;
      
      // constructors
      
      explicit Cur(T *ptr_) : ptr(ptr_) {}
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ () { ptr=Link(ptr).next; }
      
      void operator -- () { ptr=Link(ptr).prev; }
     };
     
    // null <- ... <- prev <- ptr
    
    struct RevCur
     {
      T *ptr;
      
      // constructors
      
      explicit RevCur(T *ptr_) : ptr(ptr_) {}
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ () { ptr=Link(ptr).prev; }
      
      void operator -- () { ptr=Link(ptr).next; }
     };
     
    // null <- top -> next -> ... -> null
    
    struct Top
     {
      T *top;
      
      // constructors
      
      Top() { init(); }
      
      // methods
      
      void init() { top=0; }
      
      T * operator + () const { return top; }
      
      bool operator ! () const { return !top; }
      
      Cur start() const { return Cur(top); }
      
      // insert object
      
      void ins(T *obj) // obj!=0 unlinked
       {
        top=InsTop(top,obj);
       }
       
      void ins_before(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==top )
          {
           Link(obj).prev=0;
           Connect(obj,pos);
     
           top=obj;
          }
        else
          {
           InsPrev(pos,obj);
          }
       }
       
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        InsNext(pos,obj);
       }
       
      void ins_before(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_before(cur.ptr,obj);
       }
       
      void ins_after(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_after(cur.ptr,obj);
       }
      
      // delete object
       
      void del(T *obj) // obj!=0 from the list
       {
        top=DelTop(top,obj);
       }
       
      T * del()
       {
        T *ret=top;
        
        if( ret )
          {
           T *next=Link(ret).next;
         
           if( next ) Link(next).prev=0;
      
           top=next;
          }
        
        return ret;
       }
       
      T * del_and_move(Cur &cur) // +cur
       {
        T *ptr=cur.ptr;
        
        cur.ptr=Link(ptr).next;
        
        del(ptr);
        
        return ptr;
       }
     };
     
    // null <- first -> next -> ... -> last -> null
    
    struct FirstLast
     {
      T *first;
      T *last;
      
      // constructors
      
      FirstLast() { init(); }
      
      // methods
      
      void init()
       {
        first=0;
        last=0;
       }
       
      T * operator + () const { return first; }
      
      bool operator ! () const { return !first; }
      
      Cur start() const { return Cur(first); }
      
      RevCur start_rev() const { return RevCur(last); }
      
      // insert object
      
      void ins_first(T *obj) // obj!=0 unlinked
       {
        Link(obj).prev=0;
        
        if( first )
          {
           Connect(obj,first);
          }
        else
          {
           Link(obj).next=0;
           last=obj;
          }  
       
        first=obj;
       }
       
      void ins_last(T *obj) // obj!=0 unlinked
       {
        Link(obj).next=0;
        
        if( last )
          {
           Connect(last,obj);
          }
        else
          {
           Link(obj).prev=0;
           first=obj;
          }  
       
        last=obj;
       }
       
      void ins_before(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==first )
          {
           Link(obj).prev=0;
           Connect(obj,pos);
           
           first=obj;
          }
        else
          {
           InsPrev(pos,obj);
          }
       }
       
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==last )
          {
           Link(obj).next=0;
           Connect(pos,obj);
           
           last=obj;
          }
        else
          {
           InsNext(pos,obj);
          }
       }
       
      void ins_before(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_before(cur.ptr,obj);
       }
       
      void ins_before(RevCur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_before(cur.ptr,obj);
       }
       
      void ins_after(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_after(cur.ptr,obj);
       }
       
      void ins_after(RevCur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_after(cur.ptr,obj);
       }
       
      // delete object
      
      void del(T *obj) // obj!=0 from the list
       {
        T *prev=Link(obj).prev;
        T *next=Link(obj).next;
        
        if( prev )
          {
           Link(prev).next=next;
          }
        else
          {
           first=next;
          }
          
        if( next )  
          {
           Link(next).prev=prev;
          }
        else
          {
           last=prev;
          }  
       }
       
      T * del_first()
       {
        T *ret=first;
        
        if( ret )
          {
           T *next=Link(ret).next;
        
           first=next;
        
           if( next )
             {
              Link(next).prev=0;
             }
           else
             {
              last=0;
             }
          }
        
        return ret;
       }
       
      T * del_last()
       {
        T *ret=last;
        
        if( ret )
          {
           T *prev=Link(ret).prev;
        
           last=prev;
        
           if( prev )
             {
              Link(prev).next=0;
             }
           else
             {
              first=0;
             }
          }
        
        return ret;
       } 
 
      T * del_and_move(Cur &cur) // +cur
       {
        T *ptr=cur.ptr;
        
        cur.ptr=Link(ptr).next;
        
        del(ptr);
        
        return ptr;
       }
       
      T * del_and_move(RevCur &cur) // +cur
       {
        T *ptr=cur.ptr;
        
        cur.ptr=Link(ptr).prev;
        
        del(ptr);
        
        return ptr;
       }
     };
   };
   
  template <DLink<T> T::* LinkMember>
  struct CircularAlgo
   {
    static DLink<T> & Link(T *obj) { return obj->*LinkMember; }
    
    // Connect()
    
    static void Connect(T *a,T *b)
     {
      Link(a).next=b;
      Link(b).prev=a;
     }
     
    static void Connect(T *a,T *b,T *c)
     {
      Connect(a,b);
      Connect(b,c);
     }
     
    // obj <- obj -> obj 
     
    static void Init(T *obj) // obj!=0 unlinked
     {
      Connect(obj,obj);
     }
     
    // place -> obj -> next -> ... -> place 
     
    static void InsNext(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Connect(place,obj,Link(place).next);
     }
     
    // place <- ... <- prev <- obj <- place 
     
    static void InsPrev(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Connect(Link(place).prev,obj,place);
     }
     
    // ... <- prev <- obj -> next -> ...
     
    static void Del(T *obj) // obj!=0 linked
     {
      Connect(Link(obj).prev,Link(obj).next);
     }
     
    // place -> obj -> next -> ... -> place
    
    static T * DelNext(T *place) // place!=0 linked
     {
      T *obj=Link(place).next;
      
      if( obj==place ) return 0;
      
      Del(obj);
      
      return obj;
     }
     
    // place <- ... <- prev <- obj <- place
    
    static T * DelPrev(T *place) // place!=0 linked
     {
      T *obj=Link(place).prev;
      
      if( obj==place ) return 0;
      
      Del(obj);
      
      return obj;
     }
     
    // top -> next -> ... -> last -> top
    
    static T * /* top */ InsTopFirst(T *top,T *obj) // obj!=0 unlinked
     {
      if( top )
        {
         InsPrev(top,obj);
        }
      else
        {
         Init(obj);
        }
         
      return obj;
     }
     
    // top -> next -> ... -> last -> top
    
    static T * /* top */ InsTopLast(T *top,T *obj) // obj!=0 unlinked
     {
      if( top )
        {
         InsPrev(top,obj);
        
         return top;
        }
      else
        {
         Init(obj);
         
         return obj;
        }
     }
     
    // top -> ... -> obj -> ... -> last -> top
    
    static T * /* top */ DelTop(T *top,T *obj) // obj!=0 linked
     {
      if( top==obj )
        {
         top=Link(obj).next;
        
         if( top==obj ) return 0;
        }
        
      Del(obj);
         
      return top;
     }
     
    // ptr -> next -> ... -> last
    
    struct Cur
     {
      T *ptr;
      T *last;
      
      // constructors
      
      explicit Cur(T *ptr_)
       : ptr(ptr_) 
       {
        if( ptr_ )
          last=Link(ptr_).prev;
        else
          last=0;
       }
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ ()
       {
        if( ptr!=last )
          ptr=Link(ptr).next;
        else
          ptr=0;
       }
      
      void operator -- ()
       {
        ptr=Link(ptr).prev;
        
        if( ptr==last ) ptr=0;
       }
      
      // insert object
       
      void ins_after(T *obj) // +, obj!=0 unlinked
       {
        T *pos=ptr;
        
        InsNext(pos,obj);
        
        if( pos==last ) last=obj;
       } 
     };
     
    // first <- ... <- prev <- ptr
    
    struct RevCur
     {
      T *ptr;
      T *first;
      
      // constructors
      
      explicit RevCur(T *first_)
       : first(first_) 
       {
        if( first_ )
          ptr=Link(first_).prev;
        else
          ptr=0;
       }
      
      // object ptr
      
      T * operator + () const { return ptr; }
      
      bool operator ! () const { return !ptr; }
      
      T & operator * () const { return *ptr; }
  
      T * operator -> () const { return ptr; }
      
      // cursor
      
      void operator ++ ()
       {
        if( ptr!=first )
          ptr=Link(ptr).prev;
        else
          ptr=0;
       }
      
      void operator -- ()
       {
        ptr=Link(ptr).next;
        
        if( ptr==first ) ptr=0;
       }
       
      // insert object
      
      void ins_after(T *obj) // +, obj!=0 unlinked
       {
        InsNext(ptr,obj);
       }
     };
     
    // top -> ... -> obj -> ... -> last -> top
    
    struct Top
     {
      T *top;
      
      // constructors
      
      Top() { init(); }
      
      // methods
      
      void init() { top=0; }
      
      T * operator + () const { return top; }
      
      bool operator ! () const { return !top; }
      
      Cur start() const { return Cur(top); }
      
      RevCur start_rev() const { return RevCur(top); }
      
      // insert object
      
      void ins_first(T *obj) // obj!=0 unlinked
       {
        top=InsTopFirst(top,obj);
       }
       
      void ins_last(T *obj) // obj!=0 unlinked
       {
        top=InsTopLast(top,obj);
       }
       
      void ins_before(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        if( pos==top )
          {
           InsPrev(pos,obj);
           
           top=obj;
          }
        else
          {
           InsPrev(pos,obj);
          }
       }
       
      void ins_after(T *pos,T *obj) // pos!=0, obj!=0 unlinked
       {
        InsNext(pos,obj);
       }
       
      void ins_before(Cur cur,T *obj) // +cur, obj!=0 unlinked
       {
        ins_before(cur.ptr,obj);
       }
      
      void ins_after(Cur &cur,T *obj) // +cur, obj!=0 unlinked
       {
        cur.ins_after(obj);
       }
      
      void ins_before(RevCur &cur,T *obj) // +cur, obj!=0 unlinked
       {
        T *pos=cur.ptr;
       
        if( pos==top )
          {
           InsPrev(pos,obj);
           
           top=obj;
           cur.first=obj;
          }
        else
          {
           InsPrev(pos,obj);
          }
       }
       
      void ins_after(RevCur cur,T *obj) // +cur, obj!=0 unlinked
       {
        cur.ins_after(obj);
       }
      
      // delete object
      
      void del(T *obj) // obj!=0 from the list
       {
        top=DelTop(top,obj);
       }
       
      T * del_first()
       {
        T *ret=top;
        
        if( ret )
          {
           T *next=Link(ret).next;
          
           Del(ret);

           if( next!=ret )
             top=next;
           else
             top=0;  
          }
        
        return ret;
       }
       
      T * del_last()
       {
        T *ptr=top;
        
        if( ptr )
          {
           T *ret=Link(ptr).prev;
           
           Del(ret);
           
           if( ptr==ret ) top=0;
           
           return ret;
          }
          
        return 0;
       } 
       
      T * del_and_move(Cur &cur) // +cur
       {
        T *ptr=cur.ptr;
        
        if( ptr==cur.last )
          {
           cur.ptr=0;
           cur.last=0;
          }
        else
          {
           cur.ptr=Link(ptr).next;
          }  
          
        del(ptr);
        
        return ptr;
       }
       
      T * del_and_move(RevCur &cur) // +cur
       {
        T *ptr=cur.ptr;
        
        if( ptr==cur.first )
          {
           cur.ptr=0;
           cur.first=0;
          }
        else
          {
           cur.ptr=Link(ptr).prev;
          }
        
        del(ptr);
        
        return ptr;
       }
       
      // rotate
      
      T * rotate_forward() // return top element moved to bottom
       {
        T *ret=top;
        
        if( ret )
          {
           top=Link(ret).next;
          }
        
        return ret;
       }
       
      T * rotate_backward() // return bottom element moved to top
       {
        T *ptr=top;
        
        if( ptr )
          {
           top=Link(ptr).prev;
          }
        
        return top;
       }
     };
   };
 };
 
} // namespace CCore
 
#endif
 

