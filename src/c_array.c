#include "c_lib.h"
#include <string.h>


#define CLIB_ARRAY_INDEX(x)  ((char *)(pArray)->elements + ((pArray)->size_of_element * (x)))

static clib_array_ptr 
array_check_and_grow ( clib_array_ptr pArray, int index) {
    clib_bool reallocation_required = clib_false;

    if ( pArray->no_max_elements <= index ){
        pArray->no_max_elements  = pArray->no_max_elements * 2;
        reallocation_required = clib_true;
    }

    if ( reallocation_required ) {
        pArray->elements = (clib_type)realloc(pArray->elements, 
                              (pArray->size_of_element * pArray->no_max_elements));
    }
    return pArray;
}
static clib_error 
insert_c_array ( clib_array_ptr pArray, int index, clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;

    clib_memcpy ( CLIB_ARRAY_INDEX(index), elem, pArray->size_of_element);

    pArray->no_of_elements++;
    return rc;
}


clib_array_ptr 
new_c_array(int array_size, clib_compare fn_c, clib_destroy fn_d , size_t elem_size) {

    clib_array_ptr pArray = (clib_array_ptr)clib_malloc(sizeof(clib_array));
	if ( pArray == clib_array_null )
		return clib_array_null;

    pArray->no_max_elements = array_size < 8 ? 8 : array_size;
    pArray->elements = (clib_type)clib_malloc(pArray->no_max_elements * elem_size);

	if ( pArray == clib_array_null )
		return clib_array_null;

	pArray->size_of_element = elem_size;
    pArray->compare_fn      = fn_c;
    pArray->destruct_fn     = fn_d;
    pArray->no_of_elements  = 0;


    return pArray;

}

clib_error 
push_back_c_array (clib_array_ptr pArray, clib_type elem) {
	clib_error rc       = CLIB_ERROR_SUCCESS;	
	if ( pArray == clib_array_null )
		return CLIB_ARRAY_NOT_INITIALIZED;

    array_check_and_grow ( pArray, pArray->no_of_elements + 1);

    rc = insert_c_array( pArray, pArray->no_of_elements, elem);
    return rc;
}
extern clib_error 
element_at_c_array (clib_array_ptr pArray, int index,clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;

	if ( pArray == clib_array_null )
		return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    clib_memcpy(elem, CLIB_ARRAY_INDEX(index), pArray->size_of_element);

    return rc;
}
int
size_c_array ( clib_array_ptr pArray ) {
    if ( pArray == clib_array_null )
        return 0;
    return pArray->no_of_elements - 1 ;
}
int
capacity_c_array ( clib_array_ptr pArray ) {
    if ( pArray == clib_array_null )
        return 0;
    return pArray->no_max_elements;
}
clib_bool  
empty_c_array ( clib_array_ptr pArray) {
    if ( pArray == clib_array_null )
        return 0;
    return pArray->no_of_elements == 0 ? clib_true : clib_false;
}
clib_error 
reserve_c_array ( clib_array_ptr pArray, int new_size) {
    if ( pArray == clib_array_null )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( new_size <= pArray->no_max_elements )
        return CLIB_ERROR_SUCCESS;
    
    array_check_and_grow ( pArray, new_size );
    return CLIB_ERROR_SUCCESS;

}
clib_error 
front_c_array ( clib_array_ptr pArray,clib_type elem) {
    return element_at_c_array ( pArray, 0, elem );
}
clib_error 
back_c_array ( clib_array_ptr pArray,clib_type elem) {
    return element_at_c_array ( pArray, pArray->no_of_elements - 1, elem );
}
clib_error 
pop_back_c_array( clib_array_ptr pArray, clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    rc = element_at_c_array ( pArray, pArray->no_of_elements - 1, elem );
    pArray->no_of_elements--;
    return rc;
}
clib_error 
insert_at_c_array ( clib_array_ptr pArray, int index, clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;

	if ( pArray == clib_array_null )
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

clib_error 
delete_c_array( clib_array_ptr pArray) {
    clib_error rc = CLIB_ERROR_SUCCESS;

	if ( pArray == clib_array_null )
		return rc;

    if ( pArray->destruct_fn ) {
        int i = 0;
        for ( i = 0; i < pArray->no_of_elements; i++) {
                clib_type elem;
                if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, i , &elem ) )
                    pArray->destruct_fn(elem);
        }
    }

    clib_free ( pArray->elements);
    clib_free ( pArray );
    return rc;

}
