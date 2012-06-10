#include <config.h>

#ifndef FTPWHO
#include <stdio.h>

int main(void)
{
    puts("Please compile the server with --with-ftpwho\n"
         "to use this feature. Thank you.");
    
    return 0;
}
#else

# include "ftpd.h"
# include "dynamic.h"
# include "ftpwho-update.h"
# if !defined(NO_GETOPT_LONG) && !defined(HAVE_GETOPT_LONG)
#  include "gnu-getopt.h"
# else
#  ifdef HAVE_GETOPT_H
#    include <getopt.h>
#  endif
# endif

# ifdef WITH_DMALLOC
#  include <dmalloc.h>
# endif

int mmap_fd = -1;
static signed char html_raw;
static signed char html_cgi;
static signed char verbose;
static signed char dont_resolve_ip;
static struct flock lock;

void ftpwho_unlock(void) 
{
    lock.l_type = F_UNLCK;
    while (fcntl(mmap_fd, F_SETLK, &lock) < 0) {
        if (errno != EINTR) {
            return;
        }    
    }
}

void ftpwho_lock(void)
{
    lock.l_type = F_RDLCK;
    while (fcntl(mmap_fd, F_SETLKW, &lock) < 0) {
        if (errno != EINTR) {
            return;
        }    
    }    
}

static RETSIGTYPE sigfpe(int sig)
{
    (void) sig;
    fprintf(stderr, "* Arithmetic exception *\n\n"
            "Please report what you were doing when it happened.\n"
            "You know, the author of this program is not very good\n"
            "at mathematics :)\n");
    exit(EXIT_FAILURE);
}

static RETSIGTYPE sigsegv(int sig)
{
    (void) sig;
    fprintf(stderr, "* This version of pure-ftpwho is not compatible *\n"
                    "* with the version of the server.               *\n"
                    "* Please reinstall properly, and try again.     *\n");
    exit(EXIT_FAILURE);
}

static void fixlimits(void)
{
#ifdef HAVE_SETRLIMIT
    static struct rlimit lim;
    
    lim.rlim_max = lim.rlim_cur = MAX_CPU_TIME;
    setrlimit(RLIMIT_CPU, &lim);
    lim.rlim_max = lim.rlim_cur = MAX_DATA_SIZE;
    setrlimit(RLIMIT_DATA, &lim);
# ifndef DEBUG
    lim.rlim_max = lim.rlim_cur = 0;
    setrlimit(RLIMIT_CORE, &lim);
# endif
#endif
}

void logfile(const int facility, const char *format, ...)
{
    va_list va;
    
    (void) facility;    
    va_start(va, format);
    vfprintf(stderr, format, va);
    fprintf(stderr, "\n");
    va_end(va);
}

static inline int checkproc(const pid_t proc)
{    
    return kill(proc, 0) == 0;
}

/* Text output */

static void text_output_header(void)
{
    if (verbose == 0) {
        puts("\n"
"+------+---------+-------+------+-------------------------------------------+\n"
"| PID  |  Login  |For/Spd| What |                 File/IP                   |\n"
"+------+---------+-------+------+-------------------------------------------+");    
    } else {
        puts("\n"
"+------+---------+-------+------+-------------------------------------------+\n"
"| PID  |  Login  |For/Spd| What |     File/Remote IP/Size(Kb)/Local IP      |\n"
"+------+---------+-------+------+-------------------------------------------+");
    }
}

static void text_output_line(const pid_t pid, const char * const account,
                             const unsigned long since,
                             const unsigned long xfer_since,
                             const char * const state,
                             const char * const filename,
                             const char * const hbuf,
                             const char * const local_hbuf,
                             const char * const local_port,
                             const off_t restartat,
                             const off_t total_size,
                             const off_t current_size)
{
    unsigned long bandwidth = 0UL;    
    long double pct;
    int pcti = 0;

    if (current_size > (off_t) 0 && current_size > restartat) {
        if (xfer_since > 0UL) {
            bandwidth = (unsigned long) ((current_size - restartat) / xfer_since);
        }         
        if ((long double) total_size > 0.0L) {
            pct = ((long double) current_size * 100.0) / (long double) total_size;
            pcti = (int) (pct + 0.5L);
            if (pcti > 100) {
                pcti = 100;           /* should never happen */
            }
        }
    }             
    printf("|%5lu | %-8s| %02lu:%02lu | %s | %-42s|\n",
           (unsigned long) pid, account, 
           (since / 60UL) / 60UL, (since / 60UL) % 60UL,
           state, filename);
    printf("|  ''  |    ''   |");
    if (bandwidth > 0UL) {
        if (bandwidth < 1024UL) {
            printf("%4lub/s|", bandwidth);
        } else {
            bandwidth /= 1024UL;
            if (bandwidth < 1024UL) {
                printf("%4luK/s|", bandwidth);
            } else {
                bandwidth /= 1024UL;
                if (bandwidth < 1024UL) {
                    printf("%4luM/s|", bandwidth);
                } else {
                    bandwidth /= 1024UL;
                    if (bandwidth < 1024UL) {
                        printf("%4luG/s|", bandwidth);
                    } else {
                        printf("   ''  |");
                    }                    
                }
            }    
        }
    } else {
        printf("   ''  |");
    }
    if (pcti > 0) {
        printf(" %3d%% |", pcti);
    } else {
        printf("  ''  |");
    }
    printf(" ->%39.39s |\n", hbuf);
    if (verbose != 0) {
        if (current_size > 0) {
            if (total_size > 0) {
                printf("|  ''  |    ''   |       |      | Total size:%9llu Transfered:%9llu |\n",
                       (unsigned long long) (total_size / 1024),
                       (unsigned long long) (current_size / 1024));
            } else {
                printf("|  ''  |    ''   |       |      | Transfered: %-29llu |\n",
                       (unsigned long long) (current_size / 1024));
            }
        }
        printf("|  ''  |    ''   |       |      | <-%33.33s:%-5.5s |\n",
               local_hbuf, local_port);
    }
    puts("+------+---------+-------+------+-------------------------------------------+");
}

static void text_output_footer(void)
{
    puts("");
}

/* HTML output */

static void html_output_header(void)
{
    if (html_cgi != 0) {
        puts("Content-Type: text/html\n");
    }
    if (html_raw == 0) {
        puts("<!DOCTYPE html PUBLIC \"-//W3C/DTD XHTML 1.0 Transitional//EN\" "
             "\"DTD/xhtml1-transitional.dtd\">\n"
             "<html>\n"
             "<title>Pure-FTPd server status</title>\n"
             "<body bgcolor=\"#ffffff\" text=\"#000000\">\n");
        puts("<div align=\"center\">\n");
    }
    puts("<table width=\"100%\" cellspacing=\"4\" border=\"2\" cellpadding=\"4\">");
    puts("<th>PID</th><th>Account</th><th>Time</th><th>State</th>"
         "<th>File name</th><th>Remote host</th><th>Kbytes</th><th>Local host</th>");
}

static void html_output_line(const pid_t pid, const char * const account,
                             const unsigned long since,
                             const unsigned long xfer_since,
                             const char * const state,
                             const char * const filename,
                             const char * const hbuf,
                             const char * const local_hbuf,
                             const char * const local_port,
                             const off_t restartat,
                             const off_t total_size,
                             const off_t current_size)
{    
    puts("<tr valign=\"middle\">");
    printf("<td>%lu</td>"
           "<td>%s</td>"
           "<td>%02lu:%02lu</td>"
           "<td>%s</td>"
           "<td>%s</td>"
           "<td>%s</td>\n",
           (unsigned long) pid, 
           *account == 0 ? "&nbsp;" : account,
           (since / 60UL) / 60UL, (since / 60UL) % 60UL, state, 
           *filename == 0 ? "&nbsp;" : filename, 
           hbuf);
    if (current_size > (off_t) 0) {
        unsigned long bandwidth;
        
        if (xfer_since > 0UL && current_size > restartat) {
            bandwidth = (unsigned long) ((current_size - restartat) /
                                         (xfer_since * 1024UL));
        } else {
            bandwidth = 0UL;
        }        
        if ((long double) total_size > 0.0L) {
            long double pct;
            int pcti;
                
            pct = ((long double) current_size * 100.0L) / (long double) total_size;
            pcti = (int) (pct + 0.5L);
            if (pcti > 100) {
                pcti = 100;           /* should never happen */
            }
            printf("<td>%llu/%llu (%d%% - %lu Kb/s)</td>\n",
                   (unsigned long long) (current_size / 1024),
                   (unsigned long long) (total_size / 1024), 
                   pcti, bandwidth);
        } else {
            printf("<td>%llu (%lu Kb/s)</td>\n",
                   (unsigned long long) (current_size / 1024),
                   bandwidth);
        }
    } else {
        puts("<td>&nbsp;</td>");
    }
    printf("<td>%s:%s</td>\n", local_hbuf, local_port);
    puts("</tr>");
}

static void html_output_footer(void)
{
    puts("</table>");
    if (html_raw == 0) {
        puts("\n</div>\n");
        puts("\n</body>\n</html>");
    }
}

/* XML output */

static const char *xml_escaped(const char * const s_)
{
    register const unsigned char *s = (const unsigned char *) s_;        
    static char buf[1024];
    register char *bufpnt = buf;    
    
    if (strlen(s_) >= sizeof buf) {
        return "*";
    }
    while (*s != 0U) {
        if (*s < 32U || *s > 127U || *s == '"') {
            *bufpnt = '?';
        } else {
            *bufpnt = (char) *s;
        }
        bufpnt++;
        s++;
    }
    *bufpnt = 0;
    
    return buf;
}

static void xml_output_header(void)
{
    puts("<?xml version=\"1.0\" ?>\n\n"
         "<status>");
}

static void xml_output_line(const pid_t pid, const char * const account,
                            const unsigned long since,
                            const unsigned long xfer_since,
                            const char * const state,
                            const char * const filename,
                            const char * const hbuf,
                            const char * const local_hbuf,
                            const char * const local_port,
                            const off_t restartat,                            
                            const off_t total_size,
                            const off_t current_size)
{
    printf("  <client");
    printf(" pid=\"%lu\"", (unsigned long) pid);
    printf(" account=\"%s\"", xml_escaped(account));
    printf(" time=\"%lu\"", since);
    printf(" state=\"%s\"", state);
    printf(" file=\"%s\"", xml_escaped(filename));
    printf(" host=\"%s\"", xml_escaped(hbuf));
    printf(" localhost=\"%s\"", xml_escaped(local_hbuf));
    printf(" localport=\"%s\"", xml_escaped(local_port));
    if (current_size > (off_t) 0) {
        unsigned long bandwidth;
        long double pct;
        int pcti;        
        
        if (xfer_since > 0UL && current_size > restartat) {
            bandwidth = (unsigned long) ((current_size - restartat) / xfer_since);
        } else {
            bandwidth = 0UL;
        }        
        if ((long double) total_size > 0.0L) {
            pct = ((long double) current_size * 100.0L) / (long double) total_size;
            pcti = (int) (pct + 0.5L);
            if (pcti > 100) {
                pcti = 100;           /* should never happen */
            }
            printf(" resume=\"%llu\"", (unsigned long long) restartat);
            printf(" current_size=\"%llu\"", (unsigned long long) current_size);
            printf(" total_size=\"%llu\"", (unsigned long long) total_size);
            printf(" percentage=\"%d\"", pcti);
            printf(" bandwidth=\"%lu\"", bandwidth);
        } else {
            printf(" resume=\"%llu\"", (unsigned long long) restartat);
            printf(" current_size=\"%llu\"", (unsigned long long) current_size);
            printf(" bandwidth=\"%lu\"", bandwidth);            
        }
    }
    puts(" />");
}

static void xml_output_footer(void)
{
    puts("</status>");
}

/* Shell output */

static const char *shell_escaped(const char * const s_)
{
    register const unsigned char *s = (const unsigned char *) s_;        
    static char buf[2048];
    const char * const bufend = &buf[sizeof buf];
    register char *bufpnt = buf;    
    
    if (strlen(s_) >= sizeof buf) {
        return "-";
    }
    while (*s != 0U) {
        if (*s < 32U) {
            *bufpnt = '_';
        } else if (*s == '|') {
            *bufpnt++ = '\\';
            if (bufpnt == bufend) {
                return "-";
            }
            *bufpnt = '|';
        } else {
            *bufpnt = (char) *s;
        }
        bufpnt++;
        if (bufpnt == bufend) {
            return "-";
        }
        s++;
    }
    *bufpnt = 0;
    
    return buf;
}

static void shell_output_header(void)
{
}

static void shell_output_line(const pid_t pid, const char * const account,
                              const unsigned long since,
                              const unsigned long xfer_since,
                              const char * const state,
                              const char * const filename,
                              const char * const hbuf,
                              const char * const local_hbuf,
                              const char * const local_port,
                              const off_t restartat,                              
                              const off_t total_size,
                              const off_t current_size)
{
    unsigned long bandwidth = 0UL;
    long double pct;
    int pcti = 0;        
    
    if (current_size > (off_t) 0) {        
        if (xfer_since > 0UL && current_size > restartat) {
            bandwidth = (unsigned long) ((current_size - restartat) /
                                         (xfer_since * 1024UL));
        }         
        if ((long double) total_size > 0.0L) {
            pct = ((long double) current_size * 100.0L) / (long double) total_size;
            pcti = (int) (pct + 0.5L);
            if (pcti > 100) {
                pcti = 100;           /* should never happen */
            }
        }
    }         
    printf("%lu|", (unsigned long) pid);
    printf("%s|", shell_escaped(account));
    printf("%lu|", since);
    printf("%s|", shell_escaped(state));
    printf("%s|", shell_escaped(filename));
    printf("%s|", shell_escaped(hbuf));
    printf("%s|", shell_escaped(local_hbuf));
    printf("%s|", shell_escaped(local_port));
    printf("%llu|", (unsigned long long) (current_size / 1024));
    printf("%llu|", (unsigned long long) (total_size / 1024));
    printf("%d|", pcti);
    printf("%lu\n", bandwidth);
}

static void shell_output_footer(void)
{
}

/* function pointers */

static void (*output_header)(void) = text_output_header;
static void (*output_line)(const pid_t pid, const char * const account,
                           const unsigned long since, 
                           const unsigned long xfer_since,
                           const char * const state,
                           const char * const filename,
                           const char * const hbuf,
                           const char * const local_hbuf,
                           const char * const local_port,
                           const off_t restartat,                           
                           const off_t total_size,
                           const off_t current_size) = text_output_line;
static void (*output_footer)(void) = text_output_footer;

/* Back to life */

static void help(void)
{
    puts("\nUsage :\n\n"
         "-c : this program is called by a web server (CGI mode)\n"
         "-h : help\n"
         "-H : don't resolve host names, only show IP addresses\n"
         "-n : synonym for -H\n"
         "-s : easily parsable output for shell scripts\n"
         "     format is :\n"
         "     pid|acct|time|state|file|peer|local|port|current|total|%|bandwidth\n"
         "-v : output verbose ASCII\n"         
         "-w : output HTML page (web mode)\n"
         "-W : output HTML page without header/footer (embedded mode)\n"
         "-x : output XML data\n");
    exit(EXIT_SUCCESS);
}

static int closedesc_but1(void)
{
    int fodder;
    
    (void) close(0);
    if ((fodder = open("/dev/null", O_RDONLY)) == -1) {
        return -1;
    }
    (void) dup2(fodder, 0);
    if (fodder > 0) {
        (void) close(fodder);
    }
    if (fcntl(1, F_GETFD) == -1) {
        return -1;
    }
    if (fcntl(2, F_GETFD) != -1) {
        if ((fodder = open("/dev/null", O_WRONLY)) == -1) {
            return -1;
        }
        (void) dup2(fodder, 2);
        if (fodder > 2) {
            (void) close(fodder);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    FTPWhoEntry *scanned_entry;
    int locked;
    int delete_file;
    const char *state;
    time_t now;
    int fodder;

#ifndef NON_ROOT_FTP
    if (geteuid() != (uid_t) 0) {
        puts("You must be root to run this. Sorry.");
        return 1;
    }
#endif
    if (argc < 0) {
        return -1;
    }
    if (closedesc_but1() < 0) {
        return -2;
    }
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
    
    fixlimits();
# ifdef SIGFPE
    signal(SIGFPE, sigfpe);
# endif
# ifdef SIGSEGV
    signal(SIGSEGV, sigsegv);
# endif
    
    if (getenv("GATEWAY_INTERFACE") != NULL) {
        html_cgi = html_raw = 1;
        output_header = html_output_header;
        output_line = html_output_line;            
        output_footer = html_output_footer;        
    }
    while ((fodder = getopt(argc, argv, "CchHnsvwWx")) != -1) {
        switch(fodder) {
        case 'h' :
            help();
            /* doesn't return */
        case 'n' :
        case 'H' :
            dont_resolve_ip++;
            break;
        case 'C' :
        case 'c' :
            html_cgi++;
        case 'W' :
            html_raw++;
        case 'w' :
            output_header = html_output_header;
            output_line = html_output_line;            
            output_footer = html_output_footer;
            break;
        case 's' :
            output_header = shell_output_header;
            output_line = shell_output_line;            
            output_footer = shell_output_footer;
            break;            
        case 'x' :
            output_header = xml_output_header;
            output_line = xml_output_line;            
            output_footer = xml_output_footer;
            break;            
        case 'v' :
            verbose++;
            break;
        case '?' :
            help();
        }
    }    
    now = time(NULL);
    if (chdir(SCOREBOARD_PATH) != 0 ||
        (dir = opendir(".")) == NULL) {
        fprintf(stderr, "Unable to open the ftpwho scoreboard.\n"
                "Make sure that the [" SCOREBOARD_PATH "/] directory exists,\n"
                "Or wait until a client connects, so that it gets\n"
                "automatically created. This message doesn't mean that your\n"
                "server didn't start properly. It probably just means that\n"
                "you are running it with ftpwho for the first time.\n");
        return -1;
    }
    lock.l_whence = SEEK_SET;
    lock.l_start = (off_t) 0;
    lock.l_len = (off_t) 0;
    lock.l_pid = getpid();    
    output_header();
    while ((entry = readdir(dir)) != NULL) {
        mmap_fd = -1;
        locked = 0;
        delete_file = 0;
        scanned_entry = NULL;
        if (strncmp(entry->d_name, SCOREBOARD_PREFIX,
                    sizeof SCOREBOARD_PREFIX - 1U) != 0) {
            goto nextone;
        }
        if ((mmap_fd = open(entry->d_name, O_RDWR | O_NOFOLLOW)) == -1) {
            goto nextone;
        }
        if (fstat(mmap_fd, &st) != 0 || !S_ISREG(st.st_mode) ||
            (st.st_mode & 0600) != 0600 || 
            st.st_size != (off_t) sizeof (FTPWhoEntry) ||
#ifdef NON_ROOT_FTP
            st.st_uid != geteuid()
#else
            st.st_uid != (uid_t) 0
#endif
            ) {
            goto nextone;
        }
        ftpwho_lock();
        locked++;
        if ((scanned_entry = (FTPWhoEntry *) mmap(NULL, sizeof (FTPWhoEntry),
                                                  PROT_READ, 
                                                  MAP_SHARED | MAP_FILE, 
                                                  mmap_fd, (off_t) 0)) == NULL) {
            goto nextone;
        }
        if (checkproc(scanned_entry->pid) == 0) {
            /* still in the scoreboard, but no more process */
            delete_file++;
            goto nextone;
        }        
        if (scanned_entry->state != FTPWHO_STATE_FREE) {
            unsigned long since;
            unsigned long xfer_since;
            char local_port[NI_MAXSERV];
            char local_hbuf[NI_MAXHOST];            
            char hbuf[NI_MAXHOST];

            switch (scanned_entry->state) {
            case FTPWHO_STATE_IDLE :
                state = "IDLE";
                break;
            case FTPWHO_STATE_DOWNLOAD :
                state = " DL ";
                break;
            case FTPWHO_STATE_UPLOAD :
                state = " UL ";
                break;
            default :
                state = "ERR!";
            }
            if (scanned_entry->date < now) {
                since = (unsigned long) (now - scanned_entry->date);
            } else {
                since = 0UL;
            }
            if (scanned_entry->xfer_date > (time_t) 0 &&
                scanned_entry->xfer_date < now) {
                xfer_since = (unsigned long) (now - scanned_entry->xfer_date);
            } else {
                xfer_since = 0UL;
            }
            if (getnameinfo((struct sockaddr *) &scanned_entry->addr,
                            STORAGE_LEN(scanned_entry->addr),
                            hbuf, sizeof hbuf, NULL, (size_t) 0U,
                            dont_resolve_ip != 0 ? NI_NUMERICHOST : 0) != 0 ||
                getnameinfo((struct sockaddr *) &scanned_entry->local_addr,
                            STORAGE_LEN(scanned_entry->addr),
                            local_hbuf, sizeof local_hbuf,
                            local_port, sizeof local_port,
                            dont_resolve_ip != 0 ?
                            (NI_NUMERICHOST | NI_NUMERICSERV) :
                            NI_NUMERICSERV) != 0) {
                goto nextone;
            }
            output_line(scanned_entry->pid, scanned_entry->account,
                        since, xfer_since, state, scanned_entry->filename, 
                        hbuf, local_hbuf, local_port,
                        (scanned_entry->restartat <= 
                         scanned_entry->download_current_size) ?
                        scanned_entry->restartat : (off_t) 0,
                        (scanned_entry->state == FTPWHO_STATE_DOWNLOAD) ?
                        scanned_entry->download_total_size : (off_t) 0,
                        (scanned_entry->state == FTPWHO_STATE_DOWNLOAD ||
                         scanned_entry->state == FTPWHO_STATE_UPLOAD) ?
                        scanned_entry->download_current_size : (off_t) 0);
        }
        nextone:
        if (locked != 0 && mmap_fd != -1) {
            ftpwho_unlock();
        }
        if (scanned_entry != NULL) {
            (void) munmap((void *) scanned_entry, sizeof (FTPWhoEntry));
        }
        if (mmap_fd != -1) {
            close(mmap_fd);
        }
        if (delete_file != 0) {
            unlink(entry->d_name);
        }
    }
    
    output_footer();
    
    return 0;
}

#endif
