#include "c_deque.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void
resize_deque(c_deque *_DQ)
{
	int new_size        = _DQ->_size * 2;
	void **new_deque    = (void **) calloc ( new_size, sizeof ( void *));

	memmove ( &(new_deque[5]),&(_DQ->_EL[_DQ->_F_I]), _DQ->_size);
	_DQ->_size = new_size;
	free ( _DQ->_EL );
	_DQ->_EL = new_deque;
}

c_deque * 
new_c_deque(int size , destroy fn_destroy, compare fn_compare) {

	c_deque* _DQ       = ( c_deque *) malloc ( sizeof ( c_deque ));
	_DQ->_size         = size < 8 ? 8 : size;
	_DQ->_fn_compare   = fn_compare;
	_DQ->_fn_destroy   = fn_destroy;
	_DQ->_F_I          = (int)size / 2;
	_DQ->_B_I          = _DQ->_F_I + 1;
	_DQ->_current_size = 0;
	_DQ->_EL         = ( void **) calloc ( _DQ->_size, sizeof ( void *));

	return _DQ;
}
void 
delete_c_deque ( c_deque *_DQ ) {
	int i  = 0 ;
	for ( i = 0; i < _DQ->_size; i++ ) {
		if ( _DQ->_EL[i] ) {
			(_DQ->_fn_destroy)(_DQ->_EL[i]);
		}
	}
	free ( _DQ );
}
int 
size_c_deque( c_deque *_DQ ) {
	return _DQ->_size;
}
int 
empty_c_deque( c_deque *_DQ){
	return _DQ->_size == 0;
}
void *
front_c_deque ( c_deque* _DQ) {
	return _DQ->_EL[_DQ->_F_I + 1];
}
void *
back_c_deque ( c_deque* _DQ) {
	return _DQ->_EL[_DQ->_B_I - 1];
}
void 
push_back_c_deque(c_deque* _DQ, void* value) {
	if ( _DQ->_B_I == _DQ->_size ){
		_DQ->_size = _DQ->_size * 2;
		_DQ->_EL = ( void **) realloc ( _DQ->_EL, 
		                                _DQ->_size * sizeof ( void *));
	}
	_DQ->_EL[_DQ->_B_I++] = value;
	_DQ->_current_size++;
}
void 
push_front_c_deque(c_deque* _DQ, void* value) {
	int _TO    = 0;
	int _FROM  = 0;
	int _COUNT = 0;
	if ( _DQ->_F_I == 0 ) {
		int new_size = _DQ->_size * 2;
		_DQ->_EL   = ( void **) realloc ( _DQ->_EL, 
			                          new_size * sizeof ( void *));

		_TO    = (int)(new_size - _DQ->_current_size)/2;
		_FROM  = _DQ->_F_I + 1;
		_COUNT = _DQ->_B_I - _FROM + 1;

		memmove (&(_DQ->_EL[_TO]), 
				 &(_DQ->_EL[_FROM]), 
				 _COUNT * sizeof (void *));

		_DQ->_size        = new_size;
		_DQ->_F_I = _TO - 1;
		_DQ->_B_I  = _DQ->_F_I + _COUNT;
	}
	_DQ->_EL[_DQ->_F_I--] = value;
	_DQ->_current_size++;
}
void
pop_back_c_deque ( c_deque* _DQ ) {
	void *elem = back_c_deque( _DQ );
	(_DQ->_fn_destroy)(elem);
	_DQ->_B_I--;
	_DQ->_current_size--;
}
void
pop_front_c_deque ( c_deque* _DQ ) {
	void *elem = front_c_deque ( _DQ );
	(_DQ->_fn_destroy)(elem);
	_DQ->_F_I++;
	_DQ->_current_size--;
}
void 
for_each_c_deque(c_deque* _DQ, void (*fn)(void*)) {
	int i  = 0 ;
	for ( i = _DQ->_F_I + 1; i < _DQ->_B_I; i++ ) {
		if ( _DQ->_EL[i] ) {
			(fn)(_DQ->_EL[i]);
		}
	}
}

