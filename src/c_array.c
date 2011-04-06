#include "c_lib.h"
#include <string.h>
#include <stdio.h>


#define CLIB_ARRAY_INDEX(x)  ((char *)(pArray)->pElements + (sizeof(clib_element) * (x)))

static clib_array_ptr 
array_check_and_grow ( clib_array_ptr pArray) {
    if ( pArray->no_of_elements >= pArray->no_max_elements ) {

        pArray->no_max_elements  = 2 * pArray->no_max_elements;
        pArray->pElements        = (clib_element_ptr) realloc ( pArray->pElements, 
                                                                (pArray->no_max_elements * sizeof(clib_element)));
    }
    return pArray;
}
static clib_error 
insert_c_array ( clib_array_ptr pArray, int index, clib_type elem,clib_size e_size) {

    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_element_ptr tmp;
    size_t array_element_size = sizeof(clib_element);
    /* Create element of type clib_element 
     * c_array has all the elements stored of type clib_element 
     */
    tmp        = (clib_element_ptr)clib_malloc(array_element_size);
    tmp->size  = e_size;
    tmp->elem  = ( clib_type) clib_malloc ( e_size );
    /* Make a copy of the element passed to the c_array */
    clib_memcpy ( tmp->elem, elem, e_size);
    /* Copy the element into the storage area of the c_array 
     * position is calculated based on the index passed to the
     * function 
     */       
    clib_memcpy (((char*)pArray->pElements + (index * array_element_size)), 
            tmp, 
            array_element_size);
    pArray->no_of_elements++;
    clib_free ( tmp );


    return rc;
}

clib_array_ptr 
new_c_array(int array_size, clib_compare fn_c, clib_destroy fn_d) {

    size_t array_element_size = sizeof(clib_element);

    clib_array_ptr pArray = (clib_array_ptr)clib_malloc(sizeof(clib_array));
    if ( pArray == clib_array_null )
        return clib_array_null;

    pArray->no_max_elements = array_size < 8 ? 8 : array_size;
    /* allocate the internal storage block */
    pArray->pElements = (clib_type)
        clib_malloc(pArray->no_max_elements * array_element_size);

    if ( pArray == clib_array_null )
        return clib_array_null;

    pArray->compare_fn      = fn_c;
    pArray->destruct_fn     = fn_d;
    pArray->no_of_elements  = 0;

    return pArray;

}

clib_error 
push_back_c_array (clib_array_ptr pArray, clib_type e, clib_size e_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;	
    if ( pArray == clib_array_null )
        return CLIB_ARRAY_NOT_INITIALIZED;

    array_check_and_grow ( pArray);

    rc = insert_c_array( pArray, pArray->no_of_elements, e, e_size);

    return rc;
}
clib_error 
element_at_c_array (clib_array_ptr pArray, int index,clib_type elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_element temp;

    if ( pArray == clib_array_null )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    clib_memcpy ( &temp, 
            (char*)pArray->pElements + (index * sizeof(clib_element)),
            sizeof(clib_element));

    clib_memcpy(elem, temp.elem, temp.size);

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

	array_check_and_grow ( pArray);
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
insert_at_c_array ( clib_array_ptr pArray, int index, clib_type elem, clib_size e_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    clib_type destination;
    clib_type source;
    size_t size;

    if ( pArray == clib_array_null )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    array_check_and_grow ( pArray);

    destination = (char*)pArray->pElements + ((index + 1 )* sizeof(clib_element));
    source      = (char*)pArray->pElements + (index * sizeof(clib_element));
    size        = (pArray->no_of_elements - index) * sizeof(clib_element);

    memmove(destination, source, size);
    insert_c_array ( pArray, index, elem , e_size);

    return rc;
}
clib_error     
remove_from_c_array ( clib_array_ptr pArray, int pos) {
    clib_error   rc = CLIB_ERROR_SUCCESS;
    clib_element temp;
    clib_type    destination;
    clib_type    source;
    size_t size;

    if ( pArray == clib_array_null )
        return rc;

    if ( pos < 0 || pos > pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;


    if ( pArray->destruct_fn ) {
        clib_type elem;
        if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, pos , &elem ) ) {
            pArray->destruct_fn(elem);
        }
    }
    clib_memcpy ( &temp, 
                  (char*)pArray->pElements + ( pos * sizeof(clib_element)),
                   sizeof(clib_element));
    clib_free ( temp.elem);    

    destination = (char*)pArray->pElements + (pos * sizeof(clib_element));
    source      = (char*)pArray->pElements + ((pos + 1 ) * sizeof(clib_element));
    size        = (pArray->no_of_elements - pos) * sizeof(clib_element);

    memmove(destination, source, size);
    pArray->no_of_elements--;

    return rc;
}
clib_error 
delete_c_array( clib_array_ptr pArray) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    int i = 0;

    if ( pArray == clib_array_null )
        return rc;

    if ( pArray->destruct_fn ) {
        for ( i = 0; i < pArray->no_of_elements; i++) {
            clib_type elem;
            if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, i , &elem ) )
                pArray->destruct_fn(elem);
        }
    }
    for ( i = 0; i < pArray->no_of_elements; i++) {
        clib_element temp;
        clib_memcpy ( &temp, 
                      (char*)pArray->pElements + (i * sizeof(clib_element)),
                      sizeof(clib_element));
        clib_free ( temp.elem);
    }

    clib_free ( pArray->pElements);
    clib_free ( pArray );
    return rc;

}
