#include "c_lib.h"

#include <stdio.h>

clib_set_ptr 
new_c_set ( clib_compare fn_c, clib_destroy fn_d) {

    clib_set_ptr pSet  =  (clib_set_ptr)clib_malloc(sizeof(clib_set));
    if (pSet == clib_set_null)
        return clib_set_null;

    pSet->root  = new_c_rb (fn_c, fn_d, clib_null);
    if (pSet->root == clib_rb_null)
        return clib_set_null;

    return pSet;
}
clib_error   
insert_c_set (clib_set_ptr pSet, clib_type key, clib_size key_size) {
    if (pSet == clib_set_null)
        return CLIB_SET_NOT_INITIALIZED;

    return insert_c_rb ( pSet->root, key, 0, key_size , 0);
}
clib_bool    
exists_c_set ( clib_set_ptr pSet, clib_type key) {
    clib_bool found = clib_false;
    clib_rb_node_ptr node;

    if (pSet == clib_set_null)
        return clib_false;
    
    node = find_c_rb ( pSet->root, key);
    if ( node != clib_rb_node_null ) {
        return clib_true;
    }
    return found;    
}
clib_error   
remove_c_set ( clib_set_ptr pSet, clib_type key) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_rb_node_ptr node;
    if (pSet == clib_set_null)
        return CLIB_SET_NOT_INITIALIZED;

    node = remove_c_rb ( pSet->root, key );
    if ( node != clib_rb_node_null ) {
        clib_free ( node->data.key);
        clib_free ( node );
    }
    return rc;
}

clib_error    
delete_c_set ( clib_set_ptr x) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    if ( x != clib_set_null ){
        rc = delete_c_rb ( x->root );
        clib_free ( x );
    }
    return rc;
}
