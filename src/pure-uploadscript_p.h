#ifndef __PURE_UPLOADSCRIPT_P_H__
#define __PURE_UPLOADSCRIPT_P_H__ 1

# if !defined(NO_GETOPT_LONG) && !defined(HAVE_GETOPT_LONG)
#  include "gnu-getopt.h"
# else
#  ifdef HAVE_GETOPT_H
#    include <getopt.h>
#  endif
# endif
# ifdef HAVE_SYS_WAIT_H
#  include <sys/wait.h>
# endif
# ifndef WEXITSTATUS
#  define WEXITSTATUS(st) ((unsigned) (st) >> 8)
# endif
# ifndef WIFEXITED
#  define WIFEXITED(st) (((st) & 0xff) == 0)
# endif

#ifndef WHOMAXLEN
# define WHOMAXLEN 127
#endif

static const char *GETOPT_OPTIONS =
    "Bg:"
# ifndef NO_GETOPT_LONG
    "h"
# endif
    "r:u:";

#ifndef NO_GETOPT_LONG
static struct option long_options[] = {
    { "daemonize", 0, NULL, 'B' },
    { "gid", 1, NULL, 'g' },
# ifndef NO_GETOPT_LONG
    { "help", 0, NULL, 'h' },
# endif
    { "run", 1, NULL, 'r' },
    { "uid", 1, NULL, 'u' },
    { NULL, 0, NULL, 0 }    
};
#endif

static signed char daemonize;
static uid_t uid;
static gid_t gid;
static const char *script;

#endif
