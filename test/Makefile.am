AM_CPPFLAGS = -I$(srcdir)/../inc -Dbst
bin_PROGRAMS = teststl
teststl_SOURCES = 	t_c_array.c  \
			t_c_deque.c  \
			test_clib.c  \
			t_tree.c
teststl_LDADD = ../src/libstl.la
check:
	./teststl 500


