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

#define CLIB_DEQUE_INDEX(x)  ((char *)(pDeq)->elements + ((pDeq)->size_of_element * (x)))

static clib_error 
insert_c_deque ( clib_deque_ptr pDeq, int index, clib_type elem,clib_size e_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_element_ptr tmp;

    size_t deq_element_size = sizeof(clib_element);

    tmp        = (clib_element_ptr)clib_malloc(deq_element_size);
    tmp->size  = e_size;
    tmp->elem  = ( clib_type) clib_malloc ( e_size );

    clib_memcpy ( tmp->elem, elem, e_size);

    clib_memcpy (((char*)pDeq->pElements + (index * deq_element_size)), 
            tmp, 
            deq_element_size);

    pDeq->no_of_elements++;
    clib_free ( tmp );
    return rc;
}

static clib_deque_ptr
grow_deque ( clib_deque_ptr pDeq ) {

   	pDeq->no_max_elements = pDeq->no_max_elements * 2;
    pDeq->pElements = ( clib_type) realloc (pDeq->pElements,
                        (pDeq->no_max_elements * sizeof(clib_element)));
    return pDeq;

}
clib_deque_ptr  
new_c_deque( int deq_size , clib_compare fn_c, clib_destroy fn_d) {

    clib_deque_ptr pDeq = (clib_deque_ptr)clib_malloc(sizeof(clib_deque));
	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->no_max_elements  = deq_size < 8 ? 8 : deq_size;

    pDeq->pElements = (clib_type)
        clib_malloc(pDeq->no_max_elements * sizeof(clib_element));

	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->compare_fn      = fn_c;
    pDeq->destruct_fn     = fn_d;
    pDeq->head            = (int)pDeq->no_max_elements / 2;
    pDeq->tail            = pDeq->head + 1;
    pDeq->no_of_elements  = 0;    

    return pDeq;
}
clib_error 
push_back_c_deque(clib_deque_ptr pDeq, clib_type elem, clib_size e_size) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->tail == pDeq->no_max_elements )
        pDeq = grow_deque(pDeq);

    insert_c_deque(pDeq, pDeq->tail, elem, e_size);
    pDeq->tail++;

    return CLIB_ERROR_SUCCESS;
}
clib_error 
push_front_c_deque(clib_deque_ptr pDeq, clib_type elem,clib_size e_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;	
    int to       = 0;
    int from     = 0;
    int count    = 0;
    size_t deq_element_size = sizeof(clib_element);

    if ( pDeq->head == 0 ) {
        pDeq = grow_deque(pDeq);

        to    = (pDeq->no_max_elements - pDeq->no_of_elements)/2;
	    from  = pDeq->head + 1;
	    count = pDeq->tail - from + 1;

	    memmove ((char*)pDeq->pElements + (to * deq_element_size), 
                 (char*)pDeq->pElements + (from * deq_element_size), 
                 count * sizeof(clib_element));

	    pDeq->head = to - 1;
	    pDeq->tail  = pDeq->head + count;
    }
    insert_c_deque(pDeq, pDeq->head, elem, e_size);
    pDeq->head--;
    return rc;
}

clib_error     
front_c_deque (clib_deque_ptr pDeq, clib_type elem) {

    clib_element temp;
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy ( &temp, 
            (char*)pDeq->pElements + ((pDeq->head + 1) * sizeof(clib_element)),
            sizeof(clib_element));
    clib_memcpy(elem, temp.elem, temp.size);

    return CLIB_ERROR_SUCCESS;

}
clib_error 
back_c_deque (clib_deque_ptr pDeq, clib_type elem) {
    clib_element temp;

	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy ( &temp, 
            (char*)pDeq->pElements + ((pDeq->tail - 1) * sizeof(clib_element)),
            sizeof(clib_element));
    clib_memcpy(elem, temp.elem, temp.size);



    return CLIB_ERROR_SUCCESS;
}
clib_error     
pop_back_c_deque (clib_deque_ptr pDeq, clib_type elem) {
    clib_element temp;

	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    back_c_deque( pDeq, elem);


    clib_memcpy ( &temp, 
                 (char*)pDeq->pElements + ((pDeq->tail - 1 )* sizeof(clib_element)),
                 sizeof(clib_element));
    clib_free ( temp.elem);
    pDeq->tail--;
    pDeq->no_of_elements--;

    return CLIB_ERROR_SUCCESS;

}
clib_error     
pop_front_c_deque(clib_deque_ptr pDeq, clib_type elem) {
    clib_element temp;

	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    front_c_deque ( pDeq, elem );
    clib_memcpy ( &temp, 
                 (char*)pDeq->pElements + ((pDeq->head + 1 )* sizeof(clib_element)),
                 sizeof(clib_element));
    clib_free ( temp.elem);

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
int 
size_c_deque( clib_deque_ptr pDeq ) {
	if ( pDeq == clib_deque_null )
		return clib_true;

    return pDeq->no_of_elements - 1;
}
extern clib_error 
element_at_c_deque (clib_deque_ptr pDeq, int index,clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_element temp;

	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( index < 0 || index > pDeq->no_max_elements )
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    if ( index < pDeq->head || index > pDeq->tail)
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    clib_memcpy ( &temp, 
            (char*)pDeq->pElements + (index * sizeof(clib_element)),
            sizeof(clib_element));
    clib_memcpy(elem, temp.elem, temp.size);

    return rc;
}

clib_error
delete_c_deque ( clib_deque_ptr pDeq ) {
    int i = 0;

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
        clib_element temp;
        clib_memcpy ( &temp, 
                      (char*)pDeq->pElements + (i * sizeof(clib_element)),
                      sizeof(clib_element));
        clib_free ( temp.elem);
    }
    clib_free ( pDeq->pElements);
    clib_free ( pDeq );

    return CLIB_ERROR_SUCCESS;
}
