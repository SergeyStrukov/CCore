/* RBTreeUpLink.h */ 
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

#ifndef CCore_inc_tree_RBTreeUpLink_h
#define CCore_inc_tree_RBTreeUpLink_h
 
#include <CCore/inc/tree/RBTreeBase.h>

namespace CCore {

/* classes */ 

template <class T,class K> struct RBTreeUpLink;

/* struct RBTreeUpLink<T,K> */ 

template <class T,class K> 
struct RBTreeUpLink
 {
  T *up;
  T *lo;
  T *hi;
  K key; // unique
  RBFlag flag;
  
  typedef RBTreeUpLink<T,K> Node;
  
  template <RBTreeUpLink<T,K> T::* LinkMember,class KRef=K> struct BaseAlgo;
  
  template <RBTreeUpLink<T,K> T::* LinkMember,class KRef=K> struct Algo;
 };
 
template <class T,class K> 
template <RBTreeUpLink<T,K> T::* LinkMember,class KRef> 
struct RBTreeUpLink<T,K>::BaseAlgo
 {
   // node!=0
   // root_ptr!=0
  
  static Node & Link(T *node) { return node->*LinkMember; }
  
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
 
  // struct Check
  
  struct Check
   {
    K minval;
    K maxval;
    int height;
    bool black_black;
    
    explicit Check(T *root,T *parent=0)
     : minval(),
       maxval(),
       height(-1),
       black_black(false)
     {
      if( root ) run(root,parent);
     }
    
    struct Prop
     {
      int height;
      bool black_black;
     };
    
    Prop check_lo(Node &link,T *parent)
     {
      Prop ret;
      
      if( T *lo=link.lo )
        {
         Check check(lo,parent);
         
         GuardRBTreeCheck( check.maxval<link.key ,"lo.maxval<key");
         
         minval=check.minval;
         
         ret.height=check.height;
         ret.black_black=check.black_black;
        }
      else
        {
         minval=link.key;
         
         ret.height=-1;
         ret.black_black=false;
        }
      
      return ret;
     }
    
    Prop check_hi(Node &link,T *parent)
     {
      Prop ret;
      
      if( T *hi=link.hi )
        {
         Check check(hi,parent);
         
         GuardRBTreeCheck( link.key<check.minval ,"key<hi.minval");
         
         maxval=check.maxval;
         
         ret.height=check.height;
         ret.black_black=check.black_black;
        }
      else
        {
         maxval=link.key;
         
         ret.height=-1;
         ret.black_black=false;
        }
      
      return ret;
     }
    
    void run(T *root,T *parent) // root!=0
     {
      Node &link=Link(root);
      
      GuardRBTreeCheck( link.up==parent ,"up is correct");

      Prop prop_lo=check_lo(link,root);
      Prop prop_hi=check_hi(link,root);
      
      switch( link.flag )
        {
         case RBFlag_BlackBlack :
          {
           GuardRBTreeCheck( prop_lo.height==prop_hi.height ,"lo.height+1==hi.height+1");
           
           height=prop_lo.height+1;
           black_black=true;
          }
         break;
         
         case RBFlag_LoRed :
          {
           GuardRBTreeCheck( prop_lo.height==prop_hi.height+1 ,"lo.height==hi.height+1");
           GuardRBTreeCheck( prop_lo.black_black ,"lo is BlackBlack");
           
           height=prop_lo.height;
           black_black=false;
          }
         break;
         
         case RBFlag_HiRed :
          {
           GuardRBTreeCheck( prop_lo.height+1==prop_hi.height ,"lo.height+1==hi.height");
           GuardRBTreeCheck( prop_hi.black_black ,"hi is BlackBlack");
           
           height=prop_hi.height;
           black_black=false;
          }
         break;
         
         case RBFlag_RedRed :
          {
           GuardRBTreeCheck( prop_lo.height==prop_hi.height ,"lo.height==hi.height");
           GuardRBTreeCheck( prop_lo.black_black ,"lo is BlackBlack");
           GuardRBTreeCheck( prop_hi.black_black ,"hi is BlackBlack");
           
           height=prop_lo.height;
           black_black=false;
          }
         break;
         
         default: GuardRBTreeCheck( false ,"flag is correct");
        }
     }
   };
 };

template <class T,class K> 
template <RBTreeUpLink<T,K> T::* LinkMember,class KRef> 
struct RBTreeUpLink<T,K>::Algo : BaseAlgo<LinkMember,KRef>
 {
   // node!=0
   // root_ptr!=0

  using BaseAlgo<LinkMember,KRef>::Link;
  
#if 0  
 
  // class PerformDelMin
  
  class PerformDelMin : NoCopy
   {
    private:
     
     // perform
     
     void perform(T **ptrP,T *C,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          *ptrP=B;
          
          Node &linkP=Link(P);
          
          linkB.up=Replace(linkP.up,B);
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          
          return perform_lo(P,C);
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          *ptrP=S;
          
          linkS.up=Replace(linkP.up,S);
          
          linkB.up=S;
          
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);
        
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          linkB.flag^=RBFlag_LoRed;
        
          return perform_lo(P,C);
         }
      }
     
     void perform_lo(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       if( T *C=linkP.lo )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkP.hi;
             
             Node &linkG=Link(G);
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkG.flag^=RBFlag_LoRed;
                
                linkP.flag=RBFlag_RedRed;
                
                return perform_lo(P,C);
               }
             else
               {
                return perform(&linkG.lo,C,P,B);
               }
            }
          else
            {
             return perform(&linkP.lo,C);
            }
         }
       else
         {
          found=P;

          Node &linkG=Link(G);
          
          linkG.lo=0;
          
          linkG.flag^=RBFlag_LoRed;
          
          return;
         }
      }
     
     void perform_hi(T **ptrG,T *G,T *U)
      {
       Node &linkG=Link(G);
       Node &linkU=Link(U);
       
       *ptrG=U;
       
       linkU.up=Replace(linkG.up,U);
       
       T *lo=Replace(linkU.lo,G);
       
       linkG.hi=lo; if( lo ) Link(lo).up=G;

       linkU.flag=RBFlag_LoRed;
       linkG.flag=RBFlag_BlackBlack;
       
       return perform_lo(U,G);
      }
     
     void perform(T **ptrG,T *G)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_LoRed ) 
         return perform_lo(G,linkG.lo);
       else
         return perform_hi(ptrG,G,linkG.hi);
      }
     
     void perform(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return;
       
       Node &linkR=Link(R);
       
       if( linkR.flag&RBFlag_LoRed ) return perform_lo(R,linkR.lo);
       
       if( linkR.flag&RBFlag_HiRed ) return perform_hi(root_ptr,R,linkR.hi);
       
       if( T *C=linkR.lo )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkR.hi;
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkR.flag=RBFlag_RedRed;
                
                dec_flag=true;
                
                return perform_lo(R,C);
               }
             else
               {
                return perform(root_ptr,C,R,B);
               }
            }
          else
            {
             return perform(&linkR.lo,C);
            }
         }
       else
         {
          found=R;
          
          dec_flag=true;
          
          *root_ptr=0;
          
          return;
         }
      }
     
    public: 
    
     T *found;
     bool dec_flag;
    
     explicit PerformDelMin(T **root_ptr) : found(0),dec_flag(false) { perform(root_ptr); }
   };
  
  // class PerformDelMax
  
  class PerformDelMax : NoCopy
   {
    private:
    
     // perform
    
     void perform(T **ptrP,T *B,T *P,T *C)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          *ptrP=B;
          
          Node &linkP=Link(P);
          
          linkB.up=Replace(linkP.up,B);
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          
          return perform_hi(P,C);
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          *ptrP=S;
        
          linkS.up=Replace(linkP.up,S);
          
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          linkB.flag^=RBFlag_HiRed;
        
          return perform_hi(P,C);
         }
      }
     
     void perform_hi(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       if( T *C=linkP.hi )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkP.lo;
             
             Node &linkG=Link(G);
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkG.flag^=RBFlag_HiRed;
                
                linkP.flag=RBFlag_RedRed;
                
                return perform_hi(P,C);
               }
             else
               {
                return perform(&linkG.hi,B,P,C);
               }
            }
          else
            {
             return perform(&linkP.hi,C);
            }
         }
       else
         {
          found=P;

          Node &linkG=Link(G);
          
          linkG.hi=0;
          
          linkG.flag^=RBFlag_HiRed;
          
          return;
         }
      }
     
     void perform_lo(T **ptrG,T *G,T *U)
      {
       Node &linkG=Link(G);
       Node &linkU=Link(U);
       
       *ptrG=U;
       
       linkU.up=Replace(linkG.up,U);
       
       T *hi=Replace(linkU.hi,G);
       
       linkG.lo=hi; if( hi ) Link(hi).up=G;

       linkU.flag=RBFlag_HiRed;
       linkG.flag=RBFlag_BlackBlack;
       
       return perform_hi(U,G);
      }
     
     void perform(T **ptrG,T *G)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_HiRed ) 
         return perform_hi(G,linkG.hi);
       else
         return perform_lo(ptrG,G,linkG.lo);
      }
     
     void perform(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return;
       
       Node &linkR=Link(R);
       
       if( linkR.flag&RBFlag_HiRed ) return perform_hi(R,linkR.hi);
       
       if( linkR.flag&RBFlag_LoRed ) return perform_lo(root_ptr,R,linkR.lo);
       
       if( T *C=linkR.hi )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkR.lo;
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkR.flag=RBFlag_RedRed;
                
                dec_flag=true;
                
                return perform_hi(R,C);
               }
             else
               {
                return perform(root_ptr,B,R,C);
               }
            }
          else
            {
             return perform(&linkR.hi,C);
            }
         }
       else
         {
          found=R;
          
          dec_flag=true;
          
          *root_ptr=0;
          
          return;
         }
      }
     
    public: 
    
     T *found;
     bool dec_flag;
    
     explicit PerformDelMax(T **root_ptr) : found(0),dec_flag(false) { perform(root_ptr); }
   };
  
  // class PerformDel
  
  class PerformDel : NoCopy
   {
     KRef key;
    
    private:
     
     // cmp
     
     CmpResult cmp(Node &link) const { return Cmp(key,link.key); }
     
     // del_root
     
     static void replace(T **ptrP,Node &linkP,T *S)
      {
       Node &linkS=Link(S);
       
       *ptrP=S;
       
       linkS.up=linkP.up;
       linkS.flag=linkP.flag;
       
       T *lo=linkP.lo; 
       T *hi=linkP.hi;
       
       linkS.lo=lo; if( lo ) Link(lo).up=S;
       linkS.hi=hi; if( hi ) Link(hi).up=S;
      }
     
     void del_root(T **ptrP,T *P)
      {
       found=P;
       
       Node &linkP=Link(P);
       
       T *S;

       if( linkP.flag&RBFlag_HiRed )
         {
          PerformDelMin perform(&linkP.hi);
          
          S=perform.found;
          
          if( perform.dec_flag ) linkP.flag^=RBFlag_HiRed;
         }
       else
         {
          PerformDelMax perform(&linkP.lo);
          
          S=perform.found;
          
          if( perform.dec_flag ) linkP.flag^=RBFlag_LoRed;
         }
       
       replace(ptrP,linkP,S);
      }
     
     void del_root_lo(T **ptrP,T *P)
      {
       found=P;
       
       Node &linkP=Link(P);
       
       T *S=PerformDelMax(&linkP.lo).found;
       
       replace(ptrP,linkP,S);
      }
     
     void del_root_hi(T **ptrP,T *P)
      {
       found=P;
       
       Node &linkP=Link(P);
       
       T *S=PerformDelMin(&linkP.hi).found;
       
       replace(ptrP,linkP,S);
      }
     
     // perform
     
     void perform_lo(T **ptrP,T *C,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          *ptrP=B;
          
          Node &linkP=Link(P);
          
          linkB.up=Replace(linkP.up,B);
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          
          return perform_lo(P,C);
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          *ptrP=S;
          
          linkS.up=Replace(linkP.up,S);
          
          linkB.up=S;
          
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);
        
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          linkB.flag^=RBFlag_LoRed;
        
          return perform_lo(P,C);
         }
      }
     
     void perform_hi(T **ptrP,T *B,T *P,T *C)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          *ptrP=B;
          
          Node &linkP=Link(P);
          
          linkB.up=Replace(linkP.up,B);
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          
          return perform_hi(P,C);
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          *ptrP=S;
        
          linkS.up=Replace(linkP.up,S);
          
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          linkB.flag^=RBFlag_HiRed;
        
          return perform_hi(P,C);
         }
      }
     
     void perform_lo_lo(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       if( T *C=linkP.lo )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkP.hi;
             
             Node &linkG=Link(G);
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkG.flag^=RBFlag_LoRed;
                
                linkP.flag=RBFlag_RedRed;
                
                return perform_lo(P,C);
               }
             else
               {
                return perform_lo(&linkG.lo,C,P,B);
               }
            }
          else
            {
             return perform(&linkP.lo,C);
            }
         }
       else
         {
          return; // not found
         }
      }
     
     void perform_lo(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       switch( cmp(linkP) )
        {
         case CmpLess :
          {
           if( T *C=linkP.lo )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.hi;
                 
                 Node &linkG=Link(G);
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_LoRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return perform_lo(P,C);
                   }
                 else
                   {
                    return perform_lo(&linkG.lo,C,P,B);
                   }
                }
              else
                {
                 return perform(&linkP.lo,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break;
         
         case CmpGreater :
          {
           if( T *C=linkP.hi )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.lo;
                 
                 Node &linkG=Link(G);
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_LoRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return perform_hi(P,C);
                   }
                 else
                   {
                    return perform_hi(&linkG.lo,B,P,C);
                   }
                }
              else
                {
                 return perform(&linkP.hi,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break;
         
         default:
          {
           Node &linkG=Link(G);
           
           if( T *C=linkP.hi )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.lo;
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_LoRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return del_root(&linkG.lo,P);
                   }
                 else
                   {
                    return del_root_lo(&linkG.lo,P);
                   }
                }
              else
                {
                 return del_root_hi(&linkG.lo,P);
                }
             }
           else
             {
              found=P;
              
              linkG.lo=0;
              
              linkG.flag^=RBFlag_LoRed;
              
              return;
             }
          }
        }
      }
     
     void perform_hi_hi(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       if( T *C=linkP.hi )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkP.lo;
             
             Node &linkG=Link(G);
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkG.flag^=RBFlag_HiRed;
                
                linkP.flag=RBFlag_RedRed;
                
                return perform_hi(P,C);
               }
             else
               {
                return perform_hi(&linkG.hi,B,P,C);
               }
            }
          else
            {
             return perform(&linkP.hi,C);
            }
         }
       else
         {
          return; // not found
         }
      }
     
     void perform_hi(T *G,T *P)
      {
       Node &linkP=Link(P);
       
       switch( cmp(linkP) )
        {
         case CmpLess :
          {
           if( T *C=linkP.lo )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.hi;
                 
                 Node &linkG=Link(G);
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_HiRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return perform_lo(P,C);
                   }
                 else
                   {
                    return perform_lo(&linkG.hi,C,P,B);
                   }
                }
              else
                {
                 return perform(&linkP.lo,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break;
         
         case CmpGreater :
          {
           if( T *C=linkP.hi )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.lo;
                 
                 Node &linkG=Link(G);
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_HiRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return perform_hi(P,C);
                   }
                 else
                   {
                    return perform_hi(&linkG.hi,B,P,C);
                   }
                }
              else
                {
                 return perform(&linkP.hi,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break;
         
         default:
          {
           Node &linkG=Link(G);
           
           if( T *C=linkP.hi )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkP.lo;
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkG.flag^=RBFlag_HiRed;
                    
                    linkP.flag=RBFlag_RedRed;
                    
                    return del_root(&linkG.hi,P);
                   }
                 else
                   {
                    return del_root_lo(&linkG.hi,P);
                   }
                }
              else
                {
                 return del_root_hi(&linkG.hi,P);
                }
             }
           else
             {
              found=P;
              
              linkG.hi=0;
              
              linkG.flag^=RBFlag_HiRed;
              
              return;
             }
          }
        }
      }
     
     void perform_lo(T **ptrG,T *G,T *U)
      {
       Node &linkG=Link(G);
       Node &linkU=Link(U);
       
       *ptrG=U;
       
       linkU.up=Replace(linkG.up,U);
       
       T *hi=Replace(linkU.hi,G);
       
       linkG.lo=hi; if( hi ) Link(hi).up=G;

       linkU.flag=RBFlag_HiRed;
       linkG.flag=RBFlag_BlackBlack;
       
       return perform_hi_hi(U,G);
      }
     
     void perform_hi(T **ptrG,T *G,T *U)
      {
       Node &linkG=Link(G);
       Node &linkU=Link(U);
       
       *ptrG=U;
       
       linkU.up=Replace(linkG.up,U);
       
       T *lo=Replace(linkU.lo,G);
       
       linkG.hi=lo; if( lo ) Link(lo).up=G;

       linkU.flag=RBFlag_LoRed;
       linkG.flag=RBFlag_BlackBlack;
       
       return perform_lo_lo(U,G);
      }
     
     void perform(T **ptrG,T *G)
      {
       Node &linkG=Link(G);
       
       switch( cmp(linkG) )
        {
         case CmpLess :
          {
           if( linkG.flag&RBFlag_LoRed ) 
             return perform_lo(G,linkG.lo);
           else
             return perform_hi(ptrG,G,linkG.hi);
          }
         break;
         
         case CmpGreater :
          {
           if( linkG.flag&RBFlag_HiRed ) 
             return perform_hi(G,linkG.hi);
           else
             return perform_lo(ptrG,G,linkG.lo);
          }
         break;
         
         default:
          {
           return del_root(ptrG,G);
          }
        }
      }
     
     void perform(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return;
       
       Node &linkR=Link(R);
       
       switch( cmp(linkR) )
        {
         case CmpLess :
          {
           if( linkR.flag&RBFlag_LoRed ) return perform_lo(R,linkR.lo);
           
           if( linkR.flag&RBFlag_HiRed ) return perform_hi(root_ptr,R,linkR.hi);
           
           if( T *C=linkR.lo )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkR.hi;
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkR.flag=RBFlag_RedRed;
                    
                    return perform_lo(R,C);
                   }
                 else
                   {
                    return perform_lo(root_ptr,C,R,B);
                   }
                }
              else
                {
                 return perform(&linkR.lo,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break; 
          
         case CmpGreater :
          {
           if( linkR.flag&RBFlag_HiRed ) return perform_hi(R,linkR.hi);
           
           if( linkR.flag&RBFlag_LoRed ) return perform_lo(root_ptr,R,linkR.lo);
           
           if( T *C=linkR.hi )
             {
              if( Link(C).flag==RBFlag_BlackBlack )
                {
                 T *B=linkR.lo;
                 
                 if( Link(B).flag==RBFlag_BlackBlack )
                   {
                    linkR.flag=RBFlag_RedRed;
                    
                    return perform_hi(R,C);
                   }
                 else
                   {
                    return perform_hi(root_ptr,B,R,C);
                   }
                }
              else
                {
                 return perform(&linkR.hi,C);
                }
             }
           else
             {
              return; // not found
             }
          }
         break; 
          
         default:
          {
           if( linkR.flag==RBFlag_BlackBlack )
             {
              if( T *C=linkR.hi )
                {
                 if( Link(C).flag==RBFlag_BlackBlack )
                   {
                    T *B=linkR.lo;
                    
                    if( Link(B).flag==RBFlag_BlackBlack )
                      {
                       linkR.flag=RBFlag_RedRed;
                       
                       return del_root(root_ptr,R);
                      }
                    else
                      {
                       return del_root_lo(root_ptr,R);
                      }
                   }
                 else
                   {
                    return del_root_hi(root_ptr,R);
                   }
                }
              else
                {
                 found=R;
                 
                 *root_ptr=0;
                 
                 return;
                }
             }
           else
             {
              return del_root(root_ptr,R);
             }
          }
        }
      }
     
    public: 
     
     T *found;
     
     PerformDel(T **root_ptr,KRef key_) : key(key_),found(0) { perform(root_ptr); }
   };
  
#endif  
  
  // class PerformDelMinNode
  
  class PerformDelMinNode : NoCopy
   {
    private:
     
     // transform
     
     static void transform_lo(T **root_ptr,T *R,T *C,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_HiRed )
         {
          T *B=linkP.hi;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; Link(lo).up=P;
          
          if( Link(lo).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_HiRed;
            }
          else
            {
             linkB.flag=RBFlag_LoRed;
             linkP.flag=RBFlag_BlackBlack;
             
             transform_hi(root_ptr,*root_ptr,C,P,lo);
            }
         }
       else
         {
          linkP.flag^=RBFlag_LoRed;
         }
      }
     
     static void transform_hi(T **root_ptr,T *R,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
        
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);

          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
          linkB.flag^=RBFlag_LoRed;
         }
      }
     
     static bool transform(T **root_ptr,T *R,T *C)
      {
       while( C!=R )
         {
          T *P=Link(C).up;
          Node &linkP=Link(P);
          
          if( linkP.flag==RBFlag_BlackBlack )
            {
             T *B=linkP.hi;
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkP.flag^=RBFlag_HiRed;
                
                C=P;
               }
             else
               {
                transform_hi(root_ptr,R,C,P,B);
                
                return false;
               }
            }
          else
            {
             transform_lo(root_ptr,R,C,P);
             
             return false;
            }
         }
       
       return true;
      }
     
     // perform
     
     static void perform_red_lo(T *P)
      {
       Node &linkP=Link(P);
       
       linkP.lo=0;
       linkP.flag^=RBFlag_LoRed;
      }
     
     static void perform_lo(T **root_ptr,T *R,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_HiRed )
         {
          T *B=linkP.hi;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; Link(lo).up=P;
          
          if( Link(lo).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_RedRed;
             
             perform_red_lo(P);
            }
          else
            {
             linkB.flag=RBFlag_LoRed;
             linkP.flag=RBFlag_BlackBlack;

             perform_hi(root_ptr,*root_ptr,D,P,lo);
            }
         }
       else
         {
          perform_red_lo(P);
         }
      }
     
     static void perform_hi(T **root_ptr,T *R,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).lo=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
        
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);

          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          linkB.flag^=RBFlag_LoRed;
         }
       
       perform_red_lo(P);
      }
     
     static bool perform(T **root_ptr,T *R,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_BlackBlack )
         {
          T *B=linkP.hi;
          
          if( Link(B).flag==RBFlag_BlackBlack )
            {
             linkP.flag=RBFlag_RedRed;
             
             bool ret=transform(root_ptr,R,P);
             
             perform_red_lo(P);
             
             return ret;
            }
          else
            {
             perform_hi(root_ptr,R,D,P,B);
             
             return false;
            }
         }
       else
         {
          perform_lo(root_ptr,R,D,P);
          
          return false;
         }
      }
     
     void perform(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return;
       
       T *D=R;
       
       while( T *lo=Link(D).lo ) D=lo;
       
       found=D;
       
       Node &linkD=Link(D);       

       if( linkD.flag==RBFlag_BlackBlack )
         {
          if( D!=R )
            {
             T *P=linkD.up;
             
             dec_flag=perform(root_ptr,R,D,P);
            }
          else
            {
             *root_ptr=0;
             
             dec_flag=true;
            }
         }
       else
         {
          T *U=linkD.up;
          T *N=linkD.hi;
          
          if( D==R ) 
            *root_ptr=N;
          else
            Link(U).lo=N;
          
          Link(N).up=U;
         }
      }
     
    public:
     
     T *found;
     bool dec_flag;
     
     explicit PerformDelMinNode(T **root_ptr) : found(0),dec_flag(false) { perform(root_ptr); } 
   };
  
  // class PerformDelMaxNode
  
  class PerformDelMaxNode : NoCopy
   {
    private:
     
     // transform
     
     static void transform_hi(T **root_ptr,T *R,T *C,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_LoRed )
         {
          T *B=linkP.lo;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; Link(hi).up=P;
          
          if( Link(hi).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_LoRed;
            }
          else
            {
             linkB.flag=RBFlag_HiRed;
             linkP.flag=RBFlag_BlackBlack;
             
             transform_lo(root_ptr,*root_ptr,C,P,hi);
            }
         }
       else
         {
          linkP.flag^=RBFlag_HiRed;
         }
      }
     
     static void transform_lo(T **root_ptr,T *R,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);

          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
          linkB.flag^=RBFlag_HiRed;
         }
      }
     
     static bool transform(T **root_ptr,T *R,T *C)
      {
       while( C!=R )
         {
          T *P=Link(C).up;
          Node &linkP=Link(P);
          
          if( linkP.flag==RBFlag_BlackBlack )
            {
             T *B=linkP.lo;
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkP.flag^=RBFlag_LoRed;
                
                C=P;
               }
             else
               {
                transform_lo(root_ptr,R,C,P,B);
                
                return false;
               }
            }
          else
            {
             transform_hi(root_ptr,R,C,P);
             
             return false;
            }
         }
       
       return true;
      }
     
     // perform
     
     static void perform_red_hi(T *P)
      {
       Node &linkP=Link(P);
       
       linkP.hi=0;
       linkP.flag^=RBFlag_HiRed;
      }
     
     static void perform_hi(T **root_ptr,T *R,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_LoRed )
         {
          T *B=linkP.lo;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; Link(hi).up=P;
          
          if( Link(hi).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_RedRed;
             
             perform_red_hi(P);
            }
          else
            {
             linkB.flag=RBFlag_HiRed;
             linkP.flag=RBFlag_BlackBlack;

             perform_lo(root_ptr,*root_ptr,D,P,hi);
            }
         }
       else
         {
          perform_red_hi(P);
         }
      }
     
     static void perform_lo(T **root_ptr,T *R,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( P!=R )
            {
             Link(U).hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);

          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          linkB.flag^=RBFlag_HiRed;
         }
       
       perform_red_hi(P);
      }
     
     static bool perform(T **root_ptr,T *R,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_BlackBlack )
         {
          T *B=linkP.lo;
          
          if( Link(B).flag==RBFlag_BlackBlack )
            {
             linkP.flag=RBFlag_RedRed;
             
             bool ret=transform(root_ptr,R,P);
             
             perform_red_hi(P);
             
             return ret;
            }
          else
            {
             perform_lo(root_ptr,R,D,P,B);
             
             return false;
            }
         }
       else
         {
          perform_hi(root_ptr,R,D,P);
          
          return false;
         }
      }
     
     void perform(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return;
       
       T *D=R;
       
       while( T *hi=Link(D).hi ) D=hi;
       
       found=D;
       
       Node &linkD=Link(D);       

       if( linkD.flag==RBFlag_BlackBlack )
         {
          if( D!=R )
            {
             T *P=linkD.up;
             
             dec_flag=perform(root_ptr,R,D,P);
            }
          else
            {
             *root_ptr=0;
             
             dec_flag=true;
            }
         }
       else
         {
          T *U=linkD.up;
          T *N=linkD.lo;
          
          if( D==R ) 
            *root_ptr=N;
          else
            Link(U).hi=N;
          
          Link(N).up=U;
         }
      }
     
    public:
     
     T *found;
     bool dec_flag;
     
     explicit PerformDelMaxNode(T **root_ptr) : found(0),dec_flag(false) { perform(root_ptr); } 
   };
  
  // PerformDelNode
  
  class PerformDelNode : NoCopy
   {
    private:
     
     // find
     
     static T ** FindPtr(T **root_ptr,T *C)
      {
       if( T *P=Link(C).up )
         {
          Node &linkP=Link(P);
          
          if( linkP.lo==C ) 
            return &linkP.lo;
          else
            return &linkP.hi;
         }
       else
         {
          return root_ptr;
         }
      }
     
     struct FindBrother
      {
       T *B;
       RBFlag flag;
       
       FindBrother(T *C,Node &linkP)
        {
         if( linkP.lo==C )
           {
            B=linkP.hi;
            flag=RBFlag_HiRed;
           }
         else
           {
            B=linkP.lo;
            flag=RBFlag_LoRed;
           }
        }
      };
     
     // del_root
     
     static void replace(T **ptrP,Node &linkP,T *S)
      {
       Node &linkS=Link(S);
       
       *ptrP=S;
       
       linkS.up=linkP.up;
       linkS.flag=linkP.flag;
       
       T *lo=linkP.lo;
       T *hi=linkP.hi;
       
       linkS.lo=lo; if( lo ) Link(lo).up=S;
       linkS.hi=hi; if( hi ) Link(hi).up=S;
      }
     
     static void del_root(T **ptrP,T *P)
      {
       Node &linkP=Link(P);
       
       T *S;

       if( linkP.flag&RBFlag_HiRed )
         {
          PerformDelMinNode perform(&linkP.hi);
          
          S=perform.found;
          
          if( perform.dec_flag ) linkP.flag^=RBFlag_HiRed;
         }
       else
         {
          PerformDelMaxNode perform(&linkP.lo);
          
          S=perform.found;
          
          if( perform.dec_flag ) linkP.flag^=RBFlag_LoRed;
         }
       
       replace(ptrP,linkP,S);
      }
     
     static void del_root_lo(T **ptrP,T *P)
      {
       Node &linkP=Link(P);
       
       T *S=PerformDelMaxNode(&linkP.lo).found;
       
       replace(ptrP,linkP,S);
      }
     
     static void del_root_hi(T **ptrP,T *P)
      {
       Node &linkP=Link(P);
       
       T *S=PerformDelMinNode(&linkP.hi).found;
       
       replace(ptrP,linkP,S);
      }
     
     static bool del_bbroot(T **ptrP,T *P)
      {
       Node &linkP=Link(P);
       
       if( T *C=linkP.lo )
         {
          if( Link(C).flag==RBFlag_BlackBlack )
            {
             T *B=linkP.hi;
             
             if( Link(B).flag==RBFlag_BlackBlack )
               {
                linkP.flag=RBFlag_RedRed;
                
                del_root(ptrP,P);
                
                return true;
               }
             else
               {
                del_root_hi(ptrP,P);
                
                return false;
               }
            }
          else
            {
             del_root_lo(ptrP,P);
             
             return false;
            }
         }
       else
         {
          *ptrP=0;
          
          return true;
         }
      }
     
     // transform
     
     static void transform_hi(T **root_ptr,T *C,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_LoRed )
         {
          T *B=linkP.lo;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; Link(hi).up=P;
          
          if( Link(hi).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_LoRed;
            }
          else
            {
             linkB.flag=RBFlag_HiRed;
             linkP.flag=RBFlag_BlackBlack;
             
             transform_lo(root_ptr,C,P,hi);
            }
         }
       else
         {
          linkP.flag^=RBFlag_HiRed;
         }
      }
     
     static void transform_lo(T **root_ptr,T *C,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_HiRed )
         {
          T *B=linkP.hi;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; Link(lo).up=P;
          
          if( Link(lo).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_HiRed;
            }
          else
            {
             linkB.flag=RBFlag_LoRed;
             linkP.flag=RBFlag_BlackBlack;
             
             transform_hi(root_ptr,C,P,lo);
            }
         }
       else
         {
          linkP.flag^=RBFlag_LoRed;
         }
      }
     
     static void transform_hi(T **root_ptr,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=S;
             else
               linkU.hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
        
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);

          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
          linkB.flag^=RBFlag_LoRed;
         }
      }
     
     static void transform_lo(T **root_ptr,T *,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=S;
             else
               linkU.hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);

          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_BlackBlack;
          linkB.flag^=RBFlag_HiRed;
         }
      }
     
     static void transform(T **root_ptr,T *C)
      {
       while( T *P=Link(C).up )
         {
          Node &linkP=Link(P);
          
          if( linkP.flag==RBFlag_BlackBlack )
            {
             FindBrother find(C,linkP);
             
             if( Link(find.B).flag==RBFlag_BlackBlack )
               {
                linkP.flag^=find.flag;
                
                C=P;
               }
             else
               {
                if( find.flag==RBFlag_HiRed )
                  return transform_hi(root_ptr,C,P,find.B);
                else
                  return transform_lo(root_ptr,C,P,find.B);
               }
            }
          else
            {
             if( linkP.hi==C )
               return transform_hi(root_ptr,C,P);
             else
               return transform_lo(root_ptr,C,P);
            }
         }
      }
     
     // perform
     
     static void perform_red_hi(T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( del_bbroot(&linkP.hi,D) ) linkP.flag^=RBFlag_HiRed;
      }
     
     static void perform_red_lo(T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( del_bbroot(&linkP.lo,D) ) linkP.flag^=RBFlag_LoRed;
      }
     
     static void perform_hi(T **root_ptr,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_LoRed )
         {
          T *B=linkP.lo;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; Link(hi).up=P;
          
          if( Link(hi).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_RedRed;
             
             perform_red_hi(D,P);
            }
          else
            {
             linkB.flag=RBFlag_HiRed;
             linkP.flag=RBFlag_BlackBlack;

             perform_lo(root_ptr,D,P,hi);
            }
         }
       else
         {
          perform_red_hi(D,P);
         }
      }
     
     static void perform_lo(T **root_ptr,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_HiRed )
         {
          T *B=linkP.hi;
          
          Node &linkB=Link(B);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; Link(lo).up=P;
          
          if( Link(lo).flag==RBFlag_BlackBlack )
            {
             linkB.flag=RBFlag_BlackBlack;
             linkP.flag=RBFlag_RedRed;
             
             perform_red_lo(D,P);
            }
          else
            {
             linkB.flag=RBFlag_LoRed;
             linkP.flag=RBFlag_BlackBlack;

             perform_hi(root_ptr,D,P,lo);
            }
         }
       else
         {
          perform_red_lo(D,P);
         }
      }
     
     static void perform_hi(T **root_ptr,T *D,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_HiRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *lo=Replace(linkB.lo,P);
          
          linkP.hi=lo; if( lo ) Link(lo).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
         }
       else
         {
          T *S=linkB.lo;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=S;
             else
               linkU.hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
        
          T *lo=Replace(linkS.lo,P);
          T *hi=Replace(linkS.hi,B);

          linkP.hi=lo; if( lo ) Link(lo).up=P;
          linkB.lo=hi; if( hi ) Link(hi).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_LoRed;
          linkB.flag^=RBFlag_LoRed;
         }
       
       perform_red_lo(D,P);
      }
     
     static void perform_lo(T **root_ptr,T *D,T *P,T *B)
      {
       Node &linkB=Link(B);

       if( linkB.flag==RBFlag_LoRed )
         {
          Node &linkP=Link(P);
          
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=B;
             else
               linkU.hi=B;
            }
          else
            {
             *root_ptr=B;
            }
          
          linkB.up=U;
          linkP.up=B;
          
          T *hi=Replace(linkB.hi,P);
          
          linkP.lo=hi; if( hi ) Link(hi).up=P;
          
          linkB.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
         }
       else
         {
          T *S=linkB.hi;
        
          Node &linkP=Link(P);
          Node &linkS=Link(S);
        
          T *U=linkP.up;
          
          if( U )
            {
             Node &linkU=Link(U);
             
             if( linkU.lo==P )
               linkU.lo=S;
             else
               linkU.hi=S;
            }
          else
            {
             *root_ptr=S;
            }
          
          linkS.up=U;
          linkP.up=S;
          linkB.up=S;
          
          T *hi=Replace(linkS.hi,P);
          T *lo=Replace(linkS.lo,B);

          linkP.lo=hi; if( hi ) Link(hi).up=P;
          linkB.hi=lo; if( lo ) Link(lo).up=B;
        
          linkS.flag=RBFlag_BlackBlack;
          linkP.flag=RBFlag_HiRed;
          linkB.flag^=RBFlag_HiRed;
         }
       
       perform_red_hi(D,P);
      }
     
     static void perform(T **root_ptr,T *D,T *P)
      {
       Node &linkP=Link(P);
       
       if( linkP.flag==RBFlag_BlackBlack )
         {
          FindBrother find(D,linkP);
          
          if( Link(find.B).flag==RBFlag_BlackBlack )
            {
             linkP.flag=RBFlag_RedRed;
             
             transform(root_ptr,P);
             
             if( find.flag==RBFlag_HiRed )
               perform_red_lo(D,P);
             else
               perform_red_hi(D,P);
            }
          else
            {
             if( find.flag==RBFlag_HiRed )
               perform_hi(root_ptr,D,P,find.B);
             else
               perform_lo(root_ptr,D,P,find.B);
            }
         }
       else
         {
          if( linkP.lo==D )
            perform_lo(root_ptr,D,P);
          else
            perform_hi(root_ptr,D,P);
         }
      }
     
     static void perform(T **root_ptr,T *D)
      {
       Node &linkD=Link(D);       

       if( linkD.flag==RBFlag_BlackBlack )
         {
          if( T *P=linkD.up )
            {
             perform(root_ptr,D,P);
            }
          else
            {
             if( T *C=linkD.lo )
               {
                if( Link(C).flag==RBFlag_BlackBlack )
                  {
                   T *B=linkD.hi;
                   
                   if( Link(B).flag==RBFlag_BlackBlack )
                     {
                      linkD.flag=RBFlag_RedRed;
                      
                      del_root(root_ptr,D);
                     }
                   else
                     {
                      del_root_hi(root_ptr,D);
                     }
                  }
                else
                  {
                   del_root_lo(root_ptr,D);
                  }
               }
             else
               {
                *root_ptr=0;
               }
            }
         }
       else
         {
          del_root(FindPtr(root_ptr,D),D);
         }
      }
     
    public:
     
     PerformDelNode(T **root_ptr,T *node) { perform(root_ptr,node); }
   };
  
  // Del
  
  static T * DelMin(T **root_ptr)
   {
    PerformDelMinNode perform(root_ptr);
    
    return perform.found;
   }
  
  static T * DelMax(T **root_ptr)
   {
    PerformDelMaxNode perform(root_ptr);
    
    return perform.found;
   }
  
  static T * Del(T **root_ptr,KRef key)
   {
    if( T *ret=BaseAlgo<LinkMember,KRef>::Find(*root_ptr,key) )
      {
       PerformDelNode perform(root_ptr,ret);
       
       return ret;
      }
    
    return 0;
   }
  
  static void Del(T **root_ptr,T *node)
   {
    PerformDelNode perform(root_ptr,node);
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
    
    T * find(KRef key) const { return BaseAlgo<LinkMember,KRef>::Find(root,key); }
    
    T * findMin() const { return BaseAlgo<LinkMember,KRef>::FindMin(root); }
    
    T * findMin(KRef key) const { return BaseAlgo<LinkMember,KRef>::FindMin(root,key); }
    
    T * findMax() const { return BaseAlgo<LinkMember,KRef>::FindMax(root); }
    
    T * findMax(KRef key) const { return BaseAlgo<LinkMember,KRef>::FindMax(root,key); }
    
    // del
    
    T * delMin() { return DelMin(&root); } 
    
    T * delMax() { return DelMax(&root); } 
    
    T * del(KRef key) { return Del(&root,key); }
    
    void del(T *node) { Del(&root,node); }
    
    // replace
    
    void replace(T *place,T *obj) // place!=0 linked, obj!=0 unlinked
     {
      Node &link=Link(obj);
      Node &link_place=Link(place);

      {
       T *up=link_place.up;
       
       link.up=up;
       
       if( up )
         {
          if( Link(up).lo==place ) Link(up).lo=obj;
          if( Link(up).hi==place ) Link(up).hi=obj;
         }
       else
         {
          root=obj;
         }
      }
      
      {
       T *lo=link_place.lo;
       
       link.lo=lo;
       
       if( lo ) Link(lo).up=obj;
      }
      
      {
       T *hi=link_place.hi;
       
       link.hi=hi;
       
       if( hi ) Link(hi).up=obj;
      }
      
      link.flag=link_place.flag;
      
      Swap(link.key,link_place.key);
     }
   };
  
  // class PrepareIns

  class PrepareIns : NoCopy
   {
     KRef key;
     
     T **ptr;
     T *G;
     T *P;
     
     void (PrepareIns::*complete_func)(T *node);
    
    private:
     
     // cmp
     
     CmpResult cmp(Node &link) const { return Cmp(key,link.key); }
     
     // link
     
     void newlink(T *N,T *up)
      {
       Node &linkN=Link(N);
       
       linkN.up=up;
       linkN.lo=0;
       linkN.hi=0;
       linkN.key=key;
       linkN.flag=RBFlag_BlackBlack;
      }
     
     // set
     
     void set_found(T *C)
      {
       found=C;
      }
    
     void complete_empty(T *N)
      {
       *ptr=N;
       
       newlink(N,0);
      }
     
     void set_empty(T **root_ptr)
      {
       ptr=root_ptr;
       
       complete_func=&PrepareIns::complete_empty;
      }
     
     void complete_lo(T *N)
      {
       Node &linkP=Link(P);

       linkP.lo=N;
       linkP.flag|=RBFlag_LoRed;
       
       newlink(N,P);
      }
     
     void complete_hi(T *N)
      {
       Node &linkP=Link(P);

       linkP.hi=N;
       linkP.flag|=RBFlag_HiRed;
       
       newlink(N,P);
      }
     
     void set_lo(T *P_)
      {
       P=P_;
       
       complete_func=&PrepareIns::complete_lo;
      }
     
     void set_hi(T *P_)
      {
       P=P_;
       
       complete_func=&PrepareIns::complete_hi;
      }
     
     void complete_lo_lo(T *N)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_LoRed )
         {
          *ptr=P;
          
          Node &linkP=Link(P);
          
          linkP.lo=N;
          linkP.hi=G;
          linkP.flag=RBFlag_RedRed;
          
          linkG.lo=0;
          linkG.flag=RBFlag_BlackBlack;
          
          linkP.up=Replace(linkG.up,P);
          
          newlink(N,P);
         }
       else
         {
          complete_lo(N);
         }
      }
     
     void complete_hi_hi(T *N)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_HiRed )
         {
          *ptr=P;
          
          Node &linkP=Link(P);
          
          linkP.hi=N;
          linkP.lo=G;
          linkP.flag=RBFlag_RedRed;
          
          linkG.hi=0;
          linkG.flag=RBFlag_BlackBlack;
          
          linkP.up=Replace(linkG.up,P);
          
          newlink(N,P);
         }
       else
         {
          complete_hi(N);
         }
      }
     
     void set_lo_lo(T **ptrG,T *G_,T *P_)
      {
       ptr=ptrG;
       G=G_;
       P=P_;
       
       complete_func=&PrepareIns::complete_lo_lo;
      }
     
     void set_hi_hi(T **ptrG,T *G_,T *P_)
      {
       ptr=ptrG;
       G=G_;
       P=P_;
       
       complete_func=&PrepareIns::complete_hi_hi;
      }
     
     void complete_lo_hi(T *N)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_LoRed )
         {
          *ptr=N;
          
          Node &linkN=Link(N);
          
          linkN.up=Replace(linkG.up,N);
          linkN.lo=P;
          linkN.hi=G;
          linkN.key=key;
          linkN.flag=RBFlag_RedRed;
          
          linkG.lo=0;
          linkG.flag=RBFlag_BlackBlack;
          
          Link(P).up=N;
         }
       else
         {
          complete_hi(N);
         }
      }
     
     void complete_hi_lo(T *N)
      {
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_HiRed )
         {
          *ptr=N;
          
          Node &linkN=Link(N);
          
          linkN.up=Replace(linkG.up,N);
          linkN.hi=P;
          linkN.lo=G;
          linkN.key=key;
          linkN.flag=RBFlag_RedRed;
          
          linkG.hi=0;
          linkG.flag=RBFlag_BlackBlack;
          
          Link(P).up=N;
         }
       else
         {
          complete_lo(N);
         }
      }
     
     void set_lo_hi(T **ptrG,T *G_,T *P_)
      {
       ptr=ptrG;
       G=G_;
       P=P_;
       
       complete_func=&PrepareIns::complete_lo_hi;
      }
     
     void set_hi_lo(T **ptrG,T *G_,T *P_)
      {
       ptr=ptrG;
       G=G_;
       P=P_;
       
       complete_func=&PrepareIns::complete_hi_lo;
      }
     
     // transform
     
     static void transform_lo_lo(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);
       
       *ptrG=P;
       
       T *hi=Replace(linkP.hi,G);
       
       linkG.lo=hi; Link(hi).up=G;
       
       linkP.up=Replace(linkG.up,P);
       
       linkP.flag=RBFlag_RedRed;
       linkC.flag=RBFlag_BlackBlack;
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_hi_hi(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);
       
       *ptrG=P;
       
       T *lo=Replace(linkP.lo,G);
       
       linkG.hi=lo; Link(lo).up=G;
       
       linkP.up=Replace(linkG.up,P);
       
       linkP.flag=RBFlag_RedRed;
       linkC.flag=RBFlag_BlackBlack;
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_lo_hi(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);

       *ptrG=C;
       
       T *lo=Replace(linkC.lo,P);
       T *hi=Replace(linkC.hi,G);
       
       linkP.hi=lo; Link(lo).up=P; 
       linkG.lo=hi; Link(hi).up=G;
       
       linkC.up=Replace(linkG.up,C);
       linkP.up=C;
       
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_hi_lo(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);

       *ptrG=C;
       
       T *hi=Replace(linkC.hi,P);
       T *lo=Replace(linkC.lo,G);
       
       linkP.lo=hi; Link(hi).up=P;
       linkG.hi=lo; Link(lo).up=G;
       
       linkC.up=Replace(linkG.up,C);
       linkP.up=C;
       
       linkG.flag=RBFlag_BlackBlack;
      }
     
     // prepare

     void prepare_lo_lo(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return set_lo_lo(ptrG,G,P);
       
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_LoRed )
         {
          Node &linkC=Link(C);
          
          if( linkC.flag==RBFlag_RedRed )
            {
             transform_lo_lo(ptrG,G,P,C);
             
             return prepare_lo(ptrG,P,C);
            }
          else
            {
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_lo(&Link(P).lo,C,linkC.lo);
                case CmpGreater : return prepare_hi(&Link(P).lo,C,linkC.hi);
                
                default: return set_found(C);
               }
            }
         }
       else
         {
          return prepare_lo(&linkG.lo,P,C); 
         }
      }
     
     void prepare_hi_hi(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return set_hi_hi(ptrG,G,P);
       
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_HiRed )
         {
          Node &linkC=Link(C);
          
          if( linkC.flag==RBFlag_RedRed )
            {
             transform_hi_hi(ptrG,G,P,C);
             
             return prepare_hi(ptrG,P,C);
            }
          else
            {
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_lo(&Link(P).hi,C,linkC.lo);
                case CmpGreater : return prepare_hi(&Link(P).hi,C,linkC.hi);
                
                default: return set_found(C);
               }
            }
         }
       else
         {
          return prepare_hi(&linkG.hi,P,C); 
         }
      }
     
     void prepare_lo_hi(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return set_lo_hi(ptrG,G,P);
       
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_LoRed )
         {
          Node &linkC=Link(C);
          
          if( linkC.flag==RBFlag_RedRed )
            {
             transform_lo_hi(ptrG,G,P,C);
             
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_hi(&linkC.lo,P,Link(P).hi);
                case CmpGreater : return prepare_lo(&linkC.hi,G,Link(G).lo);
                
                default: return set_found(C);
               }
            }
          else
            {
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_lo(&Link(P).hi,C,linkC.lo);
                case CmpGreater : return prepare_hi(&Link(P).hi,C,linkC.hi);
                
                default: return set_found(C);
               }
            }
         }
       else
         {
          return prepare_hi(&linkG.lo,P,C); 
         }
      }
     
     void prepare_hi_lo(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return set_hi_lo(ptrG,G,P);
       
       Node &linkG=Link(G);
       
       if( linkG.flag&RBFlag_HiRed )
         {
          Node &linkC=Link(C);
          
          if( linkC.flag==RBFlag_RedRed )
            {
             transform_hi_lo(ptrG,G,P,C);
             
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_hi(&linkC.lo,G,Link(G).hi);
                case CmpGreater : return prepare_lo(&linkC.hi,P,Link(P).lo);
                
                default: return set_found(C);
               }
            }
          else
            {
             switch( cmp(linkC) )
               {
                case CmpLess    : return prepare_lo(&Link(P).lo,C,linkC.lo);
                case CmpGreater : return prepare_hi(&Link(P).lo,C,linkC.hi);
                
                default: return set_found(C);
               }
            }
         }
       else
         {
          return prepare_lo(&linkG.hi,P,C); 
         }
      }
     
     void prepare_lo(T **ptrP,T *P,T *C)
      {
       if( !C ) return set_lo(P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed )
         {
          linkC.flag=RBFlag_BlackBlack;
          
          Link(P).flag|=RBFlag_LoRed;
         }
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return prepare_lo_lo(ptrP,P,C,linkC.lo);
          case CmpGreater : return prepare_lo_hi(ptrP,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void prepare_hi(T **ptrP,T *P,T *C)
      {
       if( !C ) return set_hi(P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed )
         {
          linkC.flag=RBFlag_BlackBlack;
          
          Link(P).flag|=RBFlag_HiRed;
         }
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return prepare_hi_lo(ptrP,P,C,linkC.lo);
          case CmpGreater : return prepare_hi_hi(ptrP,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void prepare(T **root_ptr)
      {
       T *R=*root_ptr;
       
       if( !R ) return set_empty(root_ptr);
       
       Node &linkR=Link(R);
       
       if( linkR.flag==RBFlag_RedRed ) linkR.flag=RBFlag_BlackBlack;
       
       switch( cmp(linkR) )
         {
          case CmpLess    : return prepare_lo(root_ptr,R,linkR.lo);
          case CmpGreater : return prepare_hi(root_ptr,R,linkR.hi);
         
          default: return set_found(R); 
         }
      }
    
    public:
     
     T *found;
     
     PrepareIns(T **root_ptr,KRef key_) : key(key_),found(0) { prepare(root_ptr); }
     
     PrepareIns(Root &root,KRef key_) : key(key_),found(0) { prepare(&root.root); }
     
     void complete(T *node) { (this->*complete_func)(node); }
   };
 };

} // namespace CCore
 
#endif
 

