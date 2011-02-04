#include "cstl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_elem ( void *in ) {
    char *t = ( char *) in ;
    if ( t ) {
	free (t);
    }
}

void test_vector(){
    int i = 0;
    iterator *itr;

    VECTOR *pVec = vector_new ( 5 ,free_elem);
    for ( i = 0; i < 50 ; i++ ) {
	char buffer[10];
	sprintf ( buffer, "Entry %d", i );
	pVec->push_back( pVec, strdup ( buffer ));
    }
    int n = pVec->size(pVec );
    for ( i = 0; i < n;i++ ) {
	char *value = (char*)pVec->element_at( pVec, i );
	if ( value )  {
	    printf ( "Value = %s\n", value );
	}
    }
    itr = pVec->get_f_iterator(pVec);
    while ( ! itr->end( pVec ) ){
	char * value = ( char *) itr->get_value ( pVec );
	if ( value ) {
	    printf ( "Itertor Value = %s\n", value );
	}
	itr->next ( pVec );
    }
    vector_destroy ( pVec);
}
int 
main ( int argc, char ** argv )  {
    test_vector();
    return 0;
}
