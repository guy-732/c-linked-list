CC = gcc
CFLAGS = -Wall -Wextra

COBJS = linked-list.o _internal.o

default: all

$(COBJS): %.o: %.c

linked-list.o: linked-list.h _internal.h
_internal.o: linked-list.h _internal.h


all: all-objs
all-objs: $(COBJS)


clean-objs:
	$(RM) $(COBJS)

clean: clean-objs

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS += -g
debug: all

.PHONY: all all-objs clean-objs clean default debug
