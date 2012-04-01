/* GenFile.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

                             /*                              */ 
                             /* Generic file operations 1.00 */ 
                             /*                              */ 

/* types */ 

typedef uint64 FilePosType;

typedef uint8 byte;

/* consts */ 

const ulen MaxPathLen = 512 ;
 
enum FileOpenFlags : uint32
 {
  Open_Read       = 0x01,
  Open_Write      = 0x02,
  Open_Pos        = 0x04,
  
  Open_Create     = 0x10, // if( !file ) create();
  Open_Erase      = 0x20, // if( file ) erase();
  
  Open_New        = 0x40, // if( file ) fail(); else create();
                          // if( Open_New ) ignore(Open_Create|Open_Erase);
  
  Open_AutoDelete = 0x80, // close([false]) delete file
  
  Open_PosEnd     = 0x100 // open() set file position at the end of file
 };
 
enum FileType : uint32
 {
  FileType_none = 0,
  FileType_file = 1,
  FileType_dir  = 2
 };
 
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
 
/* file operations */ 

void open(const byte *file_name,ulen len,FileOpenFlags open_flags);

void close(bool preserve_file=false);  // if( preserve_file ) ignore(Open_AutoDelete);

ulen read(byte *buf,ulen len);         // requires Open_Read

ulen write(const byte *data,ulen len); // requires Open_Write

FilePosType getLen();                  // requires Open_Pos

FilePosType getPos();                  // requires Open_Pos

void setPos(FilePosType pos);          // requires Open_Pos
                                       // if( pos>file_len ) unknown();

/* alt file operations */ 

FilePosType /* file_len */ 
 open(const byte *file_name,ulen len,FileOpenFlags open_flags); // Open_Pos Open_PosEnd are ignored

void close(bool preserve_file=false);                           // if( preserve_file ) ignore(Open_AutoDelete);

void read(FilePosType off,byte *buf,ulen len);                  // requires Open_Read , off+len<=file_len

FilePosType /* file_len */ 
 write(FilePosType off,const byte *data,ulen len);              // requires Open_Write , if( off>file_len ) [file_len,off) is unspecified filled

/* file system operations */ 

FileType getFileType(const byte *path,ulen len); 

void createFile(const byte *file_name,ulen len);

void deleteFile(const byte *file_name,ulen len);

void createDir(const byte *dir_name,ulen len);

void deleteDir(const byte *dir_name,ulen len,bool recursive); // if( !recursive ) dir must be empty

void rename(const byte *old_path,ulen old_len,const byte *new_path,ulen new_len,bool allow_overwrite);

void remove(const byte *path,ulen len); // if path is dir it must be empty

/* dir cursor */ 

byte file_name[MaxPathLen];
ulen len;
FileType type;
FileError error;

void init(const byte *dir_name,ulen len); // set to before-the-first position

bool next();

void exit();






