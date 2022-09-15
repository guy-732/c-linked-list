PKG_VERS = 1:1:0


lib_LTLIBRARIES = liblinked-list.la liblinked-list-minimal.la


liblinked_list_minimal_la_SOURCES = linked-list.c _ll-internal.c
liblinked_list_la_SOURCES = linked-list.c _ll-internal.c ll-extra.c

liblinked_list_minimal_la_LDFLAGS = -version-info $(PKG_VERS)
liblinked_list_la_LDFLAGS = -version-info $(PKG_VERS)


include_HEADERS = linked-list.h
noinst_HEADERS = _ll-internal.h
