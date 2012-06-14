/* getopt_long and getopt_long_only entry points for GNU getopt.
   Copyright (C) 1987,88,89,90,91,92,93,94,96,97,98
     Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <config.h>

#if !defined(NO_GETOPT_LONG) && !defined(HAVE_GETOPT_LONG)
#include "ftpd.h"
#ifdef _LIBC
# undef _LIBC
#endif
#ifdef _
# undef _
#endif
#define _(X) X
#include "gnu-getopt.h"

int
getopt_long(int argc,
            char *const *argv,
            const char *options,
            const struct option *long_options, int *opt_index)
{
    return _pure_getopt_internal(argc, argv, options, long_options,
                                 opt_index, 0);
}

/* Like getopt_long, but '-' as well as '--' can indicate a long option.
   If an option that starts with '-' (not '--') doesn't match a long option,
   but does match a short option, it is parsed as a short option
   instead.  */

int
getopt_long_only(int argc,
                 char *const *argv,
                 const char *options,
                 const struct option *long_options, int *opt_index)
{
    return _pure_getopt_internal(argc, argv, options, long_options,
                                 opt_index, 1);
}

#else
extern signed char v6ready;
#endif
