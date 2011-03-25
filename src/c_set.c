#include "c_set.h"

#define VALIDATE_SET_PTR if ( x == SET_NULL ) return 0;
#define VALIDATE_KEY_PTR if ( !k ) return 0;	

SET_PTR 
new_c_set( destroy fn_d, compare fn_c) {

    SET_PTR x  =  (SET_PTR ) c_malloc ( sizeof ( c_set ));

    x->fn_destroy =  fn_d;
    x->fn_compare =  fn_c;

    x->root  = new_c_rb ( fn_d, fn_c, 1);
    return x;
}
CLIB_ERROR    
delete_c_set ( SET_PTR x) {
    CLIB_ERROR rc =  CLIB_SUCCESS;
    VALIDATE_SET_PTR;

    delete_c_rb ( x->root );
    c_free ( x );

    return rc;
}
CLIB_ERROR 
insert_c_set ( SET_PTR x, TYPE k) {
    CLIB_ERROR rc =  CLIB_SUCCESS;
    VALIDATE_SET_PTR;
    VALIDATE_KEY_PTR;

    rc = insert_c_rb ( x->root, k, CLIB_NULL );

    return rc;
}
CLIB_ERROR
remove_c_set ( SET_PTR x, TYPE k ) {
    CLIB_ERROR rc =  CLIB_SUCCESS;
    VALIDATE_SET_PTR;
    VALIDATE_KEY_PTR;

    rc = remove_c_rb ( x->root, k );

    return rc;
}
int
exists_c_set( SET_PTR x, TYPE k ) {
    TYPE y = find_c_rb ( x->root, k );
    if ( y == CLIB_NULL )
	return 0;	
    return 1;
}
