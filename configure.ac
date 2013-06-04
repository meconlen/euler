AC_PREREQ(2.61)
AC_INIT([euler], [0.4], [mike@conlen.org])
AC_CONFIG_SRCDIR([src/lang/C/1-1.c])
AC_CONFIG_HEADER([config.h])
if test "x${CFLAGS}" = "x"
then
	no_CFLAGS="yes"
fi
AC_PROG_CC([gcc cl cc])

if test "x$no_CFLAGS" = "xyes" -a "x${GCC}" = "xyes"
then
	CFLAGS="-Wall -O3"
fi

if test "x${EXTRA_CFLAGS}" != "x"
then
	CFLAGS="${CFLAGS} ${EXTRA_CFLAGS}"
fi

AC_SEARCH_LIBS([powf], [m], [], [echo "powf() not found. Cannot find math libraries"; exit -1])
#AC_SEARCH_LIBS([initscr], [ncurses], [], [echo "initscr() not found. Cannot find libncurses."; exit -1])
AC_SEARCH_LIBS([pthread_create], [pthread], [], [echo "pthread_create() not found. Cannot find libpthread"; exit -1])

AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([sys/malloc.h])
AC_CHECK_HEADERS([malloc/malloc.h])

CUNIT_LIBS=""
AC_SEARCH_LIBS([CU_initialize_registry], [cunit], [
	AC_CHECK_HEADERS([CUnit/CUnit.h])
	CUNIT_LIBS=-lcunit
], [])
AC_SUBST(CUNIT_LIBS)

AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([fstat])


AC_CONFIG_FILES([Makefile
	src/Makefile
	src/lang/C/ds/Makefile
	src/lang/C/Makefile])

AC_OUTPUT
