#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


static void 
delete_e ( void *ptr ) {
    if ( ptr ) 
	free ( ptr );
}
static void 
delete_v ( void *ptr ) {
    if ( ptr ) 
	free ( ptr );
}
static int
compare_e ( void *left, void *right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
static void 
add_element_to_map ( CLIB_MAP_PTR s, int x, int y ) {
    int i = 0;
    for ( i = x; i <= y; i++ ) { 
	char *e = ( char*) malloc ( 10 * sizeof ( char ));
	char *v = ( char*) malloc ( 10 * sizeof ( char ));
	sprintf ( e, "KEY_%d", i );
	sprintf ( v, "VAL_%d", i );
	insert_c_map ( s, e ,v);
    }
}
static void
verify_all_element ( CLIB_MAP_PTR s, int x , int y) {
    int i = 0;
    char *val;
    for ( i = x; i <= y; i++ ) { 
	char *k = ( char*) malloc ( 10 * sizeof ( char ));
	char *v = ( char*) malloc ( 10 * sizeof ( char ));
	sprintf ( k, "KEY_%d", i );
	sprintf ( v, "VAL_%d", i );
	val = (char*)find_c_map ( s, k );
	assert ( strcmp ( val, v) == 0 );
	free ( k );
	free ( v );
    }
}
void
test_c_map() {
    int i = 11;
    char *val;
    char *k;

    CLIB_MAP_PTR map = new_c_map ( delete_e, delete_v, compare_e);

    add_element_to_map( map, 1, 30 );
    verify_all_element( map, 1, 30 );

    k = ( char*) malloc ( 10 * sizeof ( char ));
    sprintf ( k, "KEY_%d", i );
    remove_c_map ( map, k );
    val = (char*)find_c_map ( map, k );
    assert ( val == CLIB_NULL );
    free ( k );

    delete_c_map ( map );

}
