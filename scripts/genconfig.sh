#!/bin/sh
#
# (c) 2007, Tonnerre Lombard <tonnerre@bsdprojects.net>,
#	    BSD projects network. All rights reserved.
#
# Redistribution and use  in source and binary forms,  with or without
# modification, are  permitted provided that  the following conditions
# are met:
#
# * Redistributions  of source  code must  retain the  above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form  must reproduce the above copyright
#   notice, this  list of conditions  and the following  disclaimer in
#   the  documentation  and/or   other  materials  provided  with  the
#   distribution.
# * Neither the name of  the BSD projects network  nor the name of its
#   contributors may  be used to  endorse or promote  products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED  BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS FOR A  PARTICULAR PURPOSE ARE DISCLAIMED. IN  NO EVENT SHALL
# THE  COPYRIGHT  OWNER OR  CONTRIBUTORS  BE  LIABLE  FOR ANY  DIRECT,
# INDIRECT, INCIDENTAL,  SPECIAL, EXEMPLARY, OR  CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT  NOT LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
# SERVICES; LOSS  OF USE, DATA, OR PROFITS;  OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY  THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT  LIABILITY,  OR  TORT  (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
# ARISING IN ANY WAY OUT OF  THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

rm -f config.h
touch config.h

cat << EOT > testprog.c
int flock(int, int);

int main(void)
{
	int r = flock(0,0);
	return 0;
}
EOT
"${CC}" ${CFLAGS} ${LDFLAGS} -o testprog -s testprog.c
if [ "$?" -eq "0" ]
then
	echo '#define HAVE_FLOCK 1' >> config.h
else
	echo '#undef HAVE_FLOCK' >> config.h
fi
rm testprog testprog.c

cat << EOT > testparser.l
%%
.	|
\n	{ }
%%
EOT
${LEX} testparser.l
if grep -q YYISARRAY lex.yy.c
then
	echo '#define YYISARRAY 1' >> config.h
else
	echo '#undef YYISARRAY' >> config.h
fi
rm -f testparser.y testparser.c lex.yy.c

if [ -d '../{arch}' ]
then
	wd=`pwd`
	cd ..
	tla tree-version |	\
		awk -F'--' '{ print "#define BCOLLECT_VERSION \"" $4 "\"" }' \
		>> include/config.h
	tla tree-version |	\
		awk -F'--' '{ print "#define BCOLLECT_BRANCH \"" $3 "\"" }' \
		>> include/config.h
	cd "${wd}"
fi

if grep -q 'BCOLLECT_VERSION' config.h
then
	:
else
	if [ -f '../ChangeLog' ]
	then
		grep 'bcollect--' ../ChangeLog | head -1 |		\
			awk -F'--' '{ print "#define BCOLLECT_VERSION \"" $3 "\"" }' \
			>> config.h
		grep 'bcollect--' ../ChangeLog | head -1 |		\
			awk -F'--' '{ print "#define BCOLLECT_BRANCH \"" $2 "\"" }' \
			>> config.h
	else
		echo '#define BCOLLECT_VERSION "0.0"'
		echo '#define BCOLLECT_BRANCH "unknown"'
	fi
fi

uname -sr | awk '{ print "#define BCOLLECT_OSNAME \"" $1 " " $2 "\"" }'	\
	>> config.h

exit 0
