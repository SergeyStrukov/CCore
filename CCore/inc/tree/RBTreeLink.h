/* RBTreeLink.h */ 
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

#ifndef CCore_inc_tree_RBTreeLink_h
#define CCore_inc_tree_RBTreeLink_h

#include <CCore/inc/tree/RBTreeBase.h>
 
namespace CCore {

/* classes */ 

template <class T,class K> struct RBTreeLink;

/* struct RBTreeLink<T,K> */ 

template <class T,class K> 
struct RBTreeLink
 {
  T *lo;
  T *hi;
  K key; // unique
  RBFlag flag;
  
  typedef RBTreeLink<T,K> Node;
  
  template <RBTreeLink<T,K> T::* LinkMember,class KRef=K> struct BaseAlgo;
  
  template <RBTreeLink<T,K> T::* LinkMember,class KRef=K> struct Algo;
  
  template <RBTreeLink<T,K> T::* LinkMember,class KRef=K> struct AltAlgo;
 };
 
template <class T,class K> 
template <RBTreeLink<T,K> T::* LinkMember,class KRef> 
struct RBTreeLink<T,K>::BaseAlgo
 {
   // node!=0
  
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
    
    explicit Check(T *root)
     : minval(),
       maxval(),
       height(-1),
       black_black(false)
     {
      if( root ) run(root);
     }
    
    struct Prop
     {
      int height;
      bool black_black;
     };
    
    Prop check_lo(Node &link)
     {
      Prop ret;
      
      if( T *lo=link.lo )
        {
         Check check(lo);
         
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
    
    Prop check_hi(Node &link)
     {
      Prop ret;
      
      if( T *hi=link.hi )
        {
         Check check(hi);
         
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
    
    void run(T *root) // root!=0
     {
      Node &link=Link(root);

      Prop prop_lo=check_lo(link);
      Prop prop_hi=check_hi(link);
      
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
template <RBTreeLink<T,K> T::* LinkMember,class KRef> 
struct RBTreeLink<T,K>::Algo : BaseAlgo<LinkMember,KRef>
 {
   // node!=0
   // root_ptr!=0

  using BaseAlgo<LinkMember,KRef>::Link;
  
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
          
          linkP.hi=Replace(linkB.lo,P);
          
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
        
          linkP.hi=Replace(linkS.lo,P);
          linkB.lo=Replace(linkS.hi,B);
        
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
       
       linkG.hi=Replace(linkU.lo,G);

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
          
          linkP.lo=Replace(linkB.hi,P);
          
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
        
          linkP.lo=Replace(linkS.hi,P);
          linkB.hi=Replace(linkS.lo,B);
        
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
       
       linkG.lo=Replace(linkU.hi,G);

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
       
       linkS.lo=linkP.lo;
       linkS.hi=linkP.hi;
       linkS.flag=linkP.flag;
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
          
          linkP.hi=Replace(linkB.lo,P);
          
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
        
          linkP.hi=Replace(linkS.lo,P);
          linkB.lo=Replace(linkS.hi,B);
        
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
          
          linkP.lo=Replace(linkB.hi,P);
          
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
        
          linkP.lo=Replace(linkS.hi,P);
          linkB.hi=Replace(linkS.lo,B);
        
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
       
       linkG.lo=Replace(linkU.hi,G);

       linkU.flag=RBFlag_HiRed;
       linkG.flag=RBFlag_BlackBlack;
       
       return perform_hi_hi(U,G);
      }
     
     void perform_hi(T **ptrG,T *G,T *U)
      {
       Node &linkG=Link(G);
       Node &linkU=Link(U);
       
       *ptrG=U;
       
       linkG.hi=Replace(linkU.lo,G);

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
  
  // Del
  
  static T * DelMin(T **root_ptr)
   {
    PerformDelMin perform(root_ptr);
    
    return perform.found;
   }
  
  static T * DelMax(T **root_ptr)
   {
    PerformDelMax perform(root_ptr);
    
    return perform.found;
   }
  
  static T * Del(T **root_ptr,KRef key)
   {
    PerformDel perform(root_ptr,key);
    
    return perform.found;
   }
  
  static void Del(T **root_ptr,T *node)
   {
    Del(root_ptr,Link(node).key);
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
     
     void newlink(T *N)
      {
       Node &linkN=Link(N);
       
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
       
       newlink(N);
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
       
       newlink(N);
      }
     
     void complete_hi(T *N)
      {
       Node &linkP=Link(P);

       linkP.hi=N;
       linkP.flag|=RBFlag_HiRed;
       
       newlink(N);
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
          
          newlink(N);
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
          
          newlink(N);
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
          
          linkN.lo=P;
          linkN.hi=G;
          linkN.key=key;
          linkN.flag=RBFlag_RedRed;
          
          linkG.lo=0;
          linkG.flag=RBFlag_BlackBlack;
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
          
          linkN.hi=P;
          linkN.lo=G;
          linkN.key=key;
          linkN.flag=RBFlag_RedRed;
          
          linkG.hi=0;
          linkG.flag=RBFlag_BlackBlack;
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
       
       linkG.lo=Replace(linkP.hi,G);
       
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
       
       linkG.hi=Replace(linkP.lo,G);
       
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
       
       linkP.hi=Replace(linkC.lo,P);
       linkG.lo=Replace(linkC.hi,G);
       
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_hi_lo(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);

       *ptrG=C;
       
       linkP.lo=Replace(linkC.hi,P);
       linkG.hi=Replace(linkC.lo,G);
       
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

template <class T,class K> 
template <RBTreeLink<T,K> T::* LinkMember,class KRef> 
struct RBTreeLink<T,K>::AltAlgo : Algo<LinkMember,KRef>
 {
   // node!=0
   // root_ptr!=0

  using Algo<LinkMember,KRef>::Link;
   
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
    
    T * find(KRef key) const { return Algo<LinkMember,KRef>::Find(root,key); }
    
    T * findMin() const { return Algo<LinkMember,KRef>::FindMin(root); }
    
    T * findMin(KRef key) const { return Algo<LinkMember,KRef>::FindMin(root,key); }
    
    T * findMax() const { return Algo<LinkMember,KRef>::FindMax(root); }
    
    T * findMax(KRef key) const { return Algo<LinkMember,KRef>::FindMax(root,key); }
    
    // del
    
    T * delMin() { return Algo<LinkMember,KRef>::DelMin(&root); } 
    
    T * delMax() { return Algo<LinkMember,KRef>::DelMax(&root); } 
    
    T * del(KRef key) { return Algo<LinkMember,KRef>::Del(&root,key); }
    
    void del(T *node) { Algo<LinkMember,KRef>::Del(&root,node); }
   };
   
  // class PrepareIns
  
  class PrepareIns : NoCopy
   {
     static const ulen BufLen = 100 ;
     
     struct Rec
      {
       T *P;
       T *C;
       RBFlag flag;
       
       Rec() {}
       
       void set(T *P_,T *C_,RBFlag flag_) { P=P_; C=C_; flag=flag_; }
       
       void transform()
        {
         Link(C).flag=RBFlag_BlackBlack;
         Link(P).flag=flag;
        }
       
       T ** getPtr()
        {
         if( flag==RBFlag_LoRed )
           return &Link(P).lo;
         else
           return &Link(P).hi;
        }
      };
     
     Rec buf[BufLen];
     
    private: 
    
     KRef key;
     
     T **ptr;
     T *P;
     T *C;
     
     void (PrepareIns::*complete_func)(T *node);
    
    private:
     
     // cmp
     
     CmpResult cmp(const Node &link) const { return Cmp(key,link.key); }
     
     // link
     
     void newlink(T *N)
      {
       Node &linkN=Link(N);
       
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
       
       newlink(N);
      }
     
     void set_empty(T **root_ptr)
      {
       ptr=root_ptr;
       
       complete_func=&PrepareIns::complete_empty;
      }
     
     void complete_lo(T *N)
      {
       Node &linkC=Link(C);

       linkC.lo=N;
       linkC.flag|=RBFlag_LoRed;
       
       newlink(N);
      }
     
     void complete_hi(T *N)
      {
       Node &linkC=Link(C);

       linkC.hi=N;
       linkC.flag|=RBFlag_HiRed;
       
       newlink(N);
      }
     
     void set_lo(T *C_)
      {
       C=C_;
       
       complete_func=&PrepareIns::complete_lo;
      }
     
     void set_hi(T *C_)
      {
       C=C_;
       
       complete_func=&PrepareIns::complete_hi;
      }
     
     void complete_lo_lo(T *N)
      {
       Node &linkC=Link(C);
       Node &linkP=Link(P);
          
       *ptr=C;
       
       linkC.lo=N;
       linkC.hi=P;
       linkC.flag=RBFlag_RedRed;
       
       linkP.lo=0;
       linkP.flag=RBFlag_BlackBlack;
       
       newlink(N);
      }
     
     void complete_hi_hi(T *N)
      {
       Node &linkC=Link(C);
       Node &linkP=Link(P);
          
       *ptr=C;
       
       linkC.hi=N;
       linkC.lo=P;
       linkC.flag=RBFlag_RedRed;
       
       linkP.hi=0;
       linkP.flag=RBFlag_BlackBlack;
       
       newlink(N);
      }
     
     void set_lo_lo(T **ptrP,T *P_,T *C_)
      {
       ptr=ptrP;
       P=P_;
       C=C_;
       
       complete_func=&PrepareIns::complete_lo_lo;
      }
     
     void set_hi_hi(T **ptrP,T *P_,T *C_)
      {
       ptr=ptrP;
       P=P_;
       C=C_;
       
       complete_func=&PrepareIns::complete_hi_hi;
      }
     
     void complete_lo_hi(T *N)
      {
       Node &linkN=Link(N);
       Node &linkP=Link(P);
          
       *ptr=N;
       
       linkN.lo=C;
       linkN.hi=P;
       linkN.key=key;
       linkN.flag=RBFlag_RedRed;
       
       linkP.lo=0;
       linkP.flag=RBFlag_BlackBlack;
      }
     
     void complete_hi_lo(T *N)
      {
       Node &linkN=Link(N);
       Node &linkP=Link(P);
          
       *ptr=N;
       
       linkN.hi=C;
       linkN.lo=P;
       linkN.key=key;
       linkN.flag=RBFlag_RedRed;
       
       linkP.hi=0;
       linkP.flag=RBFlag_BlackBlack;
      }
     
     void set_lo_hi(T **ptrP,T *P_,T *C_)
      {
       ptr=ptrP;
       P=P_;
       C=C_;
       
       complete_func=&PrepareIns::complete_lo_hi;
      }
     
     void set_hi_lo(T **ptrP,T *P_,T *C_)
      {
       ptr=ptrP;
       P=P_;
       C=C_;
       
       complete_func=&PrepareIns::complete_hi_lo;
      }
     
     // transform
     
     static void transform_lo_lo(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);
       
       *ptrG=P;
       
       linkG.lo=Replace(linkP.hi,G);
       
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
       
       linkG.hi=Replace(linkP.lo,G);
       
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
       
       linkP.hi=Replace(linkC.lo,P);
       linkG.lo=Replace(linkC.hi,G);
       
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_hi_lo(T **ptrG,T *G,T *P,T *C)
      {
       Node &linkG=Link(G);
       Node &linkP=Link(P);
       Node &linkC=Link(C);

       *ptrG=C;
       
       linkP.lo=Replace(linkC.hi,P);
       linkG.hi=Replace(linkC.lo,G);
       
       linkG.flag=RBFlag_BlackBlack;
      }
     
     static void transform_lo_lo(T **ptrG,T *G,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       if( Link(G).flag&RBFlag_LoRed )
         {
          transform_lo_lo(ptrG,G,P,C);
         }
       else
         {
          Link(C).flag=RBFlag_BlackBlack;
          Link(P).flag^=RBFlag_LoRed;
         }
      }
     
     static void transform_hi_hi(T **ptrG,T *G,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       if( Link(G).flag&RBFlag_HiRed )
         {
          transform_hi_hi(ptrG,G,P,C);
         }
       else
         {
          Link(C).flag=RBFlag_BlackBlack;
          Link(P).flag^=RBFlag_HiRed;
         }
      }
     
     static void transform_lo_hi(T **ptrG,T *G,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       if( Link(G).flag&RBFlag_LoRed )
         {
          transform_lo_hi(ptrG,G,P,C);
         }
       else
         {
          Link(C).flag=RBFlag_BlackBlack;
          Link(P).flag^=RBFlag_HiRed;
         }
      }
     
     static void transform_hi_lo(T **ptrG,T *G,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       if( Link(G).flag&RBFlag_HiRed )
         {
          transform_hi_lo(ptrG,G,P,C);
         }
       else
         {
          Link(C).flag=RBFlag_BlackBlack;
          Link(P).flag^=RBFlag_LoRed;
         }
      }
     
     static void transform_lo(T **,T *,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       Link(C).flag=RBFlag_BlackBlack;
       Link(P).flag^=RBFlag_LoRed;
      }
     
     static void transform_hi(T **,T *,T *P,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       Link(C).flag=RBFlag_BlackBlack;
       Link(P).flag^=RBFlag_HiRed;
      }
     
     static void transform_root(T **,T *,T *,T *C,Rec *buf,ulen count)
      {
       for(auto r=Range(buf,count); +r ;++r) r->transform();
       
       Link(C).flag=RBFlag_BlackBlack;
      }
     
     typedef void (*transform_ptr)(T **ptrG,T *G,T *P,T *C,Rec *buf,ulen count);
     
     // prepare
     
     void prepare_lo_lo(T **ptrP,T *P,T *C)
      {
       if( Link(P).flag&RBFlag_LoRed )
         {
          return set_lo_lo(ptrP,P,C);
         }
       else
         {
          return set_lo(C);
         }
      }
     
     void prepare_hi_hi(T **ptrP,T *P,T *C)
      {
       if( Link(P).flag&RBFlag_HiRed )
         {
          return set_hi_hi(ptrP,P,C);
         }
       else
         {
          return set_hi(C);
         }
      }
     
     void prepare_lo_hi(T **ptrP,T *P,T *C)
      {
       if( Link(P).flag&RBFlag_LoRed )
         {
          return set_lo_hi(ptrP,P,C);
         }
       else
         {
          return set_hi(C);
         }
      }
     
     void prepare_hi_lo(T **ptrP,T *P,T *C)
      {
       if( Link(P).flag&RBFlag_HiRed )
         {
          return set_hi_lo(ptrP,P,C);
         }
       else
         {
          return set_lo(C);
         }
      }
     
     void path(T **ptrG,T *G,T *P,T *C,transform_ptr transform)
      {
       for(;;)
         {
          ulen count=0;
          T *L=C;
          
          for(;;)
            {
             Node &linkL=Link(L);
             
             switch( cmp(linkL) )
               {
                case CmpLess : 
                 {
                  T *D=linkL.lo;
                  Node &linkD=Link(D);
                  
                  switch( cmp(linkD) )
                    {
                     case CmpLess : 
                      {
                       T *E=linkD.lo;
                       
                       if( !E ) 
                         {
                          transform(ptrG,G,P,C,buf,count);
                          
                          return set_lo(D);
                         }
                       
                       Node &linkE=Link(E);
                       
                       if( linkE.flag==RBFlag_RedRed )
                         {
                          if( count<BufLen )
                            {
                             buf[count++].set(D,E,RBFlag_LoRed);
                             
                             L=E;
                            }
                          else
                            {
                             transform(ptrG,G,P,C,buf,count);
                             
                             T **ptrL=buf[BufLen-1].getPtr();
                             
                             return path(ptrL,L,D,E,transform_lo_lo);
                            }
                         }
                       else
                         {
                          switch( cmp(linkE) )
                            {
                             case CmpLess    : return loop_lo_lo(&linkL.lo,D,E,linkE.lo); 
                             case CmpGreater : return loop_lo_hi(&linkL.lo,D,E,linkE.hi); 
                             
                             default: return set_found(E);
                            }
                         }
                      }
                     break;
                     
                     case CmpGreater : 
                      {
                       T *E=linkD.hi;
                       
                       if( !E )
                         {
                          transform(ptrG,G,P,C,buf,count);
                          
                          return set_hi(D);
                         }
                       
                       Node &linkE=Link(E);
                       
                       if( linkE.flag==RBFlag_RedRed )
                         {
                          if( count<BufLen )
                            {
                             buf[count++].set(D,E,RBFlag_HiRed);
                             
                             L=E;
                            }
                          else
                            {
                             transform(ptrG,G,P,C,buf,count);
                             
                             T **ptrL=buf[BufLen-1].getPtr();
                             
                             return path(ptrL,L,D,E,transform_lo_hi);
                            }
                         }
                       else
                         {
                          switch( cmp(linkE) )
                            {
                             case CmpLess    : return loop_hi_lo(&linkL.lo,D,E,linkE.lo); 
                             case CmpGreater : return loop_hi_hi(&linkL.lo,D,E,linkE.hi); 
                             
                             default: return set_found(E);
                            }
                         }
                      }
                     break;
                     
                     default: return set_found(D);
                    }
                 }
                break;
                
                case CmpGreater : 
                 {
                  T *D=linkL.hi;
                  
                  Node &linkD=Link(D);
                  
                  switch( cmp(linkD) )
                    {
                     case CmpLess : 
                      {
                       T *E=linkD.lo;
                       
                       if( !E ) 
                         {
                          transform(ptrG,G,P,C,buf,count);
                          
                          return set_lo(D);
                         }
                       
                       Node &linkE=Link(E);
                       
                       if( linkE.flag==RBFlag_RedRed )
                         {
                          if( count<BufLen )
                            {
                             buf[count++].set(D,E,RBFlag_LoRed);
                             
                             L=E;
                            }
                          else
                            {
                             transform(ptrG,G,P,C,buf,count);
                             
                             T **ptrL=buf[BufLen-1].getPtr();
                             
                             return path(ptrL,L,D,E,transform_hi_lo);
                            }
                         }
                       else
                         {
                          switch( cmp(linkE) )
                            {
                             case CmpLess    : return loop_lo_lo(&linkL.hi,D,E,linkE.lo); 
                             case CmpGreater : return loop_lo_hi(&linkL.hi,D,E,linkE.hi); 
                             
                             default: return set_found(E);
                            }
                         }
                      }
                     break;
                     
                     case CmpGreater : 
                      {
                       T *E=linkD.hi;
                       
                       if( !E )
                         {
                          transform(ptrG,G,P,C,buf,count);
                          
                          return set_hi(D);
                         }
                       
                       Node &linkE=Link(E);
                       
                       if( linkE.flag==RBFlag_RedRed )
                         {
                          if( count<BufLen )
                            {
                             buf[count++].set(D,E,RBFlag_HiRed);
                             
                             L=E;
                            }
                          else
                            {
                             transform(ptrG,G,P,C,buf,count);
                             
                             T **ptrL=buf[BufLen-1].getPtr();
                             
                             return path(ptrL,L,D,E,transform_hi_hi);
                            }
                         }
                       else
                         {
                          switch( cmp(linkE) )
                            {
                             case CmpLess    : return loop_hi_lo(&linkL.hi,D,E,linkE.lo); 
                             case CmpGreater : return loop_hi_hi(&linkL.hi,D,E,linkE.hi); 
                             
                             default: return set_found(E);
                            }
                         }
                      }
                     break;
                     
                     default: return set_found(D);
                    }
                 }
                break;
                
                default: return set_found(L);
               }
            }
         }
      }
     
     void loop_lo_lo(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return prepare_lo_lo(ptrG,G,P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed ) return path(ptrG,G,P,C,transform_lo_lo);
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return loop_lo_lo(&Link(G).lo,P,C,linkC.lo);
          case CmpGreater : return loop_lo_hi(&Link(G).lo,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void loop_hi_hi(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return prepare_hi_hi(ptrG,G,P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed ) return path(ptrG,G,P,C,transform_hi_hi);
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return loop_hi_lo(&Link(G).hi,P,C,linkC.lo);
          case CmpGreater : return loop_hi_hi(&Link(G).hi,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void loop_lo_hi(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return prepare_lo_hi(ptrG,G,P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed ) return path(ptrG,G,P,C,transform_lo_hi);
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return loop_hi_lo(&Link(G).lo,P,C,linkC.lo);
          case CmpGreater : return loop_hi_hi(&Link(G).lo,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void loop_hi_lo(T **ptrG,T *G,T *P,T *C)
      {
       if( !C ) return prepare_hi_lo(ptrG,G,P);
       
       Node &linkC=Link(C);
       
       if( linkC.flag==RBFlag_RedRed ) return path(ptrG,G,P,C,transform_hi_lo);
       
       switch( cmp(linkC) )
         {
          case CmpLess    : return loop_lo_lo(&Link(G).hi,P,C,linkC.lo);
          case CmpGreater : return loop_lo_hi(&Link(G).hi,P,C,linkC.hi);
          
          default: return set_found(C);
         }
      }
     
     void prepare(T **root_ptr)
      {
       T *G=*root_ptr;
       
       if( !G ) return set_empty(root_ptr);
       
       Node &linkG=Link(G);
       
       if( linkG.flag==RBFlag_RedRed ) return path(0,0,0,G,transform_root);
       
       switch( cmp(linkG) )
         {
          case CmpLess :
           {
            T *P=linkG.lo;
            
            if( !P ) return set_lo(G);
            
            Node &linkP=Link(P);
               
            if( linkP.flag==RBFlag_RedRed ) return path(0,0,G,P,transform_lo);
            
            switch( cmp(linkP) )
              {
               case CmpLess    : return loop_lo_lo(root_ptr,G,P,linkP.lo);
               case CmpGreater : return loop_lo_hi(root_ptr,G,P,linkP.hi);
               
               default: return set_found(P);
              }
           }
          break;
          
          case CmpGreater : 
           {
            T *P=linkG.hi;
            
            if( !P ) return set_hi(G);
            
            Node &linkP=Link(P);
               
            if( linkP.flag==RBFlag_RedRed ) return path(0,0,G,P,transform_hi);
            
            switch( cmp(linkP) )
              {
               case CmpLess    : return loop_hi_lo(root_ptr,G,P,linkP.lo);
               case CmpGreater : return loop_hi_hi(root_ptr,G,P,linkP.hi);
               
               default: return set_found(P);
              }
           }
          break;
          
          default: return set_found(G);
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
 

