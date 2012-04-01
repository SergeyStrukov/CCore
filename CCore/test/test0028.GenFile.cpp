/* test0028.GenFile.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/GenFile.h>

namespace App {

/* Testit<28> */ 

template<>
const char *const Testit<28>::Name="Test28 GenFile";

template<>
bool Testit<28>::Main() 
 { 
  Printf(Con,"to read = #;\n",Open_ToRead);
  Printf(Con,"to write = #;\n",Open_ToWrite);
  Printf(Con,"to read = #;\n",Open_ToAppend);
  Printf(Con,"to map = #;\n",Open_Read|Open_Pos);
  
  Printf(Con,"\n\n#;\n\n",FileError_Ok);
  
  Printf(Con,"#;\n",FileError_NoDevice);
  Printf(Con,"#;\n",FileError_NoPath);
  Printf(Con,"#;\n",FileError_NoFile);
  Printf(Con,"#;\n",FileError_NoAccess);
  Printf(Con,"#;\n\n",FileError_FileExist);
  
  Printf(Con,"#;\n\n",FileError_NoMethod);
  
  Printf(Con,"#;\n",FileError_OpenFault);
  Printf(Con,"#;\n",FileError_CloseFault);
  Printf(Con,"#;\n",FileError_ReadFault);
  Printf(Con,"#;\n",FileError_WriteFault);
  Printf(Con,"#;\n\n",FileError_PosFault);
  
  Printf(Con,"#;\n",FileError_OpFault);
  Printf(Con,"#;\n",FileError_TransFault);
  Printf(Con,"#;\n\n",FileError_Cancelled);
  
  Printf(Con,"#;\n",FileError_SysOverload);
  Printf(Con,"#;\n",FileError_TooLongPath);
  Printf(Con,"#;\n",FileError_DiskFull);
  Printf(Con,"#;\n",FileError_WriteProtect);
  Printf(Con,"#;\n\n",FileError_DirIsNotEmpty);
  
  Printf(Con,"#;\n",FileError_BadId);
  Printf(Con,"#;\n",FileError_LenOverflow);
  Printf(Con,"#;\n",FileError_ReadLenMismatch);
  Printf(Con,"#;\n",FileError_WriteLenMismatch);
  Printf(Con,"#;\n",FileError_BadName);
  Printf(Con,"#;\n",FileError_BadPosition);
  Printf(Con,"#;\n\n",FileError_BadLen);
  
  Printf(Con,"#;\n",FileError_Some);
  Printf(Con,"#;\n",FileError(FileError_Some+100));
 
  return true;
 }
 
} // namespace App
 
