#ifndef _CONFIG_WIN32_H_
#define _CONFIG_WIN32_H_

#define PACKAGE "musicbrainz"
#define VERSION "3.0.0-dev"

#define SIZEOF_LONG 4

#define usleep(x) ::Sleep(x/1000)
#define strcasecmp(a,b) stricmp(a,b)
#define strncasecmp(a,b,c) strnicmp(a,b,c)
typedef int socklen_t;

#endif 
