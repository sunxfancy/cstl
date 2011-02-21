#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int array[] = { 0,1,2,3,4,5,6,7,8,9};
char *carray[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
                  "P","Q","R","S","T","U","V","W","X","Y","Z"};

void 
free_elements ( void *ptr ) {
    if ( ptr ) {
	char *t = (char*) ptr;
	free ( t );
    }
    return;
}
    
void
test_push_back() {
    int i = 0;
    vector *vec = vector_new ( 10 ,NULL);
    for ( i = 0; i < sizeof ( array ) / sizeof ( array[0] ); i++) {
	vector_push_back( vec, &i );
    }
    for ( i = 0; i < vector_size(vec); i++) {
	int *v = (int*)vector_element_at ( vec, i );
	if ( v ) {
	    /*printf ( "[%d] --> [%d]\n", i, *v );*/
	}
    }
    vector_clear( vec );
}
void
test_push_back_2() {
    int i = 0;
    char *v;
    vector *vec = vector_new ( 10 ,free_elements );
    for ( i = 0; i < sizeof ( carray ) / sizeof ( carray[0] ); i++) {
	char *t = strdup ( carray[i] );
	vector_push_back( vec, t);
    }
    for ( i = 0; i < vector_size(vec); i++) {
	char *v = (char*)vector_element_at ( vec, i );
	if ( v ) {
	    /*printf ( "[%d] --> [%s]\n", i, v );*/
	}
    }
    iterator itr = vector_begin( vec );
    v   = ITR_VALUE(itr);
    printf ( "%s\n", (char*)v);

    itr = ITR_NEXT(itr);
    v   = ITR_VALUE(itr);
    printf ( "%s\n", (char*)v);

    itr = ITR_NEXT(itr);
    v   = ITR_VALUE(itr);
    printf ( "%s\n", (char*)v);

    itr = ITR_NEXT(itr);
    v   = ITR_VALUE(itr);
    printf ( "%s\n", (char*)v);

    itr = ITR_NEXT(itr);
    v   = ITR_VALUE(itr);
    printf ( "%s\n", (char*)v);



    vector_clear( vec );
}

int main ( int argc, char **argv ) {
    test_push_back(); 
    test_push_back_2();
    return 0;
}

