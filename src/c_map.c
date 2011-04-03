#include "c_lib.h"

#include <stdio.h>


CLIB_MAP_PTR 
new_c_map ( CLIB_COMPARE fn_c_k, CLIB_DESTROY fn_k_d,  
            CLIB_DESTROY fn_v_d, CLIB_SIZE key_elem_size,
            CLIB_SIZE val_elem_size) {

    CLIB_MAP_PTR pMap  =  (CLIB_MAP_PTR)clib_malloc(sizeof(CLIB_MAP));
    if (pMap == CLIB_MAP_NULL)
        return CLIB_MAP_NULL;

    pMap->root  = new_c_rb (fn_c_k, fn_k_d, fn_v_d, key_elem_size, val_elem_size);
    if (pMap->root == CLIB_RB_NULL)
        return CLIB_MAP_NULL;

    return pMap;
}
CLIB_ERROR   
insert_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key, CLIB_TYPE value) {
    if (pMap == CLIB_MAP_NULL)
        return CLIB_MAP_NOT_INITIALIZED;

    return insert_c_rb ( pMap->root, key, value);
}
CLIB_BOOL    
exists_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key) {
    CLIB_BOOL found = CLIB_FALSE;
    CLIB_RB_NODE_PTR node;

    if (pMap == CLIB_MAP_NULL)
        return CLIB_FALSE;
    
    node = find_c_rb ( pMap->root, key);
    if ( node != CLIB_RB_NODE_NULL ) {
        return CLIB_TRUE;
    }
    return found;    
}
CLIB_ERROR   
remove_c_map ( CLIB_MAP_PTR pMap, CLIB_TYPE key) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    CLIB_RB_NODE_PTR node;
    if (pMap == CLIB_MAP_NULL)
        return CLIB_MAP_NOT_INITIALIZED;

    node = remove_c_rb ( pMap->root, key );
    if ( node != CLIB_RB_NODE_NULL ) {
        clib_free ( node->data.key);
        clib_free ( node->data.value);
        clib_free ( node );
    }
    return rc;
}

CLIB_ERROR    
delete_c_map ( CLIB_MAP_PTR x) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    if ( x != CLIB_MAP_NULL ){
        rc = delete_c_rb ( x->root );
        clib_free ( x );
    }
    return rc;
}
