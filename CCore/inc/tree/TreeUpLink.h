/* TreeUpLink.h */ 
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

#ifndef CCore_inc_tree_TreeUpLink_h
#define CCore_inc_tree_TreeUpLink_h

#include <CCore/inc/Cmp.h>
 
namespace CCore {

/* functions */ 

void GuardRadixTreeUpCheckFailed(const char *text);

inline void GuardRadixTreeUpCheck(bool cond,const char *text)
 {
  if( !cond ) GuardRadixTreeUpCheckFailed(text);
 }

/* classes */ 

template <class T,class K> struct TreeUpLink;

/* struct TreeUpLink<T,K> */ 
 
template <class T,class K> 
struct TreeUpLink
 {
  T *lo; // == this for same-key nodes
  T *hi;
  T *up;
  K key; // non-unique
  
  typedef TreeUpLink<T,K> Node;
  
  template <TreeUpLink<T,K> T::* LinkMember,class KRef=K> struct BinAlgo;
   
  template <TreeUpLink<T,K> T::* LinkMember> struct RadixAlgo;
 };
 
template <class T,class K> 
template <TreeUpLink<T,K> T::* LinkMember,class KRef>
struct TreeUpLink<T,K>::BinAlgo
 {
   // node!=0
   // root_ptr!=0
 
  static Node & Link(T *node) { return node->*LinkMember; }
  
  static void Link(T *node,T *lo,T *hi,T *up)
   {
    Node &link=Link(node);
    
    link.lo=lo;
    link.hi=hi;
    link.up=up;
    
    if( lo ) Link(lo).up=node;
    if( hi ) Link(hi).up=node;
   }

  static void Link(T *node,T *hi,T *up)
   {
    Node &link=Link(node);
    
    link.lo=node;
    link.hi=hi;
    link.up=up;
    
    if( hi ) Link(hi).up=node;
   }
   
  // Find
  
  static T * Find(T *root,KRef key) // == key
   {
    while( root )
      {
       Node &link=Link(root);
       
       if( link.lo==root )
         {
          if( key==link.key ) return root;
          
          return 0;
         }
       
       switch( Cmp(key,link.key) )
         {
          case CmpLess    : root=link.lo; break;
          case CmpGreater : root=link.hi; break;
          
          default: return root;
         }
      }
      
    return 0;  
   }
  
  static T * FindMin(T *root)
   {
    T *candidate=0;
    
    while( root )
      {
       Node &link=Link(root);
       
       candidate=root; 
       
       if( link.lo==root ) break;

       root=link.lo;
      }
      
    return candidate;  
   }
  
  static T * FindMin(T *root,KRef key) // min >= key
   {
    T *candidate=0;
    
    while( root )
      {
       Node &link=Link(root);
       
       if( link.lo==root )
         {
          if( key<=link.key ) candidate=root;
          
          break;
         }

       switch( Cmp(key,link.key) )
         {
          case CmpLess    : candidate=root; root=link.lo; break;
          case CmpGreater :                 root=link.hi; break;
          
          default: return root;
         }
      }
      
    return candidate;  
   }
  
  static T * FindMax(T *root)
   {
    T *candidate=0;
    
    while( root )
      {
       Node &link=Link(root);

       candidate=root; 
       
       if( link.lo==root ) break;

       root=link.hi;
      }
      
    return candidate;  
   }

  static T * FindMax(T *root,KRef key) // max <= key
   {
    T *candidate=0;
    
    while( root )
      {
       Node &link=Link(root);

       if( link.lo==root )
         {
          if( key>=link.key ) candidate=root;
          
          break;
         }

       switch( Cmp(key,link.key) )
         {
          case CmpLess    :                 root=link.lo; break;
          case CmpGreater : candidate=root; root=link.hi; break;
          
          default: return root;
         }
      }
      
    return candidate;  
   }
  
  // Del
  
  static T * DelRoot(T *root) // root!=0
   {
    Node &link=Link(root);
    
    T *lo=link.lo;
    T *hi=link.hi;
    T *up=link.up;
    
    if( lo==root )
      {
       if( hi )
         {
          Link(hi).up=up;
          
          return hi;
         }
       else
         {
          return 0;
         }  
      }
    else if( lo )  
      {
       T *ptr=FindMax(lo);
       
       Del(&lo,ptr);
       
       Link(ptr,lo,hi,up);
       
       return ptr;
      }
    else if( hi )
      {
       T *ptr=FindMin(hi);
       
       Del(&hi,ptr);
       
       Link(ptr,lo,hi,up);
       
       return ptr;
      }
    else
      {
       return 0;
      }  
   }
  
  static void Del(T **root_ptr,T *node)
   {
    if( *root_ptr==node )
      {
       *root_ptr=DelRoot(node);
      }
    else
      {
       T *up=Link(node).up;
 
       if( Link(up).lo==node )
         {
          Link(up).lo=DelRoot(node);
         }
       else
         {
          Link(up).hi=DelRoot(node);
         }
      }
   }
 
  static T * Del(T **root_ptr,KRef key)
   {
    if( T *ret=Find(*root_ptr,key) )
      {
       Del(root_ptr,ret);
       
       return ret;
      }
      
    return 0;  
   }
 
  static T * DelMin(T **root_ptr)
   {
    if( T *ret=FindMin(*root_ptr) )
      {
       Del(root_ptr,ret);
       
       return ret;
      }
      
    return 0;  
   }
 
  static T * DelMin(T **root_ptr,KRef key)
   {
    if( T *ret=FindMin(*root_ptr,key) )
      {
       Del(root_ptr,ret);
       
       return ret;
      }
      
    return 0;  
   }
   
  static T * DelMax(T **root_ptr)
   {
    if( T *ret=FindMax(*root_ptr) )
      {
       Del(root_ptr,ret);
       
       return ret;
      }
      
    return 0;  
   }
   
  static T * DelMax(T **root_ptr,KRef key)
   {
    if( T *ret=FindMax(*root_ptr,key) )
      {
       Del(root_ptr,ret);
       
       return ret;
      }
      
    return 0;  
   }
   
  // struct Root
  
  struct Root
   {
    T *root;
    
    // constructors
    
    Root() { init(); }
    
    // methods
    
    void init() { root=0; }
    
    T * operator + () const { return root; }
    
    bool operator ! () const { return !root; }
    
    // find
    
    T * find(KRef key) const { return Find(root,key); }
    
    T * findMin() const { return FindMin(root); }
    
    T * findMin(KRef key) const { return FindMin(root,key); }
    
    T * findMax() const { return FindMax(root); }
    
    T * findMax(KRef key) const { return FindMax(root,key); }
    
    // del
    
    T * del(KRef key) { return Del(&root,key); }
    
    T * delMin() { return DelMin(&root); }
    
    T * delMin(KRef key) { return DelMin(&root,key); }
    
    T * delMax() { return DelMax(&root); }
    
    T * delMax(KRef key) { return DelMax(&root,key); }
    
    void del(T *node) { Del(&root,node); }
   };
 };
 
template <class T,class K> 
template <TreeUpLink<T,K> T::* LinkMember>
struct TreeUpLink<T,K>::RadixAlgo : BinAlgo<LinkMember,K>
 {
  static_assert( Meta::IsUInt<K>::Ret ,"CCore::TreeUpLink<T,K>::RadixAlgo<LinkMember> : K must be an unsigned integral type");
  
  using BinAlgo<LinkMember,K>::Link;
  
  typedef typename BinAlgo<LinkMember,K>::Root BaseRoot;
  
  // Med()

  static K Med(K kmin,K kmax) // kmin<kmax
   {
    return kmin+(kmax-kmin-1)/2;
   }
  
  // Ins

  static void Ins(BaseRoot &root,T *node,K kmin,K kmax)
   { 
    Ins(&root.root,node,kmin,kmax); 
   }
  
  static void Ins(T **root_ptr,T *node,K kmin,K kmax)
   {
    T *up=0;
    K key=Link(node).key;
    
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);
       
       switch( Cmp(key,link.key) )
         {
          case CmpLess :
           {
            K kmed=Med(kmin,kmax);
            
            if( key<=kmed )
              {
               up=root;
               root_ptr=&link.lo;
               kmax=kmed;
              }
            else
              {
               Link(node,link.lo,link.hi,up);
               
               *root_ptr=node;
               
               up=node;
               root_ptr=&Link(node).hi;
               node=root;
               key=Link(node).key;
               kmin=kmed+1;
              }
           }
          break;
          
          case CmpGreater :
           {
            K kmed=Med(kmin,kmax);
            
            if( kmed<key )
              {
               up=root;
               root_ptr=&link.hi;
               kmin=kmed+1;
              }
            else 
              {
               Link(node,link.lo,link.hi,up);
               
               *root_ptr=node;
               
               up=node;
               root_ptr=&Link(node).lo;
               node=root;
               key=Link(node).key;
               kmax=kmed;
              }
           }
          break;
          
          default:
           {
            if( kmin<kmax )
              {
               K kmed=Med(kmin,kmax);
              
               up=root;
               
               if( kmed<key )
                 {
                  root_ptr=&link.hi;
                  kmin=kmed+1;
                 }
               else
                 {
                  root_ptr=&link.lo;
                  kmax=kmed;
                 }
              }
            else
              {
               Link(node,root,up);
               
               *root_ptr=node;
               
               link.up=node;
              
               return;
              }
           }
         }
      }
      
    if( kmin<kmax )  
      Link(node,0,0,up);
    else
      Link(node,0,up);
    
    *root_ptr=node;
   }

  static void Ins(BaseRoot &root,T *node)
   {
    Ins(root,node,0,UIntMax());
   }
  
  static void Ins(T **root_ptr,T *node)
   {
    Ins(root_ptr,node,0,UIntMax());
   }
  
  // struct Root
  
  struct Root : BaseRoot
   {
    using BaseRoot::root;
    
    void ins(T *node,K kmin,K kmax)
     { 
      Ins(&root,node,kmin,kmax); 
     }
    
    void ins(T *node,K key,K kmin,K kmax)
     {
      Link(node).key=key;
      
      Ins(&root,node,kmin,kmax); 
     }
    
    void ins(T *node)
     { 
      Ins(&root,node); 
     }
    
    void ins(T *node,K key)
     {
      Link(node).key=key;
      
      Ins(&root,node); 
     }
   };
  
  // struct Check
  
  struct Check
   {
    K minval;
    K maxval;
    
    Check(T *root,K kmin,K kmax)
     {
      if( root )
        {
         run(root,kmin,kmax);
        } 
      else
        {
         minval=0;
         maxval=0;
        }  
     }
     
    void run(T *root,K kmin,K kmax) // root!=0
     {
      K key=Link(root).key;
  
      GuardRadixTreeUpCheck( kmin<=key && key<=kmax ,"kmin<=key && key<=kmax");
  
      if( kmin<kmax )
        {
         K kmed=Med(kmin,kmax);
    
         if( T *lo=Link(root).lo )
           {
            GuardRadixTreeUpCheck( lo!=root ,"lo link same");
            
            GuardRadixTreeUpCheck( Link(lo).up==root ,"lo link");
              
            Check check(lo,kmin,kmed);
            
            GuardRadixTreeUpCheck( check.maxval<=key ,"lo.maxval<=key");
        
            minval=check.minval;
           }
         else
           {
            minval=key;
           }  
       
         if( T *hi=Link(root).hi )
           {
            GuardRadixTreeUpCheck( Link(hi).up==root ,"hi link");
            
            Check check(hi,kmed+1,kmax);
            
            GuardRadixTreeUpCheck( key<=check.minval ,"key<=hi.minval");
        
            maxval=check.maxval;
           }
         else
           {
            maxval=key;
           } 
        }
      else
        {
         for(T *ptr=root; ptr ;ptr=Link(ptr).hi)
           {
            GuardRadixTreeUpCheck( Link(ptr).lo==ptr && Link(ptr).key==key ,"same-key node");
            
            if( T *hi=Link(ptr).hi ) GuardRadixTreeUpCheck( Link(hi).up==ptr ,"same-key node hi link");
           }   
     
         minval=key;
         maxval=key;
        }  
     }
   };  
 };

} // namespace CCore
 
#endif
 

