/* ErrorIds.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "ErrorIds.h"

namespace App {

/* functions */ 

StrLen GetErrorDesc(ErrorIdType error_id)
 {
  if( error_id>=ErrorBase && error_id<=ErrorBase+FileError_Some )
    {
     FileError fe=FileError(error_id-ErrorBase);
     
     return GetTextDesc(fe);
    }
 
  switch( error_id )
    {
     case NoError :                 return "Ok";
     
     case Error_NoFunction :        return "No such service/function";
     
     case Error_BadInput :          return "Bad input data format";
     
     case Error_Exhausted :         return "Not enough resources";
     
     case Error_Unknown :           return "Unknown error";
     
     case Error_ConNotOpened :      return "Console is not opened";
     
     case Error_BadConId :          return "Bad console id";
     
     case Error_CannotOpenMoreCon : return "Cannot open more consoles";
     
     case Error_ReadStarted :       return "Console read is already started";
     
     case Error_WriteFault :        return "Write fault";
     
     default: return "Unknown error code";
    }
 }
 
} // namespace App



