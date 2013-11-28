/* DDL2Parser.h */
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

#ifndef CCore_inc_ddl2_DDL2Parser_h
#define CCore_inc_ddl2_DDL2Parser_h

#include <CCore/inc/ddl2/DDL2Token.h>
#include <CCore/inc/ddl2/DDL2Semantic.h>

namespace CCore {
namespace DDL2 {

/* classes */

//enum AtomClass;

struct Atom;

class ParserContext;

class ElementContext;

struct ElementBase;

struct AnyElement;

struct ElementAtom;

struct Element_BODY;
struct Element_SCOPE;
struct Element_INCLUDE;
struct Element_TYPE;
struct Element_CONST;
struct Element_RNAME;
struct Element_NAME;
struct Element_RQNAME;
struct Element_QNAME;
struct Element_INT_TYPE;
struct Element_BASE_TYPE;
struct Element_TYPEDEF;
struct Element_TYPEDEF_LIST;
struct Element_STRUCT;
struct Element_SBODY;
struct Element_EXPR;
struct Element_EXPR_LIST;
struct Element_NAMED_EXPR;
struct Element_NAMED_EXPR_LIST;
struct Element_ITYPE;
struct Element_LITERAL;

class Parser;

/* enum AtomClass */

enum AtomClass
 {
  Atom_Nothing,
  
  Atom_Number,
  Atom_String,
  Atom_FileName,
  Atom_Name,
  Atom_QName,
  Atom_Dots,
  
  Atom_int,
  Atom_sint,
  Atom_uint,
  Atom_ulen,
  
  Atom_sint8,
  Atom_sint16,
  Atom_sint32,
  Atom_sint64,
  Atom_uint8,
  Atom_uint16,
  Atom_uint32,
  Atom_uint64,
  
  Atom_text,
  Atom_ip,
  Atom_struct,
  Atom_type,
  Atom_null,
  Atom_scope,
  Atom_include,
  Atom_const,
  
  Atom_asterisk,  // *
  Atom_comma,     // ,
  Atom_dot,       // .
  Atom_semicolon, // ;
  Atom_assign,    // =
  Atom_arrow,     // ->
  Atom_plus,      // +
  Atom_minus,     // -
  Atom_address,   // &
  Atom_pound,     // #
  Atom_div,       // /
  Atom_rem,       // %
  Atom_obr,       // (
  Atom_cbr,       // )
  Atom_sq_obr,    // [
  Atom_sq_cbr,    // ]
  Atom_fig_obr,   // {
  Atom_fig_cbr    // }
 };

const char * GetTextDesc(AtomClass ac);

/* struct Atom */

struct Atom
 {
  AtomClass ac;
  Token token;
  
  // constructors
  
  static AtomClass GetWordClass(StrLen str);
  
  static AtomClass GetPunctSymClass(StrLen str);
  
  static AtomClass GetAtomClass(const Token &token);
  
  Atom() : ac(Atom_Nothing) {}
  
  explicit Atom(const Token &token_) : ac(GetAtomClass(token_)),token(token_) {}
  
  // methods
  
  bool operator + () const { return ac!=Atom_Nothing; }
  
  bool operator ! () const { return ac==Atom_Nothing; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( ac )
      {
       case Atom_Number :
       case Atom_Name :
       case Atom_QName :
        {
         Printf(out,"#; #.q;",ac,token.str);
        }
       break;
       
       case Atom_Dots :
       case Atom_String :
       case Atom_FileName :
        {
         Printf(out,"#; #;",ac,token.str);
        }
       break;
       
       default: Printf(out,"#;",ac);
      }
   }
 };

/* class ParserContext */

class ParserContext : Context
 {
   struct PretextFile : FileId
    {
     virtual void printPos(PrintBase &out,TextPos pos);
    };
   
   PretextFile pretext_file;
   
  private:
   
   bool feed(Parser &parser,Tokenizer &tok);
   
   bool finish(Parser &parser,Tokenizer &tok);
   
   Element_BODY * parseText(FileId *file_id,StrLen text,StrLen pretext);
   
   Element_BODY * parseText(FileId *file_id,StrLen text);
   
   template <class Func>
   BodyNode * do_parseFile(StrLen file_name,Func func);
   
  protected:
   
   struct File
    {
     FileId *file_id;
     StrLen text;
     
     File(NothingType) : file_id(0) {}
     
     File(FileId *file_id_,StrLen text_) : file_id(file_id_),text(text_) {}
     
     bool operator ! () const { return !file_id; }
    };
   
   virtual File openFile(StrLen file_name);
   
   virtual File openFile(FileId *file_id,const Token &file_name);
   
  public:
   
   using Context::error;
   using Context::pool;
   
   // constructors
  
   explicit ParserContext(PrintBase &msg,ulen mem_cap=MaxULen);
   
   ~ParserContext();
   
   // methods
   
   ExtContext getExtContext(FileId *file_id) { return ExtContext(this,file_id); }
   
   BodyNode * parseFile(StrLen file_name,StrLen pretext);
   
   BodyNode * parseFile(StrLen file_name);
   
   Element_BODY * includeFile(FileId *file_id,const Token &file_name);
 };

/* class ElementContext */

class ElementContext
 {
   ParserContext *ctx;
   FileId *file_id;
   
  public: 
  
   ElementContext(ParserContext *ctx_,FileId *file_id_) : ctx(ctx_),file_id(file_id_) {}
  
   operator ExtContext() const { return ctx->getExtContext(file_id); }
   
   template <class ... SS>
   void error(SS && ... ss)
    {
     ctx->error( std::forward<SS>(ss)... );
    }
   
   PrintPos printPos(TextPos pos) 
    { 
     return PrintPos(file_id,pos); 
    }
  
   StrLen dup(StrLen str) 
    { 
     return ctx->pool.dup(str); 
    }
  
   template <class T,class ... SS>
   T * create(SS && ... ss)
    {
     return ctx->pool.create<T>( std::forward<SS>(ss)... );
    }
  
   Element_BODY * includeFile(const Token &file_name) 
    { 
     return ctx->includeFile(file_id,file_name); 
    }
 };

/* struct ElementBase */

struct ElementBase : NoCopy
 {
  ElementBase *prev;
  unsigned state;
  
  ElementBase() : prev(0),state(0) {}
 };

/* struct AnyElement */

struct AnyElement
 {
  ElementBase *elem;
  
  explicit AnyElement(ElementBase *elem_) : elem(elem_) {}
  
  template <class T>
  operator T * () const { return static_cast<T *>(elem); }
 };

/* struct ElementAtom */

struct ElementAtom : ElementBase
 {
  Token token;
  
  ElementAtom(ElementContext ctx,const Atom &atom)
   : token(atom.token)
   {
    token.str=ctx.dup(token.str);
   }
 
  operator const Token & () const { return token; }  
 };

/* struct Element_BODY */

struct Element_BODY : ElementBase
 {
  BodyNode *body_node;
  
  operator BodyNode * () { return body_node; }

  void start(ElementContext);

  void ext(ElementContext,Element_BODY *,Element_SCOPE *);

  void ext(ElementContext,Element_BODY *,Element_INCLUDE *);

  void ext(ElementContext,Element_BODY *,Element_TYPE *);

  void ext(ElementContext,Element_BODY *,Element_CONST *);

  void ext(ElementContext,Element_BODY *,Element_STRUCT *,ElementAtom *);
 };

/* struct Element_SCOPE */

struct Element_SCOPE : ElementBase
 {
  ScopeNode scope_node;
  
  operator ScopeNode * () { return &scope_node; }

  void build(ElementContext,ElementAtom *,ElementAtom *,ElementAtom *,Element_BODY *,ElementAtom *);
 };

/* struct Element_INCLUDE */

struct Element_INCLUDE : ElementBase
 {
  BodyNode *body_node; // may == 0
  
  operator BodyNode * () { return body_node; }

  void includeFile(ElementContext,ElementAtom *,ElementAtom *);
 };

/* struct Element_TYPE */

struct Element_TYPE : ElementBase
 {
  AliasNode alias_node;
  
  operator AliasNode * () { return &alias_node; }

  void build(ElementContext,ElementAtom *,ElementAtom *,ElementAtom *,Element_TYPEDEF *,ElementAtom *);
 };

/* struct Element_CONST */

struct Element_CONST : ElementBase
 {
  ConstNode const_node;
  
  operator ConstNode * () { return &const_node; }

  void build(ElementContext,Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
 };

/* struct Element_RNAME */

struct Element_RNAME : ElementBase
 {
  NameNode name_node;
  NameNodeList *name_list;
  
  operator NameNodeList * () { return name_list; } 

  void start(ElementContext,ElementAtom *);

  void ext(ElementContext,Element_RNAME *,ElementAtom *,ElementAtom *);
 };

/* struct Element_NAME */

struct Element_NAME : ElementBase
 {
  NameRefNode name_ref;
  
  operator NameRefNode * () { return &name_ref; } 

  void rel(ElementContext,Element_RNAME *);

  void abs(ElementContext,ElementAtom *,Element_RNAME *);

  void dot(ElementContext,ElementAtom *,ElementAtom *,Element_RNAME *);

  void dots(ElementContext,ElementAtom *,ElementAtom *,Element_RNAME *);
 };

/* struct Element_RQNAME */

struct Element_RQNAME : ElementBase
 {
  NameNode name_node;
  NameNodeList *name_list;
  
  operator NameNodeList * () { return name_list; } 

  void start_Name(ElementContext,ElementAtom *);

  void start_QName(ElementContext,ElementAtom *);

  void ext_Name(ElementContext,Element_RQNAME *,ElementAtom *,ElementAtom *);

  void ext_QName(ElementContext,Element_RQNAME *,ElementAtom *,ElementAtom *);
 };

/* struct Element_QNAME */

struct Element_QNAME : ElementBase
 {
  NameRefNode name_ref;
  
  operator NameRefNode * () { return &name_ref; }
  
  void rel(ElementContext,Element_RQNAME *);

  void abs(ElementContext,ElementAtom *,Element_RQNAME *);

  void dot(ElementContext,ElementAtom *,ElementAtom *,Element_RQNAME *);

  void dots(ElementContext,ElementAtom *,ElementAtom *,Element_RQNAME *);
 };

/* struct Element_INT_TYPE */

struct Element_INT_TYPE : ElementBase
 {
  TypeNode::Base::Type base_type;
  
  operator TypeNode::Base::Type() { return base_type; }

  void type_int(ElementContext,ElementAtom *);

  void type_sint(ElementContext,ElementAtom *);

  void type_uint(ElementContext,ElementAtom *);

  void type_ulen(ElementContext,ElementAtom *);

  void type_sint8(ElementContext,ElementAtom *);

  void type_uint8(ElementContext,ElementAtom *);

  void type_sint16(ElementContext,ElementAtom *);

  void type_uint16(ElementContext,ElementAtom *);

  void type_sint32(ElementContext,ElementAtom *);

  void type_uint32(ElementContext,ElementAtom *);

  void type_sint64(ElementContext,ElementAtom *);

  void type_uint64(ElementContext,ElementAtom *);
 };

/* struct Element_BASE_TYPE */

struct Element_BASE_TYPE : ElementBase
 {
  TypeNode::Base::Type base_type;
  
  operator TypeNode::Base::Type() { return base_type; }

  void cast(ElementContext,Element_INT_TYPE *);

  void type_text(ElementContext,ElementAtom *);

  void type_ip(ElementContext,ElementAtom *);
 };

/* struct Element_TYPEDEF */

struct Element_TYPEDEF : ElementBase
 {
  TypeNode type_node;
  
  operator TypeNode * () { return &type_node; }

  void type_named(ElementContext,Element_NAME *);

  void type_base(ElementContext,Element_BASE_TYPE *);

  void type_ptr(ElementContext,Element_TYPEDEF *,ElementAtom *);

  void type_polyptr(ElementContext,ElementAtom *,Element_TYPEDEF_LIST *,ElementAtom *,ElementAtom *);

  void type_array(ElementContext,Element_TYPEDEF *,ElementAtom *,ElementAtom *);

  void type_array_len(ElementContext,Element_TYPEDEF *,ElementAtom *,Element_EXPR *,ElementAtom *);

  void type_struct(ElementContext,Element_STRUCT *);
 };

/* struct Element_TYPEDEF_LIST */

struct Element_TYPEDEF_LIST : ElementBase
 {
  TypeListNode node;
  TypeList *type_list;
  
  operator TypeList * () { return type_list; }

  void start(ElementContext,Element_TYPEDEF *);

  void ext(ElementContext,Element_TYPEDEF_LIST *,ElementAtom *,Element_TYPEDEF *);
 };

/* struct Element_STRUCT */

struct Element_STRUCT : ElementBase
 {
  StructNode struct_node;
  
  operator StructNode * () { return &struct_node; }

  void build(ElementContext,ElementAtom *,ElementAtom *,ElementAtom *,Element_SBODY *,ElementAtom *);
 };

/* struct Element_SBODY */

struct Element_SBODY : ElementBase
 {
  SBodyNode *sbody_node;
  
  operator SBodyNode * () { return sbody_node; }

  void start(ElementContext);

  void ext(ElementContext,Element_SBODY *,Element_TYPE *);

  void ext(ElementContext,Element_SBODY *,ElementAtom *,Element_CONST *);

  void ext(ElementContext,Element_SBODY *,Element_STRUCT *,ElementAtom *);

  void ext(ElementContext,Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *);

  void ext(ElementContext,Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
 };

/* struct Element_EXPR */

struct Element_EXPR : ElementBase
 {
  ExprNode expr_node;
  
  operator ExprNode * () { return &expr_node; } 

  void cast(ElementContext,ElementAtom *,Element_EXPR *,ElementAtom *);

  void cast(ElementContext,Element_QNAME *);

  void cast(ElementContext,Element_LITERAL *);

  void opDomain(ElementContext,Element_ITYPE *,ElementAtom *,Element_EXPR *,ElementAtom *);

  void opSelect(ElementContext,Element_EXPR *,ElementAtom *,ElementAtom *);

  void opPtrSelect(ElementContext,Element_EXPR *,ElementAtom *,ElementAtom *);

  void opInd(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *,ElementAtom *);

  void cast(ElementContext,ElementAtom *);

  void opAst(ElementContext,ElementAtom *,Element_EXPR *);

  void opAmp(ElementContext,ElementAtom *,Element_EXPR *);

  void opPlus(ElementContext,ElementAtom *,Element_EXPR *);

  void opMinus(ElementContext,ElementAtom *,Element_EXPR *);

  void opMul(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *);

  void opDiv(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *);

  void opRem(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *);

  void opAdd(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *);

  void opSub(ElementContext,Element_EXPR *,ElementAtom *,Element_EXPR *);

  void emptyExprList(ElementContext,ElementAtom *,ElementAtom *);

  void buildExprList(ElementContext,ElementAtom *,Element_EXPR_LIST *,ElementAtom *);

  void buildNamedExprList(ElementContext,ElementAtom *,Element_NAMED_EXPR_LIST *,ElementAtom *);

  void applyEmpty(ElementContext,Element_EXPR *,ElementAtom *,ElementAtom *);

  void applyNamedExprList(ElementContext,Element_EXPR *,ElementAtom *,Element_NAMED_EXPR_LIST *,ElementAtom *);
 };

/* struct Element_EXPR_LIST */

struct Element_EXPR_LIST : ElementBase
 {
  ExprListNode node;
  ExprList *list;
  
  operator ExprList * () { return list; }

  void start(ElementContext,Element_EXPR *);

  void ext(ElementContext,Element_EXPR_LIST *,ElementAtom *,Element_EXPR *);
 };

/* struct Element_NAMED_EXPR */

struct Element_NAMED_EXPR : ElementBase
 {
  NamedExprListNode node;
  
  operator NamedExprListNode * () { return &node; }

  void build(ElementContext,ElementAtom *,ElementAtom *,ElementAtom *,Element_EXPR *);
 };

/* struct Element_NAMED_EXPR_LIST */

struct Element_NAMED_EXPR_LIST : ElementBase
 {
  NamedExprList *list;
  
  operator NamedExprList * () { return list; }

  void start(ElementContext,Element_NAMED_EXPR *);

  void ext(ElementContext,Element_NAMED_EXPR_LIST *,ElementAtom *,Element_NAMED_EXPR *);
 };

/* struct Element_ITYPE */

struct Element_ITYPE : ElementBase
 {
  TypeNode::Base::Type base_type;
  NameRefNode *name_ref;

  void type_int(ElementContext,Element_INT_TYPE *);

  void type_named(ElementContext,Element_QNAME *);
 };

/* struct Element_LITERAL */

struct Element_LITERAL : ElementBase
 {
  AnyPtr<LitNull,LitString,LitIP> ptr;
  
  operator AnyPtr<LitNull,LitString,LitIP> () { return ptr; }

  void cast_null(ElementContext,ElementAtom *);

  void cast_String(ElementContext,ElementAtom *);

  void buildIP(ElementContext,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *);
 };

/* class Parser */

class Parser : NoCopy
 {
   ElementContext ctx;
   ElementBase *stack;
   
  private:
   
   void push(ElementBase *elem,unsigned state)
    {
     elem->prev=stack;
     stack=elem;
     
     elem->state=state;
    }
   
   AnyElement pop()
    {
     ElementBase *elem=stack;
     
     stack=elem->prev;
     
     return AnyElement(elem);
    }
   
   void shift(const Atom &atom,unsigned state)
    {
     push(ctx.create<ElementAtom>(ctx,atom),state);
    }
   
  private:
   
   struct Action
    {
     int rule;
     unsigned element;
     
     enum SpecialRule
      {
       Shift = -1,
       Error = -2
      };
    
     Action(unsigned state,AtomClass ac=Atom_Nothing);
    };
   
   static unsigned ElementOf(AtomClass ac) { return ac-1; }
   
   static unsigned Transition(unsigned state,unsigned element);
   
   void doRule(int rule,unsigned element);
   
  public:
   
   Parser(ParserContext *ctx,FileId *file_id);
   
   ~Parser();
   
   enum Result
    {
     ResultShift,
     ResultRule,
     ResultAbort
    };
   
   Result next(const Atom &atom);
   
   Result complete(TextPos pos);
   
   Result next_loop(const Atom &atom);
   
   Result complete_loop(TextPos pos);
   
   Element_BODY * getBody() const { return static_cast<Element_BODY *>(stack); }
 };

} // namespace DDL2
} // namespace CCore

#endif

