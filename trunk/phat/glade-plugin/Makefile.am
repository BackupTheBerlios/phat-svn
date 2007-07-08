## Process this file with automake to produce Makefile.in

SUBDIRS = icons

libphat = $(top_builddir)/phat/libphat.la

# libgladephat

gladephat_LTLIBRARIES = libgladephat.la
gladephatdir = `pkg-config --variable=moduledir gladeui-1.0`


libgladephat_la_CPPLAGS =   \
	-I$(top_srcdir)    \
	-I$(top_builddir)

libgladephat_la_CFLAGS =    \
	-g -Wall           \
	-I$(top_srcdir)    \
	-I$(top_srcdir)    \
	-I$(top_builddir)


libgladephat_la_SOURCES     = glade-phat.c glade-phat.h
libgladephat_la_LDFLAGS     = -module -avoid-version
libgladephat_la_LIBADD      = $(libphat)

#if WITH_WIN32
#  libgladephat_la_LDFLAGS += -no-undefined
#endif


# catalog data

gladecatalogsdir = `pkg-config --variable=catalogdir gladeui-1.0`
gladecatalogs_DATA = phat.xml
install: all
	$(INSTALL_PROGRAM) .libs/libgladephat.so $(gladephatdir);
	$(INSTALL_DATA) phat.xml $(gladecatalogsdir);

uninstall:
	rm -f $(gladephatdir)/libgladephat.so;
	rm -f $(gladecatalogsdir)/phat.xml;
