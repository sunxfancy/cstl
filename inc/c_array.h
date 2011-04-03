#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

typedef struct __c_array {
    CLIB_TYPE    elements;
    int    no_of_elements;
    int    no_max_elements;
	size_t size_of_element;
    CLIB_COMPARE compare_fn;
    CLIB_DESTROY destruct_fn;

    CLIB_CONTEXT_PTR pContext;
}c_array;

typedef c_array         CLIB_ARRAY;
typedef c_array*        CLIB_ARRAY_PTR;
#define CLIB_ARRAY_NULL (CLIB_ARRAY_PTR)0 


extern CLIB_ARRAY_PTR new_c_array ( int, CLIB_COMPARE, CLIB_DESTROY,size_t);
extern CLIB_ERROR push_back_c_array ( CLIB_ARRAY_PTR, CLIB_TYPE);
extern CLIB_ERROR element_at_c_array ( CLIB_ARRAY_PTR,int,CLIB_TYPE);
extern CLIB_ERROR insert_at_c_array ( CLIB_ARRAY_PTR, int, CLIB_TYPE);
extern int  size_c_array ( CLIB_ARRAY_PTR);
extern int  capacity_c_array ( CLIB_ARRAY_PTR pArray );
extern CLIB_BOOL  empty_c_array ( CLIB_ARRAY_PTR);
extern CLIB_ERROR reserve_c_array ( CLIB_ARRAY_PTR, int);
extern CLIB_ERROR front_c_array ( CLIB_ARRAY_PTR,CLIB_TYPE);
extern CLIB_ERROR back_c_array ( CLIB_ARRAY_PTR,CLIB_TYPE);
extern CLIB_ERROR pop_back_c_array( CLIB_ARRAY_PTR, CLIB_TYPE);
extern CLIB_ERROR delete_c_array( CLIB_ARRAY_PTR);

#endif