#include "c_lib.h"

#include <stdio.h>


clib_map_ptr 
new_c_map ( clib_compare fn_c_k, clib_destroy fn_k_d,  
            clib_destroy fn_v_d) {

    clib_map_ptr pMap  =  (clib_map_ptr)clib_malloc(sizeof(clib_map));
    if (pMap == clib_map_null)
        return clib_map_null;

    pMap->root  = new_c_rb (fn_c_k, fn_k_d, fn_v_d);
    if (pMap->root == clib_rb_null)
        return clib_map_null;

    return pMap;
}
clib_error   
insert_c_map ( clib_map_ptr pMap, clib_type key, clib_type value, clib_size key_size, clib_size value_size) {
    if (pMap == clib_map_null)
        return CLIB_MAP_NOT_INITIALIZED;

    return insert_c_rb ( pMap->root, key, value, key_size, value_size);
}
clib_bool    
exists_c_map ( clib_map_ptr pMap, clib_type key) {
    clib_bool found = clib_false;
    clib_rb_node_ptr node;

    if (pMap == clib_map_null)
        return clib_false;
    
    node = find_c_rb ( pMap->root, key);
    if ( node != clib_rb_node_null ) {
        return clib_true;
    }
    return found;    
}
clib_error   
remove_c_map ( clib_map_ptr pMap, clib_type key) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_rb_node_ptr node;
    if (pMap == clib_map_null)
        return CLIB_MAP_NOT_INITIALIZED;

    node = remove_c_rb ( pMap->root, key );
    if ( node != clib_rb_node_null ) {
        clib_free ( node->data.key);
        clib_free ( node->data.value);
        clib_free ( node );
    }
    return rc;
}
clib_bool    
find_c_map ( clib_map_ptr pMap, clib_type key, clib_type value) {
    clib_rb_node_ptr node;

    if (pMap == clib_map_null)
        return clib_false;

    node = find_c_rb ( pMap->root, key);
    if ( node == clib_rb_node_null ) 
        return clib_false;

    clib_memcpy ( value, node->data.value, node->value_size);
    return clib_true;

}

clib_error    
delete_c_map ( clib_map_ptr x) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    if ( x != clib_map_null ){
        rc = delete_c_rb ( x->root );
        clib_free ( x );
    }
    return rc;
}
