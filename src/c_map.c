#include "c_datastructure.h"
#ifdef ABC
CLIB_MAP_PTR 
new_c_map ( CLIB_DESTROY fn_ed, CLIB_DESTROY fn_vd, CLIB_COMPARE fn_c) {
    CLIB_MAP_PTR x  =  (CLIB_MAP_PTR ) clib_malloc ( sizeof ( CLIB_SET ));
    x->root         =  new_c_rb ( fn_ed, fn_vd, fn_c, CLIB_MAP_TYPE);
    return x;
}

void    
delete_c_map ( CLIB_MAP_PTR x) {
	if ( x != CLIB_MAP_NULL ){
	    delete_c_rb ( x->root );
		clib_free ( x );
	}
}

void
insert_c_map ( CLIB_MAP_PTR x, CLIB_TYPE k, CLIB_TYPE v) {
	if ( x != CLIB_MAP_NULL && k && v ) {
	    insert_c_rb ( x->root, k, v, CLIB_RB_VALUE_COPY );
	}
}

void
remove_c_map ( CLIB_MAP_PTR x, CLIB_TYPE k ) {
	CLIB_RB_NODE_PTR t_node;
	CLIB_TYPE key, val;
	if ( x != CLIB_MAP_NULL && k  ) {
		t_node = remove_c_rb ( x->root, k );
		if ( !t_node ) {
			return;
		}
		key = t_node->value._key;
		val = t_node->value._value;
		clib_free ( key );
		clib_free ( val );
		clib_free ( t_node );
	}    
}

CLIB_TYPE    
find_c_map( CLIB_MAP_PTR x, CLIB_TYPE k) {
	CLIB_TYPE y;

	if ( x == CLIB_MAP_NULL || !k )
		return CLIB_ERROR_SUCCESS;

	y = find_c_rb ( x->root, k );
	return y;
}
#endif
