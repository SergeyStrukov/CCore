/* test0044.Path.cpp */ 
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

#include <CCore/inc/Path.h>

namespace App {

namespace Private_0044 {

/* functions */

void testSplitDev(StrLen path)
 {
  SplitDev split(path);
  
  Printf(Con,"#; #; #;\n",split.dev,split.dev_path,split.no_dev);
 }

void testSplitPath(StrLen path)
 {
  SplitPath split(path);
  
  Printf(Con,"#; #; #;\n",split.dev,split.path,split.no_dev);
 }

void testSplitDir(StrLen path)
 {
  SplitDir split(path);
  
  Printf(Con,"#; #; #;\n",split.dir,split.path,split.no_path);
 }

void testSplitName(StrLen path)
 {
  SplitName split(path);
  
  Printf(Con,"#; #; #;\n",split.path,split.name,split.no_path);
 }

void testSplitFullExt(StrLen path)
 {
  SplitFullExt split(path);
  
  Printf(Con,"#; #; #;\n",split.name,split.ext,split.no_ext);
 }

void testSplitExt(StrLen path)
 {
  SplitExt split(path);
  
  Printf(Con,"#; #; #;\n",split.name,split.ext,split.no_ext);
 }

void testSplitDevName(StrLen path)
 {
  SplitDevName split(path);
  
  if( !split )
    Printf(Con,"#;\n",split.dev_path);
  else
    Printf(Con,"#; #;\n",split.dev_name,split.dev_path);
 }

void testSplitDirName(StrLen path)
 {
  SplitDirName split(path);
  
  if( !split )
    Printf(Con,"#;\n",split.path); 
  else  
    Printf(Con,"#; #;\n",split.dir_name,split.path);
 }

void testSplitPathName(StrLen path)
 {
  SplitPathName split(path);
  
  if( !split )
    Printf(Con,"#;\n",split.name);
  else
    Printf(Con,"#; #;\n",split.path,split.name);
 }

void testPath()
 {
  Path path("host");
  
  Printf(Con,"#;\n",path);
  
  path.addPath("dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/dir9/dir10/dir11/dir12/name");
  
  Printf(Con,"#;\n",path);
 
  path.addPath("../../../../../../../../../..");
  
  Printf(Con,"#;\n",path);
 
  path.addPath("../../..");
  
  Printf(Con,"#;\n",path);
  
  path.addPath("dir1/dir2/dir3/dir4/dir5/name");
  
  Printf(Con,"#;\n",path);
  
  path.addPath("../../../../../..");
  
  Printf(Con,"#;\n",path);
  
  path.addPath("dir1/./dir2/./dir3/.");
  
  Printf(Con,"#;\n",path);
  
  path.root();
  
  path.addPath("dir1/./dir2/./dir3/.");
  
  Printf(Con,"#;\n",path);
  
  path.addPath("/dir1/./dir2/./dir3/.");
  
  Printf(Con,"#;\n",path);
  
  path.add("name1");
  
  Printf(Con,"#;\n",path);
  
  path.back();
  
  path.add("name2");
  
  Printf(Con,"#;\n",path);
 };

} // namespace Private_0044
 
using namespace Private_0044; 
 
/* Testit<44> */ 

template<>
const char *const Testit<44>::Name="Test44 Path";

template<>
bool Testit<44>::Main() 
 {
  testSplitDev("path");
  testSplitDev("dev1:path");
  testSplitDev("dev1:dev2:path");
  
  Putobj(Con,"-----\n");
  
  testSplitPath("path");
  testSplitPath("dev1:path");
  testSplitPath("dev1:dev2:path");
  
  Putobj(Con,"-----\n");
  
  testSplitDir("name");
  testSplitDir("dir1/name");
  testSplitDir("dir1\\dir2/name");
  
  Putobj(Con,"-----\n");
  
  testSplitName("name");
  testSplitName("dir1/name");
  testSplitName("dir1\\dir2/name");
  
  Putobj(Con,"-----\n");
  
  testSplitFullExt("name");
  testSplitFullExt("name.ext");
  testSplitFullExt("name.ext1.ext2");
  
  Putobj(Con,"-----\n");
  
  testSplitExt("name");
  testSplitExt("name.ext");
  testSplitExt("name.ext1.ext2");
  
  Putobj(Con,"-----\n");
  
  testSplitDevName("name");
  testSplitDevName("dev1:name");
  testSplitDevName("dev1:dev2:name");
  
  Putobj(Con,"-----\n");
  
  testSplitDirName("name");
  testSplitDirName("dir1/name");
  testSplitDirName("dir1\\dir2/name");
  
  Putobj(Con,"-----\n");
  
  testSplitPathName("name");  
  testSplitPathName("dir1/name");  
  testSplitPathName("dir1\\dir2/name");  
  
  Putobj(Con,"-----\n");
  
  testPath();
  
  Putobj(Con,"-----\n");
  
  return true;
 }
 
} // namespace App
 
