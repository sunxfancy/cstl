/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

    return insert_c_rb ( pSet->root, key, key_size, clib_null, 0);
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
        /*clib_free ( node->raw_data.key);
        clib_free ( node );*/
    }
    return rc;
}
clib_bool    
find_c_set ( clib_set_ptr pSet, clib_type key, clib_type outKey) {
    clib_rb_node_ptr node;

    if (pSet == clib_set_null)
        return clib_false;

    node = find_c_rb ( pSet->root, key);
    if ( node == clib_rb_node_null ) 
        return clib_false;

    get_raw_clib_object ( node->key, outKey );

    return clib_true;

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
