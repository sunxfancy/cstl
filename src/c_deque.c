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

#include <string.h>

#define CLIB_DEQUE_INDEX(x)  ((char *)(pDeq)->pElements + (sizeof(clib_object) * (x)))

static clib_error 
insert_c_deque ( clib_deque_ptr pDeq, clib_int index, clib_type elem,clib_size elem_size) {
    clib_error rc           = CLIB_ERROR_SUCCESS;
    clib_object_ptr pObject = new_clib_object ( elem, elem_size );
    if ( ! pObject )
        return CLIB_ARRAY_INSERT_FAILED;

    pDeq->pElements[index] = pObject;
    pDeq->no_of_elements++;
    return rc;
}

static clib_deque_ptr
grow_deque ( clib_deque_ptr pDeq ) {

   	pDeq->no_max_elements = pDeq->no_max_elements * 2;
    pDeq->pElements        = (clib_object_ptr *) realloc ( pDeq->pElements, 
                                 pDeq->no_max_elements * sizeof ( clib_object_ptr));
    return pDeq;

}
clib_deque_ptr  
new_c_deque( clib_int deq_size , clib_compare fn_c, clib_destroy fn_d) {

    clib_deque_ptr pDeq = (clib_deque_ptr)clib_malloc(sizeof(clib_deque));
	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->no_max_elements  = deq_size < 8 ? 8 : deq_size;
    pDeq->pElements = (clib_object_ptr *) clib_malloc(pDeq->no_max_elements * sizeof(clib_object_ptr));

	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->compare_fn      = fn_c;
    pDeq->destruct_fn     = fn_d;
    pDeq->head            = (clib_int)pDeq->no_max_elements / 2;
    pDeq->tail            = pDeq->head + 1;
    pDeq->no_of_elements  = 0;    

    return pDeq;
}
clib_error 
push_back_c_deque(clib_deque_ptr pDeq, clib_type elem, clib_size elem_size) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->tail == pDeq->no_max_elements )
        pDeq = grow_deque(pDeq);

    insert_c_deque(pDeq, pDeq->tail, elem, elem_size);
    pDeq->tail++;

    return CLIB_ERROR_SUCCESS;
}
clib_error 
push_front_c_deque(clib_deque_ptr pDeq, clib_type elem,clib_size elem_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;	
    clib_int to        = 0;
    clib_int from      = 0;
    clib_int count     = 0;

    if ( pDeq->head == 0 ) {
        pDeq = grow_deque(pDeq);
        to    = (pDeq->no_max_elements - pDeq->no_of_elements)/2;
        from  = pDeq->head + 1;
        count = pDeq->tail - from + 1;
        memmove (&(pDeq->pElements[to]), &(pDeq->pElements[from]), count * sizeof (clib_object_ptr));
        pDeq->head = to - 1;
        pDeq->tail  = pDeq->head + count;
    }
    insert_c_deque(pDeq, pDeq->head, elem, elem_size);
    pDeq->head--;
    return rc;
}

clib_error     
front_c_deque (clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;
    element_at_c_deque ( pDeq, pDeq->head + 1, elem );
    return CLIB_ERROR_SUCCESS;
}

clib_error 
back_c_deque (clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;
    element_at_c_deque ( pDeq, pDeq->tail - 1, elem );
    return CLIB_ERROR_SUCCESS;
}

clib_error     
pop_back_c_deque (clib_deque_ptr pDeq) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->destruct_fn ) {
        clib_type elem;
        if ( element_at_c_deque( pDeq, pDeq->tail - 1, &elem ) == CLIB_ERROR_SUCCESS ) 
            pDeq->destruct_fn(elem);
    }
    delete_clib_object(pDeq->pElements[pDeq->tail - 1]);
    pDeq->tail--;
    pDeq->no_of_elements--;

    return CLIB_ERROR_SUCCESS;

}

clib_error     
pop_front_c_deque(clib_deque_ptr pDeq) {
    
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->destruct_fn ) {
        clib_type elem;
        if ( element_at_c_deque( pDeq, pDeq->head + 1, &elem ) == CLIB_ERROR_SUCCESS ) 
            pDeq->destruct_fn(elem);
    }
    delete_clib_object(pDeq->pElements[pDeq->head + 1]);

    pDeq->head++;
    pDeq->no_of_elements--;

    return CLIB_ERROR_SUCCESS;
}
clib_bool      
empty_c_deque (clib_deque_ptr pDeq) {
	if ( pDeq == clib_deque_null )
		return clib_true;

    return pDeq->no_of_elements == 0 ? clib_true : clib_false;
}
clib_int 
size_c_deque( clib_deque_ptr pDeq ) {
	if ( pDeq == clib_deque_null )
		return clib_true;

    return pDeq->no_of_elements - 1;
}
clib_error 
element_at_c_deque (clib_deque_ptr pDeq, clib_int index, clib_type *elem) {

    clib_error rc = CLIB_ERROR_SUCCESS;

    if ( ! pDeq )
        return CLIB_DEQUE_NOT_INITIALIZED;

    get_raw_clib_object ( pDeq->pElements[index], elem );
    return rc;
}

clib_error
delete_c_deque ( clib_deque_ptr pDeq ) {
    clib_int i = 0;

	if ( pDeq == clib_deque_null )
		return CLIB_ERROR_SUCCESS;

    if ( pDeq->destruct_fn ) {
        for ( i = pDeq->head + 1; i < pDeq->tail; i++ ){
            clib_type elem;
            if ( element_at_c_deque( pDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                pDeq->destruct_fn(elem);
            }
        }
    }
    for ( i = pDeq->head + 1; i < pDeq->tail; i++ ){
        delete_clib_object(pDeq->pElements[i]);
    }
    clib_free ( pDeq->pElements);
    clib_free ( pDeq );

    return CLIB_ERROR_SUCCESS;
}

