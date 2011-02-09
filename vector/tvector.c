#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

void
free_elem ( void *ptr ) {
    char *t = ( char*) ptr;
    if ( t ) {
	free ( t );
    }
}
#define PERFORM_SIZE_CHECK(X) \
    if ( vector_size ( vec ) != (X) ) { \
	printf ( "Test [vector_size] Failed at %s:%d\n", __FILE__,__LINE__); \
	abort();\
    }

void
print_vector( vector *vec ) {
    int i = 0;
    for ( i = 0; i < vec->cur_size; i++ ) {
	char *v = (char*)vector_element_at ( vec, i );
	if ( v )  {
	    printf ( "[%d]-[%s]\n", i,v );
	} else {
	    printf ( "[%d]-[NULL]\n", i );
	}
    }
    printf ( "\n" );
}
char *input[] = {"A","B","C","D","E", "F","G","H","I","J","K", "L","M", "N",
    "O","P","Q", "R","S","T","U","V","W", "X","Y","Z",""};
int 
main( int argc, char**argv ) {
    int i = 0;
    vector *vec = vector_new ( 5, free_elem );
    if ( !vector_empty(vec) )  {
	printf ( "Test [vector_empty] Failed at %s:%d\n", __FILE__,__LINE__);
    }
    while ( input[i] != "" ) {
	vector_push_back ( vec, strdup ( input[i++] ));
    }
    for ( i = 0; i < vec->cur_size; i++ ) {
	char *v = ( char*) vector_element_at ( vec, i );
	if ( 0 != strcmp (v,input[i++])) {
	    printf ( "Test [vector_element_at] Failed at %s:%d\n",
	                                          __FILE__,__LINE__);
	}
    }
    PERFORM_SIZE_CHECK(26);

    if ( 0 != strcmp ("A", (char*)vector_front(vec)) ){
	printf ( "Test [vector_front] Failed at %s:%d\n", __FILE__,__LINE__);
    }
    if ( 0 != strcmp ("Z", (char*)vector_back(vec)) ){
	printf ( "Test [vector_back] Failed at %s:%d\n", __FILE__,__LINE__);
    }

    /* insert at start */
    vector_insert ( vec, 0, strdup("a"));
    PERFORM_SIZE_CHECK(27);
    if ( 0 != strcmp ("a", (char*)vector_front(vec)) ){
	printf ( "Test [vector_front] Failed at %s:%d\n", __FILE__,__LINE__);
    }

    /* insert at last */
    vector_insert ( vec,27, strdup("z"));
    PERFORM_SIZE_CHECK(28);
    if ( 0 != strcmp ("z", (char*)vector_back(vec)) ){
	printf ( "Test [vector_back] Failed at %s:%d\n", __FILE__,__LINE__);
    }
    /* insert in middle */
    vector_insert ( vec,4 ,strdup("d"));
    PERFORM_SIZE_CHECK(29);
    if ( 0 != strcmp ("d", (char*)vector_element_at(vec,4)) ){
	printf ( "Test [vector_element_at] Failed at %s:%d\n", 
	                                                __FILE__,__LINE__);
    }
    /* insert after+10 position */
    char *v = strdup ( "VERY_FAR_AWAY");
    vector_insert ( vec,39,v);
    PERFORM_SIZE_CHECK(39+1);
    if ( 0 != strcmp ("VERY_FAR_AWAY", (char*)vector_element_at(vec,39)) ){
	printf ( "Test [vector_element_at] Failed at %s:%d\n", 
	                                                 __FILE__,__LINE__);
    }
    /* test vector_pop_back */
    vector_pop_back(vec);
    PERFORM_SIZE_CHECK(39);
    /* vector_erase test middle */
    vector_erase ( vec,10 );
    PERFORM_SIZE_CHECK(38);
    if ( 0 != strcmp ("J", (char*)vector_element_at(vec,10)) ){
	printf ( "Test [vector_element_at] Failed at %s:%d\n", 
	                                                  __FILE__,__LINE__);
    }
    /* vector_erase first */
    vector_erase ( vec,0 );
    PERFORM_SIZE_CHECK(37);
    if ( 0 != strcmp ("A", (char*)vector_element_at(vec,0)) ){
	printf ( "Test [vector_element_at] Failed at %s:%d\n", 
	                                                 __FILE__,__LINE__);
    }

    vector_push_back ( vec, strdup ( "XX"));
    PERFORM_SIZE_CHECK(38);

    vector_push_back ( vec, strdup ( "XXX"));
    PERFORM_SIZE_CHECK(39);

    vector_erase ( vec, 39  - 1);
    PERFORM_SIZE_CHECK(38);

    vector_resize ( vec, 100 );
    if ( 100 != vector_capacity(vec) ) {
	printf ( "Test [vector_element_at] Failed at %s:%d\n", 
	                                                 __FILE__,__LINE__);
    }
    printf ( "All Tests Passed\n");
    vector_clear ( vec );
    return 0;
}
