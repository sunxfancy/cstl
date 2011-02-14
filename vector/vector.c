#include "vector.h"
#include <malloc.h>
#include <string.h>

#define VALIDATE_POINTER if ( ! vec )  return; 

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
    ptr_vector->_destroy = fn;
    return ptr_vector;
}
void
vector_push_back ( vector *vec, void *elem) {
    int temp_size = 0;
    VALIDATE_POINTER;

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
    VALIDATE_POINTER;

    if ( pos > vec->cur_size ) return (vector*)0;
    return (void*)vec->elem[pos];


}
int
vector_size( vector *vec) {
    VALIDATE_POINTER;

    return vec->cur_size;
}
int
vector_empty( vector *vec ) {
    VALIDATE_POINTER;

    if ( vec->cur_size == 0 ) return 1;
    return 0;
}
int
vector_capacity( vector *vec ) {
    VALIDATE_POINTER;
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
    return vec->elem[vec->cur_size - 1];
}
void
vector_insert( vector *vec,int pos,void* elem) {
    VALIDATE_POINTER;

    if ( pos == vec->cur_size ) {
	vector_push_back( vec, elem );
    } else if ( pos > vec->cur_size ) {
	int i = 0;
	for ( i = vec->cur_size; i < pos ; i++ ) {
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
	vec->cur_size++;
    }
}
void
vector_clear ( vector *vec ) {
    int i = 0;

    VALIDATE_POINTER;

    for ( i = 0; i < vec->cur_size; i++ ){
	(vec->_destroy)(vec->elem[i]);
    }
    if ( vec->elem ) free ( vec->elem );
    if ( vec ) free ( vec );
}
void 
vector_pop_back( vector *vec) {
    VALIDATE_POINTER;

    (vec->_destroy)(vec->elem[vec->cur_size - 1]);
    vec->cur_size--;
}
void 
vector_erase( vector *vec, int pos){
    VALIDATE_POINTER;

    if ( pos >= vec->cur_size ) return;
    (vec->_destroy)(vec->elem[pos]);
    memmove ( &(vec->elem[pos]),
	      &vec->elem[pos + 1 ],
	      (vec->cur_size - pos ) * sizeof ( void * ) );
    vec->cur_size--;
}
void 
vector_resize ( vector *vec, int new_size ) {
    VALIDATE_POINTER;

    if ( vec->capacity == new_size ) return;
    if ( vec->capacity > new_size ) return;

    vec->elem = ( void **) realloc ( vec->elem, new_size * sizeof ( void * ));
    vec->capacity = new_size;
}
iterator *
vector_new_iterator( vector *vec) {
    VALIDATE_POINTER;

    iterator *itr = ( iterator *) malloc ( sizeof ( iterator ));
    itr->ptr_to_container  = ( void *) vec;
    itr->end               = vector_itr_end;
    itr->next              = vector_itr_next;
    itr->value             = vector_itr_get_value;

    vec->iter_current_pos  = 0;
    vec->iter_end_pos      = vec->cur_size; 
    return itr;
}
void 
vector_delete_iterator( vector *vec ) {
    VALIDATE_POINTER;
    iterator *itr = ( iterator *) malloc ( sizeof ( iterator ));
    if ( itr ) {
	free ( itr );
    }
    vec->iter_current_pos = 0;
}
int 
vector_itr_end( void *v ) 
{
    vector *vec = ( vector *) v;
    VALIDATE_POINTER;

    if ( vec->iter_current_pos >= vec->iter_end_pos ) {
	return 1;
    }
    return 0;
}
void
vector_itr_next ( void *v ) {
    vector *vec = ( vector *) v;
    VALIDATE_POINTER;
    vec->iter_current_pos++;
}

void *
vector_itr_get_value ( void *v ) {
    vector *vec = ( vector *) v;
    VALIDATE_POINTER;

    return  (void*) vector_element_at ( vec, vec->iter_current_pos );
    return NULL;
}
