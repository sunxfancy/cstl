#include "c_array.h"
#include <stdlib.h>
#include <string.h>

c_array * 
new_c_array( int size, destroy fn_destroy, compare fn_compare) {
	int s = 0;
	c_array *_AR;

	s = size < 8 ? 8 : size;
	_AR  = ( c_array *) malloc (sizeof ( c_array ));
	_AR->capacity    = s;
	_AR->compare_fn  = fn_compare;
	_AR->destruct_fn = fn_destroy;
	_AR->cur_size    = 0;
	_AR->_elem       = ( void **) calloc ( s , sizeof ( void *));

	return _AR;
}
void 
delete_c_array( c_array *_AR) {
	int i = 0;
	for ( i = 0; i < _AR->cur_size; i++) {
		(_AR->destruct_fn)(_AR->_elem[i]);
	}
}
void
push_back_c_array ( c_array *_AR, void *value ) {
	int new_size = _AR->capacity * 2;
	if ( _AR->cur_size == _AR->capacity ) {
		_AR->_elem = ( void **) realloc ( _AR->_elem, 
		                                  sizeof ( void *) * new_size);
		_AR->capacity = new_size;
	}
	_AR->_elem[_AR->cur_size++] = value;
}
void *
element_at_c_array ( c_array *_AR, int pos ) {
	return _AR->_elem[pos];
}
int
size_c_array ( c_array * _AR ){
	return _AR->cur_size;
}
int 
empty_c_array ( c_array * _AR ) {
	return ( _AR->cur_size == 0 );
}
int
capacity_c_array ( c_array *_AR ) {
	return _AR->capacity;
}
void
reserve_c_array ( c_array *_AR , int size) {
	if ( _AR->capacity >= size )
		return;
	_AR->_elem = ( void **) realloc ( _AR->_elem, sizeof ( void *) * size);
	_AR->capacity = size;
}
void *
front_c_array ( c_array* _AR) {
	return _AR->_elem[0];
}
void *
back_c_array ( c_array* _AR){
	return _AR->_elem[_AR->cur_size-1];
}
void
pop_back_c_array ( c_array *_AR ) {
	(_AR->destruct_fn)(back_c_array(_AR));
	_AR->cur_size = _AR->cur_size - 1;
}
void insert_c_array ( c_array* _AR, int pos, void *value) {
	int new_size = _AR->capacity * 2;
	if ( _AR->capacity == _AR->cur_size ){
		_AR->_elem = ( void **) realloc ( _AR->_elem, 
		                                  sizeof ( void *) * new_size);
	}
	memmove (&(_AR->_elem[pos + 1]), 
	         &(_AR->_elem[pos]), 
		 (_AR->cur_size - pos) * sizeof (void *));
	_AR->_elem[pos] = value;
	_AR->cur_size++;
}

void 
for_each_c_array(c_array* _AR, void (*fn)(void*)) {
	int i = 0;
	for ( i = 0; i < _AR->cur_size; i++ ) {
		(fn)(_AR->_elem[i]);
	}
}

int 
is_equal_to_c_array ( c_array *arrL, c_array*arrR) {
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
