// -*- C++ -*- Allocate exception objects.
// Copyright (C) 2001-2013 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

// This is derived from the C++ ABI for IA-64.  Where we diverge
// for cross-architecture compatibility are noted with "@@@".

#include <bits/c++config.h>
#include <cstdlib>
#if _GLIBCXX_HOSTED
#include <cstring>
#endif
#include <climits>
#include <exception>
#include "unwind-cxx.h"
#include <ext/concurrence.h>

extern "C" void *malloc_int(std::size_t);
extern "C" void free_int(void *);
extern "C" void *memset (void *, int, std::size_t);

using namespace __cxxabiv1;

extern "C" void *
__cxxabiv1::__cxa_allocate_exception(std::size_t thrown_size) _GLIBCXX_NOTHROW
{
  void *ret;

  thrown_size += sizeof (__cxa_refcounted_exception);
  ret = malloc_int (thrown_size);

  if (! ret)
    {
	std::terminate ();
    }

  // We have an uncaught exception as soon as we allocate memory.  This
  // yields uncaught_exception() true during the copy-constructor that
  // initializes the exception object.  See Issue 475.
  __cxa_eh_globals *globals = __cxa_get_globals ();
  globals->uncaughtExceptions += 1;

  memset (ret, 0, sizeof (__cxa_refcounted_exception));

  return (void *)((char *)ret + sizeof (__cxa_refcounted_exception));
}


extern "C" void
__cxxabiv1::__cxa_free_exception(void *vptr) _GLIBCXX_NOTHROW
{
    free_int ((char *)vptr - sizeof (__cxa_refcounted_exception));
}


extern "C" __cxa_dependent_exception*
__cxxabiv1::__cxa_allocate_dependent_exception() _GLIBCXX_NOTHROW
{
  __cxa_dependent_exception *ret;

  ret = static_cast<__cxa_dependent_exception*>
    (malloc_int (sizeof (__cxa_dependent_exception)));

  if (!ret)
    {
	std::terminate ();
    }

  // We have an uncaught exception as soon as we allocate memory.  This
  // yields uncaught_exception() true during the copy-constructor that
  // initializes the exception object.  See Issue 475.
  __cxa_eh_globals *globals = __cxa_get_globals ();
  globals->uncaughtExceptions += 1;

  memset (ret, 0, sizeof (__cxa_dependent_exception));

  return ret;
}


extern "C" void
__cxxabiv1::__cxa_free_dependent_exception
  (__cxa_dependent_exception *vptr) _GLIBCXX_NOTHROW
{
    free_int (vptr);
}
