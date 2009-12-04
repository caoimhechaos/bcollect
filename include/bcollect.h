/*
 * (c) 2005, Tonnerre Lombard <tonnerre@bsdprojects.net>,
 *	     BSD projects network. All rights reserved.
 *
 * Redistribution and use in source  and binary forms, with or without
 * modification, are permitted  provided that the following conditions
 * are met:
 *
 * * Redistributions of  source code  must retain the  above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this  list of conditions and the  following disclaimer in
 *   the  documentation  and/or  other  materials  provided  with  the
 *   distribution.
 * * Neither the name of the BSD  projects network nor the name of its
 *   contributors may  be used to endorse or  promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS"  AND ANY EXPRESS  OR IMPLIED WARRANTIES  OF MERCHANTABILITY
 * AND FITNESS  FOR A PARTICULAR  PURPOSE ARE DISCLAIMED. IN  NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE,  DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT  (INCLUDING NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * bcollect main header file.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif /* HAVE_INTTYPES_H */
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif /* HAVE_STDINT_H */
#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif /* HAVE_SYS_RESOURCE_H */
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif /* HAVE_SYS_PARAM_H */
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H */
#ifdef HAVE_WAIT_H
#include <wait.h>
#endif /* HAVE_WAIT_H */
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif /* HAVE_SYS_WAIT_H */
#include <stdio.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif /* HAVE_STRINGS_H */
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif /* HAVE_FCNTL_H */
#include <errno.h>
#include <time.h>
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif /* HAVE_DIRENT_H */

#ifdef HAVE_SYS_QUEUE_H
#include <sys/queue.h>
#elif defined(HAVE_NBCOMPAT_QUEUE_H)
#include <nbcompat/queue.h>
#endif
#ifdef HAVE_CLIB_QUEUE_H
#include <clib/queue.h>
#endif
#ifdef HAVE_CLIB_CLIB_H
#include <clib/clib.h>
#endif

#ifndef HAVE_FLOCK
#include <flock.h>
#endif

/*
 * Definitions
 */
#define	MAX_INTERVALS	32
#define	DEFAULT_PATH	SYSCONFDIR "/" PACKAGE_TARNAME ".conf"

/*
 * Data structures
 */
struct interval
{
	char *		name;
	unsigned long	count;
};

struct exclude
{
	struct exclude	*next, *prev;
	char		*pattern;
};

struct backup
{
	struct backup	*next, *prev;
	char		*name, *source, *dest, *preexec, *postexec;
	unsigned long	 summary:1;
	unsigned long	 ccollect:1;
	unsigned long	 manualonly:1;
	struct exclude	 excludelist;
};

/*
 * Global variables
 */
extern FILE *yyin;
extern char *file;
#ifdef YYISARRAY
extern char yytext[];
#else
extern char *yytext;
#endif
extern struct c_hashtable *intervals;
extern struct backup backups;

/*
 * Parser functions
 */
extern void init_interval(void);
extern void declare_interval(char *, int);

extern void backup_add(void);
extern void backup_name(char *);
extern void backup_finalize(void);

extern void do_backup(struct interval *, struct backup *);
extern int rmdir_recursive(const char *);

static inline void
yyerror(char *str)
{
	fprintf(stderr, "Parse error at %s near %s: %s\n", file, yytext, str);
	exit(EXIT_FAILURE);
}
