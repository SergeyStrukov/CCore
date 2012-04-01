/* errno.h */ 
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

#ifndef XCore_errno_h
#define XCore_errno_h

#ifdef __cplusplus
extern "C" {
#endif

/* consts */ 

#define EDOM           1
#define EILSEQ         2
#define ERANGE         3

#define ENOFILE        4
#define ENOPATH        5
#define ENOACCESS      6

#define ENOMEM         7
#define EBADARG        8
#define ENOTSUPPORTED  9

#define EIOFAULT       10
#define EFAULT         11

#define EUNKNOWN       12

/* Unused -- required to build cross-compiler */ 

#define EAFNOSUPPORT    100
#define EADDRINUSE      101
#define EADDRNOTAVAIL   102
#define EISCONN         103
#define E2BIG           104
#define EBADF           106
#define EBADMSG         107
#define EPIPE           108
#define ECONNABORTED    109
#define EALREADY        110
#define ECONNREFUSED    111
#define ECONNRESET      112
#define EXDEV           113
#define EDESTADDRREQ    114
#define EBUSY           115
#define ENOTEMPTY       116
#define ENOEXEC         117
#define EEXIST          118
#define EFBIG           119
#define ENAMETOOLONG    120
#define ENOSYS          121
#define EHOSTUNREACH    122
#define EIDRM           123
#define ENOTTY          124
#define EINTR           125
#define EINVAL          126
#define ESPIPE          127
#define EIO             128
#define EISDIR          129
#define EMSGSIZE        130
#define ENETDOWN        131
#define ENETRESET       132
#define ENETUNREACH     133
#define ENOBUFS         134
#define ECHILD          135
#define ENOLINK         136
#define ENOLCK          137
#define ENODATA         138
#define ENOMSG          139
#define ENOPROTOOPT     140
#define ENOSPC          141
#define ENOSR           142
#define ENXIO           143
#define ENODEV          144
#define ENOENT          145
#define ESRCH           146
#define ENOTDIR         147
#define ENOTSOCK        148
#define ENOSTR          149
#define ENOTCONN        150
#define ENOTSUP         151
#define ECANCELED       152
#define EINPROGRESS     153
#define EPERM           154
#define EOPNOTSUPP      155
#define EWOULDBLOCK     156
#define EOWNERDEAD      157
#define EACCES          158
#define EPROTO          159
#define EPROTONOSUPPORT 160
#define EROFS           161
#define EDEADLK         162
#define EAGAIN          163
#define ENOTRECOVERABLE 164
#define ETIME           165
#define ETXTBSY         166
#define ETIMEDOUT       167
#define ENFILE          168
#define EMFILE          169
#define EMLINK          170
#define ELOOP           171
#define EOVERFLOW       172
#define EPROTOTYPE      173

/* __std_errno() */ 

extern int * __std_errno(void);

/* errno */ 

#define errno (*__std_errno())

#ifdef __cplusplus
} // extern "C"
#endif

#endif




