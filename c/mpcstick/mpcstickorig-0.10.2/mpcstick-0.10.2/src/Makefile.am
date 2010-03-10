bin_PROGRAMS = mpcstick
#AM_CFLAGS = -ggdb3

INCLUDES = $(GLIB_CFLAGS) $(LIBXML2_CFLAGS)

mpcstick_SOURCES = \
	mpcstick.c \
	libmpdclient.c libmpdclient.h
mpcstick_LDFLAGS = -g

mpcstick_LDADD = -lpthread -lgthread-2.0 -lxml2 -lm -lz $(LIBXML2_LIBS) $(GLIB_LIBS)

