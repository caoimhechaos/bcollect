#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([bcollect], [0.5.99], [tonnerre.lombard@sygroup.ch])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([flock.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_RANLIB

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

PACKAGE_OSNAME=`uname -sr`
AC_DEFINE_UNQUOTED(PACKAGE_OSNAME, ["$PACKAGE_OSNAME"], [Package operating system])

AC_CONFIG_FILES([Makefile
                 confparser/Makefile
                 include/Makefile])
AC_OUTPUT
