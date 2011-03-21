#include <stdio.h>
extern void test_c_array();
extern void test_c_deque();
extern void test_c_tree();
extern void test_c_bst();

int main( int argc, char**argv ) {	
	int limit = 0;
	sscanf( argv[1], "%d", &limit); 
	test_c_array();
	test_c_deque(limit);
	test_c_bst();
	/*test_c_tree();*/
	return 0;
}
