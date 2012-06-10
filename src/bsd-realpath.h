#ifndef __FAKEREALPATH_H__
#define __FAKEREALPATH_H__ 1

#if defined(__svr4__) && defined(__sun__) /* Solaris 2 aka SunOS 5 */
# define BROKEN_REALPATH 1
#endif
#if defined(__atheos__)
# define BROKEN_REALPATH 1
#endif

#if !defined(HAVE_REALPATH) || defined(BROKEN_REALPATH)
char *bsd_realpath(const char *path, char *resolved);
# define realpath(A, B) bsd_realpath(A, B)
#endif

#endif
