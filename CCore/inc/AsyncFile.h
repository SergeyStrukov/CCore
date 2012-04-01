/* AsyncFile.h */ 
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

#ifndef CCore_inc_AsyncFile_h
#define CCore_inc_AsyncFile_h
 
#include <CCore/inc/PacketSet.h>

#include <CCore/inc/sys/SysAsyncFileSystem.h>

namespace CCore {

/* classes */ 

class AsyncFile;

class AsyncFileSystem;

/* class AsyncFile */ 

class AsyncFile : public Funchor_nocopy
 {
   static const ulen MinLargeLen = 5*DefaultPacketMaxDataLen ;
   static const ulen MaxLargeLen = 64_KByte ;
  
   Sys::AsyncFile file;
 
   bool is_opened;
   bool preserve_file;
   
   PacketFormat write_format;
   ulen large_write_len;
   ulen max_read_len;
   FilePosType file_len; // initial file length
   
   PacketSet<uint8> pset;
   MSec timeout;
   MSec final_timeout;
   
   Mutex mutex;
   
   FileError error;
   
  private: 
   
   void setLarge();
   
   void setError(FileError fe);
   
   FileError getError();
  
   void guard();
   
   void complete_open(PacketHeader *packet);
   
   PacketFunction function_complete_open() { return FunctionOf(this,&AsyncFile::complete_open); }
   
   void complete_close(PacketHeader *packet);
   
   PacketFunction function_complete_close() { return FunctionOf(this,&AsyncFile::complete_close); }
   
   void complete_write(PacketHeader *packet);
   
   PacketFunction function_complete_write() { return FunctionOf(this,&AsyncFile::complete_write); }
   
   void complete_read(PacketHeader *packet);
   
   PacketFunction function_complete_read() { return FunctionOf(this,&AsyncFile::complete_read); }
   
  private: 
  
   void open(Sys::AsyncFileState *file_state,FileOpenFlags oflags,FilePosType file_len);
   
   friend class AsyncFileSystem;
   
  public: 
   
   // constructors
  
   AsyncFile(MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   explicit AsyncFile(StrLen file_name,FileOpenFlags oflags,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   ~AsyncFile();
   
   bool isOpened() const { return is_opened; }
   
   void setFinalTimeout(MSec t) { final_timeout=t; }
   
   // open/close
   
   FilePosType open(StrLen file_name,FileOpenFlags oflags); // return file_len
   
   void soft_close(FileMultiError &errout);
   
   void close();
   
   void preserveFile() { preserve_file=true; }
   
   void setLargeWriteLen(ulen large_write_len);
   
   void wait() { pset.wait(timeout); }
   
   void wait_final() { pset.wait(final_timeout); }
   
   void wait(MSec timeout) { pset.wait(timeout); }
   
   void cancel_and_wait() { pset.cancel_and_wait(); }
   
   // write
   
   struct WritePacket
    {
     Packet<uint8> packet;
     PtrLen<uint8> buf;
     
     WritePacket(Packet<uint8> packet_,PtrLen<uint8> buf_) : packet(packet_),buf(buf_) {}
    };
   
   WritePacket getWritePacket(); // non-null, not empty
   
   void write(FilePosType off,ulen len,Packet<uint8> packet) noexcept(EnableNoExcept);
   
   // read
   
   void read_all(FilePosType off,uint8 *buf,ulen len);
   
   ulen getMaxReadLen() const { return max_read_len; }
   
   void read(FilePosType off,ulen len,PacketFunction complete_function); 
   
    //
    // len<=getMaxReadLen()
    //
    // void complete_function(PacketHeader *packet_)
    //  {
    //   Packet<uint8,Sys::AsyncFile::ReadBufExt> packet=packet_;
    //   
    //   Sys::AsyncFile::ReadBufExt *ext=packet.getExt();
    //   
    //   ...   
    //   
    //   packet.popExt().complete();
    //  }
    //
 };
 
/* class AsyncFileSystem */ 

class AsyncFileSystem : public Funchor_nocopy
 {
   Sys::AsyncFileSystem fs;
 
   PacketSet<uint8> pset;
   MSec timeout;
   
   FileError error;
   FileType file_type;
   AsyncFile *file;
   FileOpenFlags oflags;
   
  private: 
   
   // guard
   
   void guard(const char *name,StrLen path);
   
   void guard(const char *name,StrLen path1,StrLen path2);
   
   void guard(const char *name,StrLen path1,StrLen path2,StrLen path3);
   
   // getPacket
   
   void complete_error(PacketHeader *packet);
  
   PacketFunction function_complete_error() { return FunctionOf(this,&AsyncFileSystem::complete_error); }
   
   Packet<uint8,Sys::AsyncFileSystem::ErrorExt> getPacket(const char *name,TimeScope time_scope);
   
   // getPacket_type
  
   void complete_type(PacketHeader *packet);
  
   PacketFunction function_complete_type() { return FunctionOf(this,&AsyncFileSystem::complete_type); }
   
   Packet<uint8,Sys::AsyncFileSystem::FileTypeExt> getPacket_type(const char *name,TimeScope time_scope);
   
   // getPacket_file
   
   void setFile(const char *name,AsyncFile &file,FileOpenFlags oflags);
  
   void complete_file(PacketHeader *packet);
  
   PacketFunction function_complete_file() { return FunctionOf(this,&AsyncFileSystem::complete_file); }
   
   Packet<uint8,Sys::AsyncFileSystem::FileExt> getPacket_file(const char *name,TimeScope time_scope);
   
  public:
   
   // constructors
  
   explicit AsyncFileSystem(StrLen dev_name,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   ~AsyncFileSystem();
   
   // operations
   
   FileType getFileType(StrLen path);
  
   FilePosType getFileList(StrLen dir_name,AsyncFile &file); // return file length
  
   void createFile(StrLen file_name);
  
   void deleteFile(StrLen file_name);
  
   void createDir(StrLen dir_name);
  
   void deleteDir(StrLen dir_name,bool recursive);
  
   void rename(StrLen old_path,StrLen new_path,bool allow_overwrite);
  
   void remove(StrLen path);
  
   void exec(StrLen dir,StrLen program,StrLen arg);
  
   void exec2(StrLen dir,StrLen program,AsyncFile &file);
   
   // static
   
   static FileType GetFileType(StrLen path,MSec timeout=DefaultTimeout);
  
   static void CreateFile(StrLen file_name,MSec timeout=DefaultTimeout);
  
   static void DeleteFile(StrLen file_name,MSec timeout=DefaultTimeout);
  
   static void CreateDir(StrLen dir_name,MSec timeout=DefaultTimeout);
  
   static void DeleteDir(StrLen dir_name,bool recursive,MSec timeout=DefaultTimeout);
  
   static void Rename(StrLen old_path,StrLen new_path,bool allow_overwrite,MSec timeout=DefaultTimeout);
  
   static void Remove(StrLen path,MSec timeout=DefaultTimeout);
  
   static void Exec(StrLen dir,StrLen program,StrLen arg,MSec timeout=DefaultTimeout);
 };
 
} // namespace CCore
 
#endif
 

