
/*
 * Alternative logging formats for Pure-FTPd 
 */

#include <config.h>

#ifdef WITH_ALTLOG

# include "ftpd.h"
# include "ftpwho-update.h"
# include "globals.h"
# include "altlog.h"

# ifdef WITH_DMALLOC
#  include <dmalloc.h>
# endif

static int altlog_write(const char *str)
{
    struct flock lock;
    ssize_t left;
    
    if (altlog_fd == -1 || str == NULL || 
        (left = (ssize_t) strlen(str)) <= (ssize_t) 0) {
        return -1;
    }
    lock.l_whence = SEEK_SET;
    lock.l_start = (off_t) 0;
    lock.l_len = (off_t) 0;
    lock.l_pid = getpid();
    lock.l_type = F_WRLCK;
    while (fcntl(altlog_fd, F_SETLKW, &lock) < 0 && errno == EINTR);
    if (lseek(altlog_fd, (off_t) 0, SEEK_END) < (off_t) 0) {
        return -1;
    }
    (void) safe_write(altlog_fd, str, (size_t) left);
    lock.l_type = F_UNLCK;
    while (fcntl(altlog_fd, F_SETLK, &lock) < 0 && errno == EINTR);    
    
    return 0;
}

/* Verbose but compact log format for ftpStats */

static int altlog_writexfer_stats(const int upload,
                                  const char * const filename,
                                  const off_t size,
                                  const double duration)
{
    /*
     * <date> <start.pid> <user> <ip> <u/d> <size> <duration> <file>
     */

    const char *host_ = *host != 0 ? host : "-";
    const char *account_ = *account != 0 ? account : "-";
    char *alloca_line;
    size_t line_size;
    
    line_size = 16U /* now */ + 1U + 16U /* start */ + 1U /* . */ +
        16U /* pid */ + 1U + strlen(account_) + 1U + strlen(host_) + 1U +
        1U /* U/D */ + 1U + 16U /* size */ + 16U /* duration */ +
        strlen(filename) + +1U /* \n */ + 1U;
    if ((alloca_line = ALLOCA(line_size)) == NULL) {
        return -1;
    }
    if (!SNCHECK(snprintf(alloca_line, line_size,
                          "%llu %llx.%lx %s %s %c %llu %lu %s\n",
                          (unsigned long long) time(NULL),
                          (unsigned long long) session_start_time,
                          (unsigned long) getpid(),
                          account_, host_,
                          upload != 0 ? 'U' : 'D',
                          (unsigned long long) size,
                          (unsigned long) (duration + 0.5),
                          filename), line_size)) {
        altlog_write(alloca_line);        
    }
                          
    ALLOCA_FREE(alloca_line);
    
    return 0;
}

/* HTTPd-like common log format */

static int altlog_writexfer_clf(const int upload,
                                const char * const filename,
                                const off_t size)
{
    time_t now;
    long diff;
    int sign;
    struct tm *tm;
    char *alloca_line;
    size_t line_size;
    const char *host_ = *host != 0 ? host : "-";
    const char *account_ = *account != 0 ? account : "-";    
    char date[sizeof "13/Apr/1975:12:34:56 +0100"];
    
    if ((now = time(NULL)) == (time_t) -1 ||
        (tm = localtime(&now)) == NULL ||
        tm->tm_mon > 11 || tm->tm_mon < 0) {
        return -1;
    }    
# ifdef HAVE_STRUCT_TM_TM_GMTOFF
    diff = -(tm->tm_gmtoff) / 60L;
# elif defined(HAVE_SCALAR_TIMEZONE)
    diff = -(timezone) / 60L;    
# else
    {
        struct tm gmt;
        struct tm *t;
        int days, hours, minutes;
        
        gmt = *gmtime(&now);    
        t = localtime(&now);
        days = t->tm_yday - gmt.tm_yday;
        hours = ((days < -1 ? 24 : 1 < days ? -24 : days * 24)
                 + t->tm_hour - gmt.tm_hour);
        minutes = hours * 60 + t->tm_min - gmt.tm_min;
        diff = -minutes;
    }
# endif
    if (diff > 0L) {
        sign = '+';
    } else {
        sign = '-';
        diff = -diff;
    }
    
    if (SNCHECK(snprintf(date, sizeof date, 
                         "%02d/%s/%d:%02d:%02d:%02d %c%02ld%02ld",
                         tm->tm_mday, months[tm->tm_mon], tm->tm_year + 1900,
                         tm->tm_hour, tm->tm_min, tm->tm_sec,
                         sign, diff / 60L, diff % 60L), sizeof date)) {
        return -1;
    }
    line_size = strlen(host_) + (sizeof " - " - 1U) + strlen(account_) +
        (sizeof " [" - 1U) + (sizeof date - 1U) + (sizeof "] \"" - 1U) +
        3U /* GET / PUT */ + (sizeof " " - 1U) + strlen(filename) +
        (sizeof "\" 200 1234567890\n" - 1U) + 1U;
    if ((alloca_line = ALLOCA(line_size)) == NULL) {
        return -1;
    }
    if (!SNCHECK(snprintf(alloca_line, line_size, 
                          "%s - %s [%s] \"%s %s\" 200 %llu\n",
                          host_, account_, date, 
                          upload == 0 ? "GET" : "PUT", filename,
                          (unsigned long long) size), line_size)) {
        altlog_write(alloca_line);
    }
    ALLOCA_FREE(alloca_line);
    
    return 0;
}

static int altlog_writexfer_w3c(const int upload,
                                const char * const filename,
                                const off_t size,
                                const double duration)
{
    /*
     * <date> <time> <ip> "[]sent" <file> "226" <user>
     * date time c-ip cs-method cs-uri-stem sc-status cs-username
     */

    time_t now;
    struct tm *tm;
    struct tm gmt;
    const char *host_ = *host != 0 ? host : "-";
    const char *account_ = *account != 0 ? account : "-";
    char *alloca_line;
    size_t line_size;

    (void) duration;
    if ((now = time(NULL)) == (time_t) -1 ||
        (tm = localtime(&now)) == NULL ||
        tm->tm_mon > 11 || tm->tm_mon < 0) {
        return -1;
    }
    gmt = *gmtime(&now);

    line_size = (sizeof "13-04-1975 12:34:56 " - 1U) +
        strlen(host_) + 1U + (sizeof "[]created" - 1U) + 1U +
        strlen(filename) + 1U + (sizeof "226" - 1U) +
        strlen(account_) + 1U + 42U + 1U /* \n */ + 1U;

    if ((alloca_line = ALLOCA(line_size)) == NULL) {
        return -1;
    }
    if (!SNCHECK(snprintf(alloca_line, line_size,
                          "%d-%02d-%02d %02d:%02d:%02d %s []%s %s 226 %s %llu\n",
                          gmt.tm_year + 1900, gmt.tm_mon + 1, gmt.tm_mday,
                          gmt.tm_hour, gmt.tm_min, gmt.tm_sec,
                          host_, (upload != 0 ? "created" : "sent"),
                          filename, account, (unsigned long long) size), line_size)) {
        altlog_write(alloca_line);
    }

    ALLOCA_FREE(alloca_line);

    return 0;
}

int altlog_write_w3c_header(void)
{
    time_t now;
    struct tm *tm;
    struct tm gmt;
    char *alloca_line;
    size_t line_size;

    if ((now = time(NULL)) == (time_t) -1 ||
        (tm = localtime(&now)) == NULL ||
        tm->tm_mon > 11 || tm->tm_mon < 0) {
        return -1;
    }
    gmt = *gmtime(&now);
    line_size = sizeof "#Date: 001975-04-13 12:34:56\n";   /* be year-999999 compliant :) */
    if ((alloca_line = ALLOCA(line_size)) == NULL) {
        return -1;
    }

    altlog_write("#Software: Pure-FTPd " VERSION "\n");
    altlog_write("#Version: 1.0\n");

    if (!SNCHECK(snprintf(alloca_line, line_size,
                          "#Date: %04d-%02d-%02d %02d:%02d:%02d\n",
                          gmt.tm_year + 1900, gmt.tm_mon + 1, gmt.tm_mday,
                          gmt.tm_hour, gmt.tm_min, gmt.tm_sec),
                          line_size)) {
        altlog_write(alloca_line);
    }

    altlog_write("#Fields: date time c-ip cs-method cs-uri-stem sc-status cs-username sc-bytes\n");

    ALLOCA_FREE(alloca_line);

    return 0;
}

/* 
 * We should define a structure of function pointers, 
 * and associate a structure with each logging type in AltLogPrefixes.
 * But yet we only have *three* logging methods, and the code would be
 * complicated for nothing. So let's stick with simple tests for now. -j.
 */

int altlog_writexfer(const int upload,
                     const char * const filename,
                     const off_t size,
                     const double duration)
{
    switch (altlog_format) {
    case ALTLOG_NONE:
        return 0;
    case ALTLOG_CLF:
        return altlog_writexfer_clf(upload, filename, size);
    case ALTLOG_STATS:
        return altlog_writexfer_stats(upload, filename, size, duration);
    case ALTLOG_W3C:
        return altlog_writexfer_w3c(upload, filename, size, duration);
    }    
    return -1;
}

#endif
