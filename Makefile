CFLAGS =		-I. -I./include -g
BCOLLECT_FILES =	main.o confparser/confparser.a
LIBS =			-ll -ly

all:			bcollect

bcollect:		${BCOLLECT_FILES}
	${CC} -o bcollect ${BCOLLECT_FILES} ${LIBS}

confparser/confparser.a:
	cd confparser; ${MAKE} confparser.a

clean:
	cd confparser; ${MAKE} clean
	rm -f *.o bcollect *.core core
