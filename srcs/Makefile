############################################
#
# TestMQ Server
#   copyright 2020.07.11 konoar
#
############################################

SHELL   := /bin/bash
INCDIR	:= ../inc/
BINDIR  := ../bin/
OBJDIR	:= ./obj/
TGNAME  ?= s
TGSRCS	:= $(shell ls *.c)
TGOBJS 	:= $(TGSRCS:%.c=$(OBJDIR)%.o)
TGBIN   := $(BINDIR)$(TGNAME)
CFLAGS  := -I$(INCDIR)
LDFLAGS :=

.PHONY: all

all: dirs clean $(TGBIN)

dirs:
	@if [ ! -d $(OBJDIR) ];			\
	 then					\
		mkdir $(OBJDIR);		\
	 fi

clean:
	@rm -f $(OBJDIR)*.o
	@rm -f $(TGBIN)

$(TGBIN): $(TGOBJS)
	@gcc -o $@ $^ $(LDFLAGS)

$(OBJDIR)%.o: %.c
	@gcc -o $@ -c $^ $(CFLAGS)

