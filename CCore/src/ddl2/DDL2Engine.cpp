/* DDL2Engine.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ddl2/DDL2Engine.h>

namespace CCore {
namespace DDL2 {

/* class TextEngine */

auto TextEngine::openFile(StrLen) -> File
 {
  return File(&id,text); 
 }
   
TextEngine::TextEngine(PrintBase &msg,StrLen text_,StrLen pretext_)
 : ParserContext(msg),
   pretext(pretext_),
   text(text_)
 {
 }
   
TextEngine::~TextEngine()
 {
 }
   
EngineResult TextEngine::process()
 {
  if( BodyNode *body_node=parseFile(StrLen(),pretext) )
    {
     if( EvalContext::Process(error,pool,body_node,result) )
       {
        return EngineResult(&result,body_node); 
       }
    }
  
  return Nothing;
 }

} // namespace DDL2
} // namespace CCore


