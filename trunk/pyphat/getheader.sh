gcc -E /usr/include/phat/phat.h > ./phat.h
python /usr/share/pygtk/2.0/codegen/h2def.py phat.h > phat.defs
