/* HFS.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

                             /*                               */ 
                             /* Host File System Service 1.00 */ 
                             /*                               */ 


/* 1) Data types */ 

   typedef uint64 FileLenType; // == GenFile def

   struct Path
    {
     LenType len : len<=MaxPathLen ;
     uint8 path[len];
    };
    
   struct FileId
    {
     uint32 slot;
     uint64 number;
     uint64 clock;
    }; 
 
/* 2) Constants */ 

   const unsigned MaxPathLen      =  512 ; // == GenFile def
   const unsigned DeltaReadLen    =   24 ;
   const unsigned MaxReadDataLen  = 1416 ; // MaxInfoLen-DeltaReadLen
   const unsigned DeltaWriteLen   =   40 ;
   const unsigned MaxWriteDataLen = 1400 ; // MaxInfoLen-DeltaWriteLen
   
   const ServiceIdType ServiceId = 2 ;
   
   const FunctionIdType FunctionId_Open        =  1 ;
   const FunctionIdType FunctionId_Read        =  2 ;
   const FunctionIdType FunctionId_Write       =  3 ;
   const FunctionIdType FunctionId_Close       =  4 ;
   const FunctionIdType FunctionId_GetFileType =  5 ;
   const FunctionIdType FunctionId_GetFileList =  6 ;
   const FunctionIdType FunctionId_CreateFile  =  7 ;
   const FunctionIdType FunctionId_DeleteFile  =  8 ;
   const FunctionIdType FunctionId_CreateDir   =  9 ;
   const FunctionIdType FunctionId_DeleteDir   = 10 ;
   const FunctionIdType FunctionId_Rename      = 11 ; // file or dir , rename or move
   const FunctionIdType FunctionId_Remove      = 12 ; // file or empty dir
   const FunctionIdType FunctionId_Exec        = 13 ;
   const FunctionIdType FunctionId_Exec2       = 14 ;

   const FlagType OpenFlag_Read       = 0x01 ; // == GenFile def
   const FlagType OpenFlag_Write      = 0x02 ; // == GenFile def
   const FlagType OpenFlag_Create     = 0x10 ; // == GenFile def
   const FlagType OpenFlag_Erase      = 0x20 ; // == GenFile def
   const FlagType OpenFlag_New        = 0x40 ; // == GenFile def
   const FlagType OpenFlag_AutoDelete = 0x80 ; // == GenFile def
   
   const FlagType FileType_none = 0 ; // == GenFile def
   const FlagType FileType_file = 1 ; // == GenFile def
   const FlagType FileType_dir  = 2 ; // == GenFile def
   
   const ErrorIdType ErrorBase = 100 ; // GenFile error code + ErrorBase
   
/* 3) Functions */  

   /* Open */ 
   
   struct OpenInput
    {
     FlagType open_flags;
     Path path;
    };
    
   struct OpenOutput
    {
     FileId file_id;
     FileLenType file_len;
    }; 
   
   /* Read */ 
   
   struct ReadInput
    {
     FileId file_id;
     FileLenType off;
     LenType len;
    };
   
   struct ReadOutput
    {
     FileLenType off;
     LenType len : len<=MaxReadDataLen ;
     uint8 data[len];
    };
    
   /* Write */ 
   
   struct WriteInput
    {
     FileId file_id;
     FileLenType off;
     LenType len : len<=MaxWriteDataLen ;
     uint8 data[len];
    };
    
   struct WriteOutput
    {
     FileLenType file_len;
    }; 
    
   /* Close */ 
   
   struct CloseInput
    {
     BoolType preserve_file;
     FileId file_id;
    };
    
   struct CloseOutput
    {
    }; 

   /* GetFileType */  
   
   struct GetFileTypeInput
    {
     Path path;
    };
    
   struct GetFileTypeOutput
    {
     FlagType type;
    }; 
    
   /* GetFileList */ 
    
   struct GetFileListInput
    {
     Path path;
    };
    
   struct GetFileListOutput
    {
     // temp file, OpenFlag_Read
    
     FileId file_id;
     FileLenType file_len;
    }; 
   
   /* CreateFile */ 
   
   struct CreateFileInput
    {
     Path path;
    };
    
   struct CreateFileOutput
    {
    }; 
   
   /* DeleteFile */ 

   struct DeleteFileInput
    {
     Path path;
    };
    
   struct DeleteFileOutput
    {
    }; 
    
   /* CreateDir */ 
   
   struct CreateDirInput
    {
     Path path;
    };
    
   struct CreateDirOutput
    {
    }; 
   
   /* DeleteDir */ 
   
   struct DeleteDirInput
    {
     BoolType recursive;
     Path path;
    };
    
   struct DeleteDirOutput
    {
    }; 

   /* Rename */  
   
   struct RenameInput
    {
     BoolType allow_overwrite;
     Path old_path;
     Path new_path;
    };
    
   struct RenameOutput
    {
    }; 
   
   /* Remove */ 
   
   struct RemoveInput
    {
     Path path;
    };
    
   struct RemoveOutput
    {
    }; 
   
   /* Exec */ 

   struct ExecInput
    {
     Path dir;
     Path program;
     Path arg;
    };

   struct ExecOutput
    {
    };

   /* Exec2 */ 

   struct Exec2Input
    {
     Path dir;
     Path program;
    };

   struct Exec2Output
    {
     //
     // temp file, OpenFlag_Read|OpenFlag_Write, file_len==0
     //
     // on close if( preserve ) exec program
     //
    
     FileId file_id;
    };

    
    
