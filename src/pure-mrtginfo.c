#include <config.h>

#include "ftpd.h"

#ifdef WITH_DMALLOC
# include <dmalloc.h>
#endif

static const char *uptime(void)
{
    int f;
    ssize_t r;
    unsigned long u;
    static char buf[1025];    

    if ((f = open("/proc/uptime", O_RDONLY)) == -1) {
        return "?";
    }
    while ((r = read(f, buf, sizeof buf - 1U)) < (ssize_t) 0 && errno == EINTR);
    if (r <= (ssize_t) 0) {
        return "?";
    }
    close(f);
    u = strtoul(buf, NULL, 10);
    if (SNCHECK(snprintf(buf, sizeof buf, "%lu days, %lu:%02lu:%02lu",
                         u / 86400UL, u / 3600UL % 24UL, 
                         u / 60UL % 60UL, u % 60UL),
                sizeof buf)) {
        _exit(EXIT_FAILURE);
    }
    return buf;
}

static const char *name(void)
{
    static char buf[1025];
    
    if (gethostname(buf, sizeof buf - 1U) != 0) {
        return "?";
    }
    return buf;
}

int main(int argc, char *argv[])
{
    unsigned int d;
    unsigned short server_port = 21U;

#ifdef HAVE_SETLOCALE
# ifdef LC_MESSAGES
    (void) setlocale(LC_MESSAGES, "");
# endif
# ifdef LC_CTYPE
    (void) setlocale(LC_CTYPE, "");
# endif
# ifdef LC_COLLATE
    (void) setlocale(LC_COLLATE, "");
# endif
#endif    
    
    if (argc == 2) {
        server_port = (unsigned short) strtoul(argv[1], NULL, 10);
    }
    d = daemons(server_port);
    printf("%u\n%u\n%s\n%s\n", d, d, uptime(), name());
    
    return 0;
}
