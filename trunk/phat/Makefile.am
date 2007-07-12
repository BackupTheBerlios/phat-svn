SUBDIRS = phat demos docs pixmaps

if BUILD_GLADE_PLUGIN
  SUBDIRS += glade-plugin
endif

DIST_SUBDIRS = phat demos docs pixmaps glade-plugin

EXTRA_DIST = bootstrap BUGS phat.pc.in phat.spec.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = phat.pc
