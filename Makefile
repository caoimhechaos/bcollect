CFLAGS =		-I. -I./include -g
BCOLLECT_FILES =	main.o rmdir.o backup.o flock.o confparser/confparser.a
RMFR_FILES =		rmdir.o rmfr.o
LIBS =			-ll -ly

all:			bcollect

bcollect:		${BCOLLECT_FILES}
	${CC} -o bcollect ${BCOLLECT_FILES} ${LIBS}

${BCOLLECT_FILES}:	include/config.h

rmfr:			${RMFR_FILES}
	${CC} -o rmfr ${RMFR_FILES} ${LIBS}

confparser/confparser.a:
	cd confparser; ${MAKE} confparser.a

ChangeLog:
	git shortlog > ChangeLog

include/config.h:	ChangeLog
	cd include; ${MAKE} config.h

clean:
	cd confparser; ${MAKE} clean
	cd include; ${MAKE} clean
	rm -f *.o bcollect rmfr *.core core

distclean: clean
	rm -f ChangeLog

dist:	distclean
	${SHELL} scripts/dist.sh
