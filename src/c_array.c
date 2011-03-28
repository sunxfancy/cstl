#include "c_datastructure.h"
#include <stdlib.h>
#include <string.h>

CLIB_ARRAY_PTR  
new_c_array( int size, CLIB_DESTROY fn_destroy, CLIB_COMPARE fn_compare) {
    int s = 0;
    CLIB_ARRAY_PTR array;

    s = size < 8 ? 8 : size;
    array  = ( CLIB_ARRAY_PTR ) clib_malloc (sizeof ( CLIB_ARRAY ));
    array->capacity    = s;
    array->compare_key_fn  = fn_compare;
    array->destruct_fn = fn_destroy;
    array->cur_size    = 0;
    array->_elem       = (CLIB_TYPE*)calloc(s, sizeof(CLIB_TYPE));

    return array;
}
void 
delete_c_array( CLIB_ARRAY_PTR array) {
    int i = 0;
    for ( i = 0; i < array->cur_size; i++) {
        (array->destruct_fn)(array->_elem[i]);
    }
    clib_free ( array->_elem );
    if ( array ) {
        clib_free ( array );
    }
}
void
push_back_c_array ( CLIB_ARRAY_PTR array, CLIB_TYPE value ) {
    int new_size = array->capacity * 2;
    if ( array->cur_size == array->capacity ) {
        array->_elem = ( CLIB_TYPE*) realloc ( array->_elem, 
                sizeof ( CLIB_TYPE) * new_size);
        array->capacity = new_size;
    }
    array->_elem[array->cur_size++] = value;
}
CLIB_TYPE
element_at_c_array ( CLIB_ARRAY_PTR array, int pos ) {
    return array->_elem[pos];
}
int
size_c_array ( CLIB_ARRAY_PTR  array ){
    return array->cur_size;
}
int 
empty_c_array ( CLIB_ARRAY_PTR  array ) {
    return ( array->cur_size == 0 );
}
int
capacity_c_array ( CLIB_ARRAY_PTR array ) {
    return array->capacity;
}
void 
    reserve_c_array ( CLIB_ARRAY_PTR array , int size) {
        if ( array->capacity >= size )
            return;
        array->_elem = ( CLIB_TYPE*) realloc ( array->_elem, sizeof ( CLIB_TYPE) * size);
        array->capacity = size;
    }
CLIB_TYPE
front_c_array ( CLIB_ARRAY_PTR   array) {
    return array->_elem[0];
}
CLIB_TYPE
back_c_array ( CLIB_ARRAY_PTR   array){
    return array->_elem[array->cur_size-1];
}
void
pop_back_c_array ( CLIB_ARRAY_PTR array ) {
    (array->destruct_fn)(back_c_array(array));
    array->cur_size = array->cur_size - 1;
}
void 
insert_c_array ( CLIB_ARRAY_PTR   array, int pos, CLIB_TYPE value) {
    int new_size = array->capacity * 2;
    if ( array->capacity == array->cur_size ){
        array->_elem = ( CLIB_TYPE*) realloc ( array->_elem, 
                sizeof ( CLIB_TYPE) * new_size);
    }
    memmove (&(array->_elem[pos + 1]), 
            &(array->_elem[pos]), 
            (array->cur_size - pos) * sizeof (CLIB_TYPE));
    array->_elem[pos] = value;
    array->cur_size++;
}

void 
for_each_c_array(CLIB_ARRAY_PTR   array, void (*fn)(void*)) {
    int i = 0;
    for ( i = 0; i < array->cur_size; i++ ) {
        (fn)(array->_elem[i]);
    }
}

int 
is_equal_to_c_array ( CLIB_ARRAY_PTR arrL, CLIB_ARRAY_PTR  arrR) {
    int i = 0;
    int rc = 0;
    if ( arrL->cur_size != arrR->cur_size ) 
        return 1;
    if ( arrL->compare_key_fn != arrR->compare_key_fn ) 
        return 1;

    for ( i = 0; i < arrL->cur_size; i++){
        if ( (arrL->compare_key_fn)(arrL->_elem[i], arrR->_elem[i]) != 1 ){
            rc = 1;
            break;
        }

    }
    return rc;
}
