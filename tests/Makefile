CC = gcc
CFLAGS = -Wall -Wextra

COBJS = basics.o
EXECS = basics

ARCHIVES = ../liblinked-list-min.a ../liblinked-list.a


all: all-objs all-progs

all-objs: $(COBJS)
all-progs: $(EXECS)

$(ARCHIVES) &: main-makefile

$(COBJS): %.o: %.c

basics: basics.o ../liblinked-list-min.a

clean: clean-objs clean-progs
clean-objs:
	$(RM) $(COBJS)

clean-progs:
	$(RM) $(EXECS)

main-makefile:
	$(MAKE) -C ../ CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" LDFLAGS="$(LDFLAGS)" all


debug: CFLAGS += -g
debug: CPPFLAGS += -DDEBUG
debug: all

.PHONY: all all-progs all-objs clean clean-objs clean-progs debug main-makefile
