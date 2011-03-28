#include <stdio.h>
extern void test_c_array();
extern void test_c_deque();
extern void test_c_tree();
extern void test_c_rb();
extern void test_c_set();
extern void test_c_map();

int main( int argc, char**argv ) {	
    printf ( "Performing test for dynamic array\n");
    test_c_array();
    printf ( "Performing test for deque\n");
    test_c_deque(500); 
    printf ( "Performing test for red black tree\n");
    test_c_rb(); 
    printf ( "Performing test for sets\n");
    test_c_set();
    printf ( "Performing test for map\n");
    test_c_map(); 
    return 0;
}
