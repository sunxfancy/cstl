#include "vector.h"
#include <malloc.h>
#include <string.h>

vector *
vector_new(int s, pfnDestruct fn) {

    int size = ( s < 8 ) ? 8 : s;
    
    vector *ptr_vector = ( vector *) malloc ( size * sizeof ( vector));
    if ( !ptr_vector ) return (vector*)0;
    
    ptr_vector->capacity = size;
    ptr_vector->cur_size = 0;

    ptr_vector->elem = ( void **) malloc ( size * sizeof ( void * ));
    if ( ! ptr_vector->elem ) {
	free ( ptr_vector );
	return ( vector *)0;
    }
    return ptr_vector;
}
void
vector_push_back ( vector *vec, void *elem) {
    int temp_size = 0;
    if ( ! vec )  return; 
    /* TODO :
     * Need to add a check if elem is pointer from stack or heap
     * Not sure as of now how to get that
     */
    temp_size = vec->capacity * 2;
    if ( vec->capacity == vec->cur_size ) {
	/* Perform re-allocation here */
	vec->elem = ( void **) realloc ( vec->elem, temp_size * sizeof ( void * ));
	vec->capacity = temp_size;
    }
    vec->elem[vec->cur_size++] = elem;
}
void *
vector_element_at ( vector *vec, int pos ) {
    if ( ! vec ) return ;
    if ( pos > vec->cur_size ) return (vector*)0;
    return (void*)vec->elem[pos];


}
int
vector_size( vector *vec) {
    if ( !vec ) return 0;
    return vec->cur_size;
}
int
vector_empty( vector *vec ) {
    if ( ! vec ) return 1;
    if ( vec->cur_size == 0 ) return 1;
    return 0;
}
int
vector_capacity( vector *vec ) {
    if ( !vec ) return 0;
    return vec->capacity;
}
void *
vector_front( vector *vec){
    if ( !vec ) return (vector*) 0;
    return vec->elem[0];
}
void *
vector_back( vector *vec){
    if ( !vec ) return (vector*) 0;
    return vec->elem[vec->cur_size];
}
void
vector_insert( vector *vec,int pos,void* elem) {
    if ( !vec ) return ;

    if ( pos == vec->cur_size + 1 ) {
	vector_push_back( vec, elem );
    } else if ( pos > vec->cur_size ) {
	int i = 0;
	for ( i = 0; i < pos - 1 ; i++ ) {
	    vector_push_back( vec, (void*) 0 );
	}
	vector_push_back( vec, elem );
    } else if (pos < vec->cur_size) {
	if ( vec->cur_size + pos > vec->capacity ) {
	    int tmpsize = vec->capacity * 2;
	    vec->elem = ( void **) realloc ( vec->elem, tmpsize );
	    vec->capacity = tmpsize;
	}
	memmove ( &(vec->elem[pos + 1]),
	          &vec->elem[pos],
		  (vec->cur_size - pos ) * sizeof ( void * ) );
	vec->elem[pos] = elem;
    }
}

