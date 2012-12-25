/* TreeLink.h */ 
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

#ifndef CCore_inc_tree_TreeLink_h
#define CCore_inc_tree_TreeLink_h

#include <CCore/inc/tree/TreeBase.h>
 
namespace CCore {

/* functions */ 

void GuardRadixTreeCheckFailed(const char *text);

inline void GuardRadixTreeCheck(bool cond,const char *text)
 {
  if( !cond ) GuardRadixTreeCheckFailed(text);
 }

/* classes */ 

template <class T,class K> struct TreeLink;

/* struct TreeLink<T,K> */ 

template <class T,class K>
struct TreeLink 
 {
  T *lo;
  T *hi;
  K key; // unique
  
  typedef TreeLink<T,K> Node;
  
  template <TreeLink<T,K> T::* LinkMember,class KRef=K> struct BinAlgo;
   
  template <TreeLink<T,K> T::* LinkMember> struct RadixAlgo;
 };
 
template <class T,class K>
template <TreeLink<T,K> T::* LinkMember,class KRef>
struct TreeLink<T,K>::BinAlgo
 {
   // node!=0
   // root_ptr!=0
 
  static Node & Link(T *node) { return node->*LinkMember; }
  
  static void Link(T *node,T *lo,T *hi)
   {
    Node &link=Link(node);
    
    link.lo=lo;
    link.hi=hi;
   }
  
  static void Link(T *node,T *lo,T *hi,KRef key)
   {
    Node &link=Link(node);
    
    link.lo=lo;
    link.hi=hi;
    link.key=key;
   }
  
  // Find
  
  static T * Find(T *root,KRef key) // == key
   {
    while( root )
      {
       Node &link=Link(root);
       
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

       switch( Cmp(key,link.key) )
         {
          case CmpLess    :                 root=link.lo; break;
          case CmpGreater : candidate=root; root=link.hi; break;
          
          default: return root;
         }
      }
      
    return candidate;  
   }
  
  // Locate
  
  static T ** Locate(T **root_ptr,KRef key)
   {
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);
       
       switch( Cmp(key,link.key) )
         {
          case CmpLess    : root_ptr=&link.lo; break;
          case CmpGreater : root_ptr=&link.hi; break;
          
          default: return root_ptr;
         }
      }
      
    return 0; 
   }

  static T ** LocateMin(T **root_ptr)
   {
    T **candidate=0;
    
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);

       candidate=root_ptr; 
       root_ptr=&link.lo;
      }
      
    return candidate;  
   }

  static T ** LocateMin(T **root_ptr,KRef key) // min >= key
   {
    T **candidate=0;
    
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);

       switch( Cmp(key,link.key) )
         {
          case CmpLess    : candidate=root_ptr; root_ptr=&link.lo; break;
          case CmpGreater :                     root_ptr=&link.hi; break;
          
          default: return root_ptr;
         }
      }
      
    return candidate;  
   }
   
  static T ** LocateMax(T **root_ptr)
   {
    T **candidate=0;
    
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);

       candidate=root_ptr; 
       root_ptr=&link.hi;
      }
      
    return candidate;  
   }

  static T ** LocateMax(T **root_ptr,KRef key) // max <= key
   {
    T **candidate=0;
    
    while( T *root=*root_ptr )
      {
       Node &link=Link(root);

       switch( Cmp(key,link.key) )
         {
          case CmpLess    :                     root_ptr=&link.lo; break;
          case CmpGreater : candidate=root_ptr; root_ptr=&link.hi; break;
          
          default: return root_ptr;
         }
      }
      
    return candidate;  
   }
   
  // Del 
   
  static T * DelRoot(T **root_ptr) // (*root_ptr)!=0
   {
    T *root=*root_ptr;
    
    Node &link=Link(root);
    
    if( link.lo )
      {
       T *node=DelRoot(LocateMax(&link.lo));
       
       Link(node,link.lo,link.hi);
       
       *root_ptr=node;
      }
    else if( link.hi )
      {
       T *node=DelRoot(LocateMin(&link.hi));
       
       Link(node,link.lo,link.hi);
       
       *root_ptr=node;
      }
    else
      {
       *root_ptr=0;
      }
      
    return root;  
   }
   
  static T * Del(T **root_ptr,KRef key)
   { 
    if( T **loc=Locate(root_ptr,key) ) return DelRoot(loc); 
    
    return 0;
   }
   
  static T * DelMin(T **root_ptr)
   { 
    if( T **loc=LocateMin(root_ptr) ) return DelRoot(loc); 
    
    return 0;
   }
   
  static T * DelMin(T **root_ptr,KRef key)
   { 
    if( T **loc=LocateMin(root_ptr,key) ) return DelRoot(loc); 
    
    return 0;
   }
   
  static T * DelMax(T **root_ptr)
   {
    if( T **loc=LocateMax(root_ptr) ) return DelRoot(loc);
     
    return 0; 
   }
   
  static T * DelMax(T **root_ptr,KRef key)
   {
    if( T **loc=LocateMax(root_ptr,key) ) return DelRoot(loc);
     
    return 0; 
   }
   
  static void Del(T **root_ptr,T *node)
   { 
    DelRoot(Locate(root_ptr,Link(node).key)); 
   }
   
  // struct NodePtr
  
  struct NodePtr
   {
    T **node_ptr;
    
    NodePtr(T **node_ptr_) : node_ptr(node_ptr_) {}
    
    T ** operator + () const { return node_ptr; }
    
    bool operator ! () const { return !node_ptr; }
    
    T * node() const { return *node_ptr; }
   };
  
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
    
    // locate
    
    NodePtr locate(KRef key) { return Locate(&root,key); }
    
    NodePtr locateMin() { return LocateMin(&root); }
    
    NodePtr locateMin(KRef key) { return LocateMin(&root,key); }
    
    NodePtr locateMax() { return LocateMax(&root); }
    
    NodePtr locateMax(KRef key) { return LocateMax(&root,key); }
    
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
template <TreeLink<T,K> T::* LinkMember>
struct TreeLink<T,K>::RadixAlgo : BinAlgo<LinkMember,K>
 {
  static_assert( Meta::IsUInt<K>::Ret ,"CCore::TreeLink<T,K>::RadixAlgo<LinkMember> : K must be an unsigned integral type");
 
  using BinAlgo<LinkMember,K>::Link;
  
  // Med()
  
  static K Med(K kmin,K kmax) // kmin<kmax
   {
    return K( kmin+(kmax-kmin-1)/2 );
   }
   
  // class PrepareIns
 
  class PrepareIns : NoCopy
   {
     T **root_ptr;
     T *lo;
     T *hi;
     K key;
    
     T *complete_node;
     K kmin;
     K kmax;
     void (PrepareIns::*complete_func)(T *node);
     
    private: 
    
     void set(T **root_ptr_,T *lo_,T *hi_,K key_)
      {
       found=0;
      
       root_ptr=root_ptr_;
       lo=lo_;
       hi=hi_;
       key=key_;
      } 
     
     void set_hi(T *node,K kmin_,K kmax_)
      {
       complete_node=node;
       kmin=kmin_;
       kmax=kmax_;
       complete_func=&PrepareIns::complete_hi;
      }
   
     void set_lo(T *node,K kmin_,K kmax_)
      {
       complete_node=node;
       kmin=kmin_;
       kmax=kmax_;
       complete_func=&PrepareIns::complete_lo;
      }
     
     void set_none()
      {
       complete_func=&PrepareIns::complete_none;
      }
     
     void prepare(T **root_ptr,K key,K kmin,K kmax)
      {
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
                  root_ptr=&link.lo;
                  kmax=kmed;
                 }
               else
                 {
                  set(root_ptr,link.lo,link.hi,key);
                  set_hi(root,kmed+1,kmax);
                  
                  return;
                 }
              }
             break;
          
             case CmpGreater :
              {
               K kmed=Med(kmin,kmax);
            
               if( kmed<key )
                 {
                  root_ptr=&link.hi;
                  kmin=kmed+1;
                 }
               else
                 {
                  set(root_ptr,link.lo,link.hi,key);
                  set_lo(root,kmin,kmed);
                  
                  return;
                 }
              }
             break;
          
             default: 
              {
               found=root;
               
               return;
              }
            }
         }  
       
       set(root_ptr,0,0,key); 
       set_none();
      }
     
     static void CompleteIns(T **root_ptr,K kmin,K kmax,T *node)
      {
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
                  root_ptr=&link.lo;
                  kmax=kmed;
                 }
               else
                 {
                  Link(node,link.lo,link.hi);
                 
                  *root_ptr=node;
               
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
                  root_ptr=&link.hi;
                  kmin=kmed+1;
                 }
               else
                 {
                  Link(node,link.lo,link.hi);
                  
                  *root_ptr=node;
               
                  root_ptr=&Link(node).lo;
                  node=root;
                  key=Link(node).key;
                  kmax=kmed;
                 }
              }
             break;
          
             default: 
              {
               RadixTreeBrokenAbort();
              }
            }
         }
      
       Link(node,0,0);
      
       *root_ptr=node;
      }
    
     void complete_none(T *node)
      {
       Link(node,lo,hi,key);
      
       *root_ptr=node;
      }
     
     void complete_hi(T *node)
      {
       complete_none(node);
      
       CompleteIns(&Link(node).hi,kmin,kmax,complete_node);
      }
     
     void complete_lo(T *node)
      {
       complete_none(node);
      
       CompleteIns(&Link(node).lo,kmin,kmax,complete_node);
      }
     
    public: 
   
     T *found;
    
     PrepareIns(T **root_ptr,K key)
      {
       prepare(root_ptr,key,0,UIntMax());
      }
     
     PrepareIns(typename BinAlgo<LinkMember,K>::Root &root,K key)
      {
       prepare(&root.root,key,0,UIntMax());
      }
     
     PrepareIns(T **root_ptr,K key,K kmin,K kmax)
      {
       prepare(root_ptr,key,kmin,kmax);
      }
     
     PrepareIns(typename BinAlgo<LinkMember,K>::Root &root,K key,K kmin,K kmax)
      {
       prepare(&root.root,key,kmin,kmax);
      }
     
     void complete(T *node) { (this->*complete_func)(node); }
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
  
      GuardRadixTreeCheck( kmin<=key && key<=kmax ,"kmin<=key && key<=kmax");
  
      if( kmin<kmax )
        {
         K kmed=Med(kmin,kmax);
    
         if( T *lo=Link(root).lo )
           {
            Check check(lo,kmin,kmed);
            
            GuardRadixTreeCheck( check.maxval<key ,"lo.maxval<key");
        
            minval=check.minval;
           }
         else
           {
            minval=key;
           }  
       
         if( T *hi=Link(root).hi )
           {
            Check check(hi,kmed+1,kmax);
            
            GuardRadixTreeCheck( key<check.minval ,"key<hi.minval");
        
            maxval=check.maxval;
           }
         else
           {
            maxval=key;
           } 
        }
      else
        {
         GuardRadixTreeCheck( Link(root).lo==0 || Link(root).hi==0 ,"hi==0 && lo==0");
         
         minval=key;
         maxval=key;
        }  
     }
   };
 };

} // namespace CCore
 
#endif
 

