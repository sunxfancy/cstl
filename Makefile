SUBDIRS = src \
	test
default: all

all \
release \
clean \
debug: 
	@for subdir in ${SUBDIRS} ; \
	do \
		(cd $${subdir}; $(MAKE) $@ ); \
	done

