/* ctype.h */ 
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2009 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore_ctype_h
#define XCore_ctype_h

enum 
 {
  __std_ctype_isupper  = 0x0001,  /* A-Z */ 
  __std_ctype_islower  = 0x0002,  /* a-z */ 
  __std_ctype_isdigit  = 0x0004,  /* 0-9 */ 
  __std_ctype_isxdigit = 0x0008,  /* 0-9 a-f A-F */ 
  
  __std_ctype_isalpha  = 0x0010,  /* upper|lower */ 
  __std_ctype_isalnum  = 0x0020,  /* alpha|digit */ 
  
  __std_ctype_isblank  = 0x0040,  /* ' ' '\t' */ 
  __std_ctype_isspace  = 0x0080,  /* ' ' '\t' '\r' '\n' '\f' '\v' */ 
  
  __std_ctype_iscntrl  = 0x0100,  /* code 0-31 127 */ 
  __std_ctype_isprint  = 0x0200,  /* code 32-126 */ 
  
  __std_ctype_isgraph  = 0x0400,  /* print\' ' */ 
  __std_ctype_ispunct  = 0x0800   /* print\space\alnum */ 
 };
 
#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned short __std_ctype_flags[257];

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus

inline int isupper(int c) { return __std_ctype_flags[c+1]&__std_ctype_isupper; }
inline int islower(int c) { return __std_ctype_flags[c+1]&__std_ctype_islower; }
inline int isdigit(int c) { return __std_ctype_flags[c+1]&__std_ctype_isdigit; }
inline int isxdigit(int c) { return __std_ctype_flags[c+1]&__std_ctype_isxdigit; }
 
inline int isalpha(int c) { return __std_ctype_flags[c+1]&__std_ctype_isalpha; }
inline int isalnum(int c) { return __std_ctype_flags[c+1]&__std_ctype_isalnum; }
 
inline int isblank(int c) { return __std_ctype_flags[c+1]&__std_ctype_isblank; }
inline int isspace(int c) { return __std_ctype_flags[c+1]&__std_ctype_isspace; }
 
inline int iscntrl(int c) { return __std_ctype_flags[c+1]&__std_ctype_iscntrl; }
inline int isprint(int c) { return __std_ctype_flags[c+1]&__std_ctype_isprint; }
 
inline int isgraph(int c) { return __std_ctype_flags[c+1]&__std_ctype_isgraph; }
inline int ispunct(int c) { return __std_ctype_flags[c+1]&__std_ctype_ispunct; }
 
inline int tolower(int c) { return (c<'A')?c:( (c>'Z')?c:( (c-'A')+'a' ) ); }
inline int toupper(int c) { return (c<'a')?c:( (c>'z')?c:( (c-'a')+'A' ) ); }
 
#else

extern int isupper(int c);
extern int islower(int c);
extern int isdigit(int c);
extern int isxdigit(int c);
 
extern int isalpha(int c);
extern int isalnum(int c);
 
extern int isblank(int c);
extern int isspace(int c);

extern int iscntrl(int c);
extern int isprint(int c);

extern int isgraph(int c);
extern int ispunct(int c);
 
extern int tolower(int c);
extern int toupper(int c);
 
#endif
 
#endif

