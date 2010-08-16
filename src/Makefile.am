AM_CPPFLAGS = $(fuse_CFLAGS)

bin_PROGRAMS = fusequota
fusequota_SOURCES = fusequota.c fuse_ops.c fuse_ops.h quota.c quota.h space.c space.h error.c error.h

fusequota_LDADD = $(fuse_LIBS)