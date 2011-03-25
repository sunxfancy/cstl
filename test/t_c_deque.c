#include "c_deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

c_deque *test_deq;

static void 
print_elements ( void *ptr ) {
    int value = *(int*)ptr;
    printf ( "%d\n", value);
    return;
}
static void 
free_element ( void *ptr ) {
    if ( ptr )
	free ( ptr);
}
static int 
compare_element ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}

void 
test_c_deque(int value) {
    int i = 10;
    void *elem = (void*) 0;
    int flip = 1;

    test_deq = new_c_deque (10, free_element, compare_element ); 
    for ( i = 0; i <= value; i++ ) { 
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &i, sizeof ( int ));
	if ( flip ) {
	    push_back_c_deque ( test_deq, v );
	    flip = 0;
	}else{
	    push_front_c_deque ( test_deq, v );
	    flip = 1;
	}
    }
    for_each_c_deque(test_deq, print_elements);

    elem = front_c_deque ( test_deq );
    printf ( "Front Element = %d\n", *(int*)elem);
    elem = back_c_deque ( test_deq );
    printf ( "Back  Element = %d\n", *(int*)elem);

    pop_back_c_deque(test_deq);
    elem = back_c_deque ( test_deq );
    printf ( "After Removal Back Element = %d\n", *(int*)elem);

    pop_front_c_deque(test_deq);
    elem = front_c_deque ( test_deq );
    printf ( "After Removal Front Element = %d\n", *(int*)elem);


}
