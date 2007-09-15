lib_LTLIBRARIES = libphatlv2.la

libphatlv2_la_SOURCES = phat-lv2-tree-store.c phat-lv2-tree-store.h

libphatlv2_la_BUILT_SOURCES = phat-lv2-tree-store.c phat-lv2-tree-store.h 

libphatlv2_la_CFLAGS = $(CFLAGS) -I.. -DINSTALL_DIR=\"$(datadir)\" -DSITE_PKGLIB_DIR=\"$(pkglibdir)\" -DSITE_PKGDATA_DIR=\"$(pkgdatadir)\" $(LIBSLV2_CFLAGS)

libphatlv2_la_LDFLAGS = $(LIBSLV2_LIBS)



libphatincludedir = $(includedir)/phat-lv2

libphatinclude_HEADERS = phat-lv2-tree-store.h



%.c %.h %-private.h: %.gob
	@GOB2@ $<
