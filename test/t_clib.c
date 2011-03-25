#include <stdio.h>
extern void test_c_array();
extern void test_c_deque();
extern void test_c_tree();
extern void test_c_bst();
extern void test_c_rb();
extern void test_c_set();

int main( int argc, char**argv ) {	
    test_c_array();
    test_c_deque(500);
    test_c_bst(); 
    test_c_rb();
    test_c_set();
    return 0;
}
