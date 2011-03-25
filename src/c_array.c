#include "c_array.h"
#include <stdlib.h>
#include <string.h>

ARRAY_PTR  
new_c_array( int size, destroy fn_destroy, compare fn_compare) {
    int s = 0;
    ARRAY_PTR array;

    s = size < 8 ? 8 : size;
    array  = ( ARRAY_PTR ) malloc (sizeof ( c_array ));
    array->capacity    = s;
    array->compare_fn  = fn_compare;
    array->destruct_fn = fn_destroy;
    array->cur_size    = 0;
    array->_elem       = (TYPE*)calloc(s, sizeof(TYPE));

    return array;
}
void 
delete_c_array( ARRAY_PTR array) {
    int i = 0;
    for ( i = 0; i < array->cur_size; i++) {
	(array->destruct_fn)(array->_elem[i]);
    }
}
void
push_back_c_array ( ARRAY_PTR array, TYPE value ) {
    int new_size = array->capacity * 2;
    if ( array->cur_size == array->capacity ) {
	array->_elem = ( TYPE*) realloc ( array->_elem, 
					  sizeof ( TYPE) * new_size);
	array->capacity = new_size;
    }
    array->_elem[array->cur_size++] = value;
}
TYPE
element_at_c_array ( ARRAY_PTR array, int pos ) {
    return array->_elem[pos];
}
int
size_c_array ( ARRAY_PTR  array ){
    return array->cur_size;
}
int 
empty_c_array ( ARRAY_PTR  array ) {
    return ( array->cur_size == 0 );
}
int
capacity_c_array ( ARRAY_PTR array ) {
    return array->capacity;
}
void
reserve_c_array ( ARRAY_PTR array , int size) {
    if ( array->capacity >= size )
	return;
    array->_elem = ( TYPE*) realloc ( array->_elem, sizeof ( TYPE) * size);
    array->capacity = size;
}
TYPE
front_c_array ( ARRAY_PTR   array) {
    return array->_elem[0];
}
TYPE
back_c_array ( ARRAY_PTR   array){
    return array->_elem[array->cur_size-1];
}
void
pop_back_c_array ( ARRAY_PTR array ) {
    (array->destruct_fn)(back_c_array(array));
    array->cur_size = array->cur_size - 1;
}
void 
insert_c_array ( ARRAY_PTR   array, int pos, TYPE value) {
    int new_size = array->capacity * 2;
    if ( array->capacity == array->cur_size ){
	array->_elem = ( TYPE*) realloc ( array->_elem, 
					  sizeof ( TYPE) * new_size);
    }
    memmove (&(array->_elem[pos + 1]), 
	     &(array->_elem[pos]), 
	     (array->cur_size - pos) * sizeof (TYPE));
    array->_elem[pos] = value;
    array->cur_size++;
}

void 
for_each_c_array(ARRAY_PTR   array, void (*fn)(void*)) {
    int i = 0;
    for ( i = 0; i < array->cur_size; i++ ) {
	(fn)(array->_elem[i]);
    }
}

int 
is_equal_to_c_array ( ARRAY_PTR arrL, ARRAY_PTR  arrR) {
    int i = 0;
    int rc = 0;
    if ( arrL->cur_size != arrR->cur_size ) 
	return 1;
    if ( arrL->compare_fn != arrR->compare_fn ) 
	return 1;

    for ( i = 0; i < arrL->cur_size; i++){
	if ( (arrL->compare_fn)(arrL->_elem[i], arrR->_elem[i]) != 1 ){
	    rc = 1;
	    break;
	}

    }
    return rc;
}
