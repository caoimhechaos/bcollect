/*
 * (c) 2005, Caoimhe Chaos <caoimhechaos@protonmail.com>,
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

#include "config.h"

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>

#ifndef HAVE_FLOCK
#include <flock.h>
#endif

/*
 * Definitions
 */
#define	MAX_INTERVALS	32
#define	DEFAULT_PATH	"/etc/bcollect.conf"
#define RSYNC_PATH	"/usr/pkg/bin/rsync"

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
	unsigned long	 summary;
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
extern struct interval intervals[MAX_INTERVALS];
extern int nintervals;
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
