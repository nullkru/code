#makefile v. 0.1
prefix?=/usr

ETCDIR=/etc
LIBDIR=${prefix}/lib
BINDIR=${prefix}/bin

ARCHFOSTER_LIBDIR=$(LIBDIR)/archfoster

install:
	@install -d -m755 $(DESTDIR)$(LIBDIR) $(DESTDIR)$(BINDIR)
	
	@install -m755 src/archfoster.sh $(DESTDIR)$(BINDIR)/archfoster

	@install -d -m755 $(DESTDIR)$(ARCHFOSTER_LIBDIR)
	
	@install -m644 lib/function.inc lib/common.inc \
		$(DESTDIR)$(ARCHFOSTER_LIBDIR)
	
	@echo "archfoster successfuly installed"
