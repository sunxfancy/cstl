#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

typedef struct __c_array {
    int  no_max_elements;
    int no_of_elements;
    clib_type pElements;
    clib_compare    compare_fn;
    clib_destroy    destruct_fn;

}c_array;

typedef c_array         clib_array;
typedef c_array*        clib_array_ptr;
#define clib_array_null (clib_array_ptr)0 

extern clib_array_ptr new_c_array ( int init_size, clib_compare fn_c, clib_destroy fn_d);
extern clib_error     push_back_c_array ( clib_array_ptr pArray, clib_type e, clib_size e_size);
extern clib_error     element_at_c_array( clib_array_ptr pArray, int pos, clib_type e);
extern clib_error     insert_at_c_array ( clib_array_ptr pArray, int index, clib_type elem, clib_size e_size);
extern int            size_c_array( clib_array_ptr pArray);
extern int            capacity_c_array( clib_array_ptr pArray );
extern clib_bool      empty_c_array( clib_array_ptr pArray);
extern clib_error     reserve_c_array( clib_array_ptr pArray, int pos);
extern clib_error     front_c_array( clib_array_ptr pArray,clib_type e);
extern clib_error     back_c_array( clib_array_ptr pArray,clib_type e);
extern clib_error     remove_from_c_array ( clib_array_ptr, int pos);
extern clib_error     delete_c_array( clib_array_ptr pArray);

#endif