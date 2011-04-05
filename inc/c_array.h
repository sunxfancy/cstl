#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

typedef struct __c_array {
    clib_type     elements;
    int           no_of_elements;
    int           no_max_elements;
	clib_size     size_of_element;
    clib_compare  compare_fn;
    clib_destroy  destruct_fn;

}c_array;

typedef c_array         clib_array;
typedef c_array*        clib_array_ptr;
#define clib_array_null (clib_array_ptr)0 


extern clib_array_ptr new_c_array ( int, clib_compare, clib_destroy,size_t);
extern clib_error push_back_c_array ( clib_array_ptr, clib_type);
extern clib_error element_at_c_array ( clib_array_ptr,int,clib_type);
extern clib_error insert_at_c_array ( clib_array_ptr, int, clib_type);
extern int  size_c_array ( clib_array_ptr);
extern int  capacity_c_array ( clib_array_ptr pArray );
extern clib_bool  empty_c_array ( clib_array_ptr);
extern clib_error reserve_c_array ( clib_array_ptr, int);
extern clib_error front_c_array ( clib_array_ptr,clib_type);
extern clib_error back_c_array ( clib_array_ptr,clib_type);
extern clib_error pop_back_c_array( clib_array_ptr, clib_type);
extern clib_error delete_c_array( clib_array_ptr);

#endif