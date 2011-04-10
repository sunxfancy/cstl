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

clib_slist_ptr 
new_c_slist(clib_destroy fn_d, clib_compare fn_c){
    clib_slist_ptr pSlist  = (clib_slist_ptr)clib_malloc(sizeof(clib_slist));
    pSlist->head           = clib_slist_node_null;
    pSlist->destruct_fn    = fn_d;
    pSlist->compare_key_fn = fn_c;
    pSlist->size           = 0;
    return pSlist;
}
void           
delete_c_slist( clib_slist_ptr pSlist){
    while(pSlist->size != 0) {
        remove_c_slist ( pSlist, 0 );
    }
    clib_free ( pSlist );
}

clib_error           
push_back_c_slist( clib_slist_ptr pSlist, clib_type elem, clib_size elem_size){

    clib_slist_node_ptr current  = clib_slist_node_null;
    clib_slist_node_ptr new_node = clib_slist_node_null;

    new_node = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));

    new_node->elem = new_clib_object ( elem, elem_size );
    if ( ! new_node->elem )
        return CLIB_SLIST_INSERT_FAILED;
    new_node->next = clib_slist_node_null;

    if ( pSlist->head == clib_slist_node_null ) {
        pSlist->head = new_node;
        pSlist->size++;
        return CLIB_ERROR_SUCCESS;
    }
    current = pSlist->head;
    while ( current->next != clib_slist_node_null )
        current  = current->next;    
    current->next = new_node;
    pSlist->size++;

    return CLIB_ERROR_SUCCESS;
}
static void 
__remove_c_list ( clib_slist_ptr pSlist, clib_slist_node_ptr pSlistNode ) {
    clib_type elem;
    get_raw_clib_object(pSlistNode->elem, &elem);
    if ( pSlist->destruct_fn) {             
        (pSlist->destruct_fn)(elem);
        delete_clib_object ( pSlistNode->elem );
    }else {
        clib_free ( elem );
        delete_clib_object ( pSlistNode->elem );
    }        
    clib_free ( pSlistNode);
}
void           
remove_c_slist( clib_slist_ptr pSlist, clib_int pos ) {
    clib_int i = 0;

    clib_slist_node_ptr current = pSlist->head;
    clib_slist_node_ptr temp    = clib_slist_node_null;

    if ( pos > pSlist->size ) return;

    if ( pos == 0 ) {                
        pSlist->head = current->next;    
        __remove_c_list(pSlist, current);    
        pSlist->size--;
        return;
    }
    for ( i = 1; i < pos - 1; i++)
        current = current->next;

    temp          = current->next;
    current->next = current->next->next;
    __remove_c_list ( pSlist, temp );

    pSlist->size--;
}
clib_error           
insert_c_slist(clib_slist_ptr pSlist, clib_int pos, clib_type elem, clib_size elem_size) {
    clib_int i = 0;
    clib_slist_node_ptr current  = pSlist->head;
    clib_slist_node_ptr new_node = clib_slist_node_null;
   
    if ( pos == 1 ) {
        new_node       = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));
        new_node->elem = new_clib_object ( elem, elem_size );
        if ( ! new_node->elem ) {
            clib_free ( new_node );
            return CLIB_SLIST_INSERT_FAILED;
        }
        new_node->next = pSlist->head;
        pSlist->head       = new_node;
        pSlist->size++;
        return CLIB_ERROR_SUCCESS;
    }

    if ( pos >= pSlist->size + 1 ) {
        return push_back_c_slist ( pSlist, elem, elem_size );
    }

    for ( i = 1; i < pos - 1; i++) {
        current = current->next;
    }
    new_node       = (clib_slist_node_ptr)clib_malloc(sizeof(clib_slist_node));
    new_node->elem = new_clib_object ( elem, elem_size );
    if ( ! new_node->elem ) {
        clib_free ( new_node );
        return CLIB_SLIST_INSERT_FAILED;
    }

    new_node->next = current->next;
    current->next  = new_node;
    pSlist->size++;

    return CLIB_ERROR_SUCCESS;
}
void           
for_each_c_slist (clib_slist_ptr pSlist, void (*fn)(clib_type )) {
    clib_type elem;
    clib_slist_node_ptr current  = pSlist->head;
    while ( current != clib_slist_node_null ) {
        get_raw_clib_object(current->elem, &elem);
        (fn)(elem);
        clib_free ( elem );
        current = current->next;
    }    
}
clib_bool
find_c_slist (clib_slist_ptr pSlist, clib_type find_value, clib_type *out_value) {
    clib_slist_node_ptr current  = pSlist->head;  
    while ( current != clib_slist_node_null ) {        
        get_raw_clib_object(current->elem, out_value);
        if ((pSlist->compare_key_fn)(find_value,*out_value) != 0){
            break;
        }
        clib_free ( *out_value );
        current = current->next;
    }
    if ( current ) {
        return clib_true;
    }
    return clib_false;
}
