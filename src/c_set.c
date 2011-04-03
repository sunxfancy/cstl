#include "c_datastructure.h"
#include <stdio.h>

CLIB_SET_PTR 
new_c_set ( CLIB_COMPARE fn_c, CLIB_DESTROY fn_d, CLIB_SIZE elem_size) {

    CLIB_SET_PTR pSet  =  (CLIB_SET_PTR)clib_malloc(sizeof(CLIB_SET));
    if (pSet == CLIB_SET_NULL)
        return CLIB_SET_NULL;

    pSet->root  = new_c_rb (fn_c, fn_d, CLIB_NULL, elem_size, 0);
    if (pSet->root == CLIB_RB_NULL)
        return CLIB_SET_NULL;

    return pSet;
}
CLIB_ERROR   
insert_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key) {
    if (pSet == CLIB_SET_NULL)
        return CLIB_SET_NOT_INITIALIZED;

    return insert_c_rb ( pSet->root, key, 0);
}
CLIB_BOOL    
exists_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key) {
    CLIB_BOOL found = CLIB_FALSE;
    CLIB_RB_NODE_PTR node;

    if (pSet == CLIB_SET_NULL)
        return CLIB_FALSE;
    
    node = find_c_rb ( pSet->root, key);
    if ( node != CLIB_RB_NODE_NULL ) {
        return CLIB_TRUE;
    }
    return found;    
}
CLIB_ERROR   
remove_c_set ( CLIB_SET_PTR pSet, CLIB_TYPE key) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    CLIB_RB_NODE_PTR node;
    if (pSet == CLIB_SET_NULL)
        return CLIB_SET_NOT_INITIALIZED;

    node = remove_c_rb ( pSet->root, key );
    if ( node != CLIB_RB_NODE_NULL ) {
        clib_free ( node->data.key);
        clib_free ( node );
    }
    return rc;
}

CLIB_ERROR    
delete_c_set ( CLIB_SET_PTR x) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    if ( x != CLIB_SET_NULL ){
        rc = delete_c_rb ( x->root );
        clib_free ( x );
    }
    return rc;
}
