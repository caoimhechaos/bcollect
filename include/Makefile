all:		config.h

config.h:
	CC="${CC}" CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"	\
	 YACC="${YACC}"	${SHELL} genconfig.sh

clean:
	rm -f config.h testprog.c testprog testparser.y testparser.c	\
		y.tab.c y.tab.h
