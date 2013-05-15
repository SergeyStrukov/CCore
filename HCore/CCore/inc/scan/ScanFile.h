/* ScanFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_scan_ScanFile_h
#define CCore_inc_scan_ScanFile_h

#include <CCore/inc/Scanf.h>
#include <CCore/inc/SafeBuf.h>

#include <CCore/inc/sys/SysFile.h>
 
namespace CCore {

/* classes */

class RawFileToScan;

class ScanFile;

/* class RawFileToScan */

class RawFileToScan : NoCopy
 {
   Sys::File file;
   bool opened = false ;
   
  public:
  
   // constructors
  
   RawFileToScan() {}
   
    // No destructor ! 
  
   // methods
  
   bool isOpened() const { return opened; }
  
   FileError open(StrLen file_name);
  
   void close(FileMultiError &errout);
  
   Sys::File::IOResult read(uint8 *buf,ulen len);
 };

/* class ScanFile */

class ScanFile : public ScanBase
 {
   static const ulen BufLen = 64_KByte ;
  
   RawFileToScan file;
   SafeBuf buf;
   FileError underflow_error;
   bool no_underflow_exception = false ;
  
  private:
 
   virtual PtrLen<const char> underflow();
 
  public: 
 
   // constructors
  
   ScanFile();
  
   explicit ScanFile(StrLen file_name);
  
   ~ScanFile();
   
   // methods
   
   bool isOpened() const { return file.isOpened(); }
   
   void open(StrLen file_name);
   
   void disableExceptions(); 
   
   void soft_close(FileMultiError &errout);
   
   void close();
 };

} // namespace CCore
 
#endif
 

