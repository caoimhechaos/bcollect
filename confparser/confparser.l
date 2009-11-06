%{
/*
 * (c) 2007, Caoimhe Chaos <caoimhechaos@protonmail.com>,
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
 * bcollect config file scanner.
 */

#include <bcollect.h>
#include <y.tab.h>
%}

%state DEFAULTS BACKUP COPYIN

%%
#.*$				/* Ignore comments */;
[ \t\n]+			/* Ignore Blanks */;

<INITIAL>"Begin Defaults"	{ BEGIN DEFAULTS; return BEGINDEFL; }
<INITIAL>"Begin Backup"		{ BEGIN BACKUP; return BEGINBACKUP; }

<DEFAULTS>Interval		{ return INTERVAL; }
<DEFAULTS>\"[^\"\n]*[\"\n]	{ yylval.strval = strdup(yytext+1);
					yylval.strval[yyleng-2] = '\0';
					return QSTRING; }
<DEFAULTS>[1-9][0-9]*		{ yylval.lval = atol(yytext); return NUMBER; }
<DEFAULTS>"End Defaults"	{ BEGIN INITIAL; return ENDDEFL; }

<BACKUP>Name			{ return NAME; }
<BACKUP>Source			{ return SOURCE; }
<BACKUP>Destination		{ return DESTINATION; }
<BACKUP>Summary			{ return SUMMARY; }
<BACKUP>Exclude			{ return EXCLUDELIST; }
<BACKUP>PreExec			{ return PREEXEC; }
<BACKUP>PostExec		{ return POSTEXEC; }
<BACKUP>[1-9][0-9]*		{ return NUMBER; }
<BACKUP>\"[^\"\n]*[\"\n]	{ yylval.strval = strdup(yytext+1);
					yylval.strval[yyleng-2] = '\0';
					return QSTRING; }
<BACKUP>true|false		{ yylval.lval = strcmp(yytext, "false"); return BOOLEAN; }
<BACKUP>"End Backup"		{ BEGIN INITIAL; return ENDBACKUP; }

[^\n\t ]+			{ yyerror("Unexpected input"); }
%%
