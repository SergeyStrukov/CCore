/* stdio.h */ 
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore_stdio_h
#define XCore_stdio_h

#ifdef __STDBUILD
#include <sysroot/usr/include/stddef.h>
#include <sysroot/usr/include/stdarg.h>
#else
#include <stddef.h>
#include <stdarg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* consts */ 

#define _IOFBF        1
#define _IOLBF        2
#define _IONBF        3

#define BUFSIZ        1024

#define EOF           (-1)

#define FOPEN_MAX     20

#define FILENAME_MAX  256

#define L_tmpnam      256

#define SEEK_CUR      1
#define SEEK_END      2
#define SEEK_SET      3

#define TMP_MAX       10000

/* types */ 

typedef unsigned long long fpos_t;

struct __std_FILE;
 
typedef struct __std_FILE FILE;

/* std streams */ 

extern FILE * __std_stdin(void);
extern FILE * __std_stdout(void);
extern FILE * __std_stderr(void);

#define stdin         (__std_stdin())
#define stdout        (__std_stdout())
#define stderr        (__std_stderr())

/* file functions */ 

extern int remove(const char *file_name);

extern int rename(const char *old_name,const char *new_name);

extern char * tmpnam(char buf[L_tmpnam]);

/* FILE functions */ 

extern FILE * tmpfile(void);

extern FILE * fopen(const char *file_name,const char *mode);

extern FILE * freopen(const char *file_name,const char *mode,FILE *file);

extern int fflush(FILE *file);

extern int fclose(FILE *file);

extern void setbuf(FILE *file,char buf[BUFSIZ]);

extern int setvbuf(FILE *file,char *buf,int buf_mode,size_t size);

/* FILE error function */ 

extern int feof(FILE *file);

extern int ferror(FILE *file);

extern void clearerr(FILE *file);

/* FILE position functions */ 

extern int fgetpos(FILE *file,fpos_t *pos);

extern long ftell(FILE *file);

extern fpos_t ftell_ext(FILE *file); /* ext function */ 

extern fpos_t fsize(FILE *file); /* ext function */ 

extern int fsetpos(FILE *file,const fpos_t *pos);

extern int fseek(FILE *file,long offset,int from_flag);

extern int fseek_ext(FILE *file,fpos_t offset,int from_flag); /* ext function */ 

extern void rewind(FILE *file);

/* FILE read/write functions */ 

extern size_t fread(void *buf,size_t elem_size,size_t elem_count,FILE *file);

extern size_t fwrite(const void *buf,size_t elem_size,size_t elem_count,FILE *file);

/* FILE io functions */ 

extern int fgetc(FILE *file);

extern char * fgets(char *buf,size_t buf_size,FILE *file);

extern int fputc(int c,FILE *file);

extern int fputs(const char *str,FILE *file);

extern int ungetc(int c,FILE *file);

extern int getc(FILE *file);

extern int putc(int c,FILE *file);

extern int getchar(void);

extern int putchar(int c);

extern char * gets(char *buf);

extern int puts(const char *str);

/* format functions */ 

extern int fprintf(FILE *file,const char *format,...);

extern int fscanf(FILE *file,const char *format,...);

extern int printf(const char *format,...);

extern int scanf(const char *format,...);

extern int sprintf(char *buf,const char *format,...);

extern int snprintf(char *buf,size_t buf_size,const char *format,...);

extern int sscanf(const char *str,const char *format,...);


extern int vfprintf(FILE *file,const char *format,va_list arg);

extern int vfscanf(FILE *file,const char *format,va_list arg);

extern int vprintf(const char *format,va_list arg);

extern int vscanf(const char *format,va_list arg);

extern int vsprintf(char *buf,const char *format,va_list arg);

extern int vsnprintf(char *buf,size_t buf_size,const char *format,va_list arg);

extern int vsscanf(const char *str,const char *format,va_list arg);

/* misc functions */ 

extern void perror(const char *str);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

