#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define VECTOR_SIZE 10

vector *gVec;

void free_elem ( void *in ) {
    char *t = ( char *) in ;
    if ( t ) {
	free (t);
    }
}
void 
t_vector_size(){
    int size = vector_size(gVec);
    if ( size != VECTOR_SIZE ) {
	abort();
    }
}

void
t_vector_empty() {
    if ( ! gVec ) {
	abort();
    }
    if ( vector_empty ( gVec ) == 1 ) {
	abort();
    }
}

t_vector_capacity() {
}

void 
t_vector_push_back(char *tc) {
    int i = 0;
    int test_fail = 0;

    printf ( "Testing %s ", tc );

    for ( i = 0; i < VECTOR_SIZE; i++) {
	char buffer[50];
	sprintf ( buffer, "Adding %d", i );
        char *p = strdup ( buffer );
	vector_push_back ( gVec, p );
    }

    for ( i = 0; i < gVec->cur_size ; i++ ) {
	char *rv = (char *) vector_element_at ( gVec, i );
	char buffer[50];
	sprintf ( buffer, "Adding %d", i );
	if ( 0 != strcmp ( rv, buffer ) ) {
	    printf ( "FAIL \n");
	    abort();
	}
    }
    printf ( "PASS \n");
}
void print_vector( char *tag ){

    int i = 0;
    printf ( "%s\n", tag );
    for ( i = 0; i < gVec->cur_size ; i++ ) {
	char *rv = (char *) vector_element_at ( gVec, i );
	if ( rv ) {
	    printf ( "[%d] -----> [%s]\n", i, rv );
	} else {
	    printf ( "[%d] -----> []\n", i);
	}

    }

}
void
t_vector_insert(char *tc, int pos){
    char buffer[50];

    printf ( "Testing %s [%d]  ", tc, pos );
    sprintf ( buffer, "Inserting at %d", pos );
    char *p = strdup ( buffer );

    vector_insert ( gVec, pos, p );
    char *v = (char*)vector_element_at( gVec, pos );
    if ( !v ) {
	printf ( "FAIL \n");
	abort();
    }
    else {
	if ( 0 == strcmp ( v, buffer ) ) {
	    printf ( "PASS \n");
	}else {
	    printf ( "FAIL \n");
	    abort();
	}
    }
    return;

}
void
create_vector() {
    gVec = vector_new ( 5 ,free_elem);
    if ( !gVec ) {
	fprintf ( stderr, "Memory allocation error \n");
	abort();
	return;
    }
}

void test_vector(){
    create_vector();
    t_vector_push_back("vector_push_back");
    t_vector_size();
    t_vector_empty();
    t_vector_capacity();

    t_vector_insert("vector_insert", gVec->cur_size + 1  );
    t_vector_insert("vector_insert", gVec->cur_size + 20 ); 
    t_vector_insert("vector_insert", gVec->cur_size - 10 );
}
int 
main ( int argc, char ** argv )  {
    test_vector();
    return 0;
}
