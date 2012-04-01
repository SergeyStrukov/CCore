/* test1014.FileSystem.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_1014 {

/* ShowDir() */

void ShowDir(FileSystem &fs,StrLen dir_name)
 {
  FileSystem::DirCursor cur(fs,dir_name);
  
  Printf(Con,"--- #; ---\n\n",dir_name);
  
  while( cur.next() )
    {
     Printf(Con,"#; #;\n",cur.getFileName(),cur.getFileType());
    }
    
  Printf(Con,"\n---\n\n");  
 }
 
} // namespace Private_1014
 
using namespace Private_1014; 
 
/* Testit<1014> */ 

template<>
const char *const Testit<1014>::Name="Test1014 FileSystem";

template<>
bool Testit<1014>::Main() 
 {
  ReportException report; 
  
  FileSystem fs;
 
  // getFileType()
  
  Printf(Con,". is #;\n",fs.getFileType("."));
  Printf(Con,".. is #;\n",fs.getFileType(".."));
  Printf(Con,"../obj is #;\n",fs.getFileType("../obj"));
  Printf(Con,"main.cpp is #;\n",fs.getFileType("main.cpp"));
  Printf(Con,"nofile.txt is #;\n",fs.getFileType("nofile.txt"));
  
  // createFile()
  
  fs.createFile("new_file.txt");
  
  try { fs.createFile("new_file.txt"); } catch(CatchType) {}
  
  // deleteFile()
  
  fs.deleteFile("new_file.txt");
  
  // createDir()
  
  fs.createDir("new_dir");
  
  try { fs.createDir("new_dir"); } catch(CatchType) {}
  
  // deleteDir()
  
  fs.deleteDir("new_dir",false);
  
  // remove()
  
  fs.createFile("new_file.txt");
  fs.createDir("new_dir");
  
  fs.remove("new_file.txt");
  fs.remove("new_dir");
  
  try { fs.remove("../obj"); } catch(CatchType) {}
  try { fs.remove("nodir"); } catch(CatchType) {}
  
  // rename()
  
  fs.createDir("new_dir");
  fs.createFile("new_dir/new_file.txt");
  
  fs.rename("new_dir","new_dir2",false);
  fs.rename("new_dir2/new_file.txt","new_file.txt",false);
 
  fs.createFile("new_file2.txt");
  fs.rename("new_file.txt","new_file2.txt",true);
  
  fs.remove("new_file2.txt");
  fs.remove("new_dir2");
  
  // DirCursor
  
  ShowDir(fs,".");
  ShowDir(fs,"..");
  
  // deleteDir() recursive
  
  fs.createDir("new_dir");
  fs.createFile("new_dir/new_file");
  
  fs.createDir("new_dir/new_dir1");
  fs.createFile("new_dir/new_dir1/new_file");
  
  fs.deleteDir("new_dir",true);
  
  return true;
 }
 
} // namespace App
 
