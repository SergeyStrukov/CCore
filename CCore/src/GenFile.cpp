/* GenFile.cpp */ 
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
 
#include <CCore/inc/GenFile.h>
 
namespace CCore {

/* enum FileType */ 
 
const char * GetTextDesc(FileType ft)
 {
  switch( ft )
    {
     case FileType_none : return "none";
     case FileType_file : return "file";
     case FileType_dir  : return "dir";
     
     default: return "unknown";
    }
 }
 
/* enum FileError */  

const char * GetTextDesc(FileError fe)
 {
  static const char *const Table[]=
   {
    "Success",               // FileError_Ok
    
    "No device",             // FileError_NoDevice
    "No path",               // FileError_NoPath
    "No file",               // FileError_NoFile
    "No access",             // FileError_NoAccess
    "File exist",            // FileError_FileExist
    
    "No method",             // FileError_NoMethod
    
    "Open fault",            // FileError_OpenFault
    "Close fault",           // FileError_CloseFault
    "Read fault",            // FileError_ReadFault
    "Write fault",           // FileError_WriteFault
    "Pos fault",             // FileError_PosFault
    
    "Operation fault",       // FileError_OpFault
    "Transaction fault",     // FileError_TransFault
    "Operation cancelled",   // FileError_Cancelled
    
    "System overload",       // FileError_SysOverload
    "Too long path",         // FileError_TooLongPath
    "Disk full",             // FileError_DiskFull
    "Write protect",         // FileError_WriteProtect
    "Dir is not empty",      // FileError_DirIsNotEmpty
    
    "Bad file id",           // FileError_BadId
    "Length overflow",       // FileError_LenOverflow
    "Read length mismatch",  // FileError_ReadLenMismatch
    "Write length mismatch", // FileError_WriteLenMismatch
    "Bad name",              // FileError_BadName
    "Bad file position",     // FileError_BadPosition
    "Bad length",            // FileError_BadLen
    
    "Some error"             // FileError_Some
   };
   
  if( (uint32)fe>FileError_Some ) fe=FileError_Some;
 
  return Table[fe];
 };
 
} // namespace CCore
 

