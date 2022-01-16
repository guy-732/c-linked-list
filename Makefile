CC = gcc
CFLAGS = -Wall -Wextra

COBJS = linked-list.o _internal.o
ARCHIVES = liblinked-list.a

default: all

$(COBJS): %.o: %.c

linked-list.o: linked-list.h _internal.h
_internal.o: linked-list.h _internal.h


all: all-objs all-archives
all-objs: $(COBJS)
all-archives: $(ARCHIVES)

liblinked-list.a: linked-list.o _internal.o
	$(AR) r $@ $^

clean-objs:
	$(RM) $(COBJS)

clean-archives:
	$(RM) $(ARCHIVES)

clean: clean-objs clean-archives

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS += -g
debug: all

.PHONY: all all-objs all-archives clean-objs clean-archives clean default debug
