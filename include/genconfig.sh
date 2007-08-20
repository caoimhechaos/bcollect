#!/bin/sh
#
# (c) 2007, Caoimhe Chaos <caoimhechaos@protonmail.com>,
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

# FIXME: stub
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

cat << EOT > testparser.y
%token TEST
%%
test:	TEST
%%
EOT
${YACC} testparser.y
if grep -q YYISARRAY y.tab.c
then
	echo '#define YYISARRAY 1' >> config.h
else
	echo '#undef YYISARRAY' >> config.h
fi
rm -f testparser.y testparser.c y.tab.c y.tab.h
exit 0
