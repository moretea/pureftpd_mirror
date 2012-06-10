#ifndef __OSX_EXTENSIONS_H__
#define __OSX_EXTENSIONS_H__ 1

#ifdef WITH_OSX_RENDEZVOUS

#include <DNSServiceDiscovery/DNSServiceDiscovery.h>
#include <CoreFoundation/CoreFoundation.h>

#define kServiceType CFSTR("_ftp._tcp.")
#define kMyDefaultDomain CFSTR("")
#define kPortNumberToRegister 21

/* Rendezvous */
CFStringRef gServiceName;
CFStringRef gServiceType;
UInt16 gPortNumber;
Boolean gDone;

// this function is called by ftpd.c at server startup
void doregistration(const char* name, unsigned long port);
/* EndOf RDV */

/* Notifications */
void refreshManager(void);

#endif /* WITH_OSX_RENDEZVOUS */

#endif
