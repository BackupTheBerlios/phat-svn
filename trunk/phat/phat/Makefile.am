lib_LTLIBRARIES = libphat.la

BUILT_SOURCES = \
     phatmarshallers.c phatmarshallers.h 

libphat_la_SOURCES =                        \
    phatmarshallers.h phatmarshallers.c     \
    phatrange.c phatrange.h                 \
    phatfanslider.c phatfanslider.h         \
    phatvfanslider.c phatvfanslider.h       \
    phathfanslider.c phathfanslider.h       \
    phatslider.c phatslider.h               \
    phatprivate.h phatprivate.c             \
    phatsliderbutton.c phatsliderbutton.h   \
    phatkeyboard.c phatkeyboard.h           \
    phatvkeyboard.c phatvkeyboard.h         \
    phathkeyboard.c phathkeyboard.h         \
    phatpad.c phatpad.h                     \
    phatknob.c phatknob.h		            \
    phatdpmmeter.c phatdpmmeter.h           \
    phatppmmeter.c phatppmmeter.h           \
    phatvumeter.c phatvumeter.h             \
    phatadjustment.c phatadjustment.h phatadjustmentprivate.h \
    tech-knob.c tech-knob.h techknobprivate.h \
    sample-display.c sample-display.h \
    phatscrolloscope.c phatscrolloscope.h \
    phataudiostream.c phataudiostream.h \
    phatplayaline.c phatplayaline.h

libphat_la_CFLAGS = $(CFLAGS) -std=c99 -I.. -DINSTALL_DIR=\"$(datadir)\" -DSITE_PKGLIB_DIR=\"$(pkglibdir)\" -DSITE_PKGDATA_DIR=\"$(pkgdatadir)\"

libphatincludedir = $(includedir)/phat

libphatinclude_HEADERS =    \
    phatmarshallers.h       \
    phat.h                  \
    phatrange.h             \
    phatfanslider.h         \
    phatvfanslider.h	    \
    phathfanslider.h        \
    phatsliderbutton.h      \
    phatkeyboard.h          \
    phatvkeyboard.h	    \
    phathkeyboard.h         \
    phatpad.h               \
    phatknob.h              \
    phatslider.h            \
    phatppmmeter.h          \
    phatdpmmeter.h          \
    phatvumeter.h           \
    phatadjustment.h	    \
    tech-knob.h             \
    sample-display.h        \
    phatscrolloscope.h	    \
    phataudiostream.h	    \
    phatplayaline.h

BUILT_SORCES = phatmarshallers.h phatmarshallers.c
    
phatmarshallers.h: phatmarshallers.list
	glib-genmarshal --header --prefix=phat_closure_marshal $< > $@

phatmarshallers.c: phatmarshallers.list
	glib-genmarshal --body --prefix=phat_closure_marshal $< > $@
