# -*- autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([phat/phatfanslider.c])

PHAT_VERSION=0.4.1
AC_SUBST(PHAT_VERSION)

AM_INIT_AUTOMAKE([phat],${PHAT_VERSION})
dnl AC_DISABLE_STATIC
AC_PROG_LIBTOOL



# optimization and debugging checks
with_debug="no"
AC_ARG_ENABLE([debug], 
    [AC_HELP_STRING([--enable-debug],
        [enable debugging information, accepting a performance penalty (default is NO)])],
    [if test x$enable_debug = xyes; then with_debug=yes ; fi])

if test x$with_debug = xno; then
    if test -z $CFLAGS; then
        CFLAGS="-O3"
    fi
    AC_DEFINE(DEBUG, 0, [[whether to display debugging output or not]])
else
    CFLAGS="$CFLAGS -g"
    AC_DEFINE(DEBUG, 1, [[whether to display debugging output or not]])
fi

# standard autoconf checks
AC_PROG_CC
AC_PROG_CPP
AM_PROG_CC_C_O

##################################################
# Check for gtk+-2.0, preferably >= 2.4
##################################################
with_gtk2_4=no
PKG_CHECK_MODULES(GTK, [gtk+-2.0 >= 2.4.0], [with_gtk2_4=yes], [with_gtk2_4=no])

if test x$with_gtk2_4 = xyes; then
    AC_DEFINE(HAVE_GTK2_4, 1, [[do we have gtk+ >= 2.4 ?]])
else
    PKG_CHECK_MODULES(GTK, gtk+-2.0)
fi

PKG_CHECK_MODULES( SNDFILE, sndfile )
AC_SUBST(SNDFILE_LIBS)

PKG_CHECK_MODULES( SAMPLERATE, samplerate )
AC_SUBST(SAMPLERATE_LIBS)

##################################################
# Check for glade 3 (aka gladeui-1.0)
##################################################

ac_enable_glade_plugin=no
AC_ARG_ENABLE(glade_plugin,
     [  --enable-glade-plugin     build the phat glade plugin (default:disabled)],
     [ ac_enable_glade_plugin=yes ], [ ac_enable_glade_plugin=no ])

if test "x${ac_enable_glade_plugin}" != xno ; then

  PKG_CHECK_MODULES(GLADE3, [gladeui-1.0], [build_glade=yes], [build_glade=no])
  AC_SUBST(GLADE3_CFLAGS)
  AC_SUBST(GLADE3_LIBS)

fi

AM_CONDITIONAL([BUILD_GLADE_PLUGIN], test x$build_glade = xyes)

##################################################
# Check for gtk-doc.
##################################################

GTK_DOC_CHECK(1.0)

# misc checks
PKG_CHECK_MODULES(MISC, libgnomecanvas-2.0)

# set compilation flags
CFLAGS="$CFLAGS $GTK_CFLAGS $MISC_CFLAGS -Wall -Werror"
LIBS="$LIBS $GTK_LIBS $MISC_LIBS $SNDFILE_LIBS $SAMPLERATE_LIBS" 

# print build summary
AC_CONFIG_COMMANDS_POST([
echo
echo
echo    "                   BUILD SUMMARY"
echo    "                   ============="
echo
echo -n "             Build type:          "
if test x$with_debug = xyes; then
    echo "debugging"
else
    echo "optimized"
fi
echo -n "             GTK+ Version:        "
if test x$with_gtk2_4 = xyes; then
    echo "2.4 or greater"
else
    echo "2.0 or 2.2 series"
fi
echo -n "             Build Glade Plugin:  "
if test x$build_glade = xyes; then
    echo "yes"
else
    echo "no"
fi
echo -n "             Build Docs:          "
if test x$enable_gtk_doc = xyes; then
    echo "yes"
else
    echo "no"
fi
echo
echo
])

AC_CONFIG_FILES([
Makefile
phat/Makefile
demos/Makefile
docs/Makefile
pixmaps/Makefile
glade-plugin/Makefile
glade-plugin/icons/Makefile
glade-plugin/icons/16x16/Makefile
glade-plugin/icons/22x22/Makefile
phat.pc
phat.spec
])

AM_CONFIG_HEADER([phat/config.h])
AC_OUTPUT
