/* DDLParser.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLParser_h
#define CCore_inc_ddl_DDLParser_h

#include <CCore/inc/ddl/DDLSemantic.h>
 
namespace CCore {
namespace DDL {

/* classes */

//enum AtomClass;

struct Atom;

struct ParserResult;

class ParserContext;

class ElementContext;

struct ElementBase;

struct AnyElement;

struct ElementAtom;

struct ElementTypeBase;
struct ElementExprBase;

struct Element_BODY;
struct Element_SCOPE;
struct Element_INCLUDE;
struct Element_TYPE;
struct Element_CONST;
struct Element_RNAME;
struct Element_NAME;
struct Element_INAME;
struct Element_TNAME;
struct Element_TYPEDEF;
struct Element_STRUCT;
struct Element_SBODY;
struct Element_EXPR;
struct Element_EXPR_ADD;
struct Element_EXPR_MUL;
struct Element_EXPR_UN;
struct Element_EXPR_POST;
struct Element_EXPR_NNPOST;
struct Element_EXPR_NNPRIM;
struct Element_ELIST;
struct Element_NEXPR;
struct Element_NELIST;
struct Element_ITYPE;
struct Element_NNLIT;

struct Action;

class Parser;

/* enum AtomClass */

enum AtomClass
 {
  Atom_Nothing,
  
  Atom_Number,
  Atom_String,
  Atom_FileName,
  Atom_Name,
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
  
  Atom() : ac(Atom_Nothing) {}
  
  explicit Atom(const Token &token_) : ac(GetAtomClass(token_)),token(token_) {}
  
  // methods
  
  bool operator + () const { return ac!=Atom_Nothing; }
  
  bool operator ! () const { return ac==Atom_Nothing; }
  
  static AtomClass GetWordClass(StrLen str);
  
  static AtomClass GetPunctSymClass(StrLen str);
  
  static AtomClass GetAtomClass(const Token &token);
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( ac )
      {
       case Atom_Number :
       case Atom_Name :
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

/* struct ParserResult */

struct ParserResult
 {
  BodyNode *body;
  ForwardList<ExprNode> list;
  BaseList<ExprNode> rev_list;
  
  ParserResult() : body(0) {}
  
  bool operator ! () const { return !body; }
 };

/* class ParserContext */

class ParserContext : Context
 {
   bool ok;
   ulen error_cap;
   
  private:
   
   Element_BODY * parseText(FileId *file_id,StrLen text);
   
   Element_BODY * includeFile(FileId *file_id,const Token &file_name);
  
   friend class ElementContext;
   
  protected: 
   
   template <class ... SS>
   void printfError(const char *format,SS && ... ss)
    {
     ok=false;
     
     if( error_cap )
       {
        error_cap--;
        
        Printf(msg,format, std::forward<SS>(ss)... );
       }
    }
   
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
   
   // constructors
  
   explicit ParserContext(PrintBase &msg,ulen mem_cap=MaxULen) : Context(msg,mem_cap),ok(true),error_cap(ErrorMsgCap) {}
   
   ~ParserContext() {}
   
   // methods
   
   ElementPool & getPool() { return pool; }
   
   PrintBase & getMsg() { return msg; }
   
   ParserResult parseFile(StrLen file_name);
 };

/* class ElementContext */

class ElementContext
 {
   ParserContext *ctx;
   FileId *file_id;
   
  public: 
  
   ElementContext(ParserContext *ctx_,FileId *file_id_) : ctx(ctx_),file_id(file_id_) {}
  
   operator ExtContext() const { return ExtContext(file_id,ctx); }
  
   template <class ... SS>
   void printf(const char *format,SS && ... ss)
    {
     Printf(ctx->msg,format, std::forward<SS>(ss)... );
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
  ulen state;
  
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

/* struct ElementTypeBase */

struct ElementTypeBase : ElementBase
 {
  TypeNode *type_node;
  
  template <class Type,class ... SS>
  void init(ElementContext ctx,SS && ... ss)
   {
    Type *node=ctx.create<Type>();
    
    node->init( std::forward<SS>(ss)... );
    
    type_node=node;
   }
  
  operator TypeNode * () { return type_node; }
 };

/* struct ElementExprBase */

struct ElementExprBase : ElementBase
 {
  ExprNode *expr_node;
  
  template <class Type,class ... SS>
  void init(ElementContext ctx,SS && ... ss)
   {
    Type *node=ctx.create<Type>();
    
    node->init( std::forward<SS>(ss)... );
    
    expr_node=node;
   }
  
  operator ExprNode * () { return expr_node; }
 };

/* struct Element_BODY */

struct Element_BODY : ElementBase
 {
  static ulen NextState(ulen state);
  
  BodyNode body_node;
  
  operator BodyNode * () { return &body_node; }
  
  void startBody(ElementContext ctx);

  void extBody_SCOPE(ElementContext ctx,Element_BODY *,Element_SCOPE *);

  void extBody_INCLUDE(ElementContext ctx,Element_BODY *,Element_INCLUDE *);

  void extBody_TYPE(ElementContext ctx,Element_BODY *,Element_TYPE *);

  void extBody_CONST(ElementContext ctx,Element_BODY *,Element_CONST *);

  void extBody_STRUCT(ElementContext ctx,Element_BODY *,Element_STRUCT *,ElementAtom *);
 };

/* struct Element_SCOPE */

struct Element_SCOPE : ElementBase
 {
  static ulen NextState(ulen state);

  ScopeNode scope_node;
  
  operator ScopeNode * () { return &scope_node; }
  
  void buildScope(ElementContext ctx,ElementAtom *,ElementAtom *,ElementAtom *,Element_BODY *,ElementAtom *);
 };

/* struct Element_INCLUDE */

struct Element_INCLUDE : ElementBase
 {
  static ulen NextState(ulen state);

  BodyNode *body_node;
  
  operator BodyNode * () { return body_node; }
  
  void includeFile(ElementContext ctx,ElementAtom *,ElementAtom *);
 };

/* struct Element_TYPE */

struct Element_TYPE : ElementBase
 {
  static ulen NextState(ulen state);

  AliasNode alias_node;
  
  operator AliasNode * () { return &alias_node; }
  
  void defType(ElementContext ctx,ElementAtom *,ElementAtom *,ElementAtom *,Element_TYPEDEF *,ElementAtom *);
 };

/* struct Element_CONST */

struct Element_CONST : ElementBase
 {
  static ulen NextState(ulen state);

  ConstNode const_node;
  
  operator ConstNode * () { return &const_node; }
  
  void defConst(ElementContext ctx,Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
 };

/* struct Element_RNAME */

struct Element_RNAME : ElementBase
 {
  static ulen NextState(ulen state);

  NameNode name_node;
  ForwardList<NameNode> name_list;
  
  operator ForwardList<NameNode> & () { return name_list; }
  
  void startName(ElementContext ctx,ElementAtom *);

  void extName(ElementContext ctx,Element_RNAME *,ElementAtom *,ElementAtom *);
 };

/* struct Element_NAME */

struct Element_NAME : ElementBase
 {
  static ulen NextState(ulen state);

  NameRef name;
  
  operator NameRef * () { return &name; }
  
  void relName(ElementContext ctx,Element_RNAME *);

  void absName(ElementContext ctx,ElementAtom *,Element_RNAME *);

  void dotName(ElementContext ctx,ElementAtom *,ElementAtom *,Element_RNAME *);

  void dotsName(ElementContext ctx,ElementAtom *,ElementAtom *,Element_RNAME *);
 };

/* struct Element_INAME */

struct Element_INAME : ElementTypeBase
 {
  static ulen NextState(ulen state);

  template <class T>
  void init_suint(ElementContext ctx)
   {
    typedef TypeNode_suint<T> Type;
    
    init<Type>(ctx);
   }
  
  void intName(ElementContext ctx,ElementAtom *);

  void sintName(ElementContext ctx,ElementAtom *);

  void uintName(ElementContext ctx,ElementAtom *);

  void ulenName(ElementContext ctx,ElementAtom *);

  void sint8Name(ElementContext ctx,ElementAtom *);

  void uint8Name(ElementContext ctx,ElementAtom *);

  void sint16Name(ElementContext ctx,ElementAtom *);

  void uint16Name(ElementContext ctx,ElementAtom *);

  void sint32Name(ElementContext ctx,ElementAtom *);

  void uint32Name(ElementContext ctx,ElementAtom *);

  void sint64Name(ElementContext ctx,ElementAtom *);

  void uint64Name(ElementContext ctx,ElementAtom *);
 };

/* struct Element_TNAME */

struct Element_TNAME : ElementTypeBase
 {
  static ulen NextState(ulen state);

  void cast_INAME(ElementContext ctx,Element_INAME *);

  void textName(ElementContext ctx,ElementAtom *);

  void ipName(ElementContext ctx,ElementAtom *);
 };

/* struct Element_TYPEDEF */

struct Element_TYPEDEF : ElementTypeBase
 {
  static ulen NextState(ulen state);

  void namedType(ElementContext ctx,Element_NAME *);

  void baseType(ElementContext ctx,Element_TNAME *);

  void ptrType(ElementContext ctx,Element_TYPEDEF *,ElementAtom *);

  void arrayType(ElementContext ctx,Element_TYPEDEF *,ElementAtom *,ElementAtom *);

  void arrayLenType(ElementContext ctx,Element_TYPEDEF *,ElementAtom *,Element_EXPR *,ElementAtom *);

  void structType(ElementContext ctx,Element_STRUCT *);
 };

/* struct Element_STRUCT */

struct Element_STRUCT : ElementBase
 {
  static ulen NextState(ulen state);

  StructNode struct_node;
  
  operator StructNode * () { return &struct_node; }
  
  void buildStruct(ElementContext ctx,ElementAtom *,ElementAtom *,ElementAtom *,Element_SBODY *,ElementAtom *);
 };

/* struct Element_SBODY */

struct Element_SBODY : ElementBase
 {
  static ulen NextState(ulen state);

  SBodyNode sbody_node;
  
  operator SBodyNode * () { return &sbody_node; }
  
  void startSBody(ElementContext ctx);

  void extSBody_TYPE(ElementContext ctx,Element_SBODY *,Element_TYPE *);

  void extSBody_CONST(ElementContext ctx,Element_SBODY *,ElementAtom *,Element_CONST *);

  void extSBody_STRUCT(ElementContext ctx,Element_SBODY *,Element_STRUCT *,ElementAtom *);

  void extSBody_field(ElementContext ctx,Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *);

  void extSBody_fieldVal(ElementContext ctx,Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
 };

/* struct Element_EXPR */

struct Element_EXPR : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_ADD(ElementContext ctx,Element_EXPR_ADD *);

  void emptyExprList(ElementContext ctx,ElementAtom *,ElementAtom *);

  void buildExprList(ElementContext ctx,ElementAtom *,Element_ELIST *,ElementAtom *);

  void buildNamedExprList(ElementContext ctx,ElementAtom *,Element_NELIST *,ElementAtom *);

  void applyEmpty(ElementContext ctx,Element_EXPR *,ElementAtom *,ElementAtom *);

  void applyNamedExprList(ElementContext ctx,Element_EXPR *,ElementAtom *,Element_NELIST *,ElementAtom *);
 };

/* struct Element_EXPR_ADD */

struct Element_EXPR_ADD : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_MUL(ElementContext ctx,Element_EXPR_MUL *);

  void opAdd(ElementContext ctx,Element_EXPR_ADD *,ElementAtom *,Element_EXPR_MUL *);

  void opSub(ElementContext ctx,Element_EXPR_ADD *,ElementAtom *,Element_EXPR_MUL *);
 };

/* struct Element_EXPR_MUL */

struct Element_EXPR_MUL : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_UN(ElementContext ctx,Element_EXPR_UN *);

  void opMul(ElementContext ctx,Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);

  void opDiv(ElementContext ctx,Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);

  void opRem(ElementContext ctx,Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);
 };

/* struct Element_EXPR_UN */

struct Element_EXPR_UN : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_POST(ElementContext ctx,Element_EXPR_POST *);

  void opAst(ElementContext ctx,ElementAtom *,Element_EXPR_UN *);

  void opAmp(ElementContext ctx,ElementAtom *,Element_EXPR_UN *);

  void opPlus(ElementContext ctx,ElementAtom *,Element_EXPR_UN *);

  void opMinus(ElementContext ctx,ElementAtom *,Element_EXPR_UN *);
 };

/* struct Element_EXPR_POST */

struct Element_EXPR_POST : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_NNPOST(ElementContext ctx,Element_EXPR_NNPOST *);

  void cast_Number(ElementContext ctx,ElementAtom *);
 };

/* struct Element_EXPR_NNPOST */

struct Element_EXPR_NNPOST : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR_NNPRIM(ElementContext ctx,Element_EXPR_NNPRIM *);

  void opInd(ElementContext ctx,Element_EXPR_POST *,ElementAtom *,Element_EXPR *,ElementAtom *);

  void opSelect(ElementContext ctx,Element_EXPR_NNPOST *,ElementAtom *,ElementAtom *);

  void opPtrSelect(ElementContext ctx,Element_EXPR_NNPOST *,ElementAtom *,ElementAtom *);
 };

/* struct Element_EXPR_NNPRIM */

struct Element_EXPR_NNPRIM : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_EXPR(ElementContext ctx,ElementAtom *,Element_EXPR *,ElementAtom *);

  void cast_NAME(ElementContext ctx,Element_NAME *);

  void cast_NNLIT(ElementContext ctx,Element_NNLIT *);

  void opDomain(ElementContext ctx,Element_ITYPE *,ElementAtom *,Element_EXPR *,ElementAtom *);
 };

/* struct Element_ELIST */

struct Element_ELIST : ElementBase
 {
  static ulen NextState(ulen state);

  NonameExprNode node;
  ForwardList<NonameExprNode> list;
  
  operator ForwardList<NonameExprNode> & () { return list; }
  
  void startExprList(ElementContext ctx,Element_EXPR *);

  void extExprList(ElementContext ctx,Element_ELIST *,ElementAtom *,Element_EXPR *);
 };

/* struct Element_NEXPR */

struct Element_NEXPR : ElementBase
 {
  static ulen NextState(ulen state);

  NamedExprNode node;
  
  operator NamedExprNode * () { return &node; }
  
  void nameExpr(ElementContext ctx,ElementAtom *,ElementAtom *,ElementAtom *,Element_EXPR *);
 };

/* struct Element_NELIST */

struct Element_NELIST : ElementBase
 {
  static ulen NextState(ulen state);

  BegList<NamedExprNode> list;
  
  operator BegList<NamedExprNode> & () { return list; }
  
  void startNamedExprList(ElementContext ctx,Element_NEXPR *);

  void extNamedExprList(ElementContext ctx,Element_NELIST *,ElementAtom *,Element_NEXPR *);
 };

/* struct Element_ITYPE */

struct Element_ITYPE : ElementBase
 {
  static ulen NextState(ulen state);

  DomainTypeNode domain_node;
  
  operator DomainTypeNode * () { return &domain_node; }
  
  void type_NAME(ElementContext ctx,Element_NAME *);

  void type_INAME(ElementContext ctx,Element_INAME *);
 };

/* struct Element_NNLIT */

struct Element_NNLIT : ElementExprBase
 {
  static ulen NextState(ulen state);

  void cast_null(ElementContext ctx,ElementAtom *);

  void cast_String(ElementContext ctx,ElementAtom *);

  void buildIP(ElementContext ctx,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *);
 };

/* struct Action */

struct Action
 {
  enum Rule
   {
    Abort,
    Shift,
    
    Do_startBody,
    Do_extBody_SCOPE,
    Do_extBody_INCLUDE,
    Do_extBody_TYPE,
    Do_extBody_CONST,
    Do_extBody_STRUCT,
    Do_buildScope,
    Do_includeFile,
    Do_defType,
    Do_defConst,
    Do_startName,
    Do_extName,
    Do_relName,
    Do_absName,
    Do_dotName,
    Do_dotsName,
    Do_intName,
    Do_sintName,
    Do_uintName,
    Do_ulenName,
    Do_sint8Name,
    Do_uint8Name,
    Do_sint16Name,
    Do_uint16Name,
    Do_sint32Name,
    Do_uint32Name,
    Do_sint64Name,
    Do_uint64Name,
    Do_cast_INAME,
    Do_textName,
    Do_ipName,
    Do_namedType,
    Do_baseType,
    Do_ptrType,
    Do_arrayType,
    Do_arrayLenType,
    Do_structType,
    Do_buildStruct,
    Do_startSBody,
    Do_extSBody_TYPE,
    Do_extSBody_CONST,
    Do_extSBody_STRUCT,
    Do_extSBody_field,
    Do_extSBody_fieldVal,
    Do_cast_EXPR_ADD,
    Do_emptyExprList,
    Do_buildExprList,
    Do_buildNamedExprList,
    Do_applyEmpty,
    Do_applyNamedExprList,
    Do_cast_EXPR_MUL,
    Do_opAdd,
    Do_opSub,
    Do_cast_EXPR_UN,
    Do_opMul,
    Do_opDiv,
    Do_opRem,
    Do_cast_EXPR_POST,
    Do_opAst,
    Do_opAmp,
    Do_opPlus,
    Do_opMinus,
    Do_cast_EXPR_NNPOST,
    Do_cast_Number,
    Do_cast_EXPR_NNPRIM,
    Do_opInd,
    Do_opSelect,
    Do_opPtrSelect,
    Do_cast_EXPR,
    Do_cast_NAME,
    Do_cast_NNLIT,
    Do_opDomain,
    Do_startExprList,
    Do_extExprList,
    Do_nameExpr,
    Do_startNamedExprList,
    Do_extNamedExprList,
    Do_type_NAME,
    Do_type_INAME,
    Do_cast_null,
    Do_cast_String,
    Do_buildIP
   };
  
  Rule rule;
  ulen new_state;
  
  explicit Action(ulen state,AtomClass ac=Atom_Nothing);
 };

/* class Parser */

class Parser : NoCopy
 {
   ElementContext ctx;
   ElementBase *stack;
   
  private:
   
   void push(ElementBase *elem,ulen state);
   
   AnyElement pop();
   
   void shift(const Atom &atom,ulen state);
   
  private:
   
   Element_BODY * elem_startBody();
   Element_BODY * elem_extBody_SCOPE(Element_BODY *,Element_SCOPE *);
   Element_BODY * elem_extBody_INCLUDE(Element_BODY *,Element_INCLUDE *);
   Element_BODY * elem_extBody_TYPE(Element_BODY *,Element_TYPE *);
   Element_BODY * elem_extBody_CONST(Element_BODY *,Element_CONST *);
   Element_BODY * elem_extBody_STRUCT(Element_BODY *,Element_STRUCT *,ElementAtom *);
   Element_SCOPE * elem_buildScope(ElementAtom *,ElementAtom *,ElementAtom *,Element_BODY *,ElementAtom *);
   Element_INCLUDE * elem_includeFile(ElementAtom *,ElementAtom *);
   Element_TYPE * elem_defType(ElementAtom *,ElementAtom *,ElementAtom *,Element_TYPEDEF *,ElementAtom *);
   Element_CONST * elem_defConst(Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_RNAME * elem_startName(ElementAtom *);
   Element_RNAME * elem_extName(Element_RNAME *,ElementAtom *,ElementAtom *);
   Element_NAME * elem_relName(Element_RNAME *);
   Element_NAME * elem_absName(ElementAtom *,Element_RNAME *);
   Element_NAME * elem_dotName(ElementAtom *,ElementAtom *,Element_RNAME *);
   Element_NAME * elem_dotsName(ElementAtom *,ElementAtom *,Element_RNAME *);
   Element_INAME * elem_intName(ElementAtom *);
   Element_INAME * elem_sintName(ElementAtom *);
   Element_INAME * elem_uintName(ElementAtom *);
   Element_INAME * elem_ulenName(ElementAtom *);
   Element_INAME * elem_sint8Name(ElementAtom *);
   Element_INAME * elem_uint8Name(ElementAtom *);
   Element_INAME * elem_sint16Name(ElementAtom *);
   Element_INAME * elem_uint16Name(ElementAtom *);
   Element_INAME * elem_sint32Name(ElementAtom *);
   Element_INAME * elem_uint32Name(ElementAtom *);
   Element_INAME * elem_sint64Name(ElementAtom *);
   Element_INAME * elem_uint64Name(ElementAtom *);
   Element_TNAME * elem_cast_INAME(Element_INAME *);
   Element_TNAME * elem_textName(ElementAtom *);
   Element_TNAME * elem_ipName(ElementAtom *);
   Element_TYPEDEF * elem_namedType(Element_NAME *);
   Element_TYPEDEF * elem_baseType(Element_TNAME *);
   Element_TYPEDEF * elem_ptrType(Element_TYPEDEF *,ElementAtom *);
   Element_TYPEDEF * elem_arrayType(Element_TYPEDEF *,ElementAtom *,ElementAtom *);
   Element_TYPEDEF * elem_arrayLenType(Element_TYPEDEF *,ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_TYPEDEF * elem_structType(Element_STRUCT *);
   Element_STRUCT * elem_buildStruct(ElementAtom *,ElementAtom *,ElementAtom *,Element_SBODY *,ElementAtom *);
   Element_SBODY * elem_startSBody();
   Element_SBODY * elem_extSBody_TYPE(Element_SBODY *,Element_TYPE *);
   Element_SBODY * elem_extSBody_CONST(Element_SBODY *,ElementAtom *,Element_CONST *);
   Element_SBODY * elem_extSBody_STRUCT(Element_SBODY *,Element_STRUCT *,ElementAtom *);
   Element_SBODY * elem_extSBody_field(Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *);
   Element_SBODY * elem_extSBody_fieldVal(Element_SBODY *,Element_TYPEDEF *,ElementAtom *,ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_EXPR * elem_cast_EXPR_ADD(Element_EXPR_ADD *);
   Element_EXPR * elem_emptyExprList(ElementAtom *,ElementAtom *);
   Element_EXPR * elem_buildExprList(ElementAtom *,Element_ELIST *,ElementAtom *);
   Element_EXPR * elem_buildNamedExprList(ElementAtom *,Element_NELIST *,ElementAtom *);
   Element_EXPR * elem_applyEmpty(Element_EXPR *,ElementAtom *,ElementAtom *);
   Element_EXPR * elem_applyNamedExprList(Element_EXPR *,ElementAtom *,Element_NELIST *,ElementAtom *);
   Element_EXPR_ADD * elem_cast_EXPR_MUL(Element_EXPR_MUL *);
   Element_EXPR_ADD * elem_opAdd(Element_EXPR_ADD *,ElementAtom *,Element_EXPR_MUL *);
   Element_EXPR_ADD * elem_opSub(Element_EXPR_ADD *,ElementAtom *,Element_EXPR_MUL *);
   Element_EXPR_MUL * elem_cast_EXPR_UN(Element_EXPR_UN *);
   Element_EXPR_MUL * elem_opMul(Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_MUL * elem_opDiv(Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_MUL * elem_opRem(Element_EXPR_MUL *,ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_UN * elem_cast_EXPR_POST(Element_EXPR_POST *);
   Element_EXPR_UN * elem_opAst(ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_UN * elem_opAmp(ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_UN * elem_opPlus(ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_UN * elem_opMinus(ElementAtom *,Element_EXPR_UN *);
   Element_EXPR_POST * elem_cast_EXPR_NNPOST(Element_EXPR_NNPOST *);
   Element_EXPR_POST * elem_cast_Number(ElementAtom *);
   Element_EXPR_NNPOST * elem_cast_EXPR_NNPRIM(Element_EXPR_NNPRIM *);
   Element_EXPR_NNPOST * elem_opInd(Element_EXPR_POST *,ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_EXPR_NNPOST * elem_opSelect(Element_EXPR_NNPOST *,ElementAtom *,ElementAtom *);
   Element_EXPR_NNPOST * elem_opPtrSelect(Element_EXPR_NNPOST *,ElementAtom *,ElementAtom *);
   Element_EXPR_NNPRIM * elem_cast_EXPR(ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_EXPR_NNPRIM * elem_cast_NAME(Element_NAME *);
   Element_EXPR_NNPRIM * elem_cast_NNLIT(Element_NNLIT *);
   Element_EXPR_NNPRIM * elem_opDomain(Element_ITYPE *,ElementAtom *,Element_EXPR *,ElementAtom *);
   Element_ELIST * elem_startExprList(Element_EXPR *);
   Element_ELIST * elem_extExprList(Element_ELIST *,ElementAtom *,Element_EXPR *);
   Element_NEXPR * elem_nameExpr(ElementAtom *,ElementAtom *,ElementAtom *,Element_EXPR *);
   Element_NELIST * elem_startNamedExprList(Element_NEXPR *);
   Element_NELIST * elem_extNamedExprList(Element_NELIST *,ElementAtom *,Element_NEXPR *);
   Element_ITYPE * elem_type_NAME(Element_NAME *);
   Element_ITYPE * elem_type_INAME(Element_INAME *);
   Element_NNLIT * elem_cast_null(ElementAtom *);
   Element_NNLIT * elem_cast_String(ElementAtom *);
   Element_NNLIT * elem_buildIP(ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *);
   
  private:
   
   void do_startBody();
   void do_extBody_SCOPE();
   void do_extBody_INCLUDE();
   void do_extBody_TYPE();
   void do_extBody_CONST();
   void do_extBody_STRUCT();
   void do_buildScope();
   void do_includeFile();
   void do_defType();
   void do_defConst();
   void do_startName();
   void do_extName();
   void do_relName();
   void do_absName();
   void do_dotName();
   void do_dotsName();
   void do_intName();
   void do_sintName();
   void do_uintName();
   void do_ulenName();
   void do_sint8Name();
   void do_uint8Name();
   void do_sint16Name();
   void do_uint16Name();
   void do_sint32Name();
   void do_uint32Name();
   void do_sint64Name();
   void do_uint64Name();
   void do_cast_INAME();
   void do_textName();
   void do_ipName();
   void do_namedType();
   void do_baseType();
   void do_ptrType();
   void do_arrayType();
   void do_arrayLenType();
   void do_structType();
   void do_buildStruct();
   void do_startSBody();
   void do_extSBody_TYPE();
   void do_extSBody_CONST();
   void do_extSBody_STRUCT();
   void do_extSBody_field();
   void do_extSBody_fieldVal();
   void do_cast_EXPR_ADD();
   void do_emptyExprList();
   void do_buildExprList();
   void do_buildNamedExprList();
   void do_applyEmpty();
   void do_applyNamedExprList();
   void do_cast_EXPR_MUL();
   void do_opAdd();
   void do_opSub();
   void do_cast_EXPR_UN();
   void do_opMul();
   void do_opDiv();
   void do_opRem();
   void do_cast_EXPR_POST();
   void do_opAst();
   void do_opAmp();
   void do_opPlus();
   void do_opMinus();
   void do_cast_EXPR_NNPOST();
   void do_cast_Number();
   void do_cast_EXPR_NNPRIM();
   void do_opInd();
   void do_opSelect();
   void do_opPtrSelect();
   void do_cast_EXPR();
   void do_cast_NAME();
   void do_cast_NNLIT();
   void do_opDomain();
   void do_startExprList();
   void do_extExprList();
   void do_nameExpr();
   void do_startNamedExprList();
   void do_extNamedExprList();
   void do_type_NAME();
   void do_type_INAME();
   void do_cast_null();
   void do_cast_String();
   void do_buildIP();
   
   void doRule(Action::Rule rule);
   
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
   
   Element_BODY * getBody() const { return static_cast<Element_BODY *>(stack); }
 };
 
} // namespace DDL
} // namespace CCore
 
#endif
 

