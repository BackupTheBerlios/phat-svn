AC_PREREQ(2.52)

AC_INIT([pyphat], [0.4.1], [loki.davison@gmail.com])
AC_SUBST(ACLOCAL_AMFLAGS, "-I m4 -I .")

AC_CONFIG_SRCDIR([phatmodule.c])

AM_INIT_AUTOMAKE
dnl put the ACLOCAL flags in the makefile
ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AM_PATH_PYTHON(2.3.5)

AM_CHECK_PYTHON_HEADERS(,[AC_MSG_ERROR(could not find Python headers)])

CPPFLAGS="${CPPFLAGS}"

dnl get rid of the -export-dynamic stuff from the configure flags ...
export_dynamic=`(./libtool --config; echo eval echo \\$export_dynamic_flag_spec) | sh`

dnl gtk+; first try to find gtk+ and pycairo, if that fails look for gtk+ alone
PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.7)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

# Check for pygtk and phat
PKG_CHECK_MODULES(PYGTK, pygtk-2.0 >= 2.4)
AC_SUBST(PYGTK_LIBS)
AC_SUBST(PYGTK_CFLAGS)

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

PKG_CHECK_MODULES(PHAT, phat >= 0.4.1)
AC_SUBST(PHAT_LIBS)
AC_SUBST(PHAT_CFLAGS)

dnl add required cflags ...
JH_ADD_CFLAG([-Wall])
JH_ADD_CFLAG([-std=c9x])
JH_ADD_CFLAG([-fno-strict-aliasing])

AC_CONFIG_FILES(
  Makefile)
AC_OUTPUT
