/* test3011.AsyncFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

#include <CCore/inc/AsyncFileToMem.h>

namespace App {

namespace Private_3011 {

/* test1() */

void test1()
 {
  ReportException report;
  
  AsyncFileSystem fs("host");
  
  // getFileType()
  
  Printf(Con,". is #;\n",fs.getFileType("."));
  Printf(Con,"PTPServerLog.txt is #;\n",fs.getFileType("PTPServerLog.txt"));
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
  
  // deleteDir() recursive
  
  fs.createDir("new_dir");
  fs.createFile("new_dir/new_file");
  
  fs.createDir("new_dir/new_dir1");
  fs.createFile("new_dir/new_dir1/new_file");
  
  fs.deleteDir("new_dir",true);
  
  // exec
  
  fs.exec("test-dir","exectest.exe","1 2 3 4 5");
 }

/* test2() */

void test2()
 {
  AsyncFileListToMem list("host:.");
  
  Printf(Con,"\n#;\n\n",StrLen(Mutate<const char>(Range(list))));
  
  while( list.next() )
    {
     Printf(Con,"#.q; #;\n",list.getFileName(),list.getFileType());
    }
    
  Printf(Con,"\n");  
 }

/* test3() */

void test3()
 {
  PrintAsyncFile out;
  
  out.exec2("host:test-dir1","host:exectest.exe");

  for(int i=1; i<10 ;i++)
    Printf(out,"\"--- line #; ---\"\n",i);
  
  out.preserveFile();
 }

/* test4() */

void test4()
 {
  AsyncFileSystem::CreateFile("host:new_file.txt");
  
  Printf(Con,"type = #;\n",AsyncFileSystem::GetFileType("host:new_file.txt"));
  
  AsyncFileSystem::DeleteFile("host:new_file.txt");
  
  AsyncFileSystem::CreateDir("host:new_dir");
  
  AsyncFileSystem::Rename("host:new_dir","host:new_dir1",false);
  
  AsyncFileSystem::Remove("host:new_dir1");
  
  AsyncFileSystem::Exec("host:test-dir","host:exectest.exe","1 2 3 4 5");
 }
  
} // namespace Private_3011
 
using namespace Private_3011; 
 
/* Testit<3011> */ 

template<>
const char *const Testit<3011>::Name="Test3011 AsyncFile";

template<>
bool Testit<3011>::Main() 
 { 
  IPEngine ip_engine;
  
  HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));

  test1();
  test2();
  test3();
  test4();
  
  return true;
 }
 
} // namespace App
 
