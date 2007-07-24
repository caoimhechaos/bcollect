%{
/*
 * (c) 2007, Tonnerre Lombard <tonnerre@bsdprojects.net>,
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
 * * Neither  the  name  of the  SyGroup  GmbH  nor  the name  of  its
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
 * bcollect config file parser
 */

#include <bcollect.h>
%}

%union {
	unsigned long lval;
	unsigned char *strval;
}

%token BEGINDEFL BEGINBACKUP ENDDEFL ENDBACKUP INTERVAL NAME SOURCE
%token DESTINATION SUMMARY EXCLUDELIST

%token <strval> QSTRING
%token <lval> NUMBER
%token <lval> BOOLEAN
%%

config: defaults backups

defaults: BEGINDEFL default_list ENDDEFL
	;

default_list: default
	| default_list default
	;

default: INTERVAL QSTRING NUMBER
	{ declare_interval($2, $3); };

backups: /* empty */
	| backups backup;

backup: backup_primer backup_defs backup_terminator;

backup_primer: BEGINBACKUP	{ backup_add(); };

backup_terminator: ENDBACKUP	{ backup_finalize(); };

backup_defs: backup_def
	| backup_defs backup_def;

backup_def: name_def
	| source_def
	| dest_def
	| summary_def
	| exclude_def;

name_def: NAME QSTRING		{ backup_name($2); };

source_def: SOURCE QSTRING;

dest_def: DESTINATION QSTRING;

summary_def: SUMMARY BOOLEAN;

exclude_def: EXCLUDELIST QSTRING;

%%
