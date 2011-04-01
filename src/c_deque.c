#include "c_datastructure.h"
#include <string.h>

#define CLIB_DEQUE_INDEX(x)  ((char *)(pDeq)->elements + ((pDeq)->size_of_element * (x)))

static CLIB_ERROR 
insert_c_deque ( CLIB_DEQUE_PTR pDeq, int index, CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

    clib_memcpy ( CLIB_DEQUE_INDEX(index), elem, pDeq->size_of_element);
    pDeq->no_of_elements++;
    return rc;
}

static CLIB_DEQUE_PTR
grow_deque ( CLIB_DEQUE_PTR pDeq ) {
   	pDeq->no_max_elements = pDeq->no_max_elements * 2;
        pDeq->elements = ( CLIB_TYPE*) realloc (pDeq->elements,
                                                pDeq->no_max_elements * pDeq->size_of_element);
    return pDeq;
}
CLIB_DEQUE_PTR  
new_c_deque( int deq_size , CLIB_COMPARE fn_c, CLIB_DESTROY fn_d, CLIB_SIZE elem_size) {

    CLIB_DEQUE_PTR pDeq = (CLIB_DEQUE_PTR)clib_malloc(sizeof(CLIB_DEQUE));
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NULL;

    pDeq->no_max_elements  = deq_size < 8 ? 8 : deq_size;
    pDeq->size_of_element = elem_size;

    pDeq->elements = (CLIB_TYPE)clib_malloc(pDeq->no_max_elements * pDeq->size_of_element);
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NULL;

    pDeq->compare_fn      = fn_c;
    pDeq->destruct_fn     = fn_d;
    pDeq->head            = (int)deq_size / 2;
    pDeq->tail            = pDeq->head + 1;
    pDeq->no_of_elements  = 0;
    

    return pDeq;
}
CLIB_ERROR 
push_back_c_deque(CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( pDeq->tail == pDeq->no_max_elements )
        pDeq = grow_deque(pDeq);

    insert_c_deque(pDeq, pDeq->tail, elem);
    pDeq->tail++;
    return CLIB_ERROR_SUCCESS;
}
CLIB_ERROR 
push_front_c_deque(CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;	
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

CLIB_ERROR     
front_c_deque (CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy(elem, 
                CLIB_DEQUE_INDEX(pDeq->head + 1), 
                pDeq->size_of_element);

    return CLIB_ERROR_SUCCESS;

}
CLIB_ERROR 
back_c_deque (CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    clib_memcpy(elem, 
                CLIB_DEQUE_INDEX(pDeq->tail - 1), 
                pDeq->size_of_element);

    return CLIB_ERROR_SUCCESS;
}
CLIB_ERROR     
pop_back_c_deque (CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    back_c_deque( pDeq, elem);
    pDeq->tail--;
    pDeq->no_of_elements--;

    return CLIB_ERROR_SUCCESS;

}
CLIB_ERROR     
pop_front_c_deque(CLIB_DEQUE_PTR pDeq, CLIB_TYPE elem) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    front_c_deque ( pDeq, elem );
    pDeq->head++;
    pDeq->no_of_elements--;
    return CLIB_ERROR_SUCCESS;
}
CLIB_BOOL      
empty_c_deque (CLIB_DEQUE_PTR pDeq) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_TRUE;

    return pDeq->no_of_elements == 0 ? CLIB_TRUE : CLIB_FALSE;
}
int 
size_c_deque( CLIB_DEQUE_PTR pDeq ) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_TRUE;

    return pDeq->no_of_elements - 1;
}
extern CLIB_ERROR 
element_at_c_deque (CLIB_DEQUE_PTR pDeq, int index,CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_DEQUE_NOT_INITIALIZED;

    if ( index < 0 || index > pDeq->no_max_elements )
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    if ( index < pDeq->head || index > pDeq->tail)
        return CLIB_DEQUE_INDEX_OUT_OF_BOUND;

    clib_memcpy(elem, CLIB_DEQUE_INDEX(index), pDeq->size_of_element);
    return rc;
}

CLIB_ERROR
delete_c_deque ( CLIB_DEQUE_PTR pDeq ) {
	if ( pDeq == CLIB_DEQUE_NULL )
		return CLIB_ERROR_SUCCESS;

    if ( pDeq->destruct_fn ) {
        int i = 0;
        for ( i = pDeq->head + 1; i < pDeq->tail; i++ ){
            CLIB_TYPE elem;
            if ( element_at_c_deque( pDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                pDeq->destruct_fn(elem);
            }
        }
    }
    clib_free ( pDeq->elements);
    clib_free ( pDeq );

    return CLIB_ERROR_SUCCESS;
}
