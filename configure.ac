dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.5])
AC_INIT([vpr-midas], [1.0], [0x@vpr.io])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

dnl Check for x86_64-w64-mingw32-gcc
AC_CHECK_PROG([MINGW_CC], [x86_64-w64-mingw32-gcc], [x86_64-w64-mingw32-gcc], [:])

dnl Print error if x86_64-w64-mingw32-gcc is not found
if test "x$MINGW_CC" = "x:"; then
  AC_MSG_ERROR([x86_64-w64-mingw32-gcc is required to build])
fi

dnl Checks for programs.
AC_PROG_CC([x86_64-w64-mingw32-gcc])
AC_PROG_INSTALL
AC_PROG_MAKE_SET

dnl Enable automake
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

dnl Set default build type to "debug"
build_type=debug
AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug], [enable debugging information (default=no)])],
  [enable_debug=$enableval], [enable_debug=no])
AM_CONDITIONAL(BUILD_DEBUG, test x$enable_debug = xyes)

dnl Output build type
AC_MSG_NOTICE([Build type: ${build_type}])

dnl Enable options for debug and release builds
AC_ARG_ENABLE([debug],
  AS_HELP_STRING([--enable-debug],
    [Build with debugging information (default: yes)]),
  [case "${enableval}" in
    yes) build_type=debug ;;
    no) build_type=release ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],
  [build_type=debug])
AC_ARG_ENABLE([release],
  AS_HELP_STRING([--disable-release],
    [Build without optimization (default: no)]),
  [case "${enableval}" in
    yes) build_type=release ;;
    no) ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --disable-release]) ;;
  esac])

dnl Checks for libraries.

dnl Checks for header files.

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

AC_CONFIG_FILES([Makefile]) 
AC_OUTPUT
