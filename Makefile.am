SUBDIRS=		include confparser
bin_PROGRAMS=		bcollect
noinst_PROGRAMS=	rmfr
bcollect_SOURCES=	confparser/libconfparser.a main.c rmdir.c backup.c flock.c
bcollect_LDADD=		confparser/libconfparser.a
rmfr_SOURCES=		rmdir.c rmfr.c
