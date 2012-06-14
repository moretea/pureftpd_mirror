/*
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 */

#include <config.h>
#define FAKECHROOT_EXCEPTION 1

#include "ftpd.h"
#include "bsd-realpath.h"
#if !defined(HAVE_REALPATH) || defined(BROKEN_REALPATH)

# ifdef WITH_DMALLOC
#  include <dmalloc.h>
# endif

# ifndef MAXSYMLINKS
#  define MAXSYMLINKS 5
# endif
# if MAXSYMLINKS > UINT_MAX
#  undef MAXSYMLINKS
#  define MAXSYMLINKS UINT_MAX
# endif

/*
 * char *realpath(const char *path, char resolved_path[MAXPATHLEN]);
 *
 * Find the real name of path, by removing all ".", ".." and symlink
 * components.  Returns (resolved) on success, or (NULL) on failure,
 * in which case the path which caused trouble is left in (resolved).
 */
char *bsd_realpath(const char *path, char *resolved)
{
    struct stat sb;
    int fd, n, rootd, serrno;
    char *p, *q, wbuf[MAXPATHLEN + 1U];
    unsigned int symlinks = 0U;
    const size_t sizeof_resolved = MAXPATHLEN;

    /* Save the starting point. */
    if ((fd = open(".", O_RDONLY)) == -1) {
        resolved[0] = '.';
        resolved[1] = 0;
        
        return NULL;
    }

    /* Convert "." -> "" to optimize away a needless lstat() and chdir() */
    if (path[0] == '.' && path[1] == '\0') {
        path = "";
    }
    
    /*
     * Find the dirname and basename from the path to be resolved.
     * Change directory to the dirname component.
     * lstat the basename part.
     *     if it is a symlink, read in the value and loop.
     *     if it is a directory, then change to that directory.
     * get the current directory name and append the basename.
     */
    {
        const size_t path_len = strlen(path) + (size_t) 1U;
        
        if (path_len > sizeof_resolved) {
#ifdef ENAMETOOLONG
            errno = ENAMETOOLONG;
#endif            
            return NULL;
        }
        memcpy(resolved, path, path_len);
    }
    
    loop:    
    if ((q = strrchr(resolved, '/')) != NULL) {
        p = q + 1;
        if (q == resolved) {
            q = (char *) "/";
        } else {
            do {
                q--;
            } while (q > resolved && *q == '/');
            q[1] = 0;
            q = resolved;
        }
        if (chdir(q) < 0) {
            goto err1;
        }
    } else {
        p = resolved;
    }

    /* Deal with the last component. */
    if (*p != '\0' && lstat(p, &sb) == 0) {
        if (S_ISLNK(sb.st_mode)) {
            if (symlinks >= MAXSYMLINKS) {
#ifdef ELOOP
                errno = ELOOP;
#endif
                goto err1;
            }
            symlinks++;
            n = readlink(p, resolved, sizeof resolved);
            if (n < 0) {
                goto err1;
            }
            resolved[n] = 0;
            goto loop;
        }
        if (S_ISDIR(sb.st_mode)) {
            if (chdir(p) < 0) {
                goto err1;
            }
            p = (char *) "";
        }
    }

    /*
     * Save the last component name and get the full pathname of
     * the current directory.
     */
    (void) strncpy(wbuf, p, sizeof wbuf);
    wbuf[sizeof wbuf - 1U] = 0;
    if (getcwd(resolved, sizeof_resolved) == NULL) {
        goto err1;
    }

    /*
     * Join the two strings together, ensuring that the right thing
     * happens if the last component is empty, or the dirname is root.
     */
    if (resolved[0] == '/' && resolved[1] == 0) {
        rootd = 1;
    } else {
        rootd = 0;
    }

    if (*wbuf) {
        if (strlen(resolved) + strlen(wbuf) + rootd + 1U > sizeof_resolved) {
#ifdef ENAMETOOLONG
            errno = ENAMETOOLONG;
#endif
            goto err1;
        }
        if (rootd == 0) {
            (void) strcat(resolved, "/");   /* flawfinder: ignore - safe */
        }
        (void) strcat(resolved, wbuf); /* flawfinder: ignore - safe, see above */
    }

    /* Go back to where we came from. */
    if (fchdir(fd) < 0) {
        serrno = errno;
        goto err2;
    }

    /* It's okay if the close fails, what's an fd more or less? */
    (void) close(fd);
    return resolved;

    err1:
    serrno = errno;
    (void) fchdir(fd);
    
    err2:
    (void) close(fd);
    errno = serrno;
    
    return NULL;
}

#endif
