all:		config.h

config.h:
	CC="${CC}" CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"	\
	 LEX="${LEX}" YACC="${YACC}"	${SHELL} ../scripts/genconfig.sh

clean:
	rm -f config.h testprog.c testprog testparser.l testparser.c	\
		*.o lex.yy.c
