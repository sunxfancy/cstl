#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CLIB_DEQUE_PTR  
new_c_deque(int size , CLIB_DESTROY fn_destroy, CLIB_COMPARE fn_compare) {

    CLIB_DEQUE_PTR deq  = ( CLIB_DEQUE_PTR ) clib_malloc ( sizeof ( c_deque ));
    deq->_size          = size < 8 ? 8 : size;
    deq->_fn_compare    = fn_compare;
    deq->_fn_destroy    = fn_destroy;
    deq->_front_index   = (int)size / 2;
    deq->_back_index    = deq->_front_index + 1;
    deq->_current_size  = 0;
    deq->_elements      = ( CLIB_TYPE*) calloc ( deq->_size, sizeof ( CLIB_TYPE));

    return deq;
}
void 
delete_c_deque ( CLIB_DEQUE_PTR deq ) {
    int i  = 0 ;
    for ( i = 0; i < deq->_size; i++ ) {
	if ( deq->_elements[i] ) 
	    (deq->_fn_destroy)(deq->_elements[i]);
    }
    clib_free ( deq->_elements);
    clib_free ( deq );
}
int 
size_c_deque( CLIB_DEQUE_PTR deq ) {
    return deq->_size;
}
int 
empty_c_deque( CLIB_DEQUE_PTR deq){
    return deq->_size == 0;
}
CLIB_TYPE
front_c_deque ( CLIB_DEQUE_PTR   deq) {
    return deq->_elements[deq->_front_index + 1];
}
CLIB_TYPE
back_c_deque ( CLIB_DEQUE_PTR   deq) {
    return deq->_elements[deq->_back_index - 1];
}
void 
push_back_c_deque(CLIB_DEQUE_PTR   deq, void* value) {
    if ( deq->_back_index == deq->_size ){
	deq->_size = deq->_size * 2;
	deq->_elements = ( CLIB_TYPE*) realloc ( deq->_elements, 
						 deq->_size * sizeof ( CLIB_TYPE));
    }
    deq->_elements[deq->_back_index++] = value;
    deq->_current_size++;
}
void 
push_front_c_deque(CLIB_DEQUE_PTR   deq, void* value) {
    int _TO      = 0;
    int _FROM    = 0;
    int _COUNT   = 0;
    int new_size = 0;

    if ( deq->_front_index == 0 ) {
	new_size = deq->_size * 2;
	CLIB_TYPE *temp_elem  = (CLIB_TYPE*)realloc( deq->_elements, new_size * sizeof (CLIB_TYPE));
	if ( temp_elem != CLIB_NULL ) {
	    deq->_elements    = temp_elem;
	} else {
	    abort();
	}
	_TO    = (int)(new_size - deq->_current_size)/2;
	_FROM  = deq->_front_index + 1;
	_COUNT = deq->_back_index - _FROM + 1;

	memmove (&(deq->_elements[_TO]), 
		 &(deq->_elements[_FROM]), 
		 _COUNT * sizeof (CLIB_TYPE));

	deq->_size        = new_size;
	deq->_front_index = _TO - 1;
	deq->_back_index  = deq->_front_index + _COUNT;
    }
    deq->_elements[deq->_front_index--] = value;
    deq->_current_size++;
}
void
pop_back_c_deque ( CLIB_DEQUE_PTR   deq ) {
    CLIB_TYPE elem = back_c_deque( deq );
    (deq->_fn_destroy)(elem);
    deq->_back_index--;
    deq->_current_size--;
}
void
pop_front_c_deque ( CLIB_DEQUE_PTR   deq ) {
    CLIB_TYPE elem = front_c_deque ( deq );
    (deq->_fn_destroy)(elem);
    deq->_front_index++;
    deq->_current_size--;
}
void 
for_each_c_deque(CLIB_DEQUE_PTR   deq, void (*fn)(void*)) {
    int i  = 0 ;
    for ( i = deq->_front_index + 1; i < deq->_back_index; i++ ) {
	if ( deq->_elements[i] ) {
	    (fn)(deq->_elements[i]);
	}
    }
}

