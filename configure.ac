#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([bcollect], [0.5.99], [caoimhechaos@protonmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([flock.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_RANLIB
AC_PATH_PROG(RSYNC_PATH, rsync)
AC_DEFINE_UNQUOTED(RSYNC_PATH, ["$RSYNC_PATH"], [Path to the rsync tool])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ll':
AC_CHECK_LIB([l], [main])
# FIXME: Replace `main' with a function in `-ly':
AC_CHECK_LIB([y], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([flock memset mkdir rmdir strdup strerror])

CFLAGS="${CFLAGS} -I\$(top_srcdir)/include"
AC_SUBST(CFLAGS)
YFLAGS="-d"
AC_SUBST(YFLAGS)

dnl We need to sanitize the prefix for using sysconfdir
if test x"$prefix" = xNONE
then
	prefix="$ac_default_prefix"
fi

eval "SYSCONFDIR=$sysconfdir"
PACKAGE_OSNAME=`uname -sr`
AC_DEFINE_UNQUOTED(PACKAGE_OSNAME, ["$PACKAGE_OSNAME"], [Package operating system])
AC_DEFINE_UNQUOTED(SYSCONFDIR, ["$SYSCONFDIR"], [System configuration directory (e.g. /etc)])

AC_CONFIG_FILES([Makefile
                 confparser/Makefile
                 include/Makefile])
AC_OUTPUT
