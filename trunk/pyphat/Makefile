#DEFS=`pkg-config --variable=defsdir pygtk-2.0`         
DEFS=/usr/share/pygtk/2.0/defs
CFLAGS = $(shell pkg-config --cflags gtk+-2.0 pygtk-2.0 phat) -Wall -fPIC -I/usr/include/python2.4/ -I.
LDFLAGS = $(shell pkg-config --libs gtk+-2.0 pygtk-2.0 phat)

phat.c: phat.defs phat.override
	pygtk-codegen-2.0 --prefix phat \
	--register $(DEFS)/gdk-types.defs \
	--register $(DEFS)/gtk-types.defs \
	--override phat.override \
	phat.defs > $@

phat.so: phat.o phatmodule.o
	$(CC) $(LDFLAGS) -shared $^ -o $@  
    
