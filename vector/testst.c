#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define VECTOR_SIZE 10

void free_elem ( void *in ) {
    char *t = ( char *) in ;
    if ( t ) {
	free (t);
    }
}
void 
t_vector_size(vector *pVec) {
    printf ( "Testing [vector_size]  ");
    int size = vector_size(pVec);
    if ( size != VECTOR_SIZE ) {
	printf ( "FAIL\n");
	abort();
    }
    printf ( "PASS\n");
}

void
t_vector_empty(vector *pVec){
    printf ( "Testing [vector_empty]  ");
    if ( ! pVec ) {
	printf ( "FAIL\n");
	abort();
    }
    if ( vector_empty ( pVec ) == 1 ) {
	printf ( "FAIL\n");
	abort();
    }
    printf ( "PASS\n");
}

t_vector_capacity(vector *pVec){
    printf ( "Testing [vector_capacity]  ");
    printf ( "PASS\n");
}

void 
t_vector_push_back( vector *pVec ) {
    int i = 0;
    int test_fail = 0;

    printf ( "Testing [vector_push_back]  ");
    for ( i = 0; i < VECTOR_SIZE; i++) {
	char buffer[50];
	sprintf ( buffer, "Adding %d", i );

	vector_push_back ( pVec, strdup ( buffer ) );
    }

    for ( i = 0; i < pVec->cur_size ; i++ ) {

	char *rv = (char *) vector_element_at ( pVec, i );
	char buffer[50];
	sprintf ( buffer, "Adding %d", i );
	if ( 0 != strcmp ( rv, buffer ) ) {
	    printf ( "FAIL\n");
	    abort();
	}
    }
    printf ( "PASS\n");
}
void
t_vector_insert(vector *pVec){
    char buffer[50];
    printf ( "Testing [vector_insert]  ");
    sprintf ( buffer, "Inserting at 11" );
    vector_insert ( pVec, 11, strdup ( buffer ) );
    printf ( "PASS\n");
}

void test_vector(){
    vector *pVec = vector_new ( 5 ,free_elem);
    if ( !pVec ) {
	fprintf ( stderr, "Memory allocation error \n");
	return;
    }
    t_vector_push_back(pVec);
    t_vector_size(pVec);
    t_vector_empty(pVec);
    t_vector_capacity(pVec);
    t_vector_insert(pVec);
}
int 
main ( int argc, char ** argv )  {
    test_vector();
    return 0;
}
