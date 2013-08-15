/* Win64.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/win64/Win64.h>

namespace Win64 {

/* adapters */

bool_t ExtWriteFile(handle_t h_file,
                    const_void_ptr buf,
                    ulen_t buf_len,
                    ulen_t *ret_len)
 {
  if( buf_len<=SplitLen )
    {
     ushortlen_t ret_short_len;     
    
     bool_t ret=WriteFile(h_file,buf,(ushortlen_t)buf_len,&ret_short_len,0);
     
     if( ret_len ) *ret_len=ret_short_len;
     
     return ret;
    }
  else
    {
     ulen_t sum_len=0;
    
     while( buf_len>2*SplitLen )
       {
        ushortlen_t ret_short_len;
        
        if( WriteFile(h_file,buf,SplitLen,&ret_short_len,0) )
          {
           if( ret_short_len==SplitLen )
             {
              sum_len+=SplitLen;
              
              buf=PtrAdd(buf,SplitLen);
              
              buf_len-=SplitLen;
             }
           else
             {
              if( ret_len ) *ret_len=sum_len+ret_short_len;
              
              return true;
             }
          }
        else
          {
           if( ret_len ) *ret_len=0;
           
           return false;
          }
       }
     
     ushortlen_t ret_short_len;
     
     if( WriteFile(h_file,buf,(ushortlen_t)buf_len,&ret_short_len,0) )
       {
        if( ret_len ) *ret_len=sum_len+ret_short_len;
       
        return true;
       }
     else
       {
        if( ret_len ) *ret_len=0;
       
        return false;
       }
    }
 }

bool_t ExtReadFile(handle_t h_file,
                   void_ptr buf,
                   ulen_t buf_len,
                   ulen_t *ret_len)
 {
  if( buf_len<=SplitLen )
    {
     ushortlen_t ret_short_len;     
    
     bool_t ret=ReadFile(h_file,buf,(ushortlen_t)buf_len,&ret_short_len,0);
     
     if( ret_len ) *ret_len=ret_short_len;
     
     return ret;
    }
  else
    {
     ulen_t sum_len=0;
    
     while( buf_len>2*SplitLen )
       {
        ushortlen_t ret_short_len;
        
        if( ReadFile(h_file,buf,SplitLen,&ret_short_len,0) )
          {
           if( ret_short_len==SplitLen )
             {
              sum_len+=SplitLen;
              
              buf=PtrAdd(buf,SplitLen);
              
              buf_len-=SplitLen;
             }
           else
             {
              if( ret_len ) *ret_len=sum_len+ret_short_len;
              
              return true;
             }
          }
        else
          {
           if( ret_len ) *ret_len=0;
           
           return false;
          }
       }
     
     ushortlen_t ret_short_len;
     
     if( ReadFile(h_file,buf,(ushortlen_t)buf_len,&ret_short_len,0) )
       {
        if( ret_len ) *ret_len=sum_len+ret_short_len;
       
        return true;
       }
     else
       {
        if( ret_len ) *ret_len=0;
       
        return false;
       }
    }
 }
 
} // namespace Win64

