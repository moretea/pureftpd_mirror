/*    $NetBSD: glob.h,v 1.13 2001/03/16 21:02:42 christos Exp $    */

/*
 * Copyright (c) 1989, 1993
 *    The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the University of
 *    California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *    @(#)glob.h    8.1 (Berkeley) 6/2/93
 */

#ifndef __BSD_GLOB_H__
#define    __BSD_GLOB_H__ 1

typedef struct {
    unsigned long gl_maxfiles;  /* Maximum number of results */
    int gl_maxdepth;            /* Maximum depth */
    int gl_pathc;               /* Count of total paths so far. */
    int gl_matchc;              /* Count of paths matching pattern. */
    int gl_offs;                /* Reserved at beginning of gl_pathv. */
    int gl_flags;               /* Copy of flags parameter to glob. */
    char **gl_pathv;            /* List of paths matching pattern. */
    /* Copy of errfunc parameter to glob. */
    int (*gl_errfunc) (const char *, int);

    /*
     * Alternate filesystem access methods for glob; replacement
     * versions of closedir(3), readdir(3), opendir(3), stat(2)
     * and lstat(2).
     */
    void (*gl_closedir) (void *);
    struct dirent *(*gl_readdir) (void *);
    void *(*gl_opendir) (const char *);
    int (*gl_lstat) (const char *, struct stat *);
    int (*gl_stat) (const char *, struct stat *);
} glob_t;

#define    GLOB_ERR    0x0004  /* Return on error. */
#define    GLOB_NOCHECK    0x0010  /* Return pattern itself if nothing matches. */
#define    GLOB_NOSORT    0x0020  /* Don't sort. */
#define    GLOB_NOESCAPE    0x1000  /* Disable backslash escaping. */

#define    GLOB_NOSPACE    (-1)    /* Malloc call failed. */
#define    GLOB_ABORTED    (-2)    /* Unignored error. */
#define    GLOB_NOMATCH    (-3)    /* Malloc call failed. */
#define    GLOB_NOSYS    (-4)    /* Implementation does not support function. */

#define    GLOB_BRACE    0x0080  /* Expand braces ala csh. */
#define    GLOB_MAGCHAR    0x0100  /* Pattern had globbing characters. */
#define    GLOB_QUOTE    0       /* source compatibility */

#define    GLOB_ABEND    GLOB_ABORTED    /* source compatibility */

#ifdef DISABLE_GLOBBING
# define glob(A, B, C, D) (GLOB_NOSYS)
# define sglob(A, B, C, D, E, F) (GLOB_NOSYS)
# define globfree(A) (void) 0
#else
# ifndef USELESS_FOR_PUREFTPD
int glob(const char *, int, int (*)(const char *, int), glob_t *);
# endif
int sglob(char *, int, int (*)(const char *, int),
          glob_t *, unsigned long, int);
void globfree(glob_t *);
#endif

#define GLOB_PERIOD 0
#ifdef DEBUG
# include <assert.h>
# define _DIAGASSERT(X) assert(X)
#else
# define _DIAGASSERT(X) (void) 0
#endif

#endif                          /* !__GLOB_H__ */
