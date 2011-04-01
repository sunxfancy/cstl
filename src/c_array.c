#include "c_datastructure.h"
#include <string.h>


#define CLIB_ARRAY_INDEX(x)  ((char *)(pArray)->elements + ((pArray)->size_of_element * (x)))

static CLIB_ARRAY_PTR 
array_check_and_grow ( CLIB_ARRAY_PTR pArray, int index) {
    CLIB_BOOL reallocation_required = CLIB_FALSE;

    if ( pArray->no_max_elements <= index ){
        pArray->no_max_elements  = pArray->no_max_elements * 2;
        reallocation_required = CLIB_TRUE;
    }

    if ( reallocation_required ) {
        pArray->elements = (CLIB_TYPE)realloc(pArray->elements, 
                              (pArray->size_of_element * pArray->no_max_elements));
    }
    return pArray;
}
static CLIB_ERROR 
insert_c_array ( CLIB_ARRAY_PTR pArray, int index, CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

    clib_memcpy ( CLIB_ARRAY_INDEX(index), elem, pArray->size_of_element);
    pArray->no_of_elements++;
    return rc;
}


CLIB_ARRAY_PTR 
new_c_array(int array_size, CLIB_COMPARE fn_c, CLIB_DESTROY fn_d , size_t elem_size) {

    CLIB_ARRAY_PTR pArray = (CLIB_ARRAY_PTR)clib_malloc(sizeof(CLIB_ARRAY));
	if ( pArray == CLIB_ARRAY_NULL )
		return CLIB_ARRAY_NULL;

    pArray->no_max_elements = array_size < 8 ? 8 : array_size;
    pArray->elements = (CLIB_TYPE)clib_malloc(pArray->no_max_elements * elem_size);

	if ( pArray == CLIB_ARRAY_NULL )
		return CLIB_ARRAY_NULL;

	pArray->size_of_element = elem_size;
    pArray->compare_fn      = fn_c;
    pArray->destruct_fn     = fn_d;
    pArray->no_of_elements  = 0;
   
    return pArray;

}

CLIB_ERROR 
push_back_c_array (CLIB_ARRAY_PTR pArray, CLIB_TYPE elem) {
	CLIB_ERROR rc       = CLIB_ERROR_SUCCESS;	
	if ( pArray == CLIB_ARRAY_NULL )
		return CLIB_ARRAY_NOT_INITIALIZED;

    array_check_and_grow ( pArray, pArray->no_of_elements + 1);

    rc = insert_c_array( pArray, pArray->no_of_elements, elem);
    return rc;
}
extern CLIB_ERROR 
element_at_c_array (CLIB_ARRAY_PTR pArray, int index,CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

	if ( pArray == CLIB_ARRAY_NULL )
		return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    clib_memcpy(elem, CLIB_ARRAY_INDEX(index), pArray->size_of_element);
    return rc;
}
int
size_c_array ( CLIB_ARRAY_PTR pArray ) {
    if ( pArray == CLIB_ARRAY_NULL )
        return 0;
    return pArray->no_of_elements - 1 ;
}
int
capacity_c_array ( CLIB_ARRAY_PTR pArray ) {
    if ( pArray == CLIB_ARRAY_NULL )
        return 0;
    return pArray->no_max_elements;
}
CLIB_BOOL  
empty_c_array ( CLIB_ARRAY_PTR pArray) {
    if ( pArray == CLIB_ARRAY_NULL )
        return 0;
    return pArray->no_of_elements == 0 ? CLIB_TRUE : CLIB_FALSE;
}
CLIB_ERROR 
reserve_c_array ( CLIB_ARRAY_PTR pArray, int new_size) {
    if ( pArray == CLIB_ARRAY_NULL )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( new_size <= pArray->no_max_elements )
        return CLIB_ERROR_SUCCESS;
    
    array_check_and_grow ( pArray, new_size );
    return CLIB_ERROR_SUCCESS;

}
CLIB_ERROR 
front_c_array ( CLIB_ARRAY_PTR pArray,CLIB_TYPE elem) {
    return element_at_c_array ( pArray, 0, elem );
}
CLIB_ERROR 
back_c_array ( CLIB_ARRAY_PTR pArray,CLIB_TYPE elem) {
    return element_at_c_array ( pArray, pArray->no_of_elements - 1, elem );
}
CLIB_ERROR 
pop_back_c_array( CLIB_ARRAY_PTR pArray, CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;
    rc = element_at_c_array ( pArray, pArray->no_of_elements - 1, elem );
    pArray->no_of_elements--;
    return rc;
}
CLIB_ERROR 
insert_at_c_array ( CLIB_ARRAY_PTR pArray, int index, CLIB_TYPE elem) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

	if ( pArray == CLIB_ARRAY_NULL )
		return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    array_check_and_grow ( pArray, pArray->no_of_elements + 1);

    memmove(CLIB_ARRAY_INDEX(index + 1), 
            CLIB_ARRAY_INDEX(index), 
            (pArray->no_of_elements - index) * pArray->size_of_element);

    insert_c_array ( pArray, index, elem );

    return rc;
}

CLIB_ERROR 
delete_c_array( CLIB_ARRAY_PTR pArray) {
    CLIB_ERROR rc = CLIB_ERROR_SUCCESS;

	if ( pArray == CLIB_ARRAY_NULL )
		return rc;

    if ( pArray->destruct_fn ) {
        int i = 0;
        for ( i = 0; i < pArray->no_of_elements; i++) {
                CLIB_TYPE elem;
                if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, i , &elem ) )
                    pArray->destruct_fn(elem);
        }
    }

    clib_free ( pArray->elements);
    clib_free ( pArray );
    return rc;

}
