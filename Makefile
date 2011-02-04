SHELL = /bin/sh
SUBDIRS = src test
default: all

all \
release \
clean \
clobber \
debug: 
	@for subdir in ${SUBDIRS} ; \
    	do \
    	(cd $${subdir}; $(MAKE) $@ ); \
    	done

