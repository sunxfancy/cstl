#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "../iterator/iterator.h"
#include "../algorithms/algorithms.h"


char *input[] = {"A","B","C","D","E", "F","G","H","I","J","K", "L","M", "N",
    "O","P","Q", "R","S","T","U","V","W", "X","Y","Z",""};

void
free_elem ( void *ptr ) {
    char *t = ( char*) ptr;
    if ( t ) {
	free ( t );
    }
}
int i = 0;
vector *vec;
#define PERFORM_SIZE_CHECK(X) \
    if ( vector_size ( vec ) != (X) ) { \
	printf ( "Test [vector_size] Failed at %s:%d\n", __FILE__,__LINE__); \
	abort();\
    }
#define INSERT_ELEMENTS \
    i = 0; \
    while ( input[i] != "" ) { \
	vector_push_back ( vec, strdup ( input[i++] ));\
    }
#define CREATE_NEW_VECTOR \
    vec = vector_new ( 5, free_elem ); \
    if ( !vector_empty(vec) )  { \
	printf ( "Test [vector_empty] Failed at %s:%d\n", __FILE__,__LINE__); \
    }
#define COMPARE_ALL_ELEMENTS \
    for ( i = 0; i < vec->cur_size; i++ ) { \
	char *v = ( char*) vector_element_at ( vec, i ); \
	if ( 0 != strcmp (v,input[i++])) { \
	    printf ( "Test [vector_element_at] Failed at %s:%d\n", \
		     __FILE__,__LINE__); \
	} \
    }
#define PERFORM_ELEMENT_CHECK(X,Y) \
    if ( 0 != strcmp ((X), (char*)vector_element_at(vec,(Y))) ){ \
	printf ( "Test [vector_element_at] Failed at %s:%d\n",  \
		 __FILE__,__LINE__);\
    }
#define PERFORM_FRONT_ELEMENT_CHECK(X) \
    if ( 0 != strcmp ((X), (char*)vector_front(vec)) ){ \
	printf ( "Test [vector_front] Failed at %s:%d\n", __FILE__,__LINE__); \
    }
#define PERFORM_BACK_ELEMENT_CHECK(X) \
    if ( 0 != strcmp ((X), (char*)vector_back(vec)) ){ \
	printf ( "Test [vector_back] Failed at %s:%d\n", __FILE__,__LINE__);\
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

void print_vec_element (void *elem)
{
    char *v = ( char *) elem;
    printf ( "for_each: [%s] \n", v );
}

int 
main( int argc, char**argv ) {

    CREATE_NEW_VECTOR;
    INSERT_ELEMENTS;
    COMPARE_ALL_ELEMENTS;
    PERFORM_SIZE_CHECK(26);
    PERFORM_FRONT_ELEMENT_CHECK("A");
    PERFORM_BACK_ELEMENT_CHECK("Z");

    /* insert at start */
    vector_insert ( vec, 0, strdup("a"));
    PERFORM_SIZE_CHECK(27);
    PERFORM_FRONT_ELEMENT_CHECK ("a");

    /* insert at last */
    vector_insert ( vec,27, strdup("z"));
    PERFORM_SIZE_CHECK(28);
    PERFORM_BACK_ELEMENT_CHECK ( "z");

    /* insert in middle */
    vector_insert ( vec,4 ,strdup("d"));
    PERFORM_SIZE_CHECK(29);
    PERFORM_ELEMENT_CHECK("d",4);

    /* insert after+10 position */
    char *v = strdup ( "VERY_FAR_AWAY");
    vector_insert ( vec,39,v);
    PERFORM_SIZE_CHECK(39+1);
    PERFORM_ELEMENT_CHECK("VERY_FAR_AWAY",39);

    /* test vector_pop_back */
    vector_pop_back(vec);
    PERFORM_SIZE_CHECK(39);
    /* vector_erase test middle */
    vector_erase ( vec,10 );
    PERFORM_SIZE_CHECK(38);
    PERFORM_ELEMENT_CHECK ( "J", 10 );

    /* vector_erase first */
    vector_erase ( vec,0 );
    PERFORM_SIZE_CHECK(37);
    PERFORM_ELEMENT_CHECK ( "A", 0 );

    vector_push_back ( vec, strdup ( "XX"));
    PERFORM_SIZE_CHECK(38);

    vector_push_back ( vec, strdup ( "XXX"));
    PERFORM_SIZE_CHECK(39);

    vector_erase ( vec, 39  - 1);
    PERFORM_SIZE_CHECK(38);

    vector_resize ( vec, 100 );
    if ( 100 != vector_capacity(vec) ) {
	printf ( "Test [vector_capacity] Failed at %s:%d\n", 
		 __FILE__,__LINE__);
    }
    vector_clear ( vec );

    CREATE_NEW_VECTOR;
    INSERT_ELEMENTS;

    iterator *vec_iterator = vector_new_iterator ( vec );
    while ( !vec_iterator->end(vec) )  {
	char *v = (char *)vec_iterator->value(vec);
	printf ( "From Iterator ==> %s\n", v );
	vec_iterator->next ( vec );
    }
    COMPARE_ALL_ELEMENTS;
    PERFORM_SIZE_CHECK(26);
    vector_delete_iterator ( vec );
    vector_clear ( vec );

    printf ( "All Tests Passed\n");
    return 0;
}
