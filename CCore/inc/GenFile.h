/* GenFile.h */ 
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

#ifndef CCore_inc_GenFile_h
#define CCore_inc_GenFile_h

#include <CCore/inc/PrintBits.h>
 
namespace CCore {

/* types */ 

typedef uint64 FilePosType;

/* consts */ 

const ulen MaxPathLen = 512 ;

/* classes */ 

//enum FileOpenFlags;

//enum FileType;

//enum FileError;

class FileMultiError;

/* enum FileOpenFlags */ 

enum FileOpenFlags : uint32
 {
  Open_Read       = 0x01,
  Open_Write      = 0x02,
  Open_Pos        = 0x04,
  
  Open_Create     = 0x10,
  Open_Erase      = 0x20,
  Open_New        = 0x40,
  Open_AutoDelete = 0x80,
  
  Open_PosEnd     = 0x100,
  
  Open_ToRead     = Open_Read,
  Open_ToWrite    = Open_Write|Open_Create|Open_Erase,
  Open_ToAppend   = Open_Write|Open_Create|Open_PosEnd
 };
 
inline FileOpenFlags operator | (FileOpenFlags a,FileOpenFlags b) 
 { 
  return FileOpenFlags( uint32(a)|uint32(b) ); 
 }
 
class FileOpenFlagsTextDesc
 {
   FileOpenFlags oflags;
   
  public:
  
   explicit FileOpenFlagsTextDesc(FileOpenFlags oflags_) : oflags(oflags_) {}
   
   template <class P>
   void print(P &out) const
    {
     PrintBits<uint32>(out,oflags)
                      (Open_Read      ,"Read")
                      (Open_Write     ,"Write")
                      (Open_Pos       ,"Pos")
                      (Open_Create    ,"Create")
                      (Open_Erase     ,"Erase")
                      (Open_New       ,"New")
                      (Open_AutoDelete,"AutoDelete")
                      (Open_PosEnd    ,"PosEnd")
                      .complete();
    }
 };
 
inline FileOpenFlagsTextDesc GetTextDesc(FileOpenFlags oflags) { return FileOpenFlagsTextDesc(oflags); }
 
/* enum FileType */ 
 
enum FileType : uint32
 {
  FileType_none = 0,
  FileType_file = 1,
  FileType_dir  = 2
 };
 
const char * GetTextDesc(FileType ft); 
 
/* enum FileError */  

enum FileError : uint32
 {
  FileError_Ok               =  0,

  FileError_NoDevice         =  1,
  FileError_NoPath           =  2,
  FileError_NoFile           =  3,
  FileError_NoAccess         =  4,
  FileError_FileExist        =  5,
  
  FileError_NoMethod         =  6,
  
  FileError_OpenFault        =  7,
  FileError_CloseFault       =  8,
  FileError_ReadFault        =  9,
  FileError_WriteFault       = 10,
  FileError_PosFault         = 11,
  
  FileError_OpFault          = 12,
  FileError_TransFault       = 13,
  FileError_Cancelled        = 14,
  
  FileError_SysOverload      = 15,
  FileError_TooLongPath      = 16,
  FileError_DiskFull         = 17,
  FileError_WriteProtect     = 18,
  FileError_DirIsNotEmpty    = 19,
  
  FileError_BadId            = 20,
  FileError_LenOverflow      = 21,
  FileError_ReadLenMismatch  = 22,
  FileError_WriteLenMismatch = 23,
  FileError_BadName          = 24,
  FileError_BadPosition      = 25,
  FileError_BadLen           = 26,
  
  FileError_Some             = 27 // last
 };
  
const char * GetTextDesc(FileError fe);

/* class FileMultiError */ 

class FileMultiError : NoCopy
 {
   static const ulen Len = 10 ;

   FileError list[Len];
   ulen len;
   ulen extra;
 
  public:
  
   FileMultiError() : len(0),extra(0) {}
   
   // methods
   
   ulen operator + () const { return len; }
   
   bool operator ! () const { return !len; }
   
   void add(FileError fe) 
    {
     if( fe )
       { 
        if( len<Len ) 
          list[len++]=fe;
        else
          extra++; 
       }
    }
   
   FileError getFirst() const { return len?list[0]:FileError_Ok; }
   
   void copyTo(FileMultiError &out) const
    {
     out.len=len;
     out.extra=extra;
     
     Range(out.list,len).copy(list);
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     auto r=Range(list,len);
    
     if( +r )
       {
        Putobj(out,*r);
        
        for(++r; +r ;++r) Printf(out,", #;",*r);
        
        if( extra ) Printf(out,", #; extra errors",extra);
       }
     else
       {
        Putobj(out,"Success");
       }  
    }
 };
 
} // namespace CCore
 
#endif
 

