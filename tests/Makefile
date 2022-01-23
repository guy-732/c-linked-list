CC = gcc
CFLAGS = -Wall -Wextra

EXECS = basics access remove-index
COBJS = $(EXECS:=.o)

ARCHIVES = ../liblinked-list-min.a ../liblinked-list.a


all: all-objs all-progs

all-objs: $(COBJS)
all-progs: $(EXECS)

$(ARCHIVES) &: main-makefile

$(COBJS): %.o: %.c

basics: basics.o ../liblinked-list-min.a
access: access.o ../liblinked-list-min.a
remove-index: remove-index.o ../liblinked-list-min.a

clean: clean-objs clean-progs
	$(MAKE) -C ../ clean

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
