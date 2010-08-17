#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([fusequota], [0.2], [augsod@gmail.com])
AC_LANG([C])
AC_CONFIG_SRCDIR([src/fusequota.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([gnu])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([fuse], [fuse_main], , AC_MSG_ERROR([unable to link libcurl]))

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stdlib.h string.h sys/statfs.h unistd.h])
AC_CHECK_HEADER([fuse.h], , AC_MSG_ERROR([unable to find libfuse headers]),
[
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif
])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_ERROR_AT_LINE
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([fdatasync memset mkdir realpath rmdir utime])

PKG_CHECK_MODULES([fuse], [fuse])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
