# LEX =			lex
# YACC =		yacc
CFLAGS =		-I. -I../include -g
LDFLAGS =		-c
#LIBS =			-ly -ll
VERIFYCONF_FILES =	verifyconf.o y.tab.o lex.yy.o
CONFPARSER_FILES =	conffuncs.o y.tab.o lex.yy.o
HEADERS =		bcollect.h
TRUE =			true

all:	verifyconf confparser.o

confparser.a:		${CONFPARSER_FILES}
	${AR} cru confparser.a ${CONFPARSER_FILES}
	${RANLIB} confparser.a || ${TRUE}

verifyconf:		${VERIFYCONF_FILES}
	${CC} -o verifyconf ${VERIFYCONF_FILES} ${LIBS}

lex.yy.o:		lex.yy.c y.tab.h

y.tab.c y.tab.h:	confparser.y
	${YACC} -d confparser.y

lex.yy.c:		confparser.l
	${LEX} confparser.l

clean:
	rm -f *.o lex.yy.* y.tab.* verifyconf confparser.[ac]
