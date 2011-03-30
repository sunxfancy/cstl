#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void 
delete_e ( void *ptr ) {
    if ( ptr ) 
	free ( ptr );
}
static int
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
static void add_element_to_set ( CLIB_SET_PTR s, int x, int y ) {
    int i = 0;
    for ( i = x; i <= y; i++ ) { 
	    char *e = ( char*) malloc ( 10 * sizeof ( char ));
	    sprintf ( e, "KEY_%d", i );
	    insert_c_set ( s, e ,CLIB_RB_VALUE_COPY);
    }
}

void 
test_c_set(){
    CLIB_SET_PTR set1 = new_c_set ( delete_e, compare_e);
    CLIB_SET_PTR set2 = new_c_set ( delete_e, compare_e);
    CLIB_SET_PTR set3 = new_c_set ( delete_e, compare_e);
    CLIB_SET_PTR set4 = new_c_set ( delete_e, compare_e);
    CLIB_SET_PTR set5 = new_c_set ( delete_e, compare_e);

    add_element_to_set( set1, 1, 20 );	
    add_element_to_set( set2, 15, 30 );

    union_c_set ( set1, set2, &set3);	
    intersection_c_set ( set1, set2, &set4);	
    difference_c_set( set1, set2, &set5);	

    delete_c_set(set1);
    delete_c_set(set2);
    delete_c_set(set3);
    delete_c_set(set4);
    delete_c_set(set5);
}
