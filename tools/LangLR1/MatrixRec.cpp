/* MatrixRec.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "MatrixRec.h"

namespace App {

/* class MatrixRec */

void MatrixRec::GuardNoNumber()
 {
  Printf(Exception,"MatrixRec::getNumber() : no number");
 }

/* class MatrixRecSet */

void MatrixRecSet::Destroy(MatrixRec *rec)
 {
  if( !rec ) return;
  
  Destroy(Algo::Link(rec).lo);
  Destroy(Algo::Link(rec).hi);
  
  delete rec;
 }

MatrixRec & MatrixRecSet::find_or_add(const EMatrix &M)
 {
  Algo::PrepareIns prepare(root,M);
  
  if( prepare.found ) return *prepare.found;
  
  MatrixRec *rec=new MatrixRec(M);
  
  prepare.complete(rec);
  
  return *rec;
 }

} // namespace App


