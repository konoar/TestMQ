############################################
#
# TestMQ
#   copyright 2020.07.11 konoar
#
############################################

SHELL   := /bin/bash
BINDIR  := ./bin/
TGTS    := s
TGTC    := c

.PHONY: all

all: clean run

dirs:
	@if [ ! -d $(BINDIR) ];			\
	 then					\
		mkdir $(BINDIR);		\
	 fi

clean:
	@rm -f $(BINDIR)$(TGTS)
	@rm -f $(BINDIR)$(TGTC)

run: dirs $(BINDIR)$(TGTS) $(BINDIR)$(TGTC)
	@-pushd $(BINDIR); ./$(TGTS); popd;

$(BINDIR)$(TGTS):
	@pushd srcs; $(MAKE) TGNAME=$(TGTS); popd;

$(BINDIR)$(TGTC):
	@pushd srcc; $(MAKE) TGNAME=$(TGTC); popd;

