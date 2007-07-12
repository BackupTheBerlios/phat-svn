lib_LTLIBRARIES = libphat.la

libphat_la_SOURCES = phatfanslider.c phatfanslider.h phatvfanslider.c	\
phatvfanslider.h phathfanslider.c phathfanslider.h phatprivate.h	\
phatprivate.c phatsliderbutton.c phatsliderbutton.h phatkeyboard.c	\
phatkeyboard.h phatvkeyboard.c phatvkeyboard.h phathkeyboard.c		\
phathkeyboard.h phatpad.c phatpad.h phatknob.c phatknob.h		\
phatppmmeter.h phatdpmmeter.h phatvumeter.h 				\
phatppmmeter.c phatdpmmeter.c phatvumeter.c 				\
phatslider.c phatslider.h						\
phat-adjustment.c phat-adjustment.h phat-adjustment-private.h


libphat_la_CFLAGS = $(CFLAGS) -std=c99 -I.. -DINSTALL_DIR=\"$(datadir)\" -DSITE_PKGLIB_DIR=\"$(pkglibdir)\" -DSITE_PKGDATA_DIR=\"$(pkgdatadir)\"

libphatincludedir = $(includedir)/phat

libphatinclude_HEADERS = phat.h phatfanslider.h phatvfanslider.h	\
phathfanslider.h phatsliderbutton.h phatkeyboard.h phatvkeyboard.h	\
phathkeyboard.h phatpad.h phatknob.h phatslider.h			\
phatppmmeter.h phatdpmmeter.h phatvumeter.h phat-adjustment.h

%.c %.h %-private.h: %.gob
	@GOB2@ $<
