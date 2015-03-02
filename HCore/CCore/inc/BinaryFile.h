/* BinaryFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_BinaryFile_h
#define CCore_inc_BinaryFile_h

#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/print/PrintFile.h>
 
namespace CCore {

/* classes */

class BinaryFile;

/* class BinaryFile */

class BinaryFile : NoCopy , public PutDevBase<BinaryFile>
 {
   static const ulen BufLen = 64_KByte ;
 
   RawFileToPrint file;
   DynArray<uint8> buf;
   FileError flush_error;
   bool no_flush_exception;
   
   PtrLen<uint8> out;
   bool has_data;   
   
  private:
   
   void provide();
   
  public: 
   
   // constructors
  
   BinaryFile();
   
   explicit BinaryFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   ~BinaryFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
   
   void disableExceptions() 
    { 
     if( !no_flush_exception )
       {
        no_flush_exception=true; 
        
        flush_error=FileError_Ok;
       }
    }
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { file.preserveFile(); }
   
   // put
   
   void do_put(uint8 value)
    {
     if( !out ) provide();
    
     *out=value;
    
     ++out;
    }
   
   void do_put(const uint8 *ptr,ulen len);
   
   PtrLen<uint8> do_putRange(ulen len);
   
   void flush();
 };

} // namespace CCore
 
#endif
 

