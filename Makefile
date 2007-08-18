CFLAGS =		-I. -I./include -g -DYYISARRAY=1
BCOLLECT_FILES =	main.o rmdir.o backup.o flock.o confparser/confparser.a
RMFR_FILES =		rmdir.o rmfr.o
LIBS =			-ll -ly

all:			bcollect

bcollect:		${BCOLLECT_FILES}
	${CC} -o bcollect ${BCOLLECT_FILES} ${LIBS}

rmfr:			${RMFR_FILES}
	${CC} -o rmfr ${RMFR_FILES} ${LIBS}

confparser/confparser.a:
	cd confparser; ${MAKE} confparser.a

clean:
	cd confparser; ${MAKE} clean
	rm -f *.o bcollect rmfr *.core core
