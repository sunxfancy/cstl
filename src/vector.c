#include "vector.h"
#include <malloc.h>
#include <string.h>

VECTOR *
vector_new(int s, pfnDestruct fn) {

    VECTOR *ptrVector = (VECTOR *)malloc(sizeof(VECTOR));
    (void ) memset ( ptrVector , 0, sizeof(VECTOR));

    ptrVector->f_iterator = (iterator *) malloc (sizeof(iterator));
    (void )memset(ptrVector->f_iterator, 0, sizeof(iterator));

    ptrVector->capacity                 = s < 8 ? 8 : s;
    ptrVector->cur_size                 = 0;
    ptrVector->push_back                = vector_push_back;
    ptrVector->element_at               = vector_element_at;
    ptrVector->size                     = vector_size;
    ptrVector->empty                    = vector_empty;
    ptrVector->reserve                  = vector_reserve;
    ptrVector->front                    = vector_front;
    ptrVector->back                     = vector_back;
    ptrVector->get_f_iterator           = vector_f_iterator;
    ptrVector->f_iterator->cur_position = 0;
    ptrVector->f_iterator->begin        = vector_begin;
    ptrVector->f_iterator->end          = vector_is_end;
    ptrVector->f_iterator->next         = vector_next;
    ptrVector->f_iterator->prev         = vector_prev;
    ptrVector->f_iterator->is_end       = vector_is_end;
    ptrVector->f_iterator->get_value    = vector_get_value;

    ptrVector->elem = (void **)malloc((sizeof (void *))*ptrVector->capacity);

    ptrVector->_destroy = fn;
}
void    
vector_push_back( VECTOR *vec, void *elem) {

    if ( vec->cur_size  ==  vec->capacity ) {

	vec->capacity = vec->capacity * 2;
	vec->elem = ( void **) realloc ( vec->elem,
	                                 vec->capacity * sizeof ( void *));
    } 
    vec->elem[vec->cur_size] = elem;
    vec->cur_size++;
} 
void *  
vector_element_at( VECTOR *vec, int pos){
    if ( pos > vec->cur_size ) {
	return ( void * ) 0;
    }
    return vec->elem[pos];
}
int
vector_size( VECTOR *vec ) {
    return vec->cur_size;
}
int     
vector_empty ( VECTOR *vec) {
    if ( vec->cur_size == 0 ) {
	return 1;
    }
    return 0;
}
void     
vector_reserve ( VECTOR *vec, int new_size) {
    if ( new_size < vec->capacity )
	return;
    int size      = new_size - vec->capacity;
    vec->capacity = vec->capacity + size;
    vec->elem = ( void ** ) realloc ( vec->elem, sizeof ( void *) * size );
}
void *   
vector_front( VECTOR *vec) {
    return vec->elem[0];
}
void *   
vector_back ( VECTOR *vec) {
    return vec->elem[vec->cur_size - 1 ];
}
iterator *
vector_f_iterator ( VECTOR *vec ) {
    return vec->f_iterator;
}
void *
vector_begin( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    return vec->elem[0];
}
void *
vector_end( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    return vec->elem[vec->cur_size - 1];
}
void
vector_next( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    vec->f_iterator->cur_position++;
}
void
vector_prev( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    vec->f_iterator->cur_position--;
}
int
vector_is_end( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    if ( vec->f_iterator->cur_position > vec->cur_size )
	return 1;
    return 0;
}
void *
vector_get_value ( void *v ) {
    VECTOR *vec = (VECTOR*)v;
    return vec->element_at( vec, vec->f_iterator->cur_position );
}
void vector_destroy ( VECTOR *vec ) {
    int index = 0;
    for ( index = 0; index < vec->size(vec); index++ ) {
	void *element = vec->elem[index];
	(vec->_destroy)(element);
	vec->elem[index] = ( void *) 0;
    }
    if ( vec->elem ) free ( vec->elem );
    if ( vec->f_iterator ) free ( vec->f_iterator );
    if ( vec ) free ( vec );
}

