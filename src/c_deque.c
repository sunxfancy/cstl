#include "c_lib.h"

#include <string.h>

#define CLIB_DEQUE_INDEX(x)  ((char *)(pDeq)->elements + ((pDeq)->size_of_element * (x)))

static clib_error 
insert_c_deque ( clib_deque_ptr pDeq, int index, clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;

    clib_memcpy ( CLIB_DEQUE_INDEX(index), elem, pDeq->size_of_element);
    pDeq->no_of_elements++;
    return rc;
}

static clib_deque_ptr
grow_deque ( clib_deque_ptr pDeq ) {
   	pDeq->no_max_elements = pDeq->no_max_elements * 2;
        pDeq->elements = ( clib_type*) realloc (pDeq->elements,
                                                pDeq->no_max_elements * pDeq->size_of_element);
    return pDeq;
}
clib_deque_ptr  
new_c_deque( int deq_size , clib_compare fn_c, clib_destroy fn_d, clib_size elem_size) {

    clib_deque_ptr pDeq = (clib_deque_ptr)clib_malloc(sizeof(clib_deque));
	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->no_max_elements  = deq_size < 8 ? 8 : deq_size;
    pDeq->size_of_element = elem_size;

    pDeq->elements = (clib_type)clib_malloc(pDeq->no_max_elements * pDeq->size_of_element);
	if ( pDeq == clib_deque_null )
		return clib_deque_null;

    pDeq->compare_fn      = fn_c;
    pDeq->destruct_fn     = fn_d;
    pDeq->head            = (int)deq_size / 2;
    pDeq->tail            = pDeq->head + 1;
    pDeq->no_of_elements  = 0;
    

    return pDeq;
}
clib_error 
push_back_c_deque(clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->tail == pDeq->no_max_elements )
        pDeq = grow_deque(pDeq);

    insert_c_deque(pDeq, pDeq->tail, elem);
    pDeq->tail++;
    return CLIB_ERROR_SUCCESS;
}
clib_error 
push_front_c_deque(clib_deque_ptr pDeq, clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;	
    int to       = 0;
    int from     = 0;
    int count    = 0;

    if ( pDeq->head == 0 ) {
        pDeq = grow_deque(pDeq);

        to    = (pDeq->no_max_elements - pDeq->no_of_elements)/2;
	    from  = pDeq->head + 1;
	    count = pDeq->tail - from + 1;

	    memmove (CLIB_DEQUE_INDEX(to), 
                 CLIB_DEQUE_INDEX(from), 
                 count * pDeq->size_of_element);

	    pDeq->head = to - 1;
	    pDeq->tail  = pDeq->head + count;
    }
    insert_c_deque(pDeq, pDeq->head, elem);
    pDeq->head--;
    return rc;
}

clib_error     
front_c_deque (clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy(elem, 
                CLIB_DEQUE_INDEX(pDeq->head + 1), 
                pDeq->size_of_element);

    return CLIB_ERROR_SUCCESS;

}
clib_error 
back_c_deque (clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy(elem, 
                CLIB_DEQUE_INDEX(pDeq->tail - 1), 
                pDeq->size_of_element);

    return CLIB_ERROR_SUCCESS;
}
clib_error     
pop_back_c_deque (clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    back_c_deque( pDeq, elem);
    pDeq->tail--;
    pDeq->no_of_elements--;

    return CLIB_ERROR_SUCCESS;

}
clib_error     
pop_front_c_deque(clib_deque_ptr pDeq, clib_type elem) {
	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    front_c_deque ( pDeq, elem );
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

	if ( pDeq == clib_deque_null )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( index < 0 || index > pDeq->no_max_elements )
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    if ( index < pDeq->head || index > pDeq->tail)
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    clib_memcpy(elem, CLIB_DEQUE_INDEX(index), pDeq->size_of_element);
    return rc;
}

clib_error
delete_c_deque ( clib_deque_ptr pDeq ) {
	if ( pDeq == clib_deque_null )
		return CLIB_ERROR_SUCCESS;

    if ( pDeq->destruct_fn ) {
        int i = 0;
        for ( i = pDeq->head + 1; i < pDeq->tail; i++ ){
            clib_type elem;
            if ( element_at_c_deque( pDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                pDeq->destruct_fn(elem);
            }
        }
    }
    clib_free ( pDeq->elements);
    clib_free ( pDeq );

    return CLIB_ERROR_SUCCESS;
}
