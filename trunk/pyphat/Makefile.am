lib_LTLIBRARIES = phat.la
CLEANFILES = 

INCLUDES = $(PYTHON_INCLUDES)

# pygtk extension modules
pkgpyexecdir = $(pyexecdir)
libdir = $(pkgpyexecdir)
# linker flags
common_ldflags = -module -avoid-version

# phat module
PHAT_DEFS = phat.defs 
CLEANFILES += phat.c
EXTRA_DIST = $(PHAT_DEFS) phat.override
phat.c: $(PHAT_DEFS) phat.override
phat_la_CFLAGS = $(PHAT_CFLAGS) $(PYGTK_CFLAGS)  $(GTK_CFLAGS)
phat_la_LIBADD = $(PHAT_LIBS) $(PYGTK_LIBS)  $(GTK_LIBS)
phat_la_LDFLAGS = $(common_ldflags)
phat_la_SOURCES = phat.c  phatmodule.c

# code generator
.defs.c:
	(pygtk-codegen-2.0 --prefix phat \
	    --register $(PYGTK_DEFSDIR)/gdk-types.defs \
	    --register $(PYGTK_DEFSDIR)/gtk-types.defs \
	    --override $*.override phat.defs) > $*.c
