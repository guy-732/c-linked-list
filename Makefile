CC = gcc
CFLAGS = -Wall -Wextra

COBJS = linked-list.o _internal.o ll-extra.o
ARCHIVES = liblinked-list-min.a liblinked-list.a
SHARED_OBJS = $(ARCHIVES:.a=.so)

default: all

$(COBJS): %.o: %.c

linked-list.o: linked-list.h _internal.h
_internal.o: linked-list.h _internal.h
ll-extra.o: ll-extra.h linked-list.h _internal.h


all: all-objs all-archives all-shared
all-objs: $(COBJS)
all-archives: $(ARCHIVES)
all-shared: $(SHARED_OBJS)

liblinked-list-min.a: linked-list.o _internal.o
	$(AR) r $@ $^

liblinked-list.a: linked-list.o _internal.o ll-extra.o
	$(AR) r $@ $^

$(SHARED_OBJS): %.so: %.a
	$(CC) -shared $(LDFLAGS) -o $@ -Wl,-whole-archive $^ -Wl,-no-whole-archive

clean-objs:
	$(RM) $(COBJS)

clean-archives:
	$(RM) $(ARCHIVES)

clean-shared:
	$(RM) $(SHARED_OBJS)

clean: clean-objs clean-archives clean-shared

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS += -g
debug: all

.PHONY: all all-objs all-archives all-shared clean-objs clean-archives clean-shared clean default debug
